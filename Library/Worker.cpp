#include "Worker.h"

void Worker::log_in()
{
	Worker* pos;
	bool err;
	cout << "Podaj ID: " << endl;
	cin >> id;
	cout << "Podaj haslo" << endl;
	cin >> password;
	err = run_show(conn, "select FirstName from workers where ID=" + id + " AND Password=" + password + ";",0);
	if (err == 1)
	{
		printf("\033c");
		cout << "Wpisano zle dane!" << endl;
		log_in();
	}
	else
	{
		cout << "Witaj ";
		run_show(conn, "select FirstName from workers where ID=" + id + " AND Password=" + password + ";", 1);
		cout << "Zalogowano jako...";
		err = run_show(conn, "select jobs.Name from jobs,workers where jobs.ID=workers.JobID AND workers.ID="+id+" AND jobs.Name='Admin' ;",1);
		if (err == 0)
		{
			pos = new Admin;
			pos->bind(conn);
			pos->start_menu();
			delete pos;

		}
		err = run_show(conn, "select jobs.Name from jobs,workers where jobs.ID=workers.JobID AND workers.ID=" + id + " AND jobs.Name='Pracownik informacji' ;",1);
		if (err == 0)
		{
			pos = new Info_staff;
			pos->bind(conn);
			pos->start_menu();
			delete pos;

		}
		err = run_show(conn, "select jobs.Name from jobs,workers where jobs.ID=workers.JobID AND workers.ID=" + id + " AND jobs.Name='Bibliotekarz' ;",1);
		if (err == 0)
		{
			pos = new Librarian;
			pos->bind(conn);
			pos->start_menu();
			delete pos;
		}
	}
}
void Worker::change_password()
{
	bool err = 1;
	cout << "Czy na pewno chcesz zmienic swoje haslo dostepu?" << endl;
	while (1)
	{
		cout << "Wprowadz T - jako tak, lub N - powrot do menu pracownika (wpisz z duzej litery)" << endl;
		char buff;
		cin >> buff;
		if (buff == 'N')
		{
			return;
		}
		if (buff == 'T')
		{
			cout << "Podaj stare haslo" << endl;
			password.clear();
			cin >> password;
			err = run_show(conn, "select * from workers where ID=" + id + " AND Password=" + password + " ;", 0);
			if (err == 0)
			{
				cout << "Podaj nowe haslo, powinno ono skladac sie z 4 cyfer" << endl;
				password.clear();
				cin >> password;
				string query = "update workers set Password = " + password + " where ID=" + id + " ;";
				mysql_query(conn, query.c_str());
				query.clear();
				return;
			}
			else
			{
				cout << "Podano zle haslo!" << endl;
			}
		}
		else
		{
			cout << "Wprowadz poprawna litere!" << endl;
		}
	}
	
}
void Worker::disp_pers_data()
{
	run_show(conn, "select * from workers where ID=" + id +" ;",1);
}
void Worker::default_menu()
{
	cout << "Wybor dzialania: " << endl;
	cout << "1 - wyswietl swoje dane osobiste" << endl;
	cout << "2 - zmien haslo" << endl;
}
void Worker::default_switch(short choose)
{
	switch (choose)
	{
	case 1:
		disp_pers_data();
		break;
	case 2:
		change_password();
		break;
	default:
		break;
	}
}
string Worker::check_reader()
{
	string ID;
	string password;
	bool err = 0;
	cout << "Podaj ID czytelnika: " << endl;
	cin >> ID;
	cout << "Podaj nr telefonu czytelnika" << endl;
	cin >> password;
	err = run_show(conn, "select * from readers where ID=" + ID + " AND PhoneNumber=" + password + " ;", 0);
	if (err == 1)
	{
		cout << "Nie znaleziono czytelnika!" << endl;
		return NULL;
	}
	else
	{
		cout << "Pomyslnie znaleziono czytelnika" << endl;
		return ID;
	}
}




