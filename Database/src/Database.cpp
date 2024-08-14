#include "Database/include/Database.h"
#include <iostream>

using namespace std;

bool Database::CreateTable(std::string tableName)
{
    try
    {
        if (connectionObject.is_open()) {

            pqxx::work w(connectionObject);
            std::string queryString = std::format("CREATE TABLE {} (id UUID DEFAULT {} PRIMARY KEY, name varchar(30), description varchar(100), price decimal, quantity integer);", tableName, GEN_UUID);

            w.exec(queryString);
            // Execute SQL query
            w.commit();
            cout << std::format("Table {} created successfully", tableName) << endl;
            return true;
        }
        else {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return false;
}

/*  
* 
* Insert a record into a table and return the newly generated id of that record
* 
*/

std::string Database::InsertRecordToTable(std::string tableName, std::string itemName, std::string itemDescription, double itemPrice, int itemQuantity)
{
    try
    {
        if (connectionObject.is_open()) {

            pqxx::work w(connectionObject);

            std::string queryString = std::format("INSERT INTO {} (name, description, price, quantity) VALUES ('{}', '{}', {}, {}) RETURNING id;", tableName, itemName, itemDescription, itemPrice, itemQuantity);

            pqxx::result R = w.exec_params(queryString);
            /* Execute SQL query */
            w.commit();

            std::string uuid = R[0]["id"].as<std::string>();

            cout << std::format("Record with ID {} inserted into {} successfully", uuid, tableName) << endl;

            return uuid;

        }
        else {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return "";
}

void Database::UpdateRecordInTable(std::string tableName, int itemQuantity, std::string itemId)
{
    try
    {
        if (connectionObject.is_open()) {

            pqxx::work w(connectionObject);

            std::string queryString = std::format("UPDATE {} set QUANTITY = {} where ID = {};", tableName, itemQuantity, itemId);
            w.exec(queryString);
            /* Execute SQL query */
            w.commit();

        }
        else {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Database::QueryRecordFromTable(std::string tableName, std::string itemId)
{
    try
    {
        if (connectionObject.is_open()) {

            pqxx::work w(connectionObject);

            std::string queryString = std::format("SELECT * from {} where id = {}", tableName, itemId);
            w.exec(queryString);
            /* Execute SQL query */
            w.commit();

        }
        else {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Database::DeleteRecordFromTable(std::string tableName, std::string itemId)
{
    try
    {
        if (connectionObject.is_open()) {

            //std::string itemId = inputItem.getItemId();

            pqxx::work w(connectionObject);

            std::string queryString = std::format("DELETE from {} where id = {}", tableName, itemId);
     
            w.exec(queryString);
            /* Execute SQL query */
            w.commit();
            cout << "Table Deleted successfully" << endl;

        }
        else {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Database::PrintEntireTable(std::string tableName)
{
    try
    {
        if (connectionObject.is_open()) {

            pqxx::nontransaction N(connectionObject);

            std::string queryString = std::format("SELECT * from {}", tableName);
            pqxx::result R(N.exec(queryString));

            for (pqxx::result::const_iterator c = R.begin(); c != R.end(); ++c) {

                cout << "ID = " << c[0].as<string>() << ", ";
                cout << "Name = " << c[1].as<string>() << ", ";
                cout << "Description = " << c[2].as<string>() << ", ";
                cout << "Price = " << c[3].as<double>() << ", ";
                cout << "Quantity = " << c[4].as<int>() << endl;
            }

            cout << "End of table " << tableName << endl;

        }
        else {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void Database::GetAllItems(std::string tableName)
{
    /*std::vector<Item> dataList;
    try
    {
        if (connectionObject.is_open()) {

            std::string queryString = std::format("SELECT * from {}", tableName);

            pqxx::work txn(connectionObject);
            pqxx::result result = txn.exec("SELECT id, name, value FROM my_table");

            for (auto row : result) {
                std::string id = row["id"].as<std::string>();
                std::string name = row["name"].as<std::string>();
                std::string description = row["description"].as<std::string>();
                double price = row["price"].as<double>();
                int quantity = row["quantity"].as<int>();

                //dataList.emplace_back(id, name, description, price, quantity);
            }

        }
        else 
        {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    for (Item item : dataList) {

        cout << "ID = " << item.getItemId() << ", ";
        cout << "Name = " << item.getItemName() << ", ";
        cout << "Description = " << item.getItemDescription() << ", ";
        cout << "Price = " << item.getItemPrice() << ", ";
        cout << "Quantity = " << item.getItemQuantity() << endl;
    }

    return dataList;*/
}

void Database::DeleteTable(std::string tableName)
{
    try
    {
        if (connectionObject.is_open()) {

            pqxx::work w(connectionObject);

            std::string queryString = std::format("DROP TABLE {};", tableName);

            w.exec(queryString);
            w.commit();

            std::cout << "Successfully dropped table " << tableName << std::endl;

        }
        else 
        {
            std::cerr << "Failed to connect to the database" << std::endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}
