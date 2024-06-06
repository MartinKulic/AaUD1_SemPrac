﻿#include "GUI2.h"
#include "Nacitavac2.h"
#include "../Algoritmus.h"

using namespace std;
//using namespace ds::adt;
using namespace ds::amt;


void GUI2::printError(errorType et, std::string msg)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (et)
	{
	case VseobecnyHelp:
		cout << msg;
		cout << "\n* 1-n -> vnorenie, zadaj cislo zodpovedajúce požadovanej uzemnej podmnožine.\n";
		cout << "*  .  -> spať, prejde do nadradenej územnej jednotky.\n";
		cout << "*  a  -> vypise celú hierarcihu\n";
		cout << "*  aa -> vypise podhierarchiu\n";
		cout << "* z/o/t-> spustí filtrovania (z - zacina na, o - obsahuje, t - je typu)\n";
		cout << "*  e  -> ukončenie\n\n";
		break;
	case nespravnyArgument:
		SetConsoleTextAttribute(handle, 12);
		cout << "Chyba so zadaným parametrom: ";
		cout << msg;
		cout << "\nRozpoznané argumenty su len:\n";
		SetConsoleTextAttribute(handle, 15);
		printError(VseobecnyHelp, "");
		break;
	default:
		break;
	}
}



GUI2::GUI2(const char vstupnySubor[])
{
	hierarchia = new MultiWayExplicitHierarchy<UzemnaJednotka*>;

	zvolenaUzemnaJednotka = &hierarchia->emplaceRoot();
	zvolenaUzemnaJednotka->data_ = new UzemnaJednotka("Česká republika", "000000", TypUzemia(undef));

	synovia = new ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>;

	this->nacitavanie(vstupnySubor);

	resetVyfiltrovanyZoznam();

	printError(errorType(VseobecnyHelp), "");
}

GUI2::~GUI2()
{
	delete  synovia;
	hierarchia->processPostOrder(hierarchia->accessRoot(), [](ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* block) {
		if (block->data_->getType() == TypUzemia(obec)) {
			delete(Obec*)block->data_;
		}
		else
		{
			delete block->data_;
		}

		});

	delete hierarchia;
}

void GUI2::startLoop()
{
	vypisMenu();
	while (1)
	{
		cout << ">";
		string vstup;
		cin >> vstup;

		if (vstup._Equal(".")) {
			if (!skusPrejstNaNadradedny())
			{
				SetConsoleTextAttribute(handle, 113);
				cout << "Už si v najnadradenejšom\n";
				SetConsoleTextAttribute(handle, 15);
			}
			resetVyfiltrovanyZoznam();
			vypisMenu();
			continue;
		}
		else if (vstup._Equal("z") || vstup._Equal("o")) {
			filtrujDialogZO(vstup[0]);
			vypisMenu();
		}
		else if (vstup._Equal("t")) {
			filtrujDialogT();
			vypisMenu();
		}
		else if (vstup._Equal("a")) {
			vypisCeluPodhierarchiu(hierarchia);
		}
		else if (vstup._Equal("aa")) {
			ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*> docasna;
			auto* nadradena = zvolenaUzemnaJednotka->parent_;

			docasna.changeRoot(zvolenaUzemnaJednotka);
			vypisCeluPodhierarchiu(&docasna);                   //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

			docasna.emplaceRoot();

			zvolenaUzemnaJednotka->parent_ = nadradena;

		}
		else if (vstup._Equal("e")) {
			break;
		}
		else //Predpoklada as ze bolo zadane cilo a teda sa chce pejst do podradeneho uzemia
		{
			int index;
			try
			{
				index = stoi(vstup);
			}
			catch (const std::invalid_argument)
			{
				vypisMenu();
				SetConsoleTextAttribute(handle, 12);
				string msg = vstup + " nie je cislo";

				printError(nespravnyArgument, msg);
				continue;
			}
			if (index <= 0 || index > synovia->size()) {
				vypisMenu();
				string msg = vstup + " Argument je mimo rozsah.";
				SetConsoleTextAttribute(handle, 203);
				cout << endl << msg;
				SetConsoleTextAttribute(handle, 15);
				cout << endl;
				continue;
			}
			if (!skusPrejstNaPodradeny(index - 1)) {
				vypisMenu();
				SetConsoleTextAttribute(handle, 124);
				cout << "Už sa nedá ísť hlbšie";
				SetConsoleTextAttribute(handle, 15);
				cout << endl;
				continue;
			}
			vypisMenu();
		}
		//vypisMenu();
	}
}



void GUI2::nacitavanie(const char vstupnySubor[])
{
	cout << "Nacitavanie: ";
	Nacitavac2::Nacitaj(vstupnySubor, *hierarchia, this, 60);
	cout << endl;
}
/// <summary>
/// Vypise culu podhierarchu vratane synov synov
/// </summary>
/// <param name="podhierarchia"></param>
void GUI2::vypisCeluPodhierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* podhierarchia)
{
	cout << "\n";
	auto start = podhierarchia->begin();
	auto stop = podhierarchia->end();
	while (start != stop) {
		cout << **start;
		start.operator++();
	}
}

void GUI2::vypisOcislovanychSynov(const ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>& podkoren)
{
	size_t pocSyn = hierarchia->degree(podkoren);
	for (size_t i = 0; i < pocSyn; i++)
	{
		string p = "[" + to_string(i + 1) + ']';
		ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* syn = hierarchia->accessSon(podkoren, i);
		cout << left << setw(6) << p << syn->data_->getNazov() << endl;
	}

}
///Vypise a ocisluje zoznam "synovia"
void GUI2::vypisOcislovanych()
{
	size_t poc = 1;

	auto stop = synovia->end();
	for (auto akt = synovia->begin(); akt != stop; akt++) {
		string p = "[" + to_string(poc) + "]";
		cout << left << setw(9) << p << (*akt)->data_->getNazov() << endl;
		poc++;
	}
}

void GUI2::vypisMenu()
{
	int vypiln = 2 * zvolenaUzemnaJednotka->data_->getType();
	string pom = "=";
	for (int i = 0; i < vypiln; i++) {
		pom += "=";
	}
	SetConsoleTextAttribute(handle, 8);
	cout << pom;
	SetConsoleTextAttribute(handle, 11);
	cout << zvolenaUzemnaJednotka->data_->getNazov();
	SetConsoleTextAttribute(handle, 8);
	cout << "==============================" << endl;
	SetConsoleTextAttribute(handle, 15);
	vypisOcislovanych();
}

bool GUI2::skusPrejstNaNadradedny()
{

	if (hierarchia->isRoot(*zvolenaUzemnaJednotka)) {
		return false;
	}
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = hierarchia->accessParent(*zvolenaUzemnaJednotka);
	if (zastupca == nullptr) {
		return false;
	}
	zvolenaUzemnaJednotka = zastupca;
	return true;
}

bool GUI2::skusPrejstNaPodradeny(size_t index)
{

	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = synovia->access(index)->data_;
	if (zastupca == nullptr || hierarchia->isLeaf(*zastupca)) {
		return false;
	}
	zvolenaUzemnaJednotka = zastupca;
	resetVyfiltrovanyZoznam();
	return true;
}

void GUI2::filtrujDialogZO(char volba)
{
	cout << "Zadaj hľadaný reťazec\n";

	string param;
	cin >> ws;
	getline(cin, param);

	ImplicitSequence<UzemnaJednotka*>* pomocna = new ImplicitSequence<UzemnaJednotka*>; // uklada vysledok
	MultiWayExplicitHierarchy<UzemnaJednotka*> podhrierarchia;
	auto* parent = zvolenaUzemnaJednotka->parent_;
	podhrierarchia.changeRoot(zvolenaUzemnaJednotka);
	
	Algoritmus<UzemnaJednotka*> alg;
	if (volba == 'z') {
		alg.filtruj(podhrierarchia.begin(), podhrierarchia.end(),
			[param](UzemnaJednotka* uj) {
				if (param.size() > uj->getNazov().size())
					return false;
				string ujNazov = uj->getNazov();
				for (int i = 0; i < param.size(); i++)
				{
					if (param[i] != ujNazov[i])
						return false;
				}
				return true;
			},
			[pomocna](UzemnaJednotka* uj) {pomocna->insertLast().data_ = uj; });
	}
	else if (volba == 'o') {
		alg.filtruj(podhrierarchia.begin(), podhrierarchia.end(),
			[param](UzemnaJednotka* uj) {
				return uj->getNazov().find(param) != -1;
			},
			[pomocna](UzemnaJednotka* uj) {pomocna->insertLast().data_ = uj; });
	}

	cout << "\n--- " << zvolenaUzemnaJednotka->data_->getNazov() << " ->\n";
	auto stop = pomocna->end();
	for (auto akt = pomocna->begin(); akt != stop; akt++) {
		if ((*akt)->getType() == TypUzemia(obec)) {
			cout << "\t\t\t" << *(Obec*)(*akt);
		}
		else
		{
			cout << **akt;
		}
	}
	SetConsoleTextAttribute(handle, 22);
	std::cout << "\nNajdenych " << pomocna->size() << " zhod\n";
	SetConsoleTextAttribute(handle, 9);
	std::cout << "\n====================================================================================================================================\n\n";
	SetConsoleTextAttribute(handle, 15);

	pomocna->clear();
	delete pomocna;
	podhrierarchia.emplaceRoot();
	zvolenaUzemnaJednotka->parent_ = parent;

	system("pause");
}

void GUI2::filtrujDialogT()
{
	string param;
	cout << "Zvol hladany typ (ob/ok/kr): ";
	cin >> param;

	ImplicitSequence<UzemnaJednotka*>* pomocna = new ImplicitSequence<UzemnaJednotka*>; // uklada vysledok
	MultiWayExplicitHierarchy<UzemnaJednotka*> podhrierarchia;
	auto* parent = zvolenaUzemnaJednotka->parent_;
	podhrierarchia.changeRoot(zvolenaUzemnaJednotka);

	Algoritmus<UzemnaJednotka*> alg;
	if (param == "ob") {
		alg.filtruj(podhrierarchia.begin(), podhrierarchia.end(),
			[](UzemnaJednotka* uj) {return uj->getType() == TypUzemia(obec); },
			[pomocna](UzemnaJednotka* uj) {pomocna->insertLast().data_ = uj; });
	}
	else if (param == "ok") {
		alg.filtruj(podhrierarchia.begin(), podhrierarchia.end(),
			[](UzemnaJednotka* uj) {return uj->getType() == TypUzemia(soorp); },
			[pomocna](UzemnaJednotka* uj) {pomocna->insertLast().data_ = uj; });
	}
	else if (param == "kr") {
		alg.filtruj(podhrierarchia.begin(), podhrierarchia.end(),
			[](UzemnaJednotka* uj) {return uj->getType() == TypUzemia(kraj); },
			[pomocna](UzemnaJednotka* uj) {pomocna->insertLast().data_ = uj; });
	}
	else {
		SetConsoleTextAttribute(handle, 192);
		cout << "nespravne parametre.";
		SetConsoleTextAttribute(handle, 15);
		cout << endl;
	}

	auto stop = pomocna->end();
	for (auto akt = pomocna->begin(); akt != stop; akt++) {
		if ((*akt)->getType() == TypUzemia(obec)) {
			cout << "\t\t\t" << *(Obec*)(*akt);
		}
		else
		{
			cout << **akt;
		}
	}
	SetConsoleTextAttribute(handle, 22);
	std::cout << "\nNajdenych " << pomocna->size() << " zhod\n";
	SetConsoleTextAttribute(handle, 9);
	std::cout << "\n====================================================================================================================================\n\n";
	SetConsoleTextAttribute(handle, 15);

	pomocna->clear();
	delete pomocna;
	podhrierarchia.emplaceRoot();
	zvolenaUzemnaJednotka->parent_ = parent;

	system("pause");
}

void GUI2::resetVyfiltrovanyZoznam()
{
	synovia->clear();
	auto stop = zvolenaUzemnaJednotka->sons_->end();
	for (auto block = zvolenaUzemnaJednotka->sons_->begin(); block != stop; block++) {
		synovia->insertLast().data_ = *block;
	}
}




void GUI2::Progressed(int by)
{
	cout << '*';
}
