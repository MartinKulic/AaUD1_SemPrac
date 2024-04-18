#include <iostream>
#include <string>
#include <vector>
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
            try
            {
                //GUI gui(argv[1]);
                //gui.startLoop();
                GUIZadanie2 gui(argv[1]);
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