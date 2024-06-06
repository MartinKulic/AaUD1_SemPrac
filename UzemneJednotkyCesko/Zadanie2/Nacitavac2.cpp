#include "Nacitavac2.h"
#include <fstream>

using namespace std;

void Nacitavac2::Nacitaj(const char vstupnySubor[], ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& strom, IGUI* gui, int freq)
{
	
	//-----------------------


	int pocNacitanych = 0;
	size_t ntyKraj = 0;
	size_t ntyOkres = 0;
	size_t ntaObec = 0;

	auto& koren = *strom.accessRoot();
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualnyKraj = nullptr;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* aktualnyOkres = nullptr;

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


			aktualnyKraj = &strom.emplaceSon(koren, ntyKraj);
			aktualnyKraj->data_ = INacitavac::vytvorNovuUzemnuJednotku(polozky, kraj);
			ntyOkres = 0;
			ntyKraj++;
			

			//Pridaj aktualny Kraj

			continue;
		}

		Obec* novaObec = INacitavac::vytvorNovuObec(polozky);
		if ((polozky[1] == "x") && !aktualnyOkres)
		{
			strom.emplaceSon(*aktualnyKraj, ntyOkres).data_ = novaObec;
			ntyOkres++;
			continue;
		}
		// okres existuje a je v tom istom okrese ako predchadzajuci no problem : inak Vytvor novy okres
		if (!aktualnyOkres || (aktualnyOkres->data_->getKod() != polozky[1]))
		{
			aktualnyOkres = &strom.emplaceSon(*aktualnyKraj, ntyOkres);
			aktualnyOkres->data_ = INacitavac::vytvorNovuUzemnuJednotku(polozky, soorp);
			ntaObec = 0;
			ntyOkres++;
			
			//Pridaj aktualny okres
		}

		auto& stromObec = strom.emplaceSon(*aktualnyOkres, ntaObec);
		stromObec.data_ = novaObec;
		ntaObec++;

		//obce.push_back(novaObec);
		// PridajNovu Obec
		//cout << *novaObec;    
		pocNacitanych++;
		if (pocNacitanych > freq)
		{
			gui->Progressed(1);
			pocNacitanych = 0;
		}
	}
	vstupnyCitac.close();
}
