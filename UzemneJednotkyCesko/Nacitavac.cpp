#include <fstream>
#include<iostream>


#include "Nacitavac.h"

namespace Nacitavac
{
	using namespace std;

	Obec* vytvorNovuObec(string polozky[])
	{
		Kanalizacia kanalizacia;
		if (polozky[13] == "-")
			kanalizacia = Kanalizacia(0);
		else if (polozky[13] != "")
			kanalizacia = Kanalizacia(stoi(polozky[13]));
		else
			kanalizacia = Kanalizacia(nezname);


		Obec* toRet = new Obec(polozky[4], polozky[5], polozky[6], stoul(polozky[9]), stoul(polozky[10]), stoul(polozky[11]), stoul(polozky[12]), kanalizacia, polozky[14] != "-" ? 1 : 0, polozky[15] != "-" ? 1 : 0);
		return toRet;
	}
	UzemnaJednotka* vytvorNovuUzemnuJednotku(string nazov, string kod, TypUzemia typ)
	{
		return new UzemnaJednotka(nazov, kod, typ);
	}

	void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce)
	{
		UzemnaJednotka* aktualnyKraj = nullptr;
		UzemnaJednotka* aktualnyOkres = nullptr;

		//Citanie-----------------------------------

		ifstream vstupnyCitac(vstupnySubor);
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

				aktualnyKraj = vytvorNovuUzemnuJednotku(polozky[2], polozky[0], kraj);
				kraje.push_back(aktualnyKraj);
				continue;
			}

			Obec* novaObec = vytvorNovuObec(polozky);

			// okres existuje a je v tom istom okrese ako predchadzajuci no problem : inak Vytvor novy okres
			if ((!aktualnyOkres || aktualnyOkres->getKod() != polozky[1]) && (polozky[1] != "x"))
			{
				aktualnyOkres = vytvorNovuUzemnuJednotku(polozky[2], polozky[1], soorp);
				okresy.push_back(aktualnyOkres);
			}

			obce.push_back(novaObec);
			//cout << *novaObec;        

		}
		vstupnyCitac.close();
	}
}

