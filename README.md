# Cpp-Postgresql

This provides boiler plate code to perform Postgresql operations using C++. 

[libpqxx](https://github.com/jtv/libpqxx) is the official C++ API client for Postgresql. This library will allow us to perform CRUD operations on our Postgresql Database using C++.

## Installation

I am running my C++ project (CMake) on Visual Studio for Windows so I used [vcpkg](https://vcpkg.io/en/) which is a package manager created by Microsoft to add packages easily to your CMake project. 
If you are running on Windows, install this package manager first and then use it to install **libpqxx**.

Be sure to add the all the environment variables that vcpkg requires and to modify the **CMAKE_TOOLCHAIN_FILE** in the **CMakeLists.txt** file, so that the path points to your vcpkg.cmake executable.

## Database.h

In the Database.h, there are a couple of things that you need for connecting your client to the database server.

*	**std::string connectionString**: Add all the information needed for your database (i.e db name, postgres user name, password, hostname, port for which db server is running on
*	**pqxx::connection connectionObject{ connectionString.c_str() }**; The ConnectionObject is necessary for making the connection to the database. It requires the information in **connectionString**, passed in as a c_string

## Overall Structure

Each read/write operation you perform on the database follows the same format:

*	Create a **worker** object
*	Pass in the SQL query into your worker object as a string
*	Execute the query and commit the transaction

Here's a code example. If I wanted to create a Table in my postgresql database called 'ITEM', the code would look something like this:
'''
try
{
	if (connectionObject.is_open()) {

		// Create worker object
		pqxx::work w(connectionObject);
		
		// Create query string
		std::string queryString = "CREATE TABLE ITEM (id UUID DEFAULT gen_random_uuid() PRIMARY KEY, name varchar(30), description varchar(100), price decimal, quantity integer);";

		// Execute the SQL query
		w.exec(queryString);
		// Commit the transaction
		w.commit();
		cout << "Table ITEM created successfully" << endl;
	}
	else {
		std::cerr << "Failed to connect to the database" << std::endl;
	}
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}
'''

In Database.h/Database.cpp, you will find many functions that perform CRUD operations on the database and you can use them as starting points and tweak anything to your needs.