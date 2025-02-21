#pragma once
using namespace System;

#include "EntityBase.h"

public ref class Category : EntityBase {
public:
	property int CategoryID;
	property String^ CategoryName;

	Category() {}

	virtual String^ ToString() override {
		return CategoryName; // ComboBox'ta gösterilecek olan metin
	}
};
