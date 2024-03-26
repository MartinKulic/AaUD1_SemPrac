#include <iostream>
#include <Windows.h>

#include "GUI.h"
#include "Nacitavac.h"



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
        cout << "\t* o (obsahuje) |> h�adan� re�azec |> ob/ok/kr - napr. o nad ob -> vyp�e v�etky obce obsahuj�ce \"nad\" vo svojom nazve\n";
        cout << "\t* z (za��na na) |> h�adan� re�azec |> ob/ok/kr - napr. z �e ok -> vyp�s� v�etky okrasy za��naj�ce na \"�e\"\n";
        cout << "\t* e -> ukoncenie\n";
        SetConsoleTextAttribute(handle, 113);
        cout << "Pr�kazy sa zad�vaj� postupne a potvrdzuj� Enterom";
        SetConsoleTextAttribute(handle, 15);
        cout << "\nVyhlad�vanie je case sensitiv\n";
        break;
    case nespravneVstupnePar:
        SetConsoleTextAttribute(handle, 12);
        cout << "\nParameter: \" ";
        SetConsoleTextAttribute(handle, 79);
        cout << msg;
        SetConsoleTextAttribute(handle, 12);
        cout << " \"Nerozpoznany.";
        SetConsoleTextAttribute(handle, 64);
        cout << "\nPou�i len tieto pr�kazy\n";
        GUI::printError(VseobecnyHelp);
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

GUI::GUI(const char vstupnySubor[])
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    
    HWND consloleWindow = GetConsoleWindow();
    RECT rectangle;
    GetWindowRect(consloleWindow, &rectangle);

    MoveWindow(consloleWindow, rectangle.left, rectangle.top, WIDTH_OF_WINDOW, 600, TRUE);
    
	this->nacitavanie(vstupnySubor);
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

    cout << "\nNa��tanie prebehlo �spe�ne:\n" << "\n\tKraje: " << kraje.size() << "\n\n\tSORP:  " << okresy.size() << "\n\n\tObce:  " << obce.size(); 
    cout << endl;
    SetConsoleTextAttribute(handle, 8);

    for (int i = 0; i < 100; i++)
    {
        cout << '=';
    }
    
    SetConsoleTextAttribute(handle, 14);
    cout << "\nDrah� u�ivate�, gratulujeme k �spe�n�mu spusteniu na�eho super duper programu. V tento moment uspe�ne prebehlo na�itanie vstupn�ch �dajou zo s�boru, ktor� si zadal ako vstupn� parameter.\n";
    cout << "Program sl��i na vyfiltrovanie zoznamu krajou, okresou(SORP) alebo obc�. Pros�m pokra�uj in�trukciami ni��ie\n";

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
        cout << "Zadaj h�adan� re�azec\n";
        
        cin >> ws;
        getline(cin, param);

        cout << "ob = obece, ok = okresy, kr = kraje\n";
        cout << "Nad kror�m po�om: ";
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
            GUI::printError(nespravneVstupnePar, kde);
        }
                
    }
}


