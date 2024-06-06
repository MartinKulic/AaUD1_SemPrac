#pragma once
#include<string>


#include "../IGUI.h"
#include "../UzemnaJednotka.h"
#include "libds/amt/explicit_hierarchy.h"
#include "libds/adt/list.h"

class MyPseudoIterator
{
private:
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* zvolenyVrchol;
public:
	MyPseudoIterator(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* predloha);
	bool skusPrejstNaNadradedny();
	bool skusPrejstNaPodradeny(size_t index);
	void vypisOcislovanePodvrcholy();
	size_t size() { return zvolenyVrchol->sons_->size(); };


	ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator end();
	ds::amt::Hierarchy<ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>>::PreOrderHierarchyIterator begin();
	//MyPseudoIterator& operator++();
	//bool operator!=(const MyPseudoIterator& other);
	MyPseudoIterator& operator--();
	UzemnaJednotka* operator*();

	
};

class GUI4 :
    public IGUI
{
	
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;
	MyPseudoIterator* myIterator;

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

	
};
