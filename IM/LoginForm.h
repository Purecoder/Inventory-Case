#pragma once



using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

#include "MainForm.h"
#include "AuthService.h"
#include "User.h"
#include "SessionManager.h"

public ref class LoginForm : public System::Windows::Forms::Form
{
public:
	LoginForm(void)
	{
		InitializeComponent();
	}

protected:
	~LoginForm()
	{
		if (components)
		{
			delete components;
		}
	}

private: System::Windows::Forms::TextBox^ txtUsername;
private: System::Windows::Forms::TextBox^ txtPassword;
private: System::Windows::Forms::Button^ btnLogin;
private: System::Windows::Forms::Label^ lblUsername;
private: System::Windows::Forms::Label^ lblPassword;

private:
	System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
	void InitializeComponent(void)
	{
		this->txtUsername = (gcnew System::Windows::Forms::TextBox());
		this->txtPassword = (gcnew System::Windows::Forms::TextBox());
		this->btnLogin = (gcnew System::Windows::Forms::Button());
		this->lblUsername = (gcnew System::Windows::Forms::Label());
		this->lblPassword = (gcnew System::Windows::Forms::Label());
		this->SuspendLayout();
		// 
		// txtUsername
		// 
		this->txtUsername->Location = System::Drawing::Point(150, 46);
		this->txtUsername->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->txtUsername->Name = L"txtUsername";
		this->txtUsername->Size = System::Drawing::Size(223, 26);
		this->txtUsername->TabIndex = 0;
		// 
		// txtPassword
		// 
		this->txtPassword->Location = System::Drawing::Point(150, 108);
		this->txtPassword->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->txtPassword->Name = L"txtPassword";
		this->txtPassword->Size = System::Drawing::Size(223, 26);
		this->txtPassword->TabIndex = 1;
		this->txtPassword->UseSystemPasswordChar = true;
		// 
		// btnLogin
		// 
		this->btnLogin->Location = System::Drawing::Point(150, 169);
		this->btnLogin->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->btnLogin->Name = L"btnLogin";
		this->btnLogin->Size = System::Drawing::Size(112, 35);
		this->btnLogin->TabIndex = 2;
		this->btnLogin->Text = L"Login";
		this->btnLogin->UseVisualStyleBackColor = true;
		this->btnLogin->Click += gcnew System::EventHandler(this, &LoginForm::btnLogin_Click);
		// 
		// lblUsername
		// 
		this->lblUsername->AutoSize = true;
		this->lblUsername->Location = System::Drawing::Point(45, 51);
		this->lblUsername->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->lblUsername->Name = L"lblUsername";
		this->lblUsername->Size = System::Drawing::Size(83, 20);
		this->lblUsername->TabIndex = 3;
		this->lblUsername->Text = L"Username";
		// 
		// lblPassword
		// 
		this->lblPassword->AutoSize = true;
		this->lblPassword->Location = System::Drawing::Point(45, 112);
		this->lblPassword->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->lblPassword->Name = L"lblPassword";
		this->lblPassword->Size = System::Drawing::Size(78, 20);
		this->lblPassword->TabIndex = 4;
		this->lblPassword->Text = L"Password";
		// 
		// LoginForm
		// 
		this->AcceptButton = this->btnLogin;
		this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(426, 248);
		this->Controls->Add(this->lblPassword);
		this->Controls->Add(this->lblUsername);
		this->Controls->Add(this->btnLogin);
		this->Controls->Add(this->txtPassword);
		this->Controls->Add(this->txtUsername);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
		this->Name = L"LoginForm";
		this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
		this->Text = L"Login";
		this->ResumeLayout(false);
		this->PerformLayout();

	}
#pragma endregion

private: System::Void btnLogin_Click(System::Object^ sender, System::EventArgs^ e) {
	String^ username = this->txtUsername->Text;
	String^ password = this->txtPassword->Text;

	User^ user = AuthService::Authenticate(username, password);
	if (user != nullptr) {
		SessionManager::CurrentUser = user;
		RoleManager::Initialize();
		this->Hide();
		MainForm^ mainForm = gcnew MainForm();
		mainForm->ShowDialog();
		this->Close();
	}
	else {
		MessageBox::Show("Invalid username or password", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}
};
