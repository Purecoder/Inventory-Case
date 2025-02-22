#pragma once
using namespace System;
using namespace System::Collections::Generic;

#include "Item.h"

public ref class Validator {
public:
	static void ValidateItem(Item^ item) {
		List<String^>^ errors = gcnew List<String^>();
		if (String::IsNullOrWhiteSpace(item->ItemName)) {
			throw gcnew Exception("�r�n ad� bo� olamaz!");
		}
		if (item->ItemName->Length > 100) {
			throw gcnew Exception("�r�n ad� 100 karakterden uzun olamaz!");
		}
		if (item->CategoryID <= 0) {
			throw gcnew Exception("Ge�erli bir kategori se�melisiniz!");
		}
		if (item->Quantity < 1) {
			throw gcnew Exception("Stok miktar� 0 ve �zeri olmal�d�r!");
		}
		if (item->UnitPrice <= 0) {
			throw gcnew Exception("Birim fiyat s�f�rdan b�y�k olmal�d�r!");
		}
	}
};
