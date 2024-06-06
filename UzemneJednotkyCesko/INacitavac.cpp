#include "INacitavac.h"

Obec* INacitavac::vytvorNovuObec(std::string polozky[])
{
	Kanalizacia kanalizacia;
	if (polozky[13] == "-")
		kanalizacia = Kanalizacia(0);
	else if (polozky[13] != "")
		kanalizacia = Kanalizacia(stoi(polozky[13]));
	else
		kanalizacia = Kanalizacia(nezname);

	if (polozky[4][0] == '\"')  // Pridane kvoli nekonzistencii vstupneho suboru - niektore zaznamy su v ""
	{
		polozky[4] = polozky[4].substr(1, polozky[4].size() - 2);
	}

	odstranMedzery(polozky[9]);
	odstranMedzery(polozky[10]);
	odstranMedzery(polozky[11]);
	odstranMedzery(polozky[12]);
	Obec* toRet = new Obec(polozky[4], polozky[5], polozky[6], stoul(polozky[9]), stoul(polozky[10]), stoul(polozky[11]), stoul(polozky[12]), kanalizacia, polozky[14] != "-" ? 1 : 0, polozky[15] != "-" ? 1 : 0);
	return toRet;
}

UzemnaJednotka* INacitavac::vytvorNovuUzemnuJednotku(std::string polozky[], TypUzemia typ)
{
	UzemnaJednotka* newUzemnaJednotka;
	switch (typ)
	{
	case kraj:
		newUzemnaJednotka = new UzemnaJednotka(polozky[2], polozky[0], typ);
		break;
	case soorp:
		newUzemnaJednotka = new UzemnaJednotka(polozky[2], polozky[1], typ);
		break;
	case obec:
		newUzemnaJednotka = INacitavac::vytvorNovuObec(polozky);
		break;
	default:
		newUzemnaJednotka = new UzemnaJednotka("Idn what", "happend", undef);
		break;
	}
	return newUzemnaJednotka;;
}

void INacitavac::odstranMedzery(std::string& textNaSpeacovanie)
{
	std::string pomocny;
	for (char ch : textNaSpeacovanie)
	{
		if (ch != ' ')
			pomocny += ch;
	}
	textNaSpeacovanie = pomocny;
}

