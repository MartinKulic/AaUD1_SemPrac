#pragma once
#include<string>
#include <Windows.h>

#include "../IGUI.h"
#include "../UzemnaJednotka.h"
#include "libds/amt/explicit_hierarchy.h"
#include "libds/adt/list.h"

class MyIterator
{
private:
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zvolenyVrchol;
public:
	MyIterator(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* predloha);
	bool skusPrejstNaNadradedny();
	bool skusPrejstNaPodradeny(size_t index);
	void vypisOcislovanePodvrcholy();
	size_t size() { return zvolenyVrchol->sons_->size(); };


	ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator end();
	ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator begin();
	//MyIterator& operator++();
	//bool operator!=(const MyIterator& other);
	MyIterator& operator--();
	UzemnaJednotka* operator*();

	
};

class GUI4 :
    public IGUI
{
	HANDLE handle;
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	MyIterator* myIterator;

	void nacitavanie(const char vstupnySubor[]);
	void vypisMoznosti();
	void filtrujDialogZO(std::function<bool(UzemnaJednotka*)>, std::string* param);
	void filtrujDialogT(std::string* param);
	void usporiadajVysledokDialog(ds::amt::ImplicitSequence<UzemnaJednotka*>* vysledok);
	void vypisVysledok(ds::amt::ImplicitSequence<UzemnaJednotka*>* vysledok);

public:
	GUI4(const char vstupnySubor[]);
	~GUI4();
	void startLoop();

	static void printError(errorType et, std::string msg);

	void Progressed(int by);

	static const std::string Consonant[];
};

const std::string GUI4::Consonant[] = {"a","e", "i", "o","u","ä","á","é","í", "ú", "ia", "ie", "iu", "ô", "A","E", "I", "O","U","Ä","Á","É","Í", "Ú", "Ia", "Ie", "Iu", "Ô" };
