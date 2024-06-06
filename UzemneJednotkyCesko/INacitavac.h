#pragma once
#include "Obec.h"
#include "UzemnaJednotka.h"
#include <string>

class INacitavac
{
public:
	static Obec* vytvorNovuObec(std::string polozky[]);
	static UzemnaJednotka* vytvorNovuUzemnuJednotku(std::string polozky[], TypUzemia typ);
	static void odstranMedzery(std::string& textNaSpeacovanie);
};
