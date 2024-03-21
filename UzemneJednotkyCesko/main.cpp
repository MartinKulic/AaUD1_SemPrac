#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "GUI.h"
#include "Nacitavac.h"
#include "Algoritmus.h"

using namespace std;
int main(int argc, char* argv[])
{
    {
        SetConsoleOutputCP(1250);
        SetConsoleCP(1250);

        if (argc < 1) {
            GUI::printError(nespravneVstupnePar, "Malo parametrov");
        }
        else
        {
            GUI gui(argv[1]);
            gui.startLoop();
        }

        //std::vector<UzemnaJednotka*> kraje;
        //std::vector<UzemnaJednotka*> okresy;
        //std::vector<Obec*> obce;

        //Nacitavac::Nacitaj("converted.csv", kraje, okresy, obce);

        ////----------------UKAZKY-----------------------------------------------------

        //cout << "\n----------------\n";

        //std::vector<UzemnaJednotka*> vyfiltrovaneKraje;
        //Algoritmus<vector<UzemnaJednotka*>> alg;

        //char obsahuje[] = "CKÝ";
        //alg.filtruj(kraje.begin(), kraje.end(), vyfiltrovaneKraje, [obsahuje](UzemnaJednotka* u) { return u->getNazov().find(obsahuje) == -1 ? false : true; });

        //for (UzemnaJednotka* uj : vyfiltrovaneKraje)
        //{
        //    cout << *uj;
        //}
        //cout << vyfiltrovaneKraje.size();
        //cout << "\n--------------------------\n";
        //
        ////-----------------------------------------------
        //vector<UzemnaJednotka*> vyfiltrovaneOkresy;
        //char zacinaNa[] = "Ho";
        //Algoritmus<vector<UzemnaJednotka*>>::filtruj(okresy.begin(), okresy.end(), vyfiltrovaneOkresy, [zacinaNa](UzemnaJednotka* u) {return u->getNazov().find(zacinaNa) == 0 ? true : false; });

        //for (UzemnaJednotka* uj : vyfiltrovaneOkresy)
        //{
        //    cout << *uj;
        //}
        //cout << vyfiltrovaneOkresy.size();
        //cout << "\n--------------------------\n";
        //
        ////-----------------------------------------------
        //vector<Obec*> vyfiltrovaneObce1;
        //char oZacinaNa[] = "Zi";
        //Algoritmus<vector<Obec*>>::filtruj(obce.begin(), obce.end(), vyfiltrovaneObce1, [oZacinaNa](Obec* o) {return o->getNazov().find(oZacinaNa) == 0 ? true : false; });

        //Obec::vypisHlavicku();
        //for (Obec* ob : vyfiltrovaneObce1)
        //{
        //    cout << *ob;
        //}
        //cout << vyfiltrovaneObce1.size();
        //cout << "\n--------------------------\n";

        ////-----------------------------------------------
        //vector<Obec*> vyfiltrovaneObce2;
        //char oObsahuje[] = "nad";
        //Algoritmus<vector<Obec*>>::filtruj(obce.begin(), obce.end(), vyfiltrovaneObce2, [oObsahuje](Obec* o) {return o->getNazov().find(oObsahuje) == -1 ? false : true; });

        //Obec::vypisHlavicku();
        //for (Obec* ob : vyfiltrovaneObce2)
        //{
        //    cout << *ob;
        //}
        //cout << vyfiltrovaneObce2.size();
        //cout << "\n--------------------------\n";

        ////-----------------------------------------------
        //vector<Obec*> vyfObce3;
        //char oZacinaNa2[] = "Kan";
        //Algoritmus<vector<Obec*>>::filtruj(obce.begin(), obce.end(), vyfObce3, [oZacinaNa2](Obec* o) {return o->getNazov().find(oZacinaNa2) == 0; });
        //
        //Obec::vypisHlavicku();
        //for (Obec* o : vyfObce3)
        //{
        //    cout << *o;
        //}
        //cout << vyfObce3.size();

        ////------------------------------------------------
        //vector<Obec*> vyfObce4;
        //char obsahuje2 = 'ø';
        //Algoritmus<vector<Obec*>>::filtruj(obce.begin(), obce.end(), vyfObce4, [obsahuje2](Obec* o) {return o->getNazov().find(obsahuje2) != -1; });
        //cout << vyfObce4.size();
       
        //obsahuje2 = 'Ø';
        //Algoritmus<vector<Obec*>>::filtruj(obce.begin(), obce.end(), vyfObce4, [obsahuje2](Obec* o) {return o->getNazov().find(obsahuje2) != -1; });

        //Obec::vypisHlavicku();
        //for (Obec* o : vyfObce4)
        //{
        //    cout << *o;
        //}
        //cout << vyfObce4.size();
        //// Destrucotrs-------------------
        //for (Obec* o : obce)
        //{
        //    delete o;
        //}
        //for (UzemnaJednotka* u : okresy)
        //{
        //    delete u;
        //}
        //for (UzemnaJednotka* u : kraje)
        //{
        //    delete u;
        //}

        //cout << "Koniec\n";
    }
    _CrtDumpMemoryLeaks();
}