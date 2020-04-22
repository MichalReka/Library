#include "Reader.h"
void Reader::log_in()
{
	string phone_number;
	bool err;
	cout << "Podaj ID: " << endl;
	cin >> id;
	cout << "Podaj nr telefonu" << endl;
	cin >> phone_number;
	err = run_show(conn, "select Name from readers where ID=" + id+" AND PhoneNumber="+phone_number+";",1);
	if (err == 1)
	{
		printf("\033c");
		cout << "Wpisano zle dane!" << endl;
		log_in();
	}
	else
	{
		cout << "Witaj!" << endl;
	}
}
void Reader::start_menu()
{
	short choose;
	string status;
	string buffer;
	cout << "Wybor dzialania: " << endl;
	cout << "1 - przejdz do wyswietlania informacji o ksiazkach" << endl;
	cout << "2 - przejdz do spisu wypozyczonych przez ciebie ksiazek" << endl;
	print_cl(2);
	cout << "Wpisz liczbe: ";
	cin >> choose;
	switch (choose)
	{
	case 1:
		show_books();
		break;
	case 2:
		run_show(conn, "select books.Tytul, books.Autor, borrowings.Date from books, borrowings where borrowings.BookID=books.ID AND borrowings.ReaderID="+id+" ;",1);
		break;
	case 3:
		printf("\033c");
		return;
		break;
	case 4:
		close_p();
	}
	start_menu();
}