#include "GUI3.h"
#include "Nacitavac3.h"
#include "MyBinaryTree.h"
#include "../Algoritmus.h"


using namespace std;
using namespace ds::adt;



void GUI3::printError(errorType et, std::string msg = "")
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (et)
	{
	case VseobecnyHelp:
		cout << "Rozpoznané príkazy majú nasledovný formát:\n";
		cout << "  (Kde sa vyhľadáva   Druh vyhľadávania   Čo je vyhľadávané):\n";
		cout << "\t* ob/ok/kr |> o (obsahuje) |> hľadaný reťazec - napr. ob o nad -> vypíše všetky obce obsahujúce \"nad\" vo svojom nazve\n";
		cout << "\t* ob/ok/kr |> z (začína na)|> hľadaný reťazec - napr. ok z Če  -> vypísš všetky okrasy začínajúce na \"Če\"\n";
		cout << "\t* k |> kľúč |> ob/ok/kr                       - napr. k Plzeň ob -> vypíše bližšie informácie o Plzni (kľúč musí byť presný)\n";
		cout << "\t* e -> ukoncenie\n";
		SetConsoleTextAttribute(handle, 113);
		cout << "Príkazy sa zadávajú postupne a potvrdzujú Enterom";
		SetConsoleTextAttribute(handle, 15);
		cout << "\nVyhladávanie je case sensitiv\n";
		break;
	case nespravnyArgument:
		SetConsoleTextAttribute(handle, 12);
		cout << "Chyba so zadaným parametrom: ";
		cout << msg;
		cout << "\nRozpoznané argumenty su len:\n";
		SetConsoleTextAttribute(handle, 15);
		printError(VseobecnyHelp, "");
		break;
	case nespravneVstupnePar:
		SetConsoleTextAttribute(handle, 12);
		cout << "\nParameter: \" ";
		SetConsoleTextAttribute(handle, 79);
		cout << msg;
		SetConsoleTextAttribute(handle, 12);
		cout << " \"Nerozpoznany.";
		SetConsoleTextAttribute(handle, 64);
		cout << "\nPouži len tieto príkazy\n";
		SetConsoleTextAttribute(handle, 15);
		GUI3::printError(VseobecnyHelp);
		break;
	default:
		break;
	}
}

void GUI3::vyhladajKluc()
{
	string kde;
	string kluc;

	cout << "Kľúč: ";
	cin >> std::ws;
	getline(std::cin, kluc);

	cout << "ob = obece, ok = okresy, kr = kraje\n";
	cout << "Nad: ";
	cin >> kde;

	if (kde == "ob")
	{
		pokracujVyhladajKluc<Obec*>(obce,kluc);
	}
	else if (kde == "ok")
	{
		pokracujVyhladajKluc<UzemnaJednotka*>(okresy, kluc);
	}
	else if (kde == "kr") {
		pokracujVyhladajKluc<UzemnaJednotka*>(kraje, kluc);
	}
	else
	{
		GUI3::printError(nespravneVstupnePar, kde);
	}



}

GUI3::GUI3(const char vstupnySubor[])
{
	kraje = new MyBinaryTree<string,UzemnaJednotka*>;
	okresy = new MyBinaryTree<string, UzemnaJednotka*>;
	obce = new MyBinaryTree<string, Obec*>;
	
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
    using TableItemType = typename ds::adt::TableItem<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>;
    GUI3::printError(VseobecnyHelp, "");
    while (1)
    {
        string kde;      

        cout << "k = kľúč / ob = obece, ok = okresy, kr = kraje, e = ukonči\n";
        cout << "-> ";
        cin >> kde;

        if (kde == "e")
        {
            break;
        }
		if (kde == "k") {
			vyhladajKluc();
		}
        else if (kde == "ob")
        {
            pokracujVyhladavanie<Obec*>(obce);
        }
        else if (kde == "ok")
        {
            pokracujVyhladavanie<UzemnaJednotka*>(okresy);
        }
		else if (kde == "kr") {
			pokracujVyhladavanie<UzemnaJednotka*>(kraje);
		}
        else
        {
            GUI3::printError(nespravneVstupnePar, kde);
        }

    

    }
	
}

void GUI3::nacitavanie(const char vstupnySubor[])
{
	cout << "Nacitavanie: ";
	Nacitavac3::Nacitaj(vstupnySubor, kraje, okresy, obce , this, 60);

	SetConsoleTextAttribute(handle, 32);
	cout << "\nNačítanie prebehlo úspešne" << "\n\n";
	SetConsoleTextAttribute(handle, 15);
		
}

void GUI3::Progressed(int by)
{
	cout << '*';
}
