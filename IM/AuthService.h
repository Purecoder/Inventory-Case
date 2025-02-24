#pragma once

#include "User.h"
#include "UserRole.h"
using namespace System;
using namespace System::Collections::Generic;

public ref class AuthService {
private:
	static Dictionary<String^, User^>^ users = gcnew Dictionary<String^, User^>();

public:
	static void RegisterUser(String^ username, String^ password, UserRole role) {
		if (!users->ContainsKey(username)) {
			users->Add(username, gcnew User(username, password, role));
		}
	}

	static User^ Authenticate(String^ username, String^ password) {
		if (users->ContainsKey(username) && users[username]->Password == password) {
			return users[username];
		}
		return nullptr;
	}

};