#pragma once


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Text::RegularExpressions;
using namespace System::Globalization;

#include "MSSQLRepository.h"
#include "Item.h"
#include "Category.h"
#include "Validator.h"
#include "EntityActionType.h"
#include "Utility.h"
#include "SessionManager.h"
#include "RoleManager.h"


public delegate void ItemFormClosedEventHandler();
public ref class ItemForm : public System::Windows::Forms::Form
{
private:
	int _updateItemId = 0;
	EntityActionType _actionType;

private: System::Windows::Forms::TextBox^ txtUnitPriceFloat;
	   Item^ _currentItem;
public:
	event ItemFormClosedEventHandler^ OnItemFormClosed;

	ItemForm(EntityActionType actionType, int itemId)
	{

		InitializeComponent();

		_updateItemId = itemId;
		_actionType = actionType;

		//Update button location defined according to action type
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
		this->txtUnitPriceFloat = (gcnew System::Windows::Forms::TextBox());
		this->SuspendLayout();
		// 
		// txtItemName
		// 
		this->txtItemName->Location = System::Drawing::Point(153, 31);
		this->txtItemName->MaxLength = 100;
		this->txtItemName->Name = L"txtItemName";
		this->txtItemName->Size = System::Drawing::Size(170, 26);
		this->txtItemName->TabIndex = 1;
		// 
		// txtQuantity
		// 
		this->txtQuantity->Location = System::Drawing::Point(153, 131);
		this->txtQuantity->MaxLength = 7;
		this->txtQuantity->Name = L"txtQuantity";
		this->txtQuantity->Size = System::Drawing::Size(170, 26);
		this->txtQuantity->TabIndex = 3;
		// 
		// txtUnitPrice
		// 
		this->txtUnitPrice->Location = System::Drawing::Point(153, 179);
		this->txtUnitPrice->MaxLength = 10;
		this->txtUnitPrice->Name = L"txtUnitPrice";
		this->txtUnitPrice->Size = System::Drawing::Size(113, 26);
		this->txtUnitPrice->TabIndex = 4;
		this->txtUnitPrice->TextChanged += gcnew System::EventHandler(this, &ItemForm::txtUnitPrice_TextChanged);
		// 
		// cmbCategories
		// 
		this->cmbCategories->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
		this->cmbCategories->Location = System::Drawing::Point(153, 80);
		this->cmbCategories->Name = L"cmbCategories";
		this->cmbCategories->Size = System::Drawing::Size(170, 28);
		this->cmbCategories->TabIndex = 2;
		// 
		// lblItemName
		// 
		this->lblItemName->AutoSize = true;
		this->lblItemName->Location = System::Drawing::Point(32, 31);
		this->lblItemName->Name = L"lblItemName";
		this->lblItemName->Size = System::Drawing::Size(87, 20);
		this->lblItemName->TabIndex = 7;
		this->lblItemName->Text = L"Item Name";
		// 
		// label1
		// 
		this->label1->AutoSize = true;
		this->label1->Location = System::Drawing::Point(32, 88);
		this->label1->Name = L"label1";
		this->label1->Size = System::Drawing::Size(73, 20);
		this->label1->TabIndex = 8;
		this->label1->Text = L"Category";
		// 
		// label2
		// 
		this->label2->AutoSize = true;
		this->label2->Location = System::Drawing::Point(32, 137);
		this->label2->Name = L"label2";
		this->label2->Size = System::Drawing::Size(68, 20);
		this->label2->TabIndex = 9;
		this->label2->Text = L"Quantity";
		// 
		// label3
		// 
		this->label3->AutoSize = true;
		this->label3->Location = System::Drawing::Point(32, 185);
		this->label3->Name = L"label3";
		this->label3->Size = System::Drawing::Size(77, 20);
		this->label3->TabIndex = 10;
		this->label3->Text = L"Unit Price";
		// 
		// btnAddItem
		// 
		this->btnAddItem->Location = System::Drawing::Point(165, 248);
		this->btnAddItem->Name = L"btnAddItem";
		this->btnAddItem->Size = System::Drawing::Size(141, 55);
		this->btnAddItem->TabIndex = 7;
		this->btnAddItem->Text = L"Save";
		this->btnAddItem->UseVisualStyleBackColor = true;
		this->btnAddItem->Click += gcnew System::EventHandler(this, &ItemForm::btnAddItem_Click);
		// 
		// btnUpdateItem
		// 
		this->btnUpdateItem->Location = System::Drawing::Point(18, 248);
		this->btnUpdateItem->Name = L"btnUpdateItem";
		this->btnUpdateItem->Size = System::Drawing::Size(141, 55);
		this->btnUpdateItem->TabIndex = 6;
		this->btnUpdateItem->Text = L"Update";
		this->btnUpdateItem->UseVisualStyleBackColor = true;
		this->btnUpdateItem->Visible = false;
		this->btnUpdateItem->Click += gcnew System::EventHandler(this, &ItemForm::btnUpdateItem_Click);
		// 
		// txtUnitPriceFloat
		// 
		this->txtUnitPriceFloat->Location = System::Drawing::Point(272, 179);
		this->txtUnitPriceFloat->MaxLength = 2;
		this->txtUnitPriceFloat->Name = L"txtUnitPriceFloat";
		this->txtUnitPriceFloat->Size = System::Drawing::Size(51, 26);
		this->txtUnitPriceFloat->TabIndex = 5;
		this->txtUnitPriceFloat->Text = L"00";
		this->txtUnitPriceFloat->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
		// 
		// ItemForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(466, 376);
		this->Controls->Add(this->txtUnitPriceFloat);
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

	Category^ cat = gcnew Category();
	cat->CategoryID = 0;
	cat->CategoryName = "Choose";
	categories->Add(cat);

	categories->Sort();
	cmbCategories->DataSource = categories;

	if (_actionType == EntityActionType::Insert)
	{
		cmbCategories->SelectedItem = cat;
	}
	else if (_actionType == EntityActionType::Update)
	{
		if (_updateItemId < 1)
		{
			MessageBox::Show("Can not retreive Item Id!", "Error");
			this->Close();
		}

		auto itemRepo = gcnew MSSQLRepository<Item^>();
		auto currentItem = itemRepo->GetById(_updateItemId);
		if (currentItem == nullptr)
		{
			MessageBox::Show("Item not found!", "Error");
			this->Close();
		}

		_currentItem = currentItem;

		Category^ relatedCategory = FindCategoryById(categories, currentItem->CategoryID);

		txtItemName->Text = currentItem->ItemName;
		cmbCategories->SelectedItem = relatedCategory;

		txtQuantity->Text = currentItem->Quantity.ToString();


		auto unitPriceStr = currentItem->UnitPrice.ToString("#.00");
		txtUnitPriceFloat->Text = unitPriceStr->Substring(unitPriceStr->Length - 2);
		txtUnitPrice->Text = unitPriceStr->Substring(0, unitPriceStr->Length - 3);
		auto cc = "";
	}

	RoleManager::ApplyRoleRestrictions(this, SessionManager::CurrentUser->Role);
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

		prepareItem(newItem);
		Validator::ValidateItem(newItem);

		auto itemRepo = gcnew MSSQLRepository<Item^>();
		itemRepo->Add(newItem);
		try
		{
			OnItemFormClosed();
		}
		catch (Exception^ ex)
		{
			// Logs can be added.
		}
		MessageBox::Show("Item added!", "Information");
		this->Close();
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message, "Error");
	}
}

private: System::Void btnUpdateItem_Click(System::Object^ sender, System::EventArgs^ e) {
	try
	{
		auto itemRepo = gcnew MSSQLRepository<Item^>();

		prepareItem(_currentItem);
		Validator::ValidateItem(_currentItem);

		itemRepo->Update(_currentItem);
		OnItemFormClosed();
		MessageBox::Show("Item Updated!", "Information");
		this->Close();
	}
	catch (Exception^ ex) {
		MessageBox::Show(ex->Message, "Error");
	}
}

private: Item^ prepareItem(Item^ item) {
	item->ItemName = txtItemName->Text;
	item->CategoryID = dynamic_cast<Category^>(cmbCategories->SelectedItem)->CategoryID;
	item->Quantity = Int32::Parse(txtQuantity->Text == "" ? "0" : txtQuantity->Text);

	String^ decimalSeparator = Utility::GetDecimalSeparator();
	auto unitPrice = (txtUnitPrice->Text == "" ? "0" : txtUnitPrice->Text) + decimalSeparator + (txtUnitPriceFloat->Text == "" ? "00" : txtUnitPriceFloat->Text);
	item->UnitPrice = Decimal::Parse(unitPrice);

	return item;
}


private: System::Void txtUnitPrice_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	ValidateInteger(txtUnitPrice);
}

private: System::Void ValidateInteger(System::Windows::Forms::TextBox^ textBox) {
	Regex^ regex = gcnew Regex("^[0-9]*$");

	if (!regex->IsMatch(textBox->Text)) {
		int cursorPos = textBox->SelectionStart - 1;
		textBox->Text = Regex::Replace(textBox->Text, "[^0-9]", "");
		textBox->SelectionStart = Math::Max(0, cursorPos);
	}
}
};
