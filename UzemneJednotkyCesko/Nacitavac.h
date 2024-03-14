#pragma once
#include <vector>

#include "UzemnaJednotka.h"
#include "Obec.h"

namespace Nacitavac
{
	using namespace std;
	Obec* vytvorNovuObec(string polozky[]);
	void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce);
}


