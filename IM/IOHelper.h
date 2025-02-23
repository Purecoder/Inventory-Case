#pragma once

using namespace System;
using namespace System::Collections::Generic;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Reflection;
using namespace System::Globalization;

public ref class IOHelper {
public:
	generic<typename T>
	static void ExportToCSV(List<T>^ items, String^ fileName) {
		try {
			String^ filePath = GetUniqueFilePath(fileName);
			StreamWriter^ writer = gcnew StreamWriter(filePath, false, System::Text::Encoding::UTF8);

			WriteHeader<T>(writer);

			for each (T item in items) {
				WriteItemToCSV(writer, item);
			}

			writer->Close();
			MessageBox::Show("Data successfully exported to a CSV file!", "Information", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

private:
	static String^ GetUniqueFilePath(String^ fileName) {
		auto dateTime = DateTime::Now;
		String^ baseFileName = String::Format(fileName + "_{0:D4}-{1:D2}-{2:D2}.csv", dateTime.Year, dateTime.Month, dateTime.Day);
		auto directory = System::Environment::CurrentDirectory;
		String^ filePath = Path::Combine(directory, baseFileName);

		int count = 1;
		while (File::Exists(filePath)) {
			String^ newFileName = String::Format(fileName + "_{0:Dd}-{1:D2}-{2:D2}_{3}.csv", dateTime.Year, dateTime.Month, dateTime.Day, count);
			filePath = Path::Combine(directory, newFileName);
			count++;
		}

		return filePath;
	}

	generic<typename T>
	static void WriteHeader(StreamWriter^ writer) {
		array<PropertyInfo^>^ properties = T::typeid->GetProperties();
		List<String^>^ headers = gcnew List<String^>();

		for each (PropertyInfo ^ property in properties) {
			headers->Add(property->Name);
		}

		writer->WriteLine(String::Join(",", headers->ToArray()));
	}

	generic<typename T>
	static void WriteItemToCSV(StreamWriter^ writer, T item) {
		array<PropertyInfo^>^ properties = T::typeid->GetProperties();
		List<String^>^ values = gcnew List<String^>();

		for each (PropertyInfo ^ property in properties) {
			Object^ value = property->GetValue(item, nullptr);
			String^ formattedValue = value != nullptr ? value->ToString() : "";

			if (property->PropertyType == Decimal::typeid) {
				formattedValue = Convert::ToDecimal(value).ToString("F2", CultureInfo::InvariantCulture);
			}
			if (property->PropertyType == Double::typeid) {
				formattedValue = Convert::ToDouble(value).ToString("F2", CultureInfo::InvariantCulture);
			}
			if (property->PropertyType == DateTime::typeid) {
				formattedValue = Convert::ToDateTime(value).ToString("yyyy-MM-dd HH:mm:ss", CultureInfo::InvariantCulture);
			}

			values->Add(formattedValue);
		}

		writer->WriteLine(String::Join(",", values->ToArray()));
	}
};
