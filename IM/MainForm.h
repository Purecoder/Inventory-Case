#pragma once

namespace IM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

#include "ItemForm.h"
#include "MSSQLRepository.h"
#include "ItemViewModel.h"
#include "EntityActionType.h"
#include "IOHelper.h"

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

	private: System::Windows::Forms::DataGridView^ grdProducts;
	private: System::Windows::Forms::Button^ btnAddNewItemForm;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtFilterStockGt;

	private: System::Windows::Forms::Label^ label1;


	private: System::Windows::Forms::Label^ lblItemName;
	private: System::Windows::Forms::TextBox^ txtFilterItemName;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtFilterStockLt;

	private: System::Windows::Forms::ComboBox^ cmbFilterCategory;
	private: System::Windows::Forms::Button^ btnFilterSearch;




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
			this->grdProducts = (gcnew System::Windows::Forms::DataGridView());
			this->btnAddNewItemForm = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btnFilterSearch = (gcnew System::Windows::Forms::Button());
			this->cmbFilterCategory = (gcnew System::Windows::Forms::ComboBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtFilterStockLt = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtFilterStockGt = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->lblItemName = (gcnew System::Windows::Forms::Label());
			this->txtFilterItemName = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdProducts))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// grdProducts
			// 
			this->grdProducts->AllowUserToAddRows = false;
			this->grdProducts->AllowUserToDeleteRows = false;
			this->grdProducts->AllowUserToOrderColumns = true;
			this->grdProducts->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->grdProducts->Location = System::Drawing::Point(12, 457);
			this->grdProducts->Name = L"grdProducts";
			this->grdProducts->ReadOnly = true;
			this->grdProducts->RowHeadersWidth = 62;
			this->grdProducts->RowTemplate->Height = 28;
			this->grdProducts->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->grdProducts->Size = System::Drawing::Size(1153, 398);
			this->grdProducts->TabIndex = 1;
			this->grdProducts->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::grdProducts_CellClick);
			// 
			// btnAddNewItemForm
			// 
			this->btnAddNewItemForm->BackColor = System::Drawing::Color::LimeGreen;
			this->btnAddNewItemForm->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->btnAddNewItemForm->ForeColor = System::Drawing::Color::Black;
			this->btnAddNewItemForm->Location = System::Drawing::Point(12, 388);
			this->btnAddNewItemForm->Name = L"btnAddNewItemForm";
			this->btnAddNewItemForm->Size = System::Drawing::Size(170, 46);
			this->btnAddNewItemForm->TabIndex = 99;
			this->btnAddNewItemForm->Text = L"Add New Item";
			this->btnAddNewItemForm->UseVisualStyleBackColor = false;
			this->btnAddNewItemForm->Click += gcnew System::EventHandler(this, &MainForm::btnAddNewItemForm_Click);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LemonChiffon;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->button1->Location = System::Drawing::Point(978, 387);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(183, 47);
			this->button1->TabIndex = 25;
			this->button1->Text = L"Low Stock Report";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->btnFilterSearch);
			this->groupBox1->Controls->Add(this->cmbFilterCategory);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->txtFilterStockLt);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->txtFilterStockGt);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->lblItemName);
			this->groupBox1->Controls->Add(this->txtFilterItemName);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(376, 320);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Filter Area";
			// 
			// btnFilterSearch
			// 
			this->btnFilterSearch->Location = System::Drawing::Point(147, 217);
			this->btnFilterSearch->Name = L"btnFilterSearch";
			this->btnFilterSearch->Size = System::Drawing::Size(137, 47);
			this->btnFilterSearch->TabIndex = 4;
			this->btnFilterSearch->Text = L"Search Filter";
			this->btnFilterSearch->UseVisualStyleBackColor = true;
			this->btnFilterSearch->Click += gcnew System::EventHandler(this, &MainForm::btnFilterSearch_Click);
			// 
			// cmbFilterCategory
			// 
			this->cmbFilterCategory->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->cmbFilterCategory->FormattingEnabled = true;
			this->cmbFilterCategory->Location = System::Drawing::Point(147, 85);
			this->cmbFilterCategory->Name = L"cmbFilterCategory";
			this->cmbFilterCategory->Size = System::Drawing::Size(137, 28);
			this->cmbFilterCategory->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(20, 182);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(85, 20);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Stock LT <";
			// 
			// txtFilterStockLt
			// 
			this->txtFilterStockLt->Location = System::Drawing::Point(147, 176);
			this->txtFilterStockLt->Name = L"txtFilterStockLt";
			this->txtFilterStockLt->Size = System::Drawing::Size(137, 26);
			this->txtFilterStockLt->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(20, 135);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(89, 20);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Stock GT >";
			// 
			// txtFilterStockGt
			// 
			this->txtFilterStockGt->Location = System::Drawing::Point(147, 129);
			this->txtFilterStockGt->Name = L"txtFilterStockGt";
			this->txtFilterStockGt->Size = System::Drawing::Size(137, 26);
			this->txtFilterStockGt->TabIndex = 2;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 88);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(73, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Category";
			// 
			// lblItemName
			// 
			this->lblItemName->AutoSize = true;
			this->lblItemName->Location = System::Drawing::Point(20, 43);
			this->lblItemName->Name = L"lblItemName";
			this->lblItemName->Size = System::Drawing::Size(87, 20);
			this->lblItemName->TabIndex = 1;
			this->lblItemName->Text = L"Item Name";
			// 
			// txtFilterItemName
			// 
			this->txtFilterItemName->Location = System::Drawing::Point(147, 37);
			this->txtFilterItemName->Name = L"txtFilterItemName";
			this->txtFilterItemName->Size = System::Drawing::Size(137, 26);
			this->txtFilterItemName->TabIndex = 0;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1173, 964);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->btnAddNewItemForm);
			this->Controls->Add(this->grdProducts);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(162)));
			this->Name = L"MainForm";
			this->Text = L"Inventory Management";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdProducts))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		loadCategoryData();
		loadGridData();
		addActionButtonsToGrid();
	}

	private: System::Void btnCellUpdate_Click(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		auto selectedRow = grdProducts->CurrentRow;
		if (selectedRow != nullptr)
		{
			auto itemIDCell = selectedRow->Cells["ItemID"];
			if (itemIDCell != nullptr)
			{
				auto itemIDValue = itemIDCell->Value;
				auto itemId = Int32::Parse(itemIDValue->ToString());

				auto itemForm = gcnew ItemForm(EntityActionType::Update, itemId);
				itemForm->OnItemFormClosed += gcnew ItemFormClosedEventHandler(this, &MainForm::loadGridData);
				itemForm->ShowDialog();
			}
		}
	}

	private: System::Void btnCellDelete_Click(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		auto confirmResult = MessageBox::Show("Are you sure you want to delete this record?", "Confirmation", MessageBoxButtons::YesNo, MessageBoxIcon::Question);

		if (confirmResult == System::Windows::Forms::DialogResult::Yes)
		{
			auto selectedRow = grdProducts->CurrentRow;
			if (selectedRow != nullptr)
			{
				auto itemIDCell = selectedRow->Cells["ItemID"];
				if (itemIDCell != nullptr)
				{
					auto itemIDValue = itemIDCell->Value;
					auto itemId = Int32::Parse(itemIDValue->ToString());

					// Show confirmation dialog

					auto itemRepo = gcnew MSSQLRepository<Item^>();
					itemRepo->Delete(itemId);
					loadGridData();
				}
			}
		}
	}

	private: System::Void btnAddNewItemForm_Click(System::Object^ sender, System::EventArgs^ e)
	{
		auto itemForm = gcnew ItemForm(EntityActionType::Insert, 0);
		itemForm->OnItemFormClosed += gcnew ItemFormClosedEventHandler(this, &MainForm::loadGridData);
		itemForm->ShowDialog();
	}

	private: System::Void grdProducts_CellClick(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e) {
		if (e->ColumnIndex >= 0 && e->RowIndex >= 0 && grdProducts->Columns[e->ColumnIndex])
		{
			auto buttonColumn = dynamic_cast<System::Windows::Forms::DataGridViewButtonColumn^>(grdProducts->Columns[e->ColumnIndex]);
			if (buttonColumn != nullptr)
			{
				if (buttonColumn->Name == "btnCellUpdate")
				{
					btnCellUpdate_Click(sender, e);
				}
				else if (buttonColumn->Name == "btnCellDelete")
				{
					btnCellDelete_Click(sender, e);
				}
			}
		}
	}

	public: void loadGridData()
	{
		auto itemRepo = gcnew MSSQLRepository<ItemViewModel^>();
		auto items = itemRepo->GetAllItems();

		grdProducts->DataSource = items;
	}

	private: System::Void loadGridDataByFilterParams()
	{
		auto itemRepo = gcnew MSSQLRepository<ItemViewModel^>();
		auto filterCategoryId = dynamic_cast<Category^>(cmbFilterCategory->SelectedItem)->CategoryID;

		auto minStock = txtFilterStockGt->Text == "" ? Nullable<int>() : Convert::ToInt32(txtFilterStockGt->Text);
		auto maxStock = txtFilterStockLt->Text == "" ? Nullable<int>() : Convert::ToInt32(txtFilterStockLt->Text);

		auto items = itemRepo->GetAllItemsByFilterParams(txtFilterItemName->Text, filterCategoryId, minStock, maxStock);
		grdProducts->DataSource = items;
	}


	private: System::Void addActionButtonsToGrid()
	{
		System::Windows::Forms::DataGridViewButtonColumn^ updateColumn = gcnew System::Windows::Forms::DataGridViewButtonColumn();
		updateColumn->HeaderText = "";
		updateColumn->Name = "btnCellUpdate";
		updateColumn->Text = "Update";
		updateColumn->UseColumnTextForButtonValue = true;
		grdProducts->Columns->Add(updateColumn);

		System::Windows::Forms::DataGridViewButtonColumn^ deleteColumn = gcnew System::Windows::Forms::DataGridViewButtonColumn();
		deleteColumn->HeaderText = "";
		deleteColumn->Name = "btnCellDelete";
		deleteColumn->Text = "Delete";
		deleteColumn->UseColumnTextForButtonValue = true;
		grdProducts->Columns->Add(deleteColumn);
	}

	private: System::Void btnRefresh_Click(System::Object^ sender, System::EventArgs^ e) {
		loadGridData();
	}

	private: System::Void loadCategoryData()
	{
		auto categoryRepo = gcnew MSSQLRepository<Category^>();
		auto categories = categoryRepo->GetAll();

		Category^ cat = gcnew Category();
		cat->CategoryID = 0;
		cat->CategoryName = "All";
		categories->Add(cat);

		categories->Sort();
		cmbFilterCategory->DataSource = categories;
	}

	private: System::Void btnFilterSearch_Click(System::Object^ sender, System::EventArgs^ e) {
		loadGridDataByFilterParams();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

		auto itemRepo = gcnew MSSQLRepository<ItemViewModel^>();
		auto items = itemRepo->GetLowStockItems();
		IOHelper::ExportToCSV(items, "LowStockData");
	}
	};
}
