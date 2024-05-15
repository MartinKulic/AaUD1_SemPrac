#include <iostream>
#include <Windows.h>

#include "GUI1.h"
#include "Nacitavac1.h"



#define WIDTH_OF_WINDOW 1300


    using namespace std;


    void GUI1::printError(errorType et, std::string msg = "")
    {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (et)
        {
        case VseobecnyHelp:
            SetConsoleTextAttribute(handle, 15);
            //cout << msg << "\n";
            cout << "Rozpoznané príkazy majú nasledovný formát:\n";
            cout << "  Druh vyh¾adávania   Èo je vyh¾adávané   Kde sa vyh¾adáva:\n";
            cout << "\t* o (obsahuje) |> h¾adaný reazec |> ob/ok/kr - napr. o nad ob -> vypíše všetky obce obsahujúce \"nad\" vo svojom nazve\n";
            cout << "\t* z (zaèína na) |> h¾adaný reazec |> ob/ok/kr - napr. z Èe ok -> vypísš všetky okrasy zaèínajúce na \"Èe\"\n";
            cout << "\t* e -> ukoncenie\n";
            SetConsoleTextAttribute(handle, 113);
            cout << "Príkazy sa zadávajú postupne a potvrdzujú Enterom";
            SetConsoleTextAttribute(handle, 15);
            cout << "\nVyhladávanie je case sensitiv\n";
            break;
        case nespravneVstupnePar:
            SetConsoleTextAttribute(handle, 12);
            cout << "\nParameter: \" ";
            SetConsoleTextAttribute(handle, 79);
            cout << msg;
            SetConsoleTextAttribute(handle, 12);
            cout << " \"Nerozpoznany.";
            SetConsoleTextAttribute(handle, 64);
            cout << "\nPouži len tieto príkazy\n";
            GUI1::printError(VseobecnyHelp);
            SetConsoleTextAttribute(handle, 15);

            break;
        case nespravneSpustenie:
            IGUI::printError(nespravneSpustenie, msg);
            break;
        case chybaSoVstupnymSuborom:
            IGUI::printError(chybaSoVstupnymSuborom, msg);
            break;
        default:
            break;
        }
    }

    GUI1::GUI1(const char vstupnySubor[])
    {
        handle = GetStdHandle(STD_OUTPUT_HANDLE);

        HWND consloleWindow = GetConsoleWindow();
        RECT rectangle;
        GetWindowRect(consloleWindow, &rectangle);

        MoveWindow(consloleWindow, rectangle.left, rectangle.top, WIDTH_OF_WINDOW, 600, TRUE);

        this->nacitavanie(vstupnySubor);

        //-------------------------------
        // PLAYNG

        //vector<Obec*>* vysledok = new vector<Obec*>;

        //Algoritmus<Obec*> alg;
        ////alg.filtruj(obce.begin(), obce.end(), [](Obec* o)->bool {return o->nazovStartsWith("Pi"); }, *vysledok, [](vector<Obec*>& k, Obec* p)->void {k.push_back(p); });
        //alg.filtruj(obce.begin(), obce.end(), [](Obec* o)->bool {return o->nazovStartsWith("Pi"); }, [vysledok]( Obec* p)->void {vysledok->push_back(p); });

        //for (auto a = vysledok->begin(); a != vysledok->end(); a++) {
        //    cout << **a;
        //}
    }

    void GUI1::Progressed(int by)
    {
        cout << '*';
    }

    GUI1::~GUI1()
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


    void GUI1::nacitavanie(const char vstupnySubor[])
    {
        cout << "Nacitavanie: ";

        Nacitavac1::Nacitaj(vstupnySubor, kraje, okresy, obce, this, 90);


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



    void GUI1::startLoop()
    {
        GUI1::printError(VseobecnyHelp, "");

        while (1)
        {
            string operacia;
            string param;
            string kde;
            //string* pparam = &param;

            std::function<bool(UzemnaJednotka*)> predicat;


            cout << "o = obsahuje, z = zacina na\n";
            cout << "Zvol operaciu (o/z): ";
            cin >> operacia;

            if (operacia == "e")
            {
                break;
            }
            /*
            else if (operacia != "o" && operacia != "z")
            {
                GUI::printError(nespravneVstupnePar, operacia);
                continue;
            }*/
            switch (operacia.at(0))
            {
            case 'o':
                predicat = [&param](UzemnaJednotka* u)->bool {return u->nazovContains(param); };
                break;
            case 'z':
                predicat = [&param](UzemnaJednotka* u)->bool {return u->nazovStartsWith(param); };
                break;
            default:
            {
                GUI1::printError(nespravneVstupnePar, operacia);
                continue;
            }
            break;
            }

            cout << "Zadaj h¾adaný reazec\n";

            cin >> ws;
            getline(cin, param);

            cout << "ob = obece, ok = okresy, kr = kraje\n";
            cout << "Nad krorým po¾om: ";
            cin >> kde;

            /*switch (operacia.at(0))
            {
            case 'o':
                predicat = [param](UzemnaJednotka* u)->bool {u->nazovContains(param); };
                break;
            case 'z':
                predicat = [param](UzemnaJednotka* u)->bool {u->nazovStartsWith(param); };
            default:
                break;
            }*/

            std::vector<UzemnaJednotka*>* vysledok = new vector<UzemnaJednotka*>;
            Algoritmus <UzemnaJednotka*> alg;
            if (kde == "ob")
            {
                alg.filtruj(obce.begin(), obce.end(), predicat, [vysledok](Obec* o) {vysledok->push_back(o); });
            }
            else if (kde == "ok")
            {
                alg.filtruj(okresy.begin(), okresy.end(), predicat, [vysledok](UzemnaJednotka* o) {vysledok->push_back(o); });
            }
            else if (kde == "kr")
            {
                alg.filtruj(kraje.begin(), kraje.end(), predicat, [vysledok](UzemnaJednotka* o) {vysledok->push_back(o); });
            }
            else
            {
                GUI1::printError(nespravneVstupnePar, kde);
            }

            if (kde == "ob")
                Obec::vypisHlavicku();
            else
                UzemnaJednotka::vypisHlavicku();

            for (auto uj = vysledok->begin(); uj != vysledok->end(); uj++) {
                if ((*uj)->getType() == TypUzemia(obec))
                    cout << *(Obec*)*uj;
                else
                    cout << **uj;
            }

            SetConsoleTextAttribute(handle, 22);
            std::cout << "\nNajdenych " << vysledok->size() << " zhod\n";
            SetConsoleTextAttribute(handle, 9);
            std::cout << "\n====================================================================================================================================\n\n";
            SetConsoleTextAttribute(handle, 15);


            delete vysledok;
        }
    }



