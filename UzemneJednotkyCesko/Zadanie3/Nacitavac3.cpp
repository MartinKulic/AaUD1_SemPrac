#include "Nacitavac3.h"
#include "MyBinaryTree.h"
#include <fstream>


using namespace std;
using namespace ds::adt;


void Nacitavac3::Nacitaj(const char vstupnySubor[], MyBinaryTree<UzemnaJednotka*>*& kraje, MyBinaryTree<UzemnaJednotka*>*& okresy, MyBinaryTree<Obec*>*& obce, IGUI* progBar, int freq)
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

			aktualnyKraj = INacitavac::vytvorNovuUzemnuJednotku(polozky, kraj);
			kraje->insert(aktualnyKraj->getNazov(), aktualnyKraj);
			continue;
		}

		Obec* novaObec = INacitavac::vytvorNovuObec(polozky);

		// okres existuje a je v tom istom okrese ako predchadzajuci no problem : inak Vytvor novy okres
		if ((!aktualnyOkres || aktualnyOkres->getKod() != polozky[1]) && (polozky[1] != "x"))
		{
			aktualnyOkres = INacitavac::vytvorNovuUzemnuJednotku(polozky, soorp);
			okresy->insert(aktualnyOkres->getNazov(), aktualnyOkres);
		}

		obce->insert(novaObec->getNazov(), novaObec);
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
