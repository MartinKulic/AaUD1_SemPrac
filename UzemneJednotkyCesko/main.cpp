// UzemneJednotkyCesko.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <libds/amt/implicit_sequence.h>
#include <vector>

#include "Obec.h"
#include "UzemnaJednotka.h"

#define CharacterConvention 1250

int main()
{
    SetConsoleOutputCP(CharacterConvention);
    SetConsoleCP(CharacterConvention);
    int i = 2;
    std::cout << "Character test: -------------\nAaÁáäBbCcÈèDdÏï...MmNnÒòOoÓóô\nKøeèovice, Králùv Dvùr\nCharacter test: -------------\n";

    Obec o1(string("Kanianka"), string("SK0001"), string("obec"), 1234, 5678, Kanalizacia(ano), true, true);
    Obec o2(string("Prievidza"), string("SK0002"), string("mesto"), 45100, 100000, Kanalizacia(ano), true, true);
    Obec o3(string("Lazany"), string("SK00-9"), string("obec"), 1000, 520, Kanalizacia(nie), true, true);
    Obec o4(string("Trencèín"), string("SK0010"), string("mesto"), 50000, 200120, Kanalizacia(COV), true, true);

    std::cout << o1 << o2 << o3 << o4;

    vector<UzemnaJednotka*> kraje;
    UzemnaJednotka* TrenciankyKraj = new UzemnaJednotka("Trenciansky Kraj", "TR 001", kraj);
    UzemnaJednotka* PrievidzkyOkres = new UzemnaJednotka("PrievidkyOkres", "PD 001", soorp);
    TrenciankyKraj->addUzemnuPodjednotku(PrievidzkyOkres);
    TrenciankyKraj->addUzemnuPodjednotku(&o4);
    PrievidzkyOkres->addUzemnuPodjednotku(&o1);
    PrievidzkyOkres->addUzemnuPodjednotku(&o2);
    PrievidzkyOkres->addUzemnuPodjednotku(&o3);

    // nacitavanie----------
    std::vector<UzemnaJednotka*> kraje;
    std::ifstream vstupnyCitac("CR.csv");
    std::string line;
    while (vstupnyCitac.good()) 
    {
        getline(vstupnyCitac, line);
        
        std::string polozky[18];
        int i = 0;
        int firstSemicol;
        do {
            firstSemicol = line.find(';');
            polozky[i] = line.substr(0, firstSemicol);
            i++;
            line = line.substr(firstSemicol+1);
        } while (firstSemicol >= 0);

        if (polozky[4] == "" && polozky[10] == "") // polozky[4 az konic] a polozky [0 az 2] su "prazdne"
        {
            pridajKraj(polozky, kraje);
        }
    }
}

UzemnaJednotka& pridajKraj(std::string polozky[], std::vector<UzemnaJednotka*>& kraje) //return kraj do ktoreho pridalo
{

}
UzemnaJednotka& pridajOkres(UzemnaJednotka kraj) //return okres do ktoreho pridalo
{

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
