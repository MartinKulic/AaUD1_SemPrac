#include <iostream>

#include "GUIZadanie2.h"
#include "NacitavacZadanie2.h"
#include "Obec.h"
#include "Algoritmus2.h"
#include "Algoritmus.h"

using namespace std;
//using namespace ds::adt;
using namespace ds::amt;


void GUIZadanie2::printError(errorType et, std::string msg)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (et)
	{
	case VseobecnyHelp:
		cout << msg;
		cout << "\n* 1-n -> vnorenie, zadaj cislo zodpovedaj˙ce poûadovanej uzemnej podmnoûine.\n";
		cout << "*  .  -> spaù, prejde do nadradenej ˙zemnej jednotky.\n";
		cout << "*  a  -> vypise cel˙ hierarcihu\n";
		cout << "*  aa -> vypise podhierarchiu\n";
		cout << "* z/o/t-> spustÌ filtrovania (z - zacina na, o - obsahuje, t - je typu)\n";
		cout << "*  e  -> ukonËenie\n\n";
		break;
	case nespravnyArgument:
		SetConsoleTextAttribute(handle, 12);
		cout << "Chyba so zadan˝m parametrom: ";
		cout << msg;
		cout << "\nRozpoznanÈ argumenty su len:\n";
		SetConsoleTextAttribute(handle, 15);
		printError(VseobecnyHelp, "");
		break;
	default:
		break;
	}
}



GUIZadanie2::GUIZadanie2(const char vstupnySubor[])
{
	hierarchia = new MultiWayExplicitHierarchy<UzemnaJednotka*>;
	
	zvolenaUzemnaJednotka = &hierarchia->emplaceRoot();
	zvolenaUzemnaJednotka->data_ = new UzemnaJednotka("»esk· republika", "000000", TypUzemia(undef));

	synovia = new ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>;

	this->nacitavanie(vstupnySubor);

	resetVyfiltrovanyZoznam();

	handle = GetStdHandle(STD_OUTPUT_HANDLE);

	printError(errorType(VseobecnyHelp), "");
}

GUIZadanie2::~GUIZadanie2()
{
	delete  synovia;
	hierarchia->processPostOrder(hierarchia->accessRoot(), [](ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* block) {
		if (block->data_->getType() == TypUzemia(obec)) {
			delete(Obec*) block->data_;
		}
		else
		{
			delete block->data_;
		}

		});

	delete hierarchia;
}

void GUIZadanie2::startLoop()
{
	vypisMenu();
	while (1)
	{
		cout << ">";
		string vstup;
		cin >> vstup;

		if (vstup._Equal(".")) {
			if(!skusPrejstNaNadradedny())
			{
				SetConsoleTextAttribute(handle, 113);
				cout << "Uû si v najnadradenejöom\n";
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
			if (index < 0 || index > synovia->size()) {
				vypisMenu();
				string msg = vstup + " Argument je mimo rozsah.";
				SetConsoleTextAttribute(handle, 203);
				cout <<endl<< msg;
				SetConsoleTextAttribute(handle, 15);
				cout << endl;
				continue;
			}
			if (!skusPrejstNaPodradeny(index - 1)) {
				vypisMenu();
				SetConsoleTextAttribute(handle, 124);
				cout << "Uû sa ned· Ìsù hlböie";
				SetConsoleTextAttribute(handle, 15);
				cout << endl;
				continue;
			}
			vypisMenu();
		}
		//vypisMenu();
	}
}



void GUIZadanie2::nacitavanie(const char vstupnySubor[])
{
	cout << "Nacitavanie: ";
	NacitavacZadanie2::Nacitaj(vstupnySubor, *hierarchia, this, 60);
	cout << endl;
}
/// <summary>
/// Vypise culu podhierarchu vratane synov synov
/// </summary>
/// <param name="podhierarchia"></param>
void GUIZadanie2::vypisCeluPodhierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* podhierarchia)
{
	cout << "\n";
	auto start = podhierarchia->begin();
	auto stop = podhierarchia->end();
	while (start != stop) {
		cout << **start;
		start.operator++();
	}
}

void GUIZadanie2::vypisOcislovanychSynov(const ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>& podkoren)
{
	size_t pocSyn = hierarchia->degree(podkoren);
	for (size_t i = 0; i < pocSyn; i++)
	{
		string p = "[" + to_string(i+1) + ']';
		ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* syn = hierarchia->accessSon(podkoren, i);
		cout << left << setw(6) << p << syn->data_->getNazov() << endl;
	}

}
///Vypise a ocisluje zoznam "synovia"
void GUIZadanie2::vypisOcislovanych()
{
	size_t poc = 1;

	auto stop = synovia->end();
	for (auto akt = synovia->begin(); akt != stop; akt++) {
		string p = "[" + to_string(poc) + "]";
		cout  << left << setw(9) << p << (*akt)->data_->getNazov()<<endl;
		poc++;
	}
}

void GUIZadanie2::vypisMenu()
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

bool GUIZadanie2::skusPrejstNaNadradedny()
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

bool GUIZadanie2::skusPrejstNaPodradeny(size_t index)
{

	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = synovia->access(index)->data_;
	if (zastupca == nullptr || hierarchia->isLeaf(*zastupca)) {
		return false;
	}
	zvolenaUzemnaJednotka = zastupca;
	resetVyfiltrovanyZoznam();
	return true;
}

void GUIZadanie2::filtrujDialogZO(char volba)
{
	cout << "Zadaj hæadan˝ reùazec\n";

	string param;
	cin >> ws;
	getline(cin, param);

	/*ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>* pomocna = new ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>;

	if (volba == 'z') {

		Algoritmus2::filtruj(synovia->begin(), synovia->end(), *pomocna,
			[param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* block) {

				if (param.size() > block->data_->getNazov().size())
					return false;
				string ujNazov = block->data_->getNazov();
				for (int i = 0; i < param.size(); i++)
				{
					if (param[i] != ujNazov[i])
						return false;
				}
				return true;
			},
			[](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* block, ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>& vyslednyZ) {
				vyslednyZ.insertLast().data_ = block;
			});
	}
		else if (volba == 'o') {
			Algoritmus2::filtruj(synovia->begin(), synovia->end(), *pomocna, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getNazov().find(param) != -1;
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>& zoz) {zoz.insertLast().data_ = uj; });
		}



		delete synovia;
		synovia = pomocna;*/

	ImplicitSequence<UzemnaJednotka*>* pomocna = new ImplicitSequence<UzemnaJednotka*>;
	MultiWayExplicitHierarchy<UzemnaJednotka*> podhrierarchia;
	auto* parent = zvolenaUzemnaJednotka->parent_;
	podhrierarchia.changeRoot(zvolenaUzemnaJednotka);

	if (volba == 'z') {
		Algoritmus2::filtruj(podhrierarchia.begin(), podhrierarchia.end(), pomocna,
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
			[](UzemnaJednotka* uj, ImplicitSequence<UzemnaJednotka*>* zoznam) {zoznam->insertLast().data_ = uj; });
	}
	else if (volba == 'o') {
		Algoritmus2::filtruj(podhrierarchia.begin(), podhrierarchia.end(), pomocna,
			[param](UzemnaJednotka* uj) {
				return uj->getNazov().find(param) != -1;
			},
			[](UzemnaJednotka* uj, ImplicitSequence<UzemnaJednotka*>* zoznam) {zoznam->insertLast().data_ = uj; });
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

void GUIZadanie2::filtrujDialogT()
{
	string param;
	cout << "Zvol hladany typ (ob/ok/kr): ";
	cin >> param;

	/*ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>* pomocna = new ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>;

	if (param == "ob") {
		Algoritmus2::filtruj(synovia->begin(), synovia->end(), *pomocna, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getType() == TypUzemia(obec);
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>& zoz) {zoz.insertLast().data_ = uj; });
	}
	else if (param == "ok") {
		Algoritmus2::filtruj(synovia->begin(), synovia->end(), *pomocna, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getType() == TypUzemia(soorp);
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>& zoz) {zoz.insertLast().data_ = uj; });
	}
	else if (param == "kr") {
		Algoritmus2::filtruj(synovia->begin(), synovia->end(), *pomocna, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getType() == TypUzemia(kraj);
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>& zoz) {zoz.insertLast().data_ = uj; });
	}
	else {
		cout << "nespravne parametre.\n";
	}

	delete synovia;
	synovia = pomocna;*/

	ImplicitSequence<UzemnaJednotka*>* pomocna = new ImplicitSequence<UzemnaJednotka*>;
	MultiWayExplicitHierarchy<UzemnaJednotka*> podhrierarchia;
	auto* parent = zvolenaUzemnaJednotka->parent_;
	podhrierarchia.changeRoot(zvolenaUzemnaJednotka);

	if (param == "ob") {
		Algoritmus2::filtruj(podhrierarchia.begin(), podhrierarchia.end(), pomocna,
			[](UzemnaJednotka* uj) {return uj->getType() == TypUzemia(obec); },
			[](UzemnaJednotka* uj, ImplicitSequence<UzemnaJednotka*>* zoznam) {zoznam->insertLast().data_ = uj; });
	}
	else if (param == "ok") {
		Algoritmus2::filtruj(podhrierarchia.begin(), podhrierarchia.end(), pomocna,
			[](UzemnaJednotka* uj) {return uj->getType() == TypUzemia(soorp); },
			[](UzemnaJednotka* uj, ImplicitSequence<UzemnaJednotka*>* zoznam) {zoznam->insertLast().data_ = uj; });
	}
	else if (param == "kr") {
		Algoritmus2::filtruj(podhrierarchia.begin(), podhrierarchia.end(), pomocna,
			[](UzemnaJednotka* uj) {return uj->getType() == TypUzemia(kraj); },
			[](UzemnaJednotka* uj, ImplicitSequence<UzemnaJednotka*>* zoznam) {zoznam->insertLast().data_ = uj; });
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
			cout <<"\t\t\t"<< *(Obec*)(*akt);
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

void GUIZadanie2::resetVyfiltrovanyZoznam()
{
	synovia->clear();
	auto stop = zvolenaUzemnaJednotka->sons_->end();
	for (auto block = zvolenaUzemnaJednotka->sons_->begin(); block != stop; block++) {
		synovia->insertLast().data_ = *block;
	}
}




void GUIZadanie2::Progressed(int by)
{
	cout << '*';
}
