#pragma once

namespace IM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

#include "MSSQLRepository.h"
#include "Item.h"
#include "AddItemForm.h"


	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::DataGridView^ grdProducts;
	private: System::Windows::Forms::Button^ btnAddNewItemForm;


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->grdProducts = (gcnew System::Windows::Forms::DataGridView());
			this->btnAddNewItemForm = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdProducts))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(342, 57);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(165, 136);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// grdProducts
			// 
			this->grdProducts->AllowUserToAddRows = false;
			this->grdProducts->AllowUserToDeleteRows = false;
			this->grdProducts->AllowUserToOrderColumns = true;
			this->grdProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->grdProducts->Location = System::Drawing::Point(12, 244);
			this->grdProducts->Name = L"grdProducts";
			this->grdProducts->ReadOnly = true;
			this->grdProducts->RowHeadersWidth = 62;
			this->grdProducts->RowTemplate->Height = 28;
			this->grdProducts->Size = System::Drawing::Size(1320, 398);
			this->grdProducts->TabIndex = 1;
			// 
			// btnAddNewItemForm
			// 
			this->btnAddNewItemForm->Location = System::Drawing::Point(1149, 191);
			this->btnAddNewItemForm->Name = L"btnAddNewItemForm";
			this->btnAddNewItemForm->Size = System::Drawing::Size(183, 47);
			this->btnAddNewItemForm->TabIndex = 2;
			this->btnAddNewItemForm->Text = L"Yeni Ürün Giriþi";
			this->btnAddNewItemForm->UseVisualStyleBackColor = true;
			this->btnAddNewItemForm->Click += gcnew System::EventHandler(this, &MainForm::btnAddNewItemForm_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1344, 700);
			this->Controls->Add(this->btnAddNewItemForm);
			this->Controls->Add(this->grdProducts);
			this->Controls->Add(this->button1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdProducts))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		auto itemRepo = gcnew MSSQLRepository<Item^>();
		auto items = itemRepo->GetAll(); // Verileri al

		// DataGridView'a verileri ekleyin
		grdProducts->DataSource = items; // Verileri DataGridView'a ata
		//IRepository<Item>^ itemRepo = gcnew MSSQLRepository<Item>();

		//IRepository<Item>^ itemRepo = gcnew MSSQLRepository<Item>("Server=localhost;Database=InventoryDB;Integrated Security=True");

		//this->grdProducts->DataSource = 
	}

		   //void LoadDataToGrid<T>(DataGridView^ grid, IRepository<T>^ repo) where T : EntityBase, gcnew() {
		   //	List<T>^ itemList = repo->GetAll();
		   //	BindingSource^ bindingSource = gcnew BindingSource();

		   //	DataTable^ table = gcnew DataTable();

		   //	// Property'leri kullanarak kolon isimlerini dinamik oluþtur
		   //	for each (auto prop in T::typeid->GetProperties()) {
		   //		table->Columns->Add(gcnew DataColumn(prop->Name, prop->PropertyType));
		   //	}

		   //	// Verileri ekleyelim
		   //	for each (T item in itemList) {
		   //		DataRow^ row = table->NewRow();
		   //		for each (auto prop in item->GetType()->GetProperties()) {
		   //			row[prop->Name] = prop->GetValue(item);
		   //		}
		   //		table->Rows->Add(row);
		   //	}

		   //	bindingSource->DataSource = table;
		   //	grid->DataSource = bindingSource;
		   //}

	private: System::Void btnAddNewItemForm_Click(System::Object^ sender, System::EventArgs^ e) {

		auto addItemForm = gcnew AddItemForm();
		addItemForm->ShowDialog(); // Modal form olarak aç
	}
};
}
