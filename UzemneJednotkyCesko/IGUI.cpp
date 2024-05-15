#include "IGUI.h"
#include <iostream>
#include<string>
#include <Windows.h>

using namespace std;
void IGUI::printError(errorType et, std::string msg = "")
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (et)
    {
    case VseobecnyHelp:
        SetConsoleTextAttribute(handle, 15);
        //cout << msg << "\n";
        cout << "Potomkovia impementuju vlasne helpy.";
        break;
    case nespravneVstupnePar:
        SetConsoleTextAttribute(handle, 12);
        cout << "\nNespravne Vstupne Parametre. Rodic nevie poskytnut viac inforamacii";
        SetConsoleTextAttribute(handle, 15);

        break;
    case nespravneSpustenie:
        SetConsoleTextAttribute(handle, 64);
        cout << msg << "\nProgram nama dostator parametrou.";
        SetConsoleTextAttribute(handle, 12);
        cout << "\nProsim uistite sa, ze ste pri spustani zadali ustupny subor.\n";
        SetConsoleTextAttribute(handle, 15);
        break;
    case chybaSoVstupnymSuborom:
        SetConsoleTextAttribute(handle, 64);
        cout << msg << "\nVstupny subor sa nenasiel, neda sa otvorit alebo jeho format je nespravny.";
        SetConsoleTextAttribute(handle, 12);
        cout << "\nProsim uistite sa, ze subor cesta k suboru je spravna a jeho format je zrozumitelny pre tento program.\n";
        SetConsoleTextAttribute(handle, 15);
        break;
    default:
        break;
    }
}
