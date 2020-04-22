#pragma once
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <mysql.h>
#include <string>
#define DATABASE "biblioteka"  // the database name in the database server
using namespace std;

class User_intf
{
protected:
	MYSQL* conn;
	bool run_show(MYSQL* connect, string query, bool ifdispl);
	void close_p();
	void bind(MYSQL* handler);
	void print_cl(short last);
	void switch_cl(short last, short choose);
	virtual void log_in() {};
	
public:
	User_intf() {};
	User_intf(MYSQL* c);
	virtual void start_menu();

	
	void show_books();
	
};

