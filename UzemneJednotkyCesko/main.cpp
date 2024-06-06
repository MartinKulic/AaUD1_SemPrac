#include <iostream>
#include <string>
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <locale>
#include <string>

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
        std::locale::global(std::locale("Slovak_Slovakia.1250"));


        if (argc < 2) {
            IGUI::printError(nespravneSpustenie, "Malo parametrov");
        }
        else
        {
            cout << "Vyber zadanie (1/2/3/4): ";
            char volba;
            cin >> volba;
          
            IGUI* gui;
            try {

                switch (volba)
                {
                case '1':
                    gui = new GUI1(argv[1]);
                    break;
                case '2':
                    gui = new GUI2(argv[1]);
                    break;
                case '3':
                    gui = new GUI3(argv[1]);
                    break;
                case '4':
                    gui = new GUI4(argv[1]);
                    break;
                default:
                    cout << "--!!!--> Nerozpoznaný argument. Reštartuj program a skus znova. <--!!!--\n";
                    return 666;
                    break;
                }

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