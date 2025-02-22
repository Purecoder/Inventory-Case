#pragma once
using namespace System;
using namespace System::Collections::Generic;

#include "Item.h"

public ref class Validator {
public:
	static void ValidateItem(Item^ item) {
		List<String^>^ errors = gcnew List<String^>();
		if (String::IsNullOrWhiteSpace(item->ItemName)) {
			throw gcnew Exception("Ürün adý boþ olamaz!");
		}
		if (item->ItemName->Length > 100) {
			throw gcnew Exception("Ürün adý 100 karakterden uzun olamaz!");
		}
		if (item->CategoryID <= 0) {
			throw gcnew Exception("Geçerli bir kategori seçmelisiniz!");
		}
		if (item->Quantity < 1) {
			throw gcnew Exception("Stok miktarý 0 ve üzeri olmalýdýr!");
		}
		if (item->UnitPrice <= 0) {
			throw gcnew Exception("Birim fiyat sýfýrdan büyük olmalýdýr!");
		}
	}
};
