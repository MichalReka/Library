#include "Admin.h"

void Admin::print_adm_menu()
{
	cout << "3 - dodaj nowego pracownika" << endl;
	cout << "4 - usun pracownika z bazy" << endl;
	cout << "5 - zmien dane pracownika" << endl;
	//cout << "6 - usun ksiazke z bazy" << endl;
	print_cl(5);
}

void Admin::print_jobs()
{
	cout << "ID stanowiska: " << endl;
	run_show(conn, "SELECT * FROM Jobs", 1);
}

void Admin::add_employee()
{
	string FirstName;
	string LastName;
	string City;
	string Address;
	string Postal_Code;
	string Bank_account;
	string JobID;
	string Password;
	char ch;
	cout << "Podaj imie: " << endl;;
	cin >> FirstName;
	cout << "Podaj nazwisko: " << endl;
	getline(cin >> ws, LastName);
	cout << "Podaj miasto: "<<endl;
	getline(cin >> ws, City);
	cout << "Podaj adres: " << endl;
	getline(cin >> ws, Address);
	cout << "Podaj kod pocztowy: " << endl;
	getline(cin >> ws, Postal_Code);
	cout << "Podaj numer konta: " << endl;
	cin >> Bank_account;
	print_jobs();
	cout << "Podaj ID" << endl;
	cin >> JobID;
	cout << endl<<"Wprowadzono dane:" << endl;
	cout << "Imie: " << FirstName << "  Nazwisko: " << LastName << endl << "Miasto: " << City << "  Adres: " << Address << "  Kod pocztowy: " << Postal_Code;
	cout << endl << "Numer konta: " << Bank_account << "  ID stanowiska: " << JobID;
	cout << endl << "Czy zatwierdzasz podane dane?" << endl;
	cout << "Wybierz t/n" << endl;
	cin >> ch;
	if (ch == 't')
	{
		string query;
		query = "INSERT INTO `workers` (`ID`, `FirstName`, `LastName`, `City`, `Address`, `Postal Code`, `Bank account`, `JobID`, `Password`) VALUES (NULL,'" + FirstName + "','" + LastName + "','" + City + "','" + Address + "','" + Postal_Code;
		query = query + "','" + Bank_account + "','" + JobID + "'," + "'1234'" + ");";
		//INSERT INTO `workers` (`ID`, `FirstName`, `LastName`, `City`, `Address`, `Postal Code`, `Bank account`, `JobID`, `Password`) VALUES(NULL, '123', '123', '123', '123', '123', '123', '1', NULL);
		bool err=mysql_query(conn, query.c_str());
		//bool err = run_show(conn, "select ID from workers where FirstName='" + FirstName + "' AND LastName='" + LastName + "' AND `Bank account`=" + Bank_account,0);
		if (err == 1)
		{
			cout << "Nie udalo sie dodac poprawnie pracownika!" << endl;
		}
		else
		{
			cout << "Pomyslnie dodano pracownika!" << endl;
			cout << "Ustawiono domyslnie haslo 1234 - nalezy jak najszybciej je zmienic w swoim panelu pracownika!" << endl;
			cout << "ID nowego pracownika: ";
			run_show(conn, "select ID from workers where FirstName='" + FirstName + "' AND LastName='" + LastName + "' AND `Bank account`=" + Bank_account, 1);
			cout << endl;
		}
	}
	else
	{
		cout << "Dodawanie pracownika do bazy zakonczylo sie niepowodzeniem" << endl;
	}
}

bool Admin::find_employee(string &ID, string &password)
{
	cout << "Podaj ID pracownika" << endl;
	cin >> ID;
	cout << "Podaj haslo pracownika" << endl;
	cin >> password;
	bool err = run_show(conn, "select ID,FirstName,LastName from workers where ID=" + ID + " AND Password=" + password + " ;", 0);
	if (err == 1)
	{
		cout << "Nie mozna odnalezc uzytkownika!" << endl;
	}
	else
	{
		cout << "Znaleziono uzytkownika: ";
		run_show(conn, "select ID,FirstName,LastName from workers where ID=" + ID + " AND Password=" + password + " ;", 1);
	}
	return err;
}

void Admin::remove_employee()
{
	string ID;
	string password;
	bool err = find_employee(ID, password);
	if (err == 1)
	{
		return;
	}
		cout << "Czy na pewno usunac tego uzytkownika z bazy danych?" << endl;
		cout << "Tak - t, Nie - n" << endl;
		char ch;
		cin >> ch;
		if (ch == 't')
		{
			string query = "DELETE FROM workers WHERE ID = " + ID + " ;";
			mysql_query(conn, query.c_str());
			err = run_show(conn, "select ID,FirstName,LastName from workers where ID=" + ID + " AND Password=" + password + " ;", 0);
			if (err == 1)
			{
				cout << "Usuwanie uzytkownika powiodlo sie" << endl;
			}
			else
			{
				cout << "Usuwanie uzytkownika nie powiodlo sie!" << endl;
			}
		}
		else
		{
			cout << "Usuwanie uzytkownika zostalo anulowane" << endl;
		}
	
}

short Admin::print_chng_menu()
{
	cout << "1 - zmien imie" << endl;
	cout << "2 - zmien nazwisko" << endl;
	cout << "3 - zmien numer bankowy" << endl;
	cout << "4 - zmien adres" << endl;
	cout << "5 - zmien stanowisko" << endl;
	cout << "6 - powrot" << endl;
	short ch_temp;
	cin >> ch_temp;
	return ch_temp;
}

void Admin::address_change(string ID)
{
	char ch;
	string query;
	string address;
	cout << "Wpisz t - tak, n - nie" << endl;
	cout << "Czy nastapila zmiana miasta? t/n" << endl;
	cin >> ch;
	if (ch == 't')
	{
		string city;
		string postal_code;
		cout << "Podaj nazwe miasta: " << endl;
		getline(cin >> ws, city);
		cout << "Podaj adres: " << endl;
		getline(cin >> ws, address);
		cout << "Podaj kod pocztowy: " << endl;
		getline(cin >> ws, postal_code);
		query = "UPDATE workers SET City='" + city + "',Address='" + address + "',`Postal Code`='" + postal_code + "' WHERE ID=" + ID + " ;";
		mysql_query(conn, query.c_str());
		return;
	}
	else
	{
		cout << "Podaj adres: " << endl;
		getline(cin >> ws, address);
		cout << "Czy zmienia sie kod pocztowy?" << endl;
		cin >> ch;
		if (ch == 't')
		{
			query = "UPDATE workers SET Address='" + address + "' WHERE ID=" + ID + " ;";
			mysql_query(conn, query.c_str());
			return;
		}
		else
		{
			string postal_code;
			cout << "Podaj kod pocztowy: " << endl;
			getline(cin >> ws, postal_code);
			query = "UPDATE workers SET Address='" + address + "', `Postal Code`='" + postal_code + "' WHERE ID=" + ID + " ;";
			mysql_query(conn, query.c_str());
			return;
		}

	}
}

void Admin::change_data()
{
	string ID;
	string password;
	string buffer;
	string query;
	bool err = find_employee(ID, password);
	if (err == 1)
	{
		return;
	}
	short temp = print_chng_menu();
	while (temp > 6 || temp < 1)
	{
		cout << "Podaj poprawna liczbe!" << endl;
		temp = print_chng_menu();
	}
	if (temp < 4)
	{
		cout << "Podaj nowa dane:" << endl;
		getline(cin >> ws, buffer);
	}
	switch (temp)
	{
	case 1:
		query = "UPDATE workers SET FirstName='" + buffer + "' WHERE ID="+ID+" ;";
		mysql_query(conn, query.c_str());
		break;
	case 2:
		query = "UPDATE workers SET LastName='" + buffer + "' WHERE ID=" + ID + " ;";
		mysql_query(conn, query.c_str());
		break;
	case 3:
		query = "UPDATE workers SET `Bank account`=" + buffer + " WHERE ID=" + ID + " ;";
		mysql_query(conn, query.c_str());
		break;
	case 4:
		address_change(ID);
		break;
	case 5:
		print_jobs();
		cout << "Podaj ID:" << endl;
		cin >> buffer;
		query = "UPDATE workers SET JobID=" + buffer + " WHERE ID=" + ID + " ;";
		mysql_query(conn, query.c_str());
		break;
	case 6:
		return;
	}
}



void Admin::start_menu()
{
	if (choose == 6)
	{
		return;
	}
	default_menu();
	print_adm_menu();
	cin >> choose;
	switch (choose)
	{
	case 3:
		add_employee();
		break;
	case 4:
		remove_employee();
		break;
	case 5:
		change_data();
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
