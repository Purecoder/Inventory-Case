#pragma once
#include "UserRole.h"

using namespace System;

public ref class User {
public:
    property String^ Username;
    property String^ Password;
    property UserRole Role;

    User(String^ username, String^ password, UserRole role) {
        Username = username;
        Password = password;
        Role = role;
    }
};