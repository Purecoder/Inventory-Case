#include "LoginForm.h"
#include "UserRole.h"
using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(cli::array<System::String^>^ args) {

	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	AuthService::RegisterUser("admin", "admin", UserRole::Admin);
	AuthService::RegisterUser("editor1", "1234", UserRole::Editor);
	AuthService::RegisterUser("editor2", "1234", UserRole::Editor);
	AuthService::RegisterUser("reportuser", "1234", UserRole::Reporter);
	AuthService::RegisterUser("user", "user", UserRole::Viewer);

	LoginForm form;

	Application::Run(% form);
}