#include <iostream>
#include <string>
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "IGUI.h"
#include "GUI1.h"

//#include "Algoritmus.h"

using namespace std;
int main(int argc, char* argv[])
{
    {
        SetConsoleOutputCP(1250);
        SetConsoleCP(1250);

        if (argc < 2) {
            IGUI::printError(nespravneSpustenie, "Malo parametrov");
        }
        else
        {
            try {
                IGUI* gui;
                gui = new GUI1(argv[1]);
                gui->startLoop();
                delete gui;
            }
            catch (problemZoSuborumExeption e)
            {
                IGUI::printError(chybaSoVstupnymSuborom, e.getMsg());
            }
            catch (std::invalid_argument e)
            {
                IGUI::printError(chybaSoVstupnymSuborom, e.what());
            }
        }
       
    }
    _CrtDumpMemoryLeaks();
}