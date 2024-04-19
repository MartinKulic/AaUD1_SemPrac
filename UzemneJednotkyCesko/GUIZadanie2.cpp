#include <iostream>

#include "GUIZadanie2.h"
#include "NacitavacZadanie2.h"
#include "Obec.h"

using namespace std;
//using namespace ds::adt;
using namespace ds::amt;



GUIZadanie2::GUIZadanie2(const char vstupnySubor[])
{
	//hierarchia = new MultiwayTree<UzemnaJednotka*>;
	hierarchia = new MultiWayExplicitHierarchy<UzemnaJednotka*>;
	
	UzemnaJednotka* koren = new UzemnaJednotka("Èeská republika", "000000", TypUzemia(undef));


	//auto& root = hierarchia->insertRoot();
	auto& root = hierarchia->emplaceRoot();
	root.data_ = koren;


	NacitavacZadanie2::Nacitaj(vstupnySubor, *hierarchia, this, 60);



	cout << "\n";
	//auto start = hierarchia->begin();
	//auto stop = hierarchia->end();
	//while (start != stop) {
	//	cout << **start;
	//	start.operator++();
	//}


}

GUIZadanie2::~GUIZadanie2()
{
	hierarchia->processPostOrder(hierarchia->accessRoot(), [](ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* block) {
		cout << *block->data_;
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


void GUIZadanie2::nacitavanie(const char vstupnySubor[])
{
}



void GUIZadanie2::Progressed(int by)
{
	cout << '*';
}
