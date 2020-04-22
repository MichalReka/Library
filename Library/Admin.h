#pragma once
#include "Worker.h"
class Admin :
	public Worker
{
private:
	void print_adm_menu();
	void print_jobs();
	void add_employee();
	bool find_employee(string &ID, string &password);
	void remove_employee();
	short print_chng_menu();
	void address_change(string ID);
	void change_data();
public:
	void log_in() override {};
	void start_menu() override;
};

