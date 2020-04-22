#include "Librarian.h"
#include <iomanip>
#include <ctime>
#include <sstream>
void Librarian::print_lib_menu()
{
	cout << "3 - wypo¿ycz ksiazke" << endl;
	cout << "4 - przyjmij zwrot ksiazki" << endl;
	cout << "5 - dodaj ksiazke z bazy" << endl;
	cout << "6 - usun ksiazke z bazy" << endl;
	print_cl(6);
}

void Librarian::borrow()
{
	string ID = check_reader();
	string bookID;
	bool err = 0;
	if (ID.size()==0)
	{
		return;
	}
	else
	{
		err = run_show(conn, "SELECT COUNT(ReaderID) FROM borrowings WHERE ReaderID = " + ID + " GROUP BY ReaderID HAVING COUNT(ReaderID) > 3 ;", 0);
		if (err == 0)
		{
			cout << "Nie mozna wypozyczyc ksiazki - czytelnik przekracza limit wypozyczen!" << endl;
			return;
		}
		else
		{
			cout << "Wpisz ID ksiazki:" << endl;
			cin >> bookID;
			string query = "UPDATE books SET Status = 0 WHERE ID = " + bookID + " ;";
			err = mysql_query(conn, query.c_str());
			if (err == 1)
			{
				cout << "Nie udalo sie zmienic statusu ksiazki - sprawdz czy podales dobre ID" << endl;
				return;
			}
			else
			{
				//CURRENT_DATE
				query.clear();
				query= "INSERT INTO `borrowings` (`ID`, `BookID`,`ReaderID`,`Date`) VALUES (NULL,'" + bookID + "','" + ID + "',DATE_ADD(CURRENT_DATE,INTERVAL 1 MONTH));";
				err = mysql_query(conn, query.c_str());
				if (err == 1)
				{
					cout << "Nie udalo sie wypozyczyc ksiazki!" << endl;
					query = "UPDATE books SET Status = 1 WHERE ID = " + bookID + " ;";
					mysql_query(conn, query.c_str());
					return;
				}
			}
		}
	}
}

void Librarian::return_book()
{
	string ID = check_reader();
	string bookID;
	bool err = 0;
	if (ID.size() == 0)
	{
		return;
	}
	else
	{
		cout << "Wpisz ID ksiazki:" << endl;
		cin >> bookID;
		string query = "UPDATE books SET Status = 1 WHERE ID = " + bookID + " ;";
		err = mysql_query(conn, query.c_str());
		if (err == 1)
		{
			cout << "Nie udalo sie zmienic statusu ksiazki - sprawdz czy podales dobre ID" << endl;
			return;
		}
		cout << "Popranie zmieniono status ksiazki na dostepna" << endl;
		err = run_show(conn, "SELECT * FROM borrowings WHERE Date<CURRENT_DATE AND BookID ="+bookID+" ;", 0);
		if (err == 1)
		{
			query = "DELETE FROM borrowings WHERE BookID = " + bookID + " ;";
			err = mysql_query(conn, query.c_str());
			if (err == 0)
			{
				cout << "Poprawnie oddano ksiazke!" << endl;
			}
		}
		else
		{
			cout << "Czytelnik musi zaplacic kare w informacji by dokonczyc zwrot ksiazki" << endl;
		}
	}
}

void Librarian::add_book()
{
	string title;
	string author;
	short amount = 0;
	bool err = 0;;
	cout << "Podaj tytul" << endl;
	getline(cin >> ws, title);
	cout << "Podaj autora" << endl;
	getline(cin >> ws, author);
	cout << "Ile chcesz dodac takich ksiazek? Wpisz liczbe: " << endl;
	cin >> amount;
	string query = "INSERT INTO `books` (`ID`, `Tytul`,`Autor`,`Status`) VALUES (NULL,'" + title + "','" + author + "','1')";
	for (short i = 0;i < amount;i++)
	{
		err=mysql_query(conn, query.c_str());
	}
	if (err == 1)
	{
		cout << "Dodawanie zakonczylo sie niepowodzeniem!" << endl;
	}
	else
	{
		cout << "Dodawanie zakonczylo sie sukcesem" << endl;
	}
}

void Librarian::remove_book()
{
	string ID;
	bool err = 0;;
	cout << "Podaj ID" << endl;
	cin >> ID;
	string query = "DELETE FROM books WHERE ID = " + ID + ";";
	err = mysql_query(conn, query.c_str());
	if (err == 1)
	{
		cout << "Usuwanie zakonczylo sie niepowodzeniem!" << endl;
	}
	else
	{
		cout << "Usuwanie zakonczylo sie sukcesem" << endl;
	}
}

void Librarian::start_menu()
{
	if (choose == 7)
	{
		return;
	}
	default_menu();
	print_lib_menu();
	cin >> choose;
	switch (choose)
	{
	case 3:
		borrow();
		break;
	case 4:
		return_book();
		break;
	case 5:
		add_book();
		break;
	case 6:
		remove_book();
		break;
	case 7:
		return;
		break;
	case 8:
		close_p();
		break;
	default:
		default_switch(choose);
		break;
	}
	start_menu();
}
