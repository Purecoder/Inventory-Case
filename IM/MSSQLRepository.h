#pragma once

#include "EntityBase.h"
#include "IRepository.h"
#include "KeyAttribute.h"
#include "SqlRepoHandler.h"

using namespace System;
using namespace System::Configuration;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Windows::Forms;
using namespace System::Reflection;
using namespace System::Threading::Tasks;

generic <typename T> where T : EntityBase, gcnew()
ref class MSSQLRepository : IRepository<T> {
private:
	String^ connectionString;

	SqlConnection^ OpenConnection() {
		try {
			SqlConnection^ conn = gcnew SqlConnection(connectionString);
			conn->Open();
			return conn;
		}
		catch (SqlException^ ex) {
			throw gcnew Exception("Error while connecting Database!", ex);
		}
	}

public:
	MSSQLRepository() {
		String^ connStr = ConfigurationManager::ConnectionStrings["Inventory"]->ConnectionString;

		if (connStr == nullptr)
		{
			throw gcnew InvalidOperationException("Cannot found 'Inventory' db object for ConnectionString!");
		}
		connectionString = connStr;
	}

	String^ LastUpdated = "LastUpdated";

	delegate void OperationDelegate(T entity);


	void Add(T entity) override {
		SqlConnection^ conn = OpenConnection();
		SqlTransaction^ transaction = nullptr;
		try {
			transaction = conn->BeginTransaction();
			String^ query = "INSERT INTO " + GetTableName() + " (";

			List<String^>^ columns = gcnew List<String^>();
			List<String^>^ parameters = gcnew List<String^>();

			for each (auto prop in entity->GetType()->GetProperties()) {
				if (prop->Name != GetIdColumnName() && prop->Name != LastUpdated) {
					columns->Add(prop->Name);
					parameters->Add("@" + prop->Name);
				}
			}

			query += String::Join(", ", columns) + ") VALUES (" + String::Join(", ", parameters) + ")";

			SqlCommand^ cmd = gcnew SqlCommand(query, conn, transaction);
			for each (auto prop in entity->GetType()->GetProperties()) {
				if (prop->Name != GetIdColumnName() && prop->Name != LastUpdated)
					cmd->Parameters->AddWithValue("@" + prop->Name, prop->GetValue(entity));
			}

			cmd->ExecuteNonQuery();
			transaction->Commit();
		}
		catch (Exception^ ex) {
			if (transaction != nullptr) {
				transaction->Rollback();
			}
			throw gcnew Exception("Error while insert data. Error: " + ex->Message);
		}
		finally {
			conn->Close();
		}
	}

	void AddAsync(T entity) override {

		SqlOperation<T>^ op = gcnew SqlOperation<T>(entity,
			gcnew Action<T>(this, &MSSQLRepository<T>::Add)
		);
		Action^ del = gcnew Action(op, &SqlOperation<T>::Execute);
		SqlRepoHandler::ExecuteAsyncHelper(del);
	}

	void Update(T entity) override {
		SqlConnection^ conn = OpenConnection();
		SqlTransaction^ transaction = nullptr;
		try {
			transaction = conn->BeginTransaction(IsolationLevel::Serializable); // Or can be IsolationLevel::Snapshot
			String^ idColumn = GetIdColumnName();
			String^ query = "UPDATE " + GetTableName() + " SET ";

			List<String^>^ setClauses = gcnew List<String^>();
			for each (auto prop in entity->GetType()->GetProperties()) {
				if (prop->Name != idColumn)
					setClauses->Add(prop->Name + " = @" + prop->Name);

			}

			query += String::Join(", ", setClauses) + " WHERE " + idColumn + " = @" + idColumn;

			auto idKey = FindPrimaryKey<T>();

			SqlCommand^ cmd = gcnew SqlCommand(query, conn, transaction);
			for each (auto prop in entity->GetType()->GetProperties()) {

				if (prop->Name == idKey)
					cmd->Parameters->AddWithValue("@" + idColumn, prop->GetValue(entity));
				else
					if (prop->Name == LastUpdated)
						cmd->Parameters->AddWithValue("@" + prop->Name, DateTime::Now);
					else
						cmd->Parameters->AddWithValue("@" + prop->Name, prop->GetValue(entity));
			}

			cmd->ExecuteNonQuery();
			transaction->Commit();
		}
		catch (Exception^ ex) {
			if (transaction != nullptr) {
				transaction->Rollback();
			}
			throw gcnew Exception("Error while update data. Error:" + ex->Message);
		}
		finally {
			conn->Close();
		}
	}

	void Delete(int id) override {
		SqlConnection^ conn = OpenConnection();
		SqlTransaction^ transaction = nullptr;
		try {
			transaction = conn->BeginTransaction();

			String^ idColumn = GetIdColumnName();
			String^ query = "DELETE FROM " + GetTableName() + " WHERE " + idColumn + " = @id";

			SqlCommand^ cmd = gcnew SqlCommand(query, conn, transaction);
			cmd->Parameters->AddWithValue("@id", id);
			cmd->ExecuteNonQuery();
			transaction->Commit();
		}
		catch (Exception^ ex) {
			if (transaction != nullptr) {
				transaction->Rollback();
			}
			throw gcnew Exception("Error while delete. Error:" + ex->Message);

		}
		finally {
			conn->Close();
		}
	}


	List<T>^ GetAllItemsHelper() {
		SqlOperation<T>^ op = gcnew SqlOperation<T>(gcnew Func<List<T>^>(this, &MSSQLRepository<T>::GetAllItems));
		op->Execute();
		return op->GetResult();
	}

	Task<List<T>^>^ GetAllItemsAsync() override {

		return Task<List<T>^>::Run(gcnew Func<List<T>^>(this, &MSSQLRepository<T>::GetAllItemsHelper));

		/*	SqlOperation<T>^ op = gcnew SqlOperation<T>(
				gcnew Func<List<T>^>(this, &MSSQLRepository<T>::GetAllItems));

			Action^ del = gcnew Action(op, &SqlOperation<T>::Execute);
			SqlRepoHandler::ExecuteAsyncHelper(del);
			return op->GetResult();*/
	}

	List<T>^ GetAllItems() override {

		List<T>^ list = gcnew List<T>();
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();
			String^ query = "SELECT item.ItemID,item.ItemName,cat.CategoryName,item.Quantity,item.UnitPrice FROM Items as item JOIN Categories as cat on item.CategoryId = cat.CategoryId";
			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
			SqlDataReader^ reader = cmd->ExecuteReader();

			while (reader->Read()) {
				T obj = gcnew T();

				auto itemPropList = obj->GetType()->GetProperties();
				for each (auto prop in itemPropList) {

					String^ columnName = prop->Name;
					prop->SetValue(obj, reader[columnName]);
				}
				list->Add(obj);
			}
		}
		catch (Exception^ ex) {
			throw gcnew Exception("Error while retrieve data. Error:" + ex->Message);
		}
		finally {
			conn->Close();
		}
		return list;
	}

	List<T>^ GetAllItemsByFilterParams(String^ itemName, Nullable<int> categoryId, Nullable<int> minStock, Nullable<int> maxStock) override {
		List<T>^ list = gcnew List<T>();
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();

			String^ query = "SELECT item.ItemID,item.ItemName,cat.CategoryName,item.Quantity,item.UnitPrice FROM Items as item JOIN Categories as cat on item.CategoryId = cat.CategoryId WHERE 1=1";
			if (!String::IsNullOrEmpty(itemName)) query += " AND ItemName LIKE @ItemName";
			if (minStock.HasValue) query += " AND Quantity > @MinStock";
			if (maxStock.HasValue) query += " AND Quantity < @MaxStock";
			if (categoryId.HasValue && categoryId.Value > 0) query += " AND cat.CategoryId = @CategoryID";

			SqlCommand^ cmd = gcnew SqlCommand(query, conn);

			if (!String::IsNullOrEmpty(itemName)) cmd->Parameters->AddWithValue("@ItemName", "%" + itemName + "%");
			if (minStock.HasValue) cmd->Parameters->AddWithValue("@MinStock", minStock.Value);
			if (maxStock.HasValue) cmd->Parameters->AddWithValue("@MaxStock", maxStock.Value);
			if (categoryId.HasValue && categoryId.Value > 0) cmd->Parameters->AddWithValue("@CategoryID", categoryId.Value);

			SqlDataReader^ reader = cmd->ExecuteReader();

			while (reader->Read()) {
				T obj = gcnew T();

				auto itemPropList = obj->GetType()->GetProperties();
				for each (auto prop in itemPropList) {

					String^ columnName = prop->Name;
					prop->SetValue(obj, reader[columnName]);
				}
				list->Add(obj);
			}
		}
		catch (Exception^ ex) {
			throw gcnew Exception("Error while retrieve data. Error:" + ex->Message);
		}
		finally {
			conn->Close();
		}
		return list;
	}

	List<T>^ GetAll() override {
		List<T>^ list = gcnew List<T>();
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();
			String^ query = "SELECT * FROM " + GetTableName();
			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
			SqlDataReader^ reader = cmd->ExecuteReader();

			while (reader->Read()) {
				T obj = gcnew T();

				auto itemPropList = obj->GetType()->GetProperties();
				for each (auto prop in itemPropList) {
					prop->SetValue(obj, reader[prop->Name]);
				}
				list->Add(obj);
			}
		}
		catch (Exception^ ex) {
			throw gcnew Exception("Error while retrieve data. Error:" + ex->Message);
		}
		finally {
			conn->Close();
		}
		return list;
	}

	T GetById(int id) override {
		T obj = gcnew T();
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();
			String^ query = "SELECT * FROM " + GetTableName() + " WHERE " + idColumn + " = @id";

			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
			cmd->Parameters->AddWithValue("@id", id);
			SqlDataReader^ reader = cmd->ExecuteReader();

			if (reader->Read()) {
				for each (auto prop in obj->GetType()->GetProperties()) {
					String^ columnName = prop->Name;
					if (columnName != "ID")
					{
						prop->SetValue(obj, reader[columnName]);
					}
				}
			}
		}
		catch (Exception^ ex) {
			throw gcnew Exception("Error while retrieve data. Error:" + ex->Message);
		}
		finally {
			conn->Close();
		}
		return obj;
	}

#pragma region Procedures

	List<T>^ GetLowStockItems() {
		List<T>^ itemList = gcnew List<T>();
		SqlConnection^ conn = OpenConnection();

		try {
			int threshold = GetStockThreshold();

			SqlCommand^ command = gcnew SqlCommand("GetLowStockItems", conn);
			command->CommandType = CommandType::StoredProcedure;
			command->Parameters->Add(gcnew SqlParameter("@Threshold", threshold));

			SqlDataAdapter^ adapter = gcnew SqlDataAdapter(command);
			DataTable^ dataTable = gcnew DataTable();
			adapter->Fill(dataTable);

			itemList = ConvertDataTableToList(dataTable);
		}
		catch (Exception^ ex) {
			throw gcnew Exception("Error while retrieve low stock data. Error:" + ex->Message);
		}
		finally {
			conn->Close();
		}

		return itemList;
	}

#pragma endregion

#pragma region Helper Methods

	int GetStockThreshold() {
		String^ thresHoldSetting = ConfigurationManager::AppSettings["StockThreshold"];
		return (thresHoldSetting != nullptr) ? Int32::Parse(thresHoldSetting) : 10;
	}

	String^ GetIdColumnName() {
		return T::typeid->Name + "ID";
	}

	String^ GetTableName() {
		String^ typeName = T::typeid->Name;
		if (typeName->EndsWith("y")) {
			return typeName->Substring(0, typeName->Length - 1) + "ies";
		}
		return typeName + "s";
	}

	List<T>^ ConvertDataTableToList(DataTable^ dataTable) {
		List<T>^ itemList = gcnew List<T>();

		for (int i = 0; i < dataTable->Rows->Count; i++) {
			T item = gcnew T();

			for each (DataColumn ^ column in dataTable->Columns) {
				String^ propertyName = column->ColumnName;
				PropertyInfo^ property = T::typeid->GetProperty(propertyName);

				if (property != nullptr) {
					property->SetValue(item, Convert::ChangeType(dataTable->Rows[i][propertyName], property->PropertyType), nullptr);
				}
			}

			itemList->Add(item);
		}

		return itemList;
	}

	generic <typename T>
	String^ FindPrimaryKey() {
		Type^ type = T::typeid;
		for each (PropertyInfo ^ prop in type->GetProperties()) {
			if (Attribute::IsDefined(prop, KeyAttribute::typeid)) {
				return prop->Name;
			}
		}
		return nullptr;
	}

#pragma endregion

};
