#pragma once
using namespace System;
using namespace System::Configuration;
using namespace System::Data;
using namespace System::Data::SqlClient;
using namespace System::Windows::Forms;


 class DbHelper {
public:
    static String^ GetConnectionString() {
        ConnectionStringSettings^ connStr = ConfigurationManager::ConnectionStrings["Inventory"];

        if (connStr == nullptr)
        {
            throw gcnew InvalidOperationException("Connection string 'Inventory' database objesi bulunamadý!");
        }

        return connStr->ConnectionString;
        //return  ConfigurationManager::ConnectionStrings["InventoryDB"] ->ConnectionString;
    }

    static SqlConnection^ GetConnection() {
        return gcnew SqlConnection(GetConnectionString());
    }
};
