#pragma once
#include <fstream>
#include "Obec.h"
#include "UzemnaJednotka.h"
#include "Nacitavac.h"
#include "GUIZadanie2.h"
class NacitavacZadanie2
{
private:
	std::ifstream prud;

public:
	//static void Nacitaj(const char vstupnySubor[], ds::adt::MultiwayTree<UzemnaJednotka*>& strom, GUIZadanie2* gui, int freq);
	static void Nacitaj(const char vstupnySubor[], ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& strom, GUIZadanie2* gui, int freq);
};


