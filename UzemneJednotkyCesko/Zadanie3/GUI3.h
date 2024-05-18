#pragma once
#include <Windows.h>
#include <iostream>

#include "../IGUI.h"
#include "../UzemnaJednotka.h"
#include "../Obec.h"
#include "../Algoritmus.h"
#include "MyBinaryTree.h"
#include "libds/adt/tree.h"
#include "libds//adt/table.h"

class GUI3 : public IGUI
{
private:
	HANDLE handle;
	
	/*ds::adt::Table<std::string, UzemnaJednotka*>* kraje;
	ds::adt::Table<std::string, UzemnaJednotka*>* okresy;
	ds::adt::Table<std::string, Obec*>* obce;*/
	
	MyBinaryTree<UzemnaJednotka*>* kraje;
	MyBinaryTree<UzemnaJednotka*>* okresy;
	MyBinaryTree<Obec*>* obce;


	void nacitavanie(const char vstupnySubor[]);
	
	template <typename DruhJednotky>
	void pokracujVyhladavanie(MyBinaryTree<DruhJednotky>* kde);
	void vyhladajKluc();
	template <typename DruhJednotky>
	void pokracujVyhladajKluc(MyBinaryTree<DruhJednotky>* kde, std::string kluc);

public:
	GUI3(const char vstupnySubor[]);
	~GUI3();
	void startLoop();

	static void printError(errorType et, std::string msg);
	void Progressed(int by);
};

template<typename DruhJednotky>
inline void GUI3::pokracujVyhladavanie(MyBinaryTree<DruhJednotky>* kde)
{
	using TableItemType = typename ds::adt::TableItem<std::string, ds::adt::ImplicitList<DruhJednotky>*>;

	std::string operacia;
	std::string param;
	std::function<bool(TableItemType)> predicat;

	std::cout << "o = obsahuje, z = zacina na\n";
	std::cout << "Zvol operaciu (o/z): ";
	std::cin >> operacia;

	switch (operacia.at(0))
	{
	case 'o':
		predicat = [&param](TableItemType u)->bool {return u.key_.find(param) != -1; };
		break;
	case 'z':
		predicat = [&param](TableItemType u)->bool {return u.key_.find(param) == 0; };
		break;
	default:
	{
		GUI3::printError(nespravneVstupnePar, operacia);
		return;
	}
	break;
	}

	std::cout << "Zadaj h¾adaný reazec\n";

	std::cin >> std::ws;
	std::getline(std::cin, param);

	ds::adt::ImplicitList<std::string>* vysledok = new ds::adt::ImplicitList<std::string>; //ds::adt::ImplicitList<ds::adt::ImplicitList<DruhJednotky>*>;


	Algoritmus<TableItemType> alg;
	alg.filtruj(kde->beginThroughtTabItem(), kde->endThroughtTabItem(), predicat, [vysledok](TableItemType o) {vysledok->insertLast(o.key_); });

	SetConsoleTextAttribute(handle, 22);
	std::cout << "Nájdené klúèe:\n";
	SetConsoleTextAttribute(handle, 15);
	for (auto uj = vysledok->begin(); uj != vysledok->end(); uj++) {
		
		std::cout << "    - " << *uj << std::endl;
	}

	SetConsoleTextAttribute(handle, 22);
	std::cout << "\nNajdenych " << vysledok->size() << " zhod\n";
	SetConsoleTextAttribute(handle, 9);
	std::cout << "\n====================================================================================================================================\n\n";
	SetConsoleTextAttribute(handle, 15);

	delete vysledok;
}

template<typename DruhJednotky>
inline void GUI3::pokracujVyhladajKluc(MyBinaryTree<DruhJednotky>* kde, std::string kluc)
{
	ds::adt::ImplicitList<DruhJednotky>** vysledok;
	if (kde->tryFind(kluc, vysledok)) {
		auto uj = (*vysledok)->begin();
		auto kon = (*vysledok)->end();

		(**uj).vypisHlavicku();
		for (; uj != kon; ++uj) {
			std::cout << **uj << std::endl;
		}
	}
	else {
		SetConsoleTextAttribute(handle, 64);
		std::cout << "Pre daný k¾úè sa nenašiel záznam.";
		SetConsoleTextAttribute(handle, 15);
	}

}
