#pragma once
#include<string>
#include <Windows.h>

#include "../IGUI.h"
#include "../UzemnaJednotka.h"
#include "libds/amt/explicit_hierarchy.h"


class GUI2 : public IGUI
{
	HANDLE handle;
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zvolenaUzemnaJednotka; //Toto je moj iterator
	//ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator*  iterator;
	ds::amt::ImplicitSequence<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>*>* synovia;

	void nacitavanie(const char vstupnySubor[]);

	void vypisCeluPodhierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* podhierarchia);
	void vypisOcislovanychSynov(const ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>& podkoren);
	void vypisOcislovanych();
	void vypisMenu();

	bool skusPrejstNaNadradedny();
	bool skusPrejstNaPodradeny(size_t index);

	void filtrujDialogZO(char v);
	void filtrujDialogT();
	void resetVyfiltrovanyZoznam();
public:
	GUI2(const char vstupnySubor[]);
	~GUI2();
	void startLoop();

	static void printError(errorType et, std::string msg);

	void Progressed(int by);
};


