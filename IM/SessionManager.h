#pragma once
using namespace System;
#include "User.h"

public ref class SessionManager abstract sealed {
public:
    static property User^ CurrentUser {
        User^ get() { return _currentUser; }
        void set(User^ value) { _currentUser = value; }
    }

private:
    static User^ _currentUser;
};
