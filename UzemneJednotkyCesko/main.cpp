#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

#include "Nacitavac.h"

using namespace std;
int main()
{
    SetConsoleOutputCP(1250);
    SetConsoleCP(1250);
    std::cout << "¾šèžýáíéúäôò¡A\n";


    std::vector<UzemnaJednotka*> kraje;
    std::vector<UzemnaJednotka*> okresy;
    std::vector<Obec*> obce;

    Nacitavac::Nacitaj("converted.csv", kraje, okresy, obce);

  /*  for (Obec* obec : obce) {
        cout << *obec;
    }*/
    for (UzemnaJednotka* okres : okresy)
    {
        cout << *okres;
    }
    for (UzemnaJednotka* kraj : kraje)
    {
        cout << *kraj;
    }
    cout << "Koniec\n";
}