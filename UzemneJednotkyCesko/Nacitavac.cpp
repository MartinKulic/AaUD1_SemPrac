#include <fstream>
#include<iostream>

#include "Nacitavac.h"
#include "GUI.h"


using namespace std;
void Nacitavac::Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce, GUI* progBar, int freq)
{

	UzemnaJednotka* aktualnyKraj = nullptr;
	UzemnaJednotka* aktualnyOkres = nullptr;
	int pocNacitanych = 0;

	//Citanie-----------------------------------

	ifstream vstupnyCitac(vstupnySubor);

	if (vstupnyCitac.fail())
		throw problemZoSuborumExeption("Subor sa nepodarilo otvorit.");

	string line;
	while (getline(vstupnyCitac, line))//vstupnyCitac.good()
	{
		string polozky[18];
		int i = 0;
		int firstSemicol;
		do {    //  Rozlozi riadok po ;
			firstSemicol = line.find(';');
			polozky[i] = line.substr(0, firstSemicol);
			i++;
			line = line.substr(firstSemicol + 1);
		} while (firstSemicol >= 0);

		// Identifikuje zaznam 

		if (polozky[4] == "" && polozky[10] == "") // polozky [4 az konic] a polozky [0 az 2] su "prazdne"
		{

			size_t posLine = vstupnyCitac.tellg();
			string pomocny;
			vstupnyCitac >> pomocny;
			vstupnyCitac.seekg(posLine);

			polozky[0] = pomocny.substr(0, pomocny.find(';'));

			aktualnyKraj = vytvorNovuUzemnuJednotku(polozky, kraj);
			kraje.push_back(aktualnyKraj);
			continue;
		}

		Obec* novaObec = vytvorNovuObec(polozky);

		// okres existuje a je v tom istom okrese ako predchadzajuci no problem : inak Vytvor novy okres
		if ((!aktualnyOkres || aktualnyOkres->getKod() != polozky[1]) && (polozky[1] != "x"))
		{
			aktualnyOkres = vytvorNovuUzemnuJednotku(polozky, soorp);
			okresy.push_back(aktualnyOkres);
		}

		obce.push_back(novaObec);
		//cout << *novaObec;    
		pocNacitanych++;
		if (pocNacitanych > freq)
		{
			progBar->Progressed(1);
			pocNacitanych = 0;
		}

	}
	vstupnyCitac.close();
}

Obec* Nacitavac::vytvorNovuObec(string polozky[])
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
		polozky[4] = polozky[4].substr(1, polozky[4].size()-2);
	}

	odstranMedzery(polozky[9]);
	odstranMedzery(polozky[10]);
	odstranMedzery(polozky[11]);
	odstranMedzery(polozky[12]);
	Obec* toRet = new Obec(polozky[4], polozky[5], polozky[6], stoul( polozky[9]), stoul(polozky[10]), stoul(polozky[11]), stoul(polozky[12]), kanalizacia, polozky[14] != "-" ? 1 : 0, polozky[15] != "-" ? 1 : 0);
	return toRet;
}

UzemnaJednotka* Nacitavac::vytvorNovuUzemnuJednotku(string polozky[], TypUzemia typ)
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
		newUzemnaJednotka = vytvorNovuObec(polozky);
		break;
	default:
		newUzemnaJednotka = new UzemnaJednotka("Idn what", "happend", undef);
		break;
	}
	return newUzemnaJednotka;;
}

void Nacitavac::odstranMedzery(string& textNaSpeacovanie)
{
	string pomocny;
	for (char ch : textNaSpeacovanie)
	{
		if (ch != ' ')
			pomocny += ch;
	}
	textNaSpeacovanie = pomocny;
}

Nacitavac::Nacitavac(const char subor[])
{
	prud.open(subor);
}

istream& Nacitavac::dajRiadok(string& line)
{
	return getline(prud, line);
}



