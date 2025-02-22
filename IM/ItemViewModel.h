#pragma once
using namespace System;

#include "EntityBase.h"
public ref class ItemViewModel : public EntityBase {
public:
	property Decimal UnitPrice;
	property int Quantity;
	property String^ CategoryName;
	property String^ ItemName;
	property int ItemID;

	ItemViewModel() {};
};
