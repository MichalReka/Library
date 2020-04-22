#include "User_intf.h"
#include <stdlib.h>
#include "Reader.h"
#include "Worker.h"
void User_intf::bind(MYSQL* handler)
{
	conn = handler;
	log_in();
	start_menu();
}

void User_intf::print_cl(short last)
{
	cout << last+1<<" - wyloguj sie" << endl;
	cout << last+2<<" - zakoncz program" << endl;
}

bool User_intf::run_show(MYSQL* connect, string query, bool ifdispl)
{

	MYSQL_RES* res_set; //Result set object to store output table from the query
	MYSQL_ROW row; // row variable to process each row from the result set.

	mysql_query(connect, query.c_str());  // execute the query, returns Zero for success. Nonzero if an error occurred. details at https://dev.mysql.com/doc/refman/5.7/en/mysql-query.html

	res_set = mysql_store_result(connect); //reads the entire result of a query, allocates a MYSQL_RES structure, details at: https://dev.mysql.com/doc/refman/5.7/en/mysql-store-result.html
	int numrows = mysql_num_rows(res_set); // get number of rows in output table/ result set
	int num_col = mysql_num_fields(res_set); // get number of columns
	int i = 0;

	while (((row = mysql_fetch_row(res_set)) != NULL)) // fetch each row one by one from the result set
	{
		i = 0;
		while (i < num_col) { // print every row
			if(ifdispl==1)cout << row[i] << " ";  //cells are separated by space
			i++;
		}
		cout << endl; // print a new line after printing a row
	}
	if (i == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
User_intf::User_intf(MYSQL* c)
{
	conn = c;
	cout << " Tables in " << DATABASE << " database " << endl;
	run_show(c, "show tables;",1); // call the user defined function to execute query and show list of tables in the given database.
}
void User_intf::close_p()
{
	mysql_close(conn);
	exit(0);
}
void User_intf::show_books()
{
	short choose;
	string status;
	string buffer;
	cout << "Wybor dzialania: " << endl;
	cout << "1 - wyswietl nazwe i autora wszystkich ksiazek" << endl;
	cout << "2 - wyswietl nazwe i autora wszystkich dostepnych ksiazek" << endl;
	cout << "3 - wyszukaj ksiazke" << endl;
	cout << "Wpisz liczbe: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		run_show(conn, "select Tytul, Autor from books;",1);
		break;
	case 2:
		run_show(conn, "select Tytul, Autor from books where status=1;",1);
		break;
	case 3:
		cout << "Czy chcesz wyszukiwac srod ksiazek dostepnych do wypozyczenia czy wszystkich?" << endl;
		cout << "Wpisz 0 dla wszystkich, 1 dla dostepnych (nie ma znaczenia przy wyszukiwaniu po id)" << endl;
		cin >> status;
		cout << "Po czym chcesz wyszukac ksiazke?" << endl;
		cout << "1 - tytul" << endl;
		cout << "2 - autor" << endl;
		cout << "3 - id" << endl;
		cin >> choose;
		switch (choose)
		{
		case 1:
			cout << "Podaj tytul: " << endl;
			getline(cin>>ws, buffer);
			buffer = "\'" + buffer + "\'";
			if (stoi(status) == 0)
			{
				run_show(conn, "select Tytul, Autor from books where Tytul=" + buffer + ";",1);
			}
			else
			{
				run_show(conn, "select Tytul, Autor from books where Tytul=" + buffer + "AND Status=" + status + ";",1);
			}
			break;
		case 2:
			cout << "Podaj autora: " << endl;
			getline(cin>>ws, buffer);
			buffer = "\'" + buffer + "\'";
			if (stoi(status) == 0)
			{
				run_show(conn, "select Tytul, Autor from ksiazki where Autor=" + buffer + ";",1);
			}
			else
			{
				run_show(conn, "select Tytul, Autor from books where Autor=" + buffer + "AND Status=" + status + ";",1);
			}
			break;
		case 3:
			cout << "Podaj id: " << endl;
			getline(cin>>ws, buffer);
			run_show(conn, "select Tytul, Autor from books where ID=" + buffer + ";",1);
			break;
		}
		break;
	default:
		cout << "Wpisz wlasciwa liczbe!" << endl;
		show_books();
		break;
	}
	cout << "Wcisnij ENTER by wrocic";
	getchar();
	getchar();
	printf("\033c");
}
void User_intf::start_menu()
{
	Reader *reader;
	Worker *worker;
	short choose;
	cout << "Wybor uzytkownika: " << endl;
	cout << "1 - czytelnik" << endl;
	cout << "2 - pracownik" << endl;
	cout << "3 - wylacz program" << endl;
	cout << "Wpisz liczbe: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		printf("\033c");	//resetowanie konsoli
		reader=new Reader;
		reader->bind(conn);
		break;
	case 2:
		printf("\033c");
		worker = new Worker;
		worker->bind(conn);
		break;
	case 3:
		close_p();
		break;
	default:
		printf("\033c");
		cout << "Wpisz wlasciwa liczbe!" << endl;
		break;
	}
	start_menu();
	return;
}