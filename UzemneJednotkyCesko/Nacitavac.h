#pragma once
#include <vector>
#include <fstream>

#include "UzemnaJednotka.h"
#include "Obec.h"
#include "GUI.h"

using namespace std;
class Nacitavac
{
private:
	ifstream prud;

	static Obec* vytvorNovuObec(string polozky[]);
	static UzemnaJednotka* vytvorNovuUzemnuJednotku(string polozky[], TypUzemia typ);
	static void odstranMedzery(string& textNaSpeacovanie);
public:
	Nacitavac(const char subor[]);
	istream& dajRiadok(string& line);
	static void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce, GUIProgressBar* gui, int freq);
};

