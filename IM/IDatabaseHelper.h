using namespace System;
using namespace System::Data;

public interface class IDatabaseHelper {
public:
    void AddItem(String^ itemName, int categoryId, int quantity, double unitPrice);
    DataTable^ GetAllItems();
    void UpdateItem(int itemId, String^ itemName, int categoryId, int quantity, double unitPrice);
    void DeleteItem(int itemId);
};
