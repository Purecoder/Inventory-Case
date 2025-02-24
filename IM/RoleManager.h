#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Windows::Forms;

#include "UserRole.h"

public ref class RoleManager {
private:
	static Dictionary<UserRole, Dictionary<String^, List<String^>^>^>^ restrictedControls;

public:
	//This place can be improved by reading from a any database or ldap system.
	static void Initialize() {
		restrictedControls = gcnew Dictionary<UserRole, Dictionary<String^, List<String^>^>^>();

#pragma region Viewer
		Dictionary<String^, List<String^>^>^ viewerControls = gcnew Dictionary<String^, List<String^>^>();
		auto viewerMainFormControls = gcnew List<String^>();
		auto viewerItemFormControls = gcnew List<String^>();

		viewerMainFormControls->AddRange(gcnew array<String^> { "btnAddNewItemForm", "grpExportReport", "btnCellUpdate", "btnCellDelete" });
		viewerItemFormControls->AddRange(gcnew array<String^> { "btnAddItem", "btnUpdateItem" });

		viewerControls->Add("MainForm", viewerMainFormControls);
		viewerControls->Add("ItemForm", viewerItemFormControls);

#pragma endregion

#pragma region Editor
		Dictionary<String^, List<String^>^>^ editorControls = gcnew Dictionary<String^, List<String^>^>();

		auto editorMainFormControls = gcnew List<String^>();
		auto editorItemFormControls = gcnew List<String^>();

		editorMainFormControls->AddRange(gcnew array<String^> { "grpExportReport", "btnCellDelete" });
		editorItemFormControls->AddRange(gcnew array<String^> { "btnDelete" });

		editorControls->Add("MainForm", editorMainFormControls);
		editorControls->Add("ItemForm", editorItemFormControls);
#pragma endregion

#pragma region Reporter
		Dictionary<String^, List<String^>^>^ reporterControls = gcnew Dictionary<String^, List<String^>^>();

		auto reporterMainFormControls = gcnew List<String^>();
		reporterMainFormControls->AddRange(gcnew array<String^> { "btnAddNewItemForm", "btnCellUpdate", "btnCellDelete"  });
		reporterControls->Add("MainForm", reporterMainFormControls);
#pragma endregion

		restrictedControls->Add(UserRole::Viewer, viewerControls);
		restrictedControls->Add(UserRole::Editor, editorControls);
		restrictedControls->Add(UserRole::Reporter, reporterControls);

	}

	static bool IsRestricted(UserRole role, String^ formName, String^ controlName) {
		if (!restrictedControls->ContainsKey(role)) return false;
		if (!restrictedControls[role]->ContainsKey(formName)) return false;
		return restrictedControls[role][formName]->Contains(controlName);
	}

	static void ApplyRoleRestrictions(Form^ form, UserRole role) {
		for each (Control ^ ctrl in form->Controls) {
			ApplyControlRestriction(form->Name, ctrl, role);
		}
	}
private:
	static void ApplyControlRestriction(String^ formName, Control^ ctrl, UserRole role) {
		if (IsRestricted(role, formName, ctrl->Name)) {
			//ctrl->Enabled = false;
			ctrl->Visible = false;
		}

		if (DataGridView^ grid = dynamic_cast<DataGridView^>(ctrl)) {
			for each (DataGridViewColumn ^ column in grid->Columns) {
				if (DataGridViewButtonColumn^ btnCol = dynamic_cast<DataGridViewButtonColumn^>(column)) {
					if (IsRestricted(role, formName, btnCol->Name)) {
						btnCol->Visible = false;
					}
				}
			}
		}
	}
};

