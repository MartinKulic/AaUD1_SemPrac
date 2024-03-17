#pragma once
#include <vector>

#include "UzemnaJednotka.h"
#include "Obec.h"

using namespace std;
class Nacitavac
{
private:
	static Obec* vytvorNovuObec(string polozky[]);
	static UzemnaJednotka* vytvorNovuUzemnuJednotku(string polozky[], TypUzemia typ);
public:
	static void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce);
};

