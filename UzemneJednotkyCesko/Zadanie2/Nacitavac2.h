#pragma once
#include "libds/amt/explicit_hierarchy.h"
#include "../UzemnaJednotka.h"
#include "../IGUI.h"
#include "../INacitavac.h"

#include <fstream>

class Nacitavac2 : INacitavac
{

	public:
		//static void Nacitaj(const char vstupnySubor[], ds::adt::MultiwayTree<UzemnaJednotka*>& strom, GUIZadanie2* gui, int freq);
		static void Nacitaj(const char vstupnySubor[], ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& strom, IGUI* gui, int freq);
	
};

