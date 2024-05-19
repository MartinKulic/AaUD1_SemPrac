#include "GUI4.h"
#include "../Zadanie2/Nacitavac2.h"
#include "../Algoritmus.h"

#include "libds/adt/list.h"

using namespace std;
//using namespace ds::adt;
using namespace ds::amt;

void GUI4::printError(errorType et, std::string msg)
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

void GUI4::nacitavanie(const char vstupnySubor[])
{
	cout << "Nacitavanie: ";
	Nacitavac2::Nacitaj(vstupnySubor, *hierarchia, this, 60);
	cout << endl;
}

void GUI4::vypisMoznosti()
{
	//(**myIterator)->data_.getType()
	int vypiln = 2 * (**myIterator)->getType();
	string pom = "=";
	for (int i = 0; i < vypiln; i++) {
		pom += "=";
	}
	SetConsoleTextAttribute(handle, 8);
	cout << pom;
	SetConsoleTextAttribute(handle, 11);
	cout << (**myIterator)->getNazov();
	SetConsoleTextAttribute(handle, 8);
	cout << "==============================" << endl;
	SetConsoleTextAttribute(handle, 15);
	myIterator->vypisOcislovanePodvrcholy();
}

void GUI4::filtrujDialogZO(std::function<bool(UzemnaJednotka*)> predicat, string* param)
{
	cout << "Hladaný retazec: ";
	cin >> std::ws;
	getline(std::cin, *param);

	ds::adt::ImplicitList<UzemnaJednotka*>* vysledok = new ds::adt::ImplicitList<UzemnaJednotka*>;

	Algoritmus<UzemnaJednotka*> alg;
	alg.filtruj(myIterator->begin(), myIterator->end(), predicat, [vysledok](UzemnaJednotka* uj) {vysledok->insertLast(uj); });

	auto end = vysledok->end();
	for (auto a = vysledok->begin(); a != end; ++a) {
		if ((*a)->getType() == TypUzemia(obec)) {
			cout << *(Obec*)(*a);
		}
		else {
			cout << **a;
		}
	}

	SetConsoleTextAttribute(handle, 22);
	std::cout << "\nNajdenych " << vysledok->size() << " zhod\n";
	SetConsoleTextAttribute(handle, 9);
	std::cout << "\n====================================================================================================================================\n\n";
	SetConsoleTextAttribute(handle, 15);

	delete vysledok;
}

GUI4::GUI4(const char vstupnySubor[])
{
	hierarchia = new MultiWayExplicitHierarchy<UzemnaJednotka*>;
	hierarchia->emplaceRoot().data_ = new UzemnaJednotka("Česká republika", "000000", TypUzemia(undef));

	this->nacitavanie(vstupnySubor);

	myIterator = new MyIterator(hierarchia);

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	printError(errorType(VseobecnyHelp), "");
}

GUI4::~GUI4()
{
	delete myIterator;
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

void GUI4::startLoop()
{
	vypisMoznosti();
	string vstup;

	while (true)
	{
		cout << ">";
		cin >> vstup;
		if (vstup._Equal("e"))
		{
			break;
		}

		string param;
		switch (vstup.at(0))
		{
		case '.':
			if (!myIterator->skusPrejstNaNadradedny())
			{
				SetConsoleTextAttribute(handle, 113);
				cout << "Už si v najnadradenej�om\n";
				SetConsoleTextAttribute(handle, 15);
			}
			break;
		case 'z': // zacina na
			filtrujDialogZO([&param](UzemnaJednotka* uj) {return uj->nazovStartsWith(param); }, &param);
			break;
		case 'o': // obsahuje
			filtrujDialogZO([&param](UzemnaJednotka* uj) {return uj->nazovContains(param); }, &param);
			break;
		case 't': // typ
			break;
		case 'u': //usporiadaj
			break;
		default:  // cislo
			int index;
			try {
				index = stoi(vstup);
			}
			catch (const std::invalid_argument)
			{
				vypisMoznosti();
				SetConsoleTextAttribute(handle, 12);
				string msg = vstup + " nie je cislo";

				printError(nespravnyArgument, msg);
				continue;
			}
			if (index <= 0 || index > myIterator->size()) {
				vypisMoznosti();
				string msg = vstup + " Argument je mimo rozsah.";
				SetConsoleTextAttribute(handle, 203);
				cout << endl << msg;
				SetConsoleTextAttribute(handle, 15);
				cout << endl;
				continue;
			}
			if (!myIterator->skusPrejstNaPodradeny(index - 1)) {
				vypisMoznosti();
				SetConsoleTextAttribute(handle, 124);
				cout << "U� sa ned� �s� hlb�ie";
				SetConsoleTextAttribute(handle, 15);
				cout << endl;
				continue;
			}
			break;
		}
		vypisMoznosti();

	}
}


void GUI4::Progressed(int by)
{
	cout << '*';
}





MyIterator::MyIterator(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* predloha)
{
	hierarchia = predloha;
	zvolenyVrchol = predloha->accessRoot();
}

bool MyIterator::skusPrejstNaNadradedny()
{
	if (hierarchia->isRoot(*zvolenyVrchol)) {
		return false;
	}
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = hierarchia->accessParent(*zvolenyVrchol);
	if (zastupca == nullptr) {
		return false;
	}
	zvolenyVrchol = zastupca;

	return true;
}

bool MyIterator::skusPrejstNaPodradeny(size_t index)
{
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zastupca = zvolenyVrchol->sons_->access(index)->data_;
	if (zastupca == nullptr || hierarchia->isLeaf(*zastupca)) {
		return false;
	}
	zvolenyVrchol = zastupca;
		
	return true;
}

void MyIterator::vypisOcislovanePodvrcholy()
{
	size_t poc = 1;
	auto stop = zvolenyVrchol->sons_->end();
	for (auto akt = zvolenyVrchol->sons_->begin(); akt != stop; akt++) {
		string p = "[" + to_string(poc) + "]";
		cout << left << setw(9) << p << (*akt)->data_->getNazov() << endl;
		poc++;
	}
}


ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator MyIterator::end()
{
	return ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator(hierarchia, nullptr);
}

ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator MyIterator::begin()
{
	return ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator(hierarchia, zvolenyVrchol);
}


MyIterator& MyIterator::operator--()
{
	skusPrejstNaNadradedny();
	return *this;
}


UzemnaJednotka* MyIterator::operator*()
{
	return zvolenyVrchol->data_;
}
