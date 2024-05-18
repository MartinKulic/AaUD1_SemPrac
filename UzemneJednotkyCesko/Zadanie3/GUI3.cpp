#include "GUI3.h"
#include "Nacitavac3.h"
#include "MyBinaryTree.h"
#include "../Algoritmus.h"


using namespace std;
using namespace ds::adt;



void GUI3::printError(errorType et, std::string msg)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (et)
	{
	case VseobecnyHelp:
		cout << msg;
		cout << "\n* 1-n -> vnorenie, zadaj cislo zodpovedaj�ce po�adovanej uzemnej podmno�ine.\n";
		cout << "*  .  -> spa�, prejde do nadradenej �zemnej jednotky.\n";
		cout << "*  a  -> vypise cel� hierarcihu\n";
		cout << "*  aa -> vypise podhierarchiu\n";
		cout << "* z/o/t-> spust� filtrovania (z - zacina na, o - obsahuje, t - je typu)\n";
		cout << "*  e  -> ukon�enie\n\n";
		break;
	case nespravnyArgument:
		SetConsoleTextAttribute(handle, 12);
		cout << "Chyba so zadan�m parametrom: ";
		cout << msg;
		cout << "\nRozpoznan� argumenty su len:\n";
		SetConsoleTextAttribute(handle, 15);
		printError(VseobecnyHelp, "");
		break;
	default:
		break;
	}
}

GUI3::GUI3(const char vstupnySubor[])
{
	handle = GetStdHandle(STD_OUTPUT_HANDLE);


	kraje = new MyBinaryTree<UzemnaJednotka*>;
	okresy = new MyBinaryTree<UzemnaJednotka*>;
	obce = new MyBinaryTree<Obec*>;

	/*MyBinaryTree table;
	table.insert("kraj", new UzemnaJednotka("kraj", "0000", TypUzemia(kraj)));
	table.insert("kraj2", new UzemnaJednotka("kraj2", "0002", TypUzemia(kraj)));
	table.insert("kraj", new UzemnaJednotka("kraj", "0003", TypUzemia(kraj)));

	table.deleteAll();*/
	
	this->nacitavanie(vstupnySubor);


}

GUI3::~GUI3()
{
	kraje->deleteAll();
	okresy->deleteAll();
	obce->deleteAll();


	delete kraje;
	delete okresy;
	delete obce;
}



void GUI3::startLoop()
{
    GUI3::printError(VseobecnyHelp, "");

	auto start = obce->begin();
	auto stop = obce->end();
	int count = 0;

	for (; start != stop; ++start) {
		cout << **start;
		count++;
	}

	cout << "vypisanych: " << count << " obci";
}

void GUI3::nacitavanie(const char vstupnySubor[])
{
	cout << "Nacitavanie: ";
	Nacitavac3::Nacitaj(vstupnySubor, kraje, okresy, obce , this, 60);



	
	SetConsoleTextAttribute(handle, 32);

	cout << "\nNačítanie prebehlo úspešne:\n" << "\n\tKraje: " << kraje->size() << "\n\n\tSORP:  " << okresy->size() << "\n\n\t";
	cout << endl;
	SetConsoleTextAttribute(handle, 15);
	
	cout << endl;
}

void GUI3::Progressed(int by)
{
	cout << '*';
}
