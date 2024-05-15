#include <iostream>
#include <string>
#include <Windows.h>

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include "GUI.h"
#include "GUIZadanie2.h"
#include "Nacitavac.h"
//#include "Algoritmus.h"

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
            GUI gui(argv[1]);
            gui.startLoop();
        }
       
    }
    _CrtDumpMemoryLeaks();
}