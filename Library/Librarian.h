#pragma once
#include "Worker.h"
class Librarian :
	public Worker
{
	void print_lib_menu();
	void borrow();
	void return_book();
	void add_book();
	void remove_book();
public:
	void log_in() override {};
	void start_menu() override;
};

