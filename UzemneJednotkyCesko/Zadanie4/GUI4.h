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

	static const char Vowels[];
	static const char Consonant[];
};
__declspec(selectany)
const char GUI4::Vowels[] = {'a','e','u', 'o', '‰','·','È','Ì', '˙', 'Ù', 'A','E', 'I', 'O','U','ƒ','¡','…','Õ', '⁄', '‘' }; //"i"
__declspec(selectany)
const char GUI4::Consonant[] = { 'd', 't', 'n', 'l', 'h', 'g', 'k', 'Ô', 'ù', 'Ú', 'æ', 'c', 'Ë', 'û', 'ö', 'j', 'b', 'm', 'p', 'r', 's', 'v', 'z', 'f', 'D', 'T', 'N', 'L', 'H', 'G', 'K', 'œ', 'ç', '“', 'º', 'C', '»', 'é', 'ä', 'J', 'B', 'M', 'P', 'R', 'S', 'V', 'Z', 'F' }; //ch dz dû
