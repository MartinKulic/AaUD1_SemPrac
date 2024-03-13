#include "Struktura.h"
#include <iostream>
#include <fstream>


using namespace std;
Struktura::Struktura(const char vstupnySubor[])
{

    UzemnaJednotka* aktualnyKraj = nullptr;
    UzemnaJednotka* aktualnyOkres = nullptr;

    //Citanie-----------------------------------

    ifstream vstupnyCitac(vstupnySubor);
    string line;
    while (vstupnyCitac.good())
    {
        getline(vstupnyCitac, line);

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

            aktualnyKraj = pridajKraj(polozky);
        }

        // je v tom istom raji predchadzajuci
		else if (polozky[0] == aktualnyKraj->getKod())
		{
			Obec* novaObec = new Obec(polozky[4], polozky[5], polozky[6], stoul(polozky[9]), stoul(polozky[10]), stoul(polozky[11]), stoul(polozky[12]), Kanalizacia(polozky[13]=="-"?0:stoi(polozky[13])), polozky[14] == "-" ? 0 : 1, polozky[15] == "-" ? 0 : 1);

            // nepadri do okresu
            if (polozky[1] == "x")
            {
                aktualnyKraj->addUzemnuPodjednotku(novaObec);
                cout << *novaObec;
                continue;
            }
			// okres existuje a je v tom istom okrese ako predchadzajuci no problem : inak Vytvor novy okres
			else if (!aktualnyOkres || aktualnyOkres->getKod() != polozky[1])
			{
                aktualnyOkres = new UzemnaJednotka(polozky[3],polozky[2], soorp);
                aktualnyKraj->addUzemnuPodjednotku(aktualnyOkres);
			}

			aktualnyOkres->addUzemnuPodjednotku(novaObec);
            cout << *novaObec;
		}

    }
    vstupnyCitac.close();
}

UzemnaJednotka* Struktura::pridajKraj(std::string polozky[])
{
    UzemnaJednotka* novyKraj = new UzemnaJednotka(polozky[2], polozky[0], kraj);
    kraje.push_back(novyKraj);

    return novyKraj;
}