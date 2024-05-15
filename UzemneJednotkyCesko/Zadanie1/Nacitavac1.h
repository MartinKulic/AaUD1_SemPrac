#pragma once
#include <vector>
#include <fstream>

#include "../UzemnaJednotka.h"
#include "../Obec.h"
#include "GUI1.h"

//using namespace std;

	class Nacitavac
	{
	private:
		std::ifstream prud;

	public:
		Nacitavac(const char subor[]);
		std::istream& dajRiadok(std::string& line);
		static void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce, GUI1* gui, int freq);


		static Obec* vytvorNovuObec(std::string polozky[]);
		static UzemnaJednotka* vytvorNovuUzemnuJednotku(std::string polozky[], TypUzemia typ);
		static void odstranMedzery(std::string& textNaSpeacovanie);
	};



