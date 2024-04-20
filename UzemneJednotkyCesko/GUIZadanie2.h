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

	//HANDLE handle;
	//MultiwayTree<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zvolenaUzemnaJednotka;

	void nacitavanie(const char vstupnySubor[]);
	void vypisCeluPodhierarchiu(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* podhierarchia);
	void vypisOcislovanychSynov(const ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>& podkoren);

	bool skusPrejstNaNadradedny();
	bool skusPrejstNaPodradeny(size_t index);

public:
	GUIZadanie2(const char vstupnySubor[]);
	~GUIZadanie2();
	void startLoop();

	static void printError(errorType et, std::string msg);

	void Progressed(int by);
};



