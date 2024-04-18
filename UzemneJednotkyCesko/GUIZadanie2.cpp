#include <iostream>

#include "GUIZadanie2.h"
#include "Obec.h"

using namespace std;
using namespace ds::adt;



GUIZadanie2::GUIZadanie2(const char vstupnySubor[])
{
	hierarchia = new MultiwayTree<UzemnaJednotka*>;
	
	UzemnaJednotka koren("Èeská republika", "000000", TypUzemia(undef));
	Obec* o = new Obec("asd","kod4513","mesto", 4565,156,651,12,Kanalizacia(nie), false, false);
	Obec* oo = new Obec("obec2","kod222","mesto", 4565,156,651,12,Kanalizacia(nie), false, false);

	auto& root = hierarchia->insertRoot();
	root.data_ = &koren;

	auto& syn = hierarchia->emplaceSon(root, 0);
	syn.data_ = o;

	auto& synsyna = hierarchia->emplaceSon(syn, 0);
	synsyna.data_ = oo;
	
	cout << *hierarchia->accessSon(root, 0)->data_;

}


void GUIZadanie2::nacitavanie(const char vstupnySubor[])
{
}



void GUIZadanie2::Progressed(int by)
{
	cout << '*';
}
