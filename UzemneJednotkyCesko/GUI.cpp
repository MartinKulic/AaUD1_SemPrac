#include <iostream>
#include <Windows.h>
#include <mmsystem.h>

#include "GUI.h"
#include "Nacitavac.h"

#pragma comment(lib,"winmm.lib")


#define WIDTH_OF_WINDOW 1300

using namespace std;

void GUI::printError(errorType et, std::string msg="")
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    switch (et)
    {
    case VseobecnyHelp:
        SetConsoleTextAttribute(handle, 15);
        //cout << msg << "\n";
        cout << "Rozpoznané príkazy majú nasledovný formát:\n";
        cout << "  Druh vyh¾adávania   Èo je vyh¾adávané   Kde sa vyh¾adáva:\n";
        cout << "\t* o (obsahuje) h¾adaný reazec ob/ok/kr - napr. o nad ob -> vypíše všetky obce obsahujúce \"nad\" vo svojom nazve\n";
        cout << "\t* z (zaèína na) h¾adaný reazec ob/ok/kr - napr. z Èe ok -> vypísš všetky okrasy zaèínajúce na \"Èe\"\n";
        cout << "\t* e pre ukoncenie\n";
        SetConsoleTextAttribute(handle, 113);
        cout << "Príkazy sa zadávajú postupne a potvrdzujú Enterom\n";
        SetConsoleTextAttribute(handle, 15);
        cout << "Vyhladávanie je case sensitiv\n";
        break;
    case nespravneVstupnePar:
        SetConsoleTextAttribute(handle, 12);
        cout << "\nParameter: \" ";
        SetConsoleTextAttribute(handle, 79);
        cout << msg;
        SetConsoleTextAttribute(handle, 12);
        cout << " \"Nerozpoznany.\n";
        SetConsoleTextAttribute(handle, 64);
        cout << "Použi len tieto príkazy\n";
        GUI::printError(VseobecnyHelp);
        SetConsoleTextAttribute(handle, 15);

        break;
    default:
        break;
    }
}

COORD GUI::getCursorPos()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(handle, &csbi);
    return csbi.dwCursorPosition;
}

void GUI::setCursorPos(COORD newpos)
{
    SetConsoleCursorPosition(handle, newpos);
}




GUI::GUI(const char vstupnySubor[])
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    HWND consloleWindow = GetConsoleWindow();
    RECT rectangle;
    GetWindowRect(consloleWindow, &rectangle);

    MoveWindow(consloleWindow, rectangle.left, rectangle.top, WIDTH_OF_WINDOW, 600, TRUE);

	//otestuj vstupny sub
    
	this->nacitavanie(vstupnySubor);
    //PlaySound(TEXT("videoplayback.wav"), NULL, SND_ASYNC);

}

void GUI::Progressed(int by)
{
    cout << '*';
}

GUI::~GUI()
{
    for (Obec* o : obce)
    {
        delete o;
    }
    for (UzemnaJednotka* u : okresy)
    {
        delete u;
    }
    for (UzemnaJednotka* u : kraje)
    {
        delete u;
    }
}


void GUI::nacitavanie(const char vstupnySubor[])
{
    cout << "Nacitavanie: ";
    Nacitavac::Nacitaj(vstupnySubor, kraje, okresy, obce, this, 90);

    SetConsoleTextAttribute(handle, 32);

    cout << "\nNaèítanie prebehlo úspešne:\n" << "\n\tKraje: " << kraje.size() << "\n\n\tSORP:  " << okresy.size() << "\n\n\tObce:  " << obce.size(); 
    cout << endl;
    SetConsoleTextAttribute(handle, 8);

    for (int i = 0; i < 100; i++)
    {
        cout << '=';
    }
    
    SetConsoleTextAttribute(handle, 14);
    cout << "\nDrahý uživate¾, gratulujeme k úspešnému spusteniu našeho super duper programu. V tento moment uspešne prebehlo naèitanie vstupných údajou zo súboru, ktorý si zadal ako vstupný parameter.\n";
    cout << "Program slúži na vyfiltrovanie zoznamu krajou, okresou(SORP) alebo obcí. Prosím pokraèuj inštrukciami nižšie\n";

    SetConsoleTextAttribute(handle, 15);
}

    

void GUI::startLoop()
{
    GUI::printError(VseobecnyHelp, "");

    while (1)
    {
        string operacia;
        string param;
        string kde;

        cout << "o = obsahuje, z = zacina na\n";
        cout << "Zvol operaciu (o/z): ";
        cin >> operacia;

        if (operacia == "e")
        {
            break;
        }
        else if (operacia != "o" && operacia != "z")
        {
            GUI::printError(nespravneVstupnePar, operacia);
            continue;
        }
        cout << "Zadaj h¾adaný reazec\n";
        
        cin >> ws;
        getline(cin, param);

        cout << "ob = obece, ok = okresy, kr = kraje\n";
        cout << "Nad krorým po¾om: ";
        cin >> kde;

        if (kde=="ob")
        {
            this->filtruj<vector<Obec*>, Obec>(operacia, param, &obce);

        }
        else if (kde == "ok")
        {
            this->filtruj<vector<UzemnaJednotka*>, UzemnaJednotka>(operacia, param, &okresy);
        }
        else if (kde == "kr")
        {
            this->filtruj<vector<UzemnaJednotka*>, UzemnaJednotka>(operacia, param, &kraje);
        }
        else
        {
            GUI::printError(nespravneVstupnePar, "kde");
        }
                
    }
}


