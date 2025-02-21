#pragma once
using namespace System;

#include "EntityBase.h"
public ref class Item : public EntityBase {
public:
	property Decimal UnitPrice;
	property int Quantity;
	property int CategoryID;
	property String^ ItemName;
	property int ItemID;

	//virtual property int ID {
	//	int get() override { return ItemID; }
	//	void set(int value) override { ItemID = value; }
	//}

	Item() {};
};
