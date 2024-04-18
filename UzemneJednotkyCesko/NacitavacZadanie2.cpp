#include "NacitavacZadanie2.h"
#include <string>

using namespace std;
//void NacitavacZadanie2::Nacitaj(const char vstupnySubor[], ds::adt::MultiwayTree<UzemnaJednotka*>& strom, GUIZadanie2* gui, int freq)
void NacitavacZadanie2::Nacitaj(const char vstupnySubor[], ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& strom, GUIZadanie2* gui, int freq)
{
	//pre testovacie ucely
	int pocNacKraj = 0;
	int pocNacOkres = 0;
	int pocNacObce = 0;
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

			//aktualnyKraj = Nacitavac::vytvorNovuUzemnuJednotku(polozky, kraj);
			
			aktualnyKraj = &strom.emplaceSon(koren, ntyKraj);
			aktualnyKraj->data_ = Nacitavac::vytvorNovuUzemnuJednotku(polozky, kraj);
			ntyOkres = 0;
			ntyKraj++;
			pocNacKraj++;
			//kraje.push_back(aktualnyKraj);
			//Pridaj aktualny Kraj

			continue;
		}

		Obec* novaObec = Nacitavac::vytvorNovuObec(polozky);

		// okres existuje a je v tom istom okrese ako predchadzajuci no problem : inak Vytvor novy okres
		if ((!aktualnyOkres || (aktualnyOkres->data_->getKod() != polozky[1]) && (polozky[1] != "x")))
		{
			//aktualnyOkres = Nacitavac::vytvorNovuUzemnuJednotku(polozky, soorp);
			aktualnyOkres = &strom.emplaceSon(*aktualnyKraj, ntyOkres);
			aktualnyOkres->data_ = Nacitavac::vytvorNovuUzemnuJednotku(polozky, soorp);
			ntaObec = 0;
			ntyOkres++;
			pocNacOkres++;
			//okresy.push_back(aktualnyOkres);
			//Pridaj aktualny okres
		}

		auto& stromObec = strom.emplaceSon(*aktualnyOkres, ntaObec);
		stromObec.data_ = novaObec;
		ntaObec++;
		pocNacObce++;
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

