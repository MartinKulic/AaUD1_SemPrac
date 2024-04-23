#include <iostream>
#include <string>
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "GUI.h"
#include "GUIZadanie2.h"
#include "Nacitavac.h"
#include "Algoritmus.h"

using namespace std;
int main(int argc, char* argv[])
{
    {
        SetConsoleOutputCP(1250);
        SetConsoleCP(1250);

        if (argc < 2) {
            GUI::printError(nespravneSpustenie, "Malo parametrov");
        }
        else
        {
            string zadanie;
            cout << "Vyber zadanie 1/2: ";
            cin >> zadanie;
            try
            {
                if (zadanie == "1")
                {
                    GUI gui(argv[1]);
                    gui.startLoop();
                }
                else if (zadanie == "2")
                {
                    GUIZadanie2 gui(argv[1]);
                    gui.startLoop();
                }
                else
                {
                    cout << "\n Nezname parametre. Reštertuj program a skjs znova.\n";
                }
            }
            catch (problemZoSuborumExeption e)
            {
                GUI::printError(chybaSoVstupnymSuborom, e.getMsg());
            }
            catch (std::invalid_argument e)
            {
                GUI::printError(chybaSoVstupnymSuborom, e.what());
            }
        }
       
    }
    _CrtDumpMemoryLeaks();
}