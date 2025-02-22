#pragma once

#include "EntityBase.h"
#include "IRepository.h"
#include "KeyAttribute.h"

using namespace System;
using namespace System::Configuration;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Windows::Forms;
using namespace System::Reflection;



generic <typename T> where T : EntityBase, gcnew()
ref class MSSQLRepository : IRepository<T> {
private:
	String^ connectionString;

	SqlConnection^ OpenConnection() {
		SqlConnection^ conn = gcnew SqlConnection(connectionString);
		conn->Open();
		return conn;
	}

public:
	MSSQLRepository() {
		String^ connStr = ConfigurationManager::ConnectionStrings["Inventory"]->ConnectionString;

		if (connStr == nullptr)
		{
			throw gcnew InvalidOperationException("Connection string 'Inventory' database objesi bulunamadý!");
		}
		connectionString = connStr;
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

	String^ LastUpdated = "LastUpdated";

	void Add(T entity) override {
		SqlConnection^ conn = OpenConnection();
		try {
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

			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
			for each (auto prop in entity->GetType()->GetProperties()) {
				if (prop->Name != GetIdColumnName() && prop->Name != LastUpdated)
					cmd->Parameters->AddWithValue("@" + prop->Name, prop->GetValue(entity));
			}

			cmd->ExecuteNonQuery();
		}
		catch (Exception^ ex) {
			Console::WriteLine("Ekleme hatasý: " + ex->Message);
		}
		finally {
			conn->Close();
		}
	}

	void Update(T entity) override {
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();
			String^ query = "UPDATE " + GetTableName() + " SET ";

			List<String^>^ setClauses = gcnew List<String^>();
			for each (auto prop in entity->GetType()->GetProperties()) {
				if (prop->Name != idColumn)
					setClauses->Add(prop->Name + " = @" + prop->Name);

			}

			query += String::Join(", ", setClauses) + " WHERE " + idColumn + " = @" + idColumn;

			auto idKey = FindPrimaryKey<T>();

			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
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
		}
		catch (Exception^ ex) {
			Console::WriteLine("Güncelleme hatasý: " + ex->Message);
		}
		finally {
			conn->Close();
		}
	}

	void Delete(int id) override {
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();
			String^ query = "DELETE FROM " + GetTableName() + " WHERE " + idColumn + " = @id";

			SqlCommand^ cmd = gcnew SqlCommand(query, conn);
			cmd->Parameters->AddWithValue("@id", id);
			cmd->ExecuteNonQuery();
		}
		catch (Exception^ ex) {
			Console::WriteLine("Silme hatasý: " + ex->Message);
		}
		finally {
			conn->Close();
		}
	}

	List<T>^ GetAllItems() override {
		List<T>^ list = gcnew List<T>();
		SqlConnection^ conn = OpenConnection();
		try {
			String^ idColumn = GetIdColumnName();
			String^ query = "SELECT item.ItemId,item.ItemName,cat.CategoryName,item.Quantity,item.UnitPrice FROM Items as item JOIN Categories as cat on item.CategoryId = cat.CategoryId";
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
			Console::WriteLine("Veri çekme hatasý: " + ex->Message);
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
			Console::WriteLine("Veri çekme hatasý: " + ex->Message);
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
					//prop->SetValue(obj, reader[prop->Name]);
				}
			}
		}
		catch (Exception^ ex) {
			Console::WriteLine("Veri çekme hatasý: " + ex->Message);
		}
		finally {
			conn->Close();
		}
		return obj;
	}

	generic <typename T>
	String^ FindPrimaryKey() {
		Type^ type = T::typeid;
		for each (PropertyInfo ^ prop in type->GetProperties()) {
			if (Attribute::IsDefined(prop, KeyAttribute::typeid)) {
				return prop->Name;
			}
		}
		return nullptr; // ID alaný bulunamazsa
	}
};
