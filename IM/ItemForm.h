#pragma once


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "MSSQLRepository.h"
#include "Item.h"
#include "Category.h"
#include "Validator.h"
#include "EntityActionType.h"

/// <summary>
/// Summary for AddItemForm
/// </summary>
public ref class ItemForm : public System::Windows::Forms::Form
{
	int _updateItemId = 0;
	EntityActionType _actionType;
	Item^ _currentItem;
public:
	ItemForm(EntityActionType actionType, int itemId)
	{
		_updateItemId = itemId;
		_actionType = actionType;
		InitializeComponent();
		if (actionType == EntityActionType::Update)
		{
			btnUpdateItem->Location = System::Drawing::Point(btnAddItem->Location.X, btnAddItem->Location.Y);
			btnUpdateItem->Visible = true;
			btnAddItem->Visible = false;
		}
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~ItemForm()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip1;
private: System::Windows::Forms::TextBox^ txtItemName;
private: System::Windows::Forms::TextBox^ txtQuantity;
private: System::Windows::Forms::TextBox^ txtUnitPrice;




private: System::Windows::Forms::ComboBox^ cmbCategories;
private: System::Windows::Forms::Label^ lblItemName;
private: System::Windows::Forms::Label^ label1;
private: System::Windows::Forms::Label^ label2;
private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Button^ btnAddItem;
private: System::Windows::Forms::Button^ btnUpdateItem;



protected:

private: System::ComponentModel::IContainer^ components;

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
	void InitializeComponent(void)
	{
		this->txtItemName = (gcnew System::Windows::Forms::TextBox());
		this->txtQuantity = (gcnew System::Windows::Forms::TextBox());
		this->txtUnitPrice = (gcnew System::Windows::Forms::TextBox());
		this->cmbCategories = (gcnew System::Windows::Forms::ComboBox());
		this->lblItemName = (gcnew System::Windows::Forms::Label());
		this->label1 = (gcnew System::Windows::Forms::Label());
		this->label2 = (gcnew System::Windows::Forms::Label());
		this->label3 = (gcnew System::Windows::Forms::Label());
		this->btnAddItem = (gcnew System::Windows::Forms::Button());
		this->btnUpdateItem = (gcnew System::Windows::Forms::Button());
		this->SuspendLayout();
		// 
		// txtItemName
		// 
		this->txtItemName->Location = System::Drawing::Point(219, 59);
		this->txtItemName->Name = L"txtItemName";
		this->txtItemName->Size = System::Drawing::Size(141, 26);
		this->txtItemName->TabIndex = 2;
		// 
		// txtQuantity
		// 
		this->txtQuantity->Location = System::Drawing::Point(219, 159);
		this->txtQuantity->Name = L"txtQuantity";
		this->txtQuantity->Size = System::Drawing::Size(141, 26);
		this->txtQuantity->TabIndex = 3;
		// 
		// txtUnitPrice
		// 
		this->txtUnitPrice->Location = System::Drawing::Point(219, 207);
		this->txtUnitPrice->Name = L"txtUnitPrice";
		this->txtUnitPrice->Size = System::Drawing::Size(141, 26);
		this->txtUnitPrice->TabIndex = 4;
		// 
		// cmbCategories
		// 
		this->cmbCategories->FormattingEnabled = true;
		this->cmbCategories->Location = System::Drawing::Point(219, 108);
		this->cmbCategories->Name = L"cmbCategories";
		this->cmbCategories->Size = System::Drawing::Size(141, 28);
		this->cmbCategories->TabIndex = 6;
		// 
		// lblItemName
		// 
		this->lblItemName->AutoSize = true;
		this->lblItemName->Location = System::Drawing::Point(98, 59);
		this->lblItemName->Name = L"lblItemName";
		this->lblItemName->Size = System::Drawing::Size(87, 20);
		this->lblItemName->TabIndex = 7;
		this->lblItemName->Text = L"Item Name";
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(98, 116);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(73, 20);
		this->label1->TabIndex = 8;
		this->label1->Text = L"Category";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(98, 165);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(68, 20);
		this->label2->TabIndex = 9;
		this->label2->Text = L"Quantity";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(98, 213);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(77, 20);
		this->label3->TabIndex = 10;
		this->label3->Text = L"Unit Price";
		// 
		// btnAddItem
		// 
		this->btnAddItem->Location = System::Drawing::Point(219, 279);
		this->btnAddItem->Name = L"btnAddItem";
		this->btnAddItem->Size = System::Drawing::Size(141, 55);
		this->btnAddItem->TabIndex = 11;
		this->btnAddItem->Text = L"Save";
		this->btnAddItem->UseVisualStyleBackColor = true;
		this->btnAddItem->Click += gcnew System::EventHandler(this, &ItemForm::btnAddItem_Click);
		// 
		// btnUpdateItem
		// 
		this->btnUpdateItem->Location = System::Drawing::Point(72, 279);
		this->btnUpdateItem->Name = L"btnUpdateItem";
		this->btnUpdateItem->Size = System::Drawing::Size(141, 55);
		this->btnUpdateItem->TabIndex = 12;
		this->btnUpdateItem->Text = L"Update";
		this->btnUpdateItem->UseVisualStyleBackColor = true;
		this->btnUpdateItem->Visible = false;
		this->btnUpdateItem->Click += gcnew System::EventHandler(this, &ItemForm::button1_Click);
		// 
		// ItemForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(729, 465);
		this->Controls->Add(this->btnUpdateItem);
		this->Controls->Add(this->btnAddItem);
		this->Controls->Add(this->label3);
		this->Controls->Add(this->label2);
		this->Controls->Add(this->label1);
		this->Controls->Add(this->lblItemName);
		this->Controls->Add(this->cmbCategories);
		this->Controls->Add(this->txtUnitPrice);
		this->Controls->Add(this->txtQuantity);
		this->Controls->Add(this->txtItemName);
		this->Name = L"ItemForm";
		this->Text = L"New Item Form";
		this->Load += gcnew System::EventHandler(this, &ItemForm::AddItemForm_Load);
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

private: System::Void AddItemForm_Load(System::Object^ sender, System::EventArgs^ e) {

	auto categoryRepo = gcnew MSSQLRepository<Category^>();
	auto categories = categoryRepo->GetAll();
	auto categoryList = dynamic_cast<List<Category^>^>(categories);

	Category^ cat = gcnew Category();
	cat->CategoryID = 0;
	cat->CategoryName = "Seçiniz";
	categoryList->Add(cat);

	categoryList->Sort();
	cmbCategories->DataSource = categoryList;

	if (_actionType == EntityActionType::Insert) {
		cmbCategories->SelectedItem = cat;
	}
	else if (_actionType == EntityActionType::Update) {
		if (_updateItemId < 1)
		{
			MessageBox::Show("Ürün Numarasý alýnamadý!", "Hata");
			this->Close();
		}

		auto itemRepo = gcnew MSSQLRepository<Item^>();
		auto currentItem = itemRepo->GetById(_updateItemId);
		if (currentItem == nullptr)
		{
			MessageBox::Show("Ürün Bulunamadý!", "Hata");
			this->Close();
		}

		_currentItem = currentItem;

		Category^ relatedCategory = FindCategoryById(categoryList, currentItem->CategoryID);

		txtItemName->Text = currentItem->ItemName;
		cmbCategories->SelectedItem = relatedCategory;

		txtQuantity->Text = currentItem->Quantity.ToString();
		txtUnitPrice->Text = currentItem->UnitPrice.ToString();

	}
}


private: Category^ FindCategoryById(List<Category^>^ categoryList, int catId) {
	for each (Category ^ cat in categoryList) {
		if (cat->CategoryID == catId) {
			return cat;
		}
	}
	return nullptr;
}




private: System::Void btnAddItem_Click(System::Object^ sender, System::EventArgs^ e) {
	try
	{
		auto newItem = gcnew Item();

		newItem->ItemName = txtItemName->Text;
		newItem->CategoryID = dynamic_cast<Category^>(cmbCategories->SelectedItem)->CategoryID;
		newItem->Quantity = Int32::Parse(txtQuantity->Text == "" ? "0" : txtQuantity->Text);
		newItem->UnitPrice = Decimal::Parse(txtUnitPrice->Text == "" ? "0" : txtUnitPrice->Text);

		Validator::ValidateItem(newItem);

		auto itemRepo = gcnew MSSQLRepository<Item^>();
		itemRepo->Add(newItem);
		MessageBox::Show("Ürün eklendi!", "Bilgi");
		this->Close();
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message, "Hata");
	}
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {

	try
	{
		auto itemRepo = gcnew MSSQLRepository<Item^>();

		_currentItem->ItemName = txtItemName->Text;
		_currentItem->CategoryID = dynamic_cast<Category^>(cmbCategories->SelectedItem)->CategoryID;
		_currentItem->Quantity = Int32::Parse(txtQuantity->Text == "" ? "0" : txtQuantity->Text);
		_currentItem->UnitPrice = Decimal::Parse(txtUnitPrice->Text == "" ? "0" : txtUnitPrice->Text);

		Validator::ValidateItem(_currentItem);

		itemRepo->Update(_currentItem);
		MessageBox::Show("Ürün Güncellendi!", "Bilgi");
		this->Close();
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message, "Hata");
	}
}
};
