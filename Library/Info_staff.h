#pragma once
#include "Worker.h"
class Info_staff :
	public Worker
{
private:
	void print_info_menu();
	void add_reader();
	void extend_return_time();
	void accept_fine();
public:
	void log_in() override {};
	void start_menu() override;
};

