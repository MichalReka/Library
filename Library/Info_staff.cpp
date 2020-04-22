#include "Info_staff.h"
void Info_staff::print_info_menu()
{
	cout << "3 - dodaj nowego czytelnika" << endl;
	cout << "4 - przedluz termin wypozyczenia" << endl;
	cout << "5 - przyjmij kare za przekroczenie terminu" << endl;
	print_cl(5);
}

void Info_staff::add_reader()
{
	string name;
	string address;
	string postal_code;
	string phone_number;
	string query;
	bool err;
	cout << "Podaj imie: " << endl;
	getline(cin >> ws, name);
	cout << "Podaj nazwisko: " << endl;
	getline(cin >> ws, name);
	cout << "Podaj adres:" << endl;
	getline(cin >> ws, name);
	cout << "Podaj numer telefonu:" << endl;
	cin >> phone_number;
	query = "INSERT INTO `readers` (`ID`,`Name`,`Address`,`Postal Code`,`PhoneNumber`) VALUES (NULL,'" + name + "'," + address + "'," + postal_code + "'," + phone_number + "');";
	err = mysql_query(conn, query.c_str());
	if (err == 1)
	{
		cout << "Nie udalo sie dodac czytelnika!" << endl;
	}
}

void Info_staff::extend_return_time()
{
	string ID = check_reader();
	string query;
	bool err;
	cout << "Wypozyczone ksiazki: " << endl;
	run_show(conn, "select books.ID books.Tytul, books.Autor, borrowings.Date from books, borrowings where borrowings.BookID=books.ID AND borrowings.ReaderID=" + ID + " ;", 1);
	string bookID;
	cout << "Podaj ID ksiazki:" << endl;
	cin >> bookID;
	query = "UPDATE borrowings SET Date=DATE_ADD(Date,INTERVAL 1 MONTH) WHERE BookID=" + bookID + " ;";
	err = mysql_query(conn, query.c_str());
	if (err == 1)
	{
		cout << "Nie udalo sie przedluzyc terminu zwrotu ksiazki" << endl;
	}
}

void Info_staff::accept_fine()
{
	string ID = check_reader();
	string query;
	string pennys;
	bool err;
	char ch;
	cout << "Wypozyczone ksiazki: " << endl;
	run_show(conn, "select books.ID,books.Tytul, books.Autor, borrowings.Date from books, borrowings where borrowings.BookID=books.ID AND borrowings.ReaderID=" + ID + " ;", 1);
	string bookID;
	cout << "Podaj ID ksiazki:" << endl;
	cin >> bookID;
	cout << "Podaj ilosc groszy za kazdy dzien po terminie" << endl;
	cin >> pennys;
	cout << "Wysokosc kary (zl): ";
	run_show(conn, "select DATEDIFF(Date,CURRENT_DATE)*0." + pennys + " FROM borrowings WHERE BookID=" + bookID + " ;",1);
	cout << "Czy czytelnik uiscil oplate? t/n" << endl;
	cin >> ch;
	if (ch == 't')
	{
		query = "DELETE FROM borrowings WHERE BookID=" + bookID + " ;";
		err=mysql_query(conn, query.c_str());
		if (err == 0)
		{
			cout << "Pomyslnie usunieto wpis w bazie!" << endl;
		}
	}
}

void Info_staff::start_menu()
{
	if (choose == 6)
	{
		return;
	}
	default_menu();
	print_info_menu();
	cin >> choose;
	switch (choose)
	{
	case 3:
		add_reader();
		break;
	case 4:
		extend_return_time();
		break;
	case 5:
		accept_fine();
		break;
	case 6:
		return;
		break;
	case 7:
		close_p();
		break;
	default:
		default_switch(choose);
		break;
	}
	start_menu();
}