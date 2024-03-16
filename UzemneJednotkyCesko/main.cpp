#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

#include "Nacitavac.h"
#include "Algoritmus.h"

using namespace std;
int main()
{
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    std::cout << "¾šèžýáíéúäôò¡A\n";


    std::vector<UzemnaJednotka*> kraje;
    std::vector<UzemnaJednotka*> okresy;
    std::vector<Obec*> obce;

    Nacitavac::Nacitaj("converted.csv", kraje, okresy, obce);

//---------------------------------------------------------------------

    cout << "\n----------------\n";

    std::vector<UzemnaJednotka*> vyfiltrovaneKraje;
    Algoritmus<UzemnaJednotka*> alg;

    char contains[] = "CKÝ";
    alg.filtruj(kraje.begin(), kraje.end(), vyfiltrovaneKraje, [contains](UzemnaJednotka* u) { return u->getNazov().find(contains) == -1 ? false : true; });

    for (UzemnaJednotka* uj : vyfiltrovaneKraje)
    {
        cout << *uj;
    }
    cout << "\n--------------------------\n";
    
    vector<UzemnaJednotka*> vyfiltrovaneOkresy;
    char zacinaNa[] = "Ho";
    alg.filtruj(okresy.begin(), okresy.end(), vyfiltrovaneOkresy, [zacinaNa](UzemnaJednotka* u) {return u->getNazov().find(zacinaNa) == 0 ? true : false; });

    for (UzemnaJednotka* uj : vyfiltrovaneOkresy)
    {
        cout << *uj;
    }
    cout << "\n--------------------------\n";

    Algoritmus<Obec*> algo;
    vector<Obec*> vyfiltrovaneObce1;
    char oZacinaNa[] = "Zi";
    algo.filtruj(obce.begin(), obce.end(), vyfiltrovaneObce1, [oZacinaNa](Obec* o) {return o->getNazov().find(oZacinaNa) == 0 ? true : false; });

    for (Obec* ob : vyfiltrovaneObce1)
    {
        cout << *ob;
    }
    cout << vyfiltrovaneObce1.size();
    cout << "\n--------------------------\n";

    vector<Obec*> vyfiltrovaneObce2;
    char oContains[] = "nad";
    algo.filtruj(obce.begin(), obce.end(), vyfiltrovaneObce2, [oContains](Obec* o) {return o->getNazov().find(oContains) == -1 ? false : true; });

    for (Obec* ob : vyfiltrovaneObce2)
    {
        cout << *ob;
    }
    cout << vyfiltrovaneObce2.size();
    cout << "\n--------------------------\n";

    cout << "Koniec\n";
}