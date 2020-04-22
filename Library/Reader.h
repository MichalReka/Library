#pragma once
#include "User_intf.h"
class Reader :
	public User_intf
{
private:
	string id;
public:
	void start_menu() override;
	void log_in() override;
	Reader() {};
};

