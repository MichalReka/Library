#pragma once
#include "User_intf.h"
static string id;
static string password;
class Worker :
	public User_intf
{
protected:
	short choose;
	void change_password();
	void disp_pers_data();
	void default_menu();
	void default_switch(short choose);
	string check_reader();
public:
	void log_in() override;
	Worker() {};
	//virtual void start_menu() override {};

};

#include "Admin.h"
#include "Info_staff.h"
#include "Librarian.h"