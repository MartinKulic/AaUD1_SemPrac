#include <iostream>
#include <string>
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include "IGUI.h"
#include "Zadanie1/GUI1.h"
#include "Zadanie2/GUI2.h"
#include "Zadanie3/GUI3.h"
#include "Zadanie4/GUI4.h"


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
            IGUI* gui;
            try {
                gui = new GUI4(argv[1]);
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