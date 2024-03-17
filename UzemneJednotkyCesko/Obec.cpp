#include "Obec.h"
#include "Obec.h"
#include <iostream>
#include <iomanip>

#define space_for_KOD 6
#define space_for_NAZOV 30
#define space_for_TYP_OBCE 12
#define space_for_KATAST_VYMERA 9
#define space_for_POCET_OBYV 9



using namespace std;

ostream& operator<<(ostream& os, const Obec& obec)
{
    os << obec.kod << " | " << left << setw(space_for_NAZOV) << obec.nazov << " | " << setw(space_for_TYP_OBCE) << obec.typObce;
    os << " | " << setw(space_for_KATAST_VYMERA) << obec.katastralnaVymera << "ha | " << setw(space_for_POCET_OBYV) << obec.pocetObyvatelovCelkom;
    os << " | " << setw(space_for_POCET_OBYV) << obec.pocetObyvatelov0az14 << " | " << setw(space_for_POCET_OBYV) << obec.pocetObyvatelov65aViac;
    os << " | " << parseKanalizaciaToStr(obec.kanalizacia) << " | " << (obec.vodovod == true ? "ano" : "nie") << " | " << (obec.plynofikacia == true ? "ano" : "nie") << "  |";
    os << endl;
    return os;
}

string parseKanalizaciaToStr(const Kanalizacia& kanalizacia)
{
    string toRet;

    switch (kanalizacia)
    {
    case ano:
        toRet = "áno";
        break;
    case nie:
        toRet = "nie";
        break;
    case COV:
        toRet = "ČOV";
        break;
    default:
        toRet = "unknow";
    }

    return toRet;
}

void Obec::vypisHlavicku()
{
    for (int i = 0; i < space_for_KOD+3+space_for_NAZOV+3+space_for_TYP_OBCE+3+space_for_KATAST_VYMERA+3+(3*space_for_KATAST_VYMERA)+9+3+3+3+3+3+3+1; i++)
    {
        cout << '-';
    }
    cout << '|' << endl;
    cout << "  kod  |              nazov             |   typ obce   | kat. vymera | poc. obyv | obyv 0-14 | obyv 65+  | kan | vod | plyn |" << endl;
    //for (int i = 0; i < space_for_KOD + 3 + space_for_NAZOV + 3 + space_for_TYP_OBCE + 3 + space_for_KATAST_VYMERA + 3 + (3 * space_for_KATAST_VYMERA) + 9 + 3 + 3 + 3 + 3 + 3 + 3; i++)
    //{
    //    cout << '-';
    //}
    cout << right << setfill('-') << setw(space_for_KOD+2) << '+' << setw(space_for_NAZOV+3) << '+' << setw(space_for_TYP_OBCE+3) << '+';
    cout << setw(space_for_KATAST_VYMERA + 5) << '+' << setw(space_for_POCET_OBYV+3) << '+' << setw(space_for_POCET_OBYV + 3) << '+';
    cout << setw(space_for_POCET_OBYV + 3) << '+' << "----+------+------|";
    cout << setfill(' ') << endl;
}
