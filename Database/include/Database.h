#pragma once
#include <string>
#include <vector>
#include <pqxx/pqxx>

const std::string GEN_UUID = "gen_random_uuid ()";

class Database {

public:

	Database() {}

	Database(Database& db){}

	~Database() {}

	bool CreateTable(std::string tableName);

	std::string InsertRecordToTable(std::string tableName, std::string itemName, std::string itemDescription, double itemPrice, int itemQuantity);

	void UpdateRecordInTable(std::string tableName, int itemQuantity, std::string itemId);

	void QueryRecordFromTable(std::string tableName, std::string itemId);

	void DeleteRecordFromTable(std::string tableName, std::string itemId);

	void PrintEntireTable(std::string tableName);

	void GetAllItems(std::string tableName);

	void DeleteTable(std::string tableName);

	Database& operator=(const Database& other) {
		return *this;
	}

private:
	std::string connectionString = ""; // Set this value using your postgres information: "host=yourhost port=port for your database dbname=your_db_name user=username password=password";
	pqxx::connection connectionObject{ connectionString.c_str() };
};