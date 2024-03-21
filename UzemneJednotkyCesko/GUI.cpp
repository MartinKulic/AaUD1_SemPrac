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
        cout << "Rozpoznan� pr�kazy maj� nasledovn� form�t:\n";
        cout << "  Druh vyh�ad�vania   �o je vyh�ad�van�   Kde sa vyh�ad�va:\n";
        cout << "\t* o (obsahuje) h�adan� re�azec ob/ok/kr - napr. o nad ob -> vyp�e v�etky obce obsahuj�ce \"nad\" vo svojom nazve\n";
        cout << "\t* z (za��na na) h�adan� re�azec ob/ok/kr - napr. z �e ok -> vyp�s� v�etky okrasy za��naj�ce na \"�e\"\n";
        cout << "\t* e pre ukoncenie\n";
        SetConsoleTextAttribute(handle, 113);
        cout << "Pr�kazy sa zad�vaj� postupne a potvrdzuj� Enterom\n";
        SetConsoleTextAttribute(handle, 15);
        cout << "Vyhlad�vanie je case sensitiv\n";
        break;
    case nespravneVstupnePar:
        SetConsoleTextAttribute(handle, 12);
        cout << "\nParameter: \" ";
        SetConsoleTextAttribute(handle, 79);
        cout << msg;
        SetConsoleTextAttribute(handle, 12);
        cout << " \"Nerozpoznany.\n";
        SetConsoleTextAttribute(handle, 64);
        cout << "Pou�i len tieto pr�kazy\n";
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
    PlaySound(TEXT("videoplayback.wav"), NULL, SND_ASYNC);

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
    string caption = "Nacitavanie: ";

    CONSOLE_SCREEN_BUFFER_INFO buffinfo;
    GetConsoleScreenBufferInfo(handle, &buffinfo);
    int totalProgressBarLen = buffinfo.srWindow.Right - buffinfo.srWindow.Left + 1 - caption.size()-8;

    GUIProgressBar progBar(this, caption, totalProgressBarLen);

    Nacitavac::Nacitaj(vstupnySubor, kraje, okresy, obce, &progBar, 90);

    SetConsoleTextAttribute(handle, 32);

    cout << "Na��tanie prebehlo �spe�ne:\n" << "\n\tKraje: " << kraje.size() << "\n\n\tSORP:  " << okresy.size() << "\n\n\tObce:  " << obce.size();

    SetConsoleTextAttribute(handle, 62);
    COORD pos = this->getCursorPos();
    pos.X += 20;
    pos.Y -= 6;
    this->vykreskyFiggle("artCUJ.txt", pos);
   
    cout << endl;
    SetConsoleTextAttribute(handle, 8);
    for (int i = 0; i < totalProgressBarLen + caption.size()+3; i++)
    {
        cout << '=';
    }
    pos = this->getCursorPos();
    cout << 'o';
    int riadokPokracovanie = pos.Y+2;
    pos.Y--;
    for (; pos.Y > 0; pos.Y--)
    {
        this->setCursorPos(pos);
        cout << "||";

    }
    pos.X = 0;
    pos.Y = riadokPokracovanie;
    this->setCursorPos(pos);

    SetConsoleTextAttribute(handle, 14);
    cout << "Drah� u�ivate�, gratulujeme k �spe�n�mu spusteniu na�eho super duper programu. V tento moment uspe�ne prebehlo na�itanie vstupn�ch �dajou zo s�boru, ktor� si zadal ako vstupn� parameter.\n";
    cout << "Program sl��i na vyfiltrovanie zoznamu krajou, okresou(SORP) alebo obc�. Pros�m pokra�uj in�trukciami ni��ie\n";

    SetConsoleTextAttribute(handle, 15);
}


void GUI::vykreskyFiggle(const char pothToFile[], COORD startPos)
{
    Nacitavac nac(pothToFile);
    string toPrint;
    while (nac.dajRiadok(toPrint))
    {
        this->setCursorPos(startPos);
        cout << toPrint;
        startPos.Y++;
    }
}
    

void GUI::startLoop()
{
    //SetConsoleMode(handle, ENABLE_LINE_INPUT);
    string druhVyhladavanie;
    string vyhladavanyRetazec;
    string kde;
    this->printError(VseobecnyHelp, "");
    COORD pos;;
    while (1)
    {
        cout << "oper�cia> ";
        pos = this->getCursorPos();
        cin >> druhVyhladavanie;
        pos.X++;
        this->setCursorPos(pos);
        if (druhVyhladavanie == "e")
            break;
        else if (druhVyhladavanie == "o")
        {
            cout << "bsahuje ";
        }
        else if(druhVyhladavanie == "z")
        {
            cout << "acina ";
        }
        else
        {
            string msg;
            msg += druhVyhladavanie;
            GUI::printError(nespravneVstupnePar, msg);
            continue;
        }
        //---------------------------------------------------------
        pos = this->getCursorPos();
        cout << "(�o/na) ";

        cin >> vyhladavanyRetazec;

        this->setCursorPos(pos);      
        for (int i = 0; i < 8 + vyhladavanyRetazec.size(); i++) {
            cout << ' ';
        }
        
        this->setCursorPos(pos);
        cout << '\"';
        cout << vyhladavanyRetazec;
        cout << "\" v ";
        pos = this->getCursorPos();
        //---------------------------------------------------------
        cin >> kde;
        if (kde != "kr" && kde != "ok" && kde != "ob")
        {
            GUI::printError(nespravneVstupnePar, kde);
            continue;
        }
        //---------------------------------------------------------

        pos.X += 2;
        this->setCursorPos(pos);
        if (kde == "ob")
        {
            cout << "ce\n";
            vector<Obec*> vyfiltrovaneObce;
            Algoritmus<vector<Obec*>>::filtruj(obce.begin(), obce.end(), vyfiltrovaneObce, GUI::getFuncion<Obec>(druhVyhladavanie, vyhladavanyRetazec));

            Obec::vypisHlavicku();
            for (Obec* o : vyfiltrovaneObce)
            {
                cout << *o;
            }
            cout << "\n\nNajden�ch: " << vyfiltrovaneObce.size() << " zh�d";
        }
        else if (kde == "kr")
        {
            cout << "aje\n";
            this->filtrujUJ(druhVyhladavanie, vyhladavanyRetazec, kraje);
        }
        else
        {
            cout << "resy\n";
            this->filtrujUJ(druhVyhladavanie, vyhladavanyRetazec, okresy);
        }
        
        cout << "\n\n====================================================================================================\n\n\n";
        }
}
void GUI::filtrujUJ(std::string druhVyhladavanie, string vyhladavanyRetazec, std::vector<UzemnaJednotka*>& zdroj)
{
    vector<UzemnaJednotka*> vyfiltrovaneUJ;
    Algoritmus<vector<UzemnaJednotka*>>::filtruj(zdroj.begin(), zdroj.end(), vyfiltrovaneUJ, GUI::getFuncion<UzemnaJednotka>(druhVyhladavanie, vyhladavanyRetazec));
    
    for (UzemnaJednotka* u : vyfiltrovaneUJ)
    {
        cout << *u;
    }
    cout << "\n\nNajden�ch: " << vyfiltrovaneUJ.size() << " zh�d";
}



//---------------------------------------------------------------
GUIProgressBar::GUIProgressBar(GUI* ngui, string caption, int ntotalLength)
{
    gui = ngui;
    SetConsoleTextAttribute(gui->getHandle(), 11);
    totalLength = ntotalLength;    
    cout << caption;
    SetConsoleTextAttribute(gui->getHandle(), 8);
    cout << '{';
    progressedPartOfProgressBar = gui->getCursorPos();
    progressedPartOfProgressBar.X++;


    for (int i = 0; i < totalLength; i++) {
        cout << '-';
    }

    endOfProggressBar = gui->getCursorPos();
    endOfProggressBar.X--;
    cout << '}';
}

void GUIProgressBar::Progressed(int by)
{
    int moveBy = (by * totalLength) / 100;

    for (int i = 0; i < moveBy; i++)
    {
        if (progressedPartOfProgressBar.X + moveBy >= endOfProggressBar.X)
            continue;

        gui->setCursorPos(progressedPartOfProgressBar);
        cout << '\b' << '*';
        progressedPartOfProgressBar.X++;
    }

}

void GUIProgressBar::Finished()
{
    gui->setCursorPos(endOfProggressBar);
    int duration = endOfProggressBar.X - progressedPartOfProgressBar.X+1;

    for (int i = 0; i < duration; i++)
    {
        cout << '\b';
    }

    for (int i = 0; i < duration+1; i++)
    {
        cout << '*';
    }
    cout << endl;
}
