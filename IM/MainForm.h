#pragma once

namespace IM {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

#include "MSSQLRepository.h"
#include "ItemViewModel.h"
#include "ItemForm.h"
#include "EntityActionType.h"


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
	private: System::Windows::Forms::Button^ btnRefresh;



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
			this->btnRefresh = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdProducts))->BeginInit();
			this->SuspendLayout();
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
			this->grdProducts->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->grdProducts->Size = System::Drawing::Size(1320, 398);
			this->grdProducts->TabIndex = 1;
			this->grdProducts->CellClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &MainForm::grdProducts_CellClick);
			// 
			// btnAddNewItemForm
			// 
			this->btnAddNewItemForm->Location = System::Drawing::Point(1149, 167);
			this->btnAddNewItemForm->Name = L"btnAddNewItemForm";
			this->btnAddNewItemForm->Size = System::Drawing::Size(183, 47);
			this->btnAddNewItemForm->TabIndex = 2;
			this->btnAddNewItemForm->Text = L"Add New Item Form";
			this->btnAddNewItemForm->UseVisualStyleBackColor = true;
			this->btnAddNewItemForm->Click += gcnew System::EventHandler(this, &MainForm::btnAddNewItemForm_Click);
			// 
			// btnRefresh
			// 
			this->btnRefresh->Location = System::Drawing::Point(12, 167);
			this->btnRefresh->Name = L"btnRefresh";
			this->btnRefresh->Size = System::Drawing::Size(127, 47);
			this->btnRefresh->TabIndex = 3;
			this->btnRefresh->Text = L"Refresh Data";
			this->btnRefresh->UseVisualStyleBackColor = true;
			this->btnRefresh->Click += gcnew System::EventHandler(this, &MainForm::btnRefresh_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1344, 747);
			this->Controls->Add(this->btnRefresh);
			this->Controls->Add(this->btnAddNewItemForm);
			this->Controls->Add(this->grdProducts);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->grdProducts))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		loadGridData();
		addAdditionalButtons();
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
				auto updateItemForm = gcnew ItemForm(EntityActionType::Update, itemId);
				updateItemForm->ShowDialog();
			}
		}
	}

	private: System::Void btnCellDelete_Click(System::Object^ sender, System::Windows::Forms::DataGridViewCellEventArgs^ e)
	{
		auto selectedRow = grdProducts->CurrentRow;
		if (selectedRow != nullptr)
		{
			auto itemIDCell = selectedRow->Cells["ItemID"];
			if (itemIDCell != nullptr)
			{
				auto itemIDValue = itemIDCell->Value;
				auto itemId = Int32::Parse(itemIDValue->ToString());

				auto itemRepo = gcnew MSSQLRepository<Item^>();
				itemRepo->Delete(itemId);
				loadGridData();
			}
		}
	}

	private: System::Void btnAddNewItemForm_Click(System::Object^ sender, System::EventArgs^ e)
	{
		auto addItemForm = gcnew ItemForm(EntityActionType::Insert, 0);
		addItemForm->ShowDialog();
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

	private: System::Void loadGridData()
	{
		auto itemRepo = gcnew MSSQLRepository<ItemViewModel^>();
		auto items = itemRepo->GetAllItems();

		grdProducts->DataSource = items;
	}

	private: System::Void addAdditionalButtons()
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
	};
}
