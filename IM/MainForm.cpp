#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(cli::array<System::String^>^ args) {

	Application::EnableVisualStyles();

	Application::SetCompatibleTextRenderingDefault(false);

	IM::MainForm form;

	Application::Run(% form);
}
