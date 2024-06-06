#pragma once
#include <vector>
#include <fstream>

#include "../UzemnaJednotka.h"
#include "../Obec.h"
#include "../INacitavac.h"
#include "GUI1.h"

//using namespace std;

	class Nacitavac1 : public INacitavac
	{

	public:
		static void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce, GUI1* gui, int freq);
	};



