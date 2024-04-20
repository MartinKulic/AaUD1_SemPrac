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
		cout << "Chyba so zadan˝m parametrom: ";
		cout << msg;
		cout << "\nRozpoznanÈ argumenty su len:\n";
		printError(VseobecnyHelp, "");
		break;
	default:
		break;
	}
}



GUIZadanie2::GUIZadanie2(const char vstupnySubor[])
{
	//hierarchia = new MultiwayTree<UzemnaJednotka*>;
	hierarchia = new MultiWayExplicitHierarchy<UzemnaJednotka*>;
	
	//auto& root = hierarchia->insertRoot();
	zvolenaUzemnaJednotka = &hierarchia->emplaceRoot();
	zvolenaUzemnaJednotka->data_ = new UzemnaJednotka("»esk· republika", "000000", TypUzemia(undef));


	this->nacitavanie(vstupnySubor);
	printError(errorType(VseobecnyHelp), "");


	//vypisCeluPodhierarchiu(hierarchia);

}

GUIZadanie2::~GUIZadanie2()
{
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
	while (1)
	{
		cout << *zvolenaUzemnaJednotka->data_ << endl;
		vypisOcislovanychSynov(*zvolenaUzemnaJednotka);
		cout << "\n> ";
		string vstup;
		cin >> vstup;

		if (vstup._Equal(".")) {
			if(!skusPrejstNaNadradedny())
			{
				cout << "Uû si v najnadradenejöom\n";
			}
			continue;
		}
		else if (vstup._Equal("z") || vstup._Equal("o")) {
			filtrujDialogZO(vstup[0]);
		}
		else if (vstup._Equal("t")) {
			filtrujDialogT();
		}
		else if (vstup._Equal("a")) {
			vypisCeluPodhierarchiu(hierarchia);
		}
		else if (vstup._Equal("aa")) {
			ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*> docasna;
			auto* nadradena = zvolenaUzemnaJednotka->parent_;
			
			docasna.changeRoot(zvolenaUzemnaJednotka);
			vypisCeluPodhierarchiu(&docasna);

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
				string msg = vstup + " nie je cislo";

				printError(nespravnyArgument, msg);
				continue;
			}
			if (index > hierarchia->degree(*zvolenaUzemnaJednotka)) {
				string msg = vstup + "Argument je mimo rozsah.";
				continue;
			}
			if (!skusPrejstNaPodradeny(index - 1)) {
				cout << "Uû sa ned· Ìsù hlböie\n";
				continue;
			}
		}
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
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = hierarchia->accessSon(*zvolenaUzemnaJednotka, index);
	if (zastupca == nullptr || hierarchia->isLeaf(*zastupca)) {
		return false;
	}
	zvolenaUzemnaJednotka = zastupca;
	return true;
}

void GUIZadanie2::filtrujDialogZO(char volba)
{
	cout << "Zadaj hæadan˝ reùazec\n";

	string param;
	cin >> ws;
	getline(cin, param);


	ImplicitSequence<UzemnaJednotka*> vyfiltrovane;
	ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*> synovia(*zvolenaUzemnaJednotka->sons_);
	if (volba == 'z') {

		Algoritmus2::filtruj(synovia.begin(), synovia.end(), vyfiltrovane, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			if (param.size() > uj->data_->getNazov().size())
				return false;
			string ujNazov = uj->data_->getNazov();
			for (int i = 0; i < param.size(); i++)
			{
				if (param[i] != ujNazov[i])
					return false;
			}
			return true;
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<UzemnaJednotka*>& zoz) {zoz.insertLast().data_ = uj->data_; });
		
	}
	else if (volba == 'o') {
		Algoritmus2::filtruj(synovia.begin(), synovia.end(), vyfiltrovane, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getNazov().find(param) != -1;
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<UzemnaJednotka*>& zoz) {zoz.insertLast().data_ = uj->data_; });
	}

	if (vyfiltrovane.accessFirst() && vyfiltrovane.accessFirst()->data_->getType() == TypUzemia(obec))
		Obec::vypisHlavicku();
	auto stop = vyfiltrovane.end();
	for (auto aktualny = vyfiltrovane.begin(); aktualny != stop; aktualny++) {
		if ((*aktualny)->getType() == TypUzemia(obec)) {
			cout << *(Obec*)*aktualny;
		}
		else {
			cout << **aktualny;
		}
	}
	cout << "najden˝ch: " << vyfiltrovane.size() << " zhÙd.\nStlaËte ENTER pre pokracovanie...\n";
	system("pause");
}

void GUIZadanie2::filtrujDialogT()
{
	string param;
	cout << "Zvol hladany typ (ob/ok/kr): ";
	cin >> param;

	ImplicitSequence<UzemnaJednotka*> vyfiltrovane;
	ImplicitSequence<MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*> synovia(*zvolenaUzemnaJednotka->sons_);

	if (param == "ob") {
		Algoritmus2::filtruj(synovia.begin(), synovia.end(), vyfiltrovane, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getType() == TypUzemia(obec);
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<UzemnaJednotka*>& zoz) {zoz.insertLast().data_ = uj->data_; });
	}
	else if (param == "ok") {
		Algoritmus2::filtruj(synovia.begin(), synovia.end(), vyfiltrovane, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getType() == TypUzemia(soorp);
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<UzemnaJednotka*>& zoz) {zoz.insertLast().data_ = uj->data_; });
	}
	else if (param == "kr") {
		Algoritmus2::filtruj(synovia.begin(), synovia.end(), vyfiltrovane, [param](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj) {
			return uj->data_->getType() == TypUzemia(kraj);
			}, [](MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* uj, ImplicitSequence<UzemnaJednotka*>& zoz) {zoz.insertLast().data_ = uj->data_; });
	}
	else {
		cout << "nespravne parametre.\n";
	}

	if (vyfiltrovane.accessFirst() && vyfiltrovane.accessFirst()->data_->getType() == TypUzemia(obec))
		Obec::vypisHlavicku();
	auto stop = vyfiltrovane.end();
	for (auto aktualny = vyfiltrovane.begin(); aktualny != stop; aktualny++) {
		if ((*aktualny)->getType() == TypUzemia(obec)) {
			cout << *(Obec*)*aktualny;
		}
		else {
			cout << **aktualny;
		}
	}
	cout << "najden˝ch: " << vyfiltrovane.size() << " zhÙd.\nStlaËte ENTER pre pokracovanie...\n";
	system("pause");
}



void GUIZadanie2::Progressed(int by)
{
	cout << '*';
}
