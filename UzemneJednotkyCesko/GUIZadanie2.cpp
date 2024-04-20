#include <iostream>

#include "GUIZadanie2.h"
#include "NacitavacZadanie2.h"
#include "Obec.h"

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
		cout << "* z/o -> spustÌ filtrovania\n";
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
		else if (vstup._Equal("a")) {
			vypisCeluPodhierarchiu(hierarchia);
		}
		else if (vstup._Equal("aa")) {
			//ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* docasna = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>;
			ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*> docasna;
			auto* nadradena = zvolenaUzemnaJednotka->parent_;
			
			docasna.changeRoot(zvolenaUzemnaJednotka);
			vypisCeluPodhierarchiu(&docasna);

			docasna.emplaceRoot();

			zvolenaUzemnaJednotka->parent_ = nadradena;
			
		    //delete docasna;
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
			catch (const std::invalid_argument& e)
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
	if (hierarchia->isLeaf(*zvolenaUzemnaJednotka)) {
		return false;
	}
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = hierarchia->accessSon(*zvolenaUzemnaJednotka, index);
	if (zastupca == nullptr) {
		return false;
	}
	zvolenaUzemnaJednotka = zastupca;
	return true;
}



void GUIZadanie2::Progressed(int by)
{
	cout << '*';
}
