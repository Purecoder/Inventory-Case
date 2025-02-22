#pragma once
using namespace System;

#include "EntityBase.h"
#include "KeyAttribute.h"

public ref class Category : EntityBase, public IComparable<Category^>
{
public:
	[Key]
	property int CategoryID;
	property String^ CategoryName;

	Category() {}

	virtual String^ ToString() override {
		return CategoryName; // ComboBox'ta gösterilecek olan metin
	}

    virtual int CompareTo(Category^ other)
    {
        int result = 0;
        if (result == 0) result = this->CategoryID.CompareTo(other->CategoryID);
        if (result == 0) result = this->CategoryName->CompareTo(other->CategoryName);
        return result;
    }
};



