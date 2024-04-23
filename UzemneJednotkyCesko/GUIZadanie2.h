#pragma once
#include<string>
#include <Windows.h>

#include "libds/adt/tree.h"
#include "libds/amt/explicit_hierarchy.h"
#include "UzemnaJednotka.h"





class GUIZadanie2
{
private:
	enum errorType {
		VseobecnyHelp,
		nespravnyArgument
	};

	HANDLE handle;
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zvolenaUzemnaJednotka; //Toto je moj iterator
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
	GUIZadanie2(const char vstupnySubor[]);
	~GUIZadanie2();
	void startLoop();

	static void printError(errorType et, std::string msg);

	void Progressed(int by);
};



