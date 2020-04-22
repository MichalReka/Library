// VisualCPPtoMysql.cpp : Defines the entry point for the console application.
//


// Include Header Files
#include<cstring>
//#include "readpassword.cpp"
//#include <conio.h>

// For mysql Connection
#include <mysql.h>
#include "User_intf.h"
using namespace std;

// Defining Constant Variables
#define SERVER "localhost"  // As your code and database are on same computer
#define USER "root" // user name by which you want to access the database ( database user name- not server)
//#define PASSWORD ""
#define DATABASE "biblioteka"  // the database name in the database server


int main()
{
	MYSQL* connect;   // Create a MYSQL object
	connect = mysql_init(NULL); // Initialize the object
	char password[100] = ""; // is to store password- take input from user
	if (!connect)  // Check if the connect object was properly initialized
	{
		cout << "mysql Initialization Failed";
		return 1;
	}
	connect = mysql_real_connect(connect, SERVER, USER, password, DATABASE, 0, NULL, 0); // Create connection to the database, returns connection handler which is same as first parameter, returns null if unsuccessful to connect
	if (connect) // check if the connection was successful, 
	{
		cout << "Connection Succeeded\n";
	}
	else
	{
		cout << "Connection Failed\n";
		return 0;
	}
	User_intf launch(connect);
	launch.start_menu();



	/*												/// Insert a record in instructor table 
	bool t = mysql_query(connect, "insert into ksiazki values(\"\",\"guwno\",\"Biology\",30000)");  // Inserting a row into instructor table, Returns Zero for success. Nonzero if an error occurred.

	if (t == 0) // check if insertion was successful, if the record is already there in the table the above query will fail because of primary key constraints
		cout << " insertion was successful" << endl;
	else
		cout << " Insertion Failed" << endl;

	*/
	////// Show the instructor table again to see the change after insertion
	//cout << " ------------------ \n instructor Table After Insertion \n--------------- " << endl;
	//run_show(connect, "select * from ksiazki;");

	

	//getchar();
	return 0;
}