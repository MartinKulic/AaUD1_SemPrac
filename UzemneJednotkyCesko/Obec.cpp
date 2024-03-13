#include "Obec.h"
#include "Obec.h"
#include <iostream>
#include <iomanip>

using namespace std;

ostream& operator<<(ostream& os, const Obec& obec)
{
    os << obec.kod << " | " << left << setw(12) << obec.nazov << " |typObce: " << setw(6) << obec.typObce << " |katVymera: " << setw(6) << obec.katastralnaVymera << "ha |pocOb: " << setw(6) << obec.pocetObyvatelovCelkom << " | pocOb0az14: " << setw(6) << obec.pocetObyvatelov0az14 << " | pocOb65+: " << setw(6) << obec.pocetObyvatelov65aViac << " |kan: " << parseKanalizaciaToStr(obec.kanalizacia) << " |vod: " << (obec.vodovod == true ? "ano" : "nie") << " |ply: " << (obec.plynofikacia == true ? "ano" : "nie") << endl;
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
        toRet = "ÈOV";
        break;
    default:
        toRet = "unknow";
    }

    return toRet;
}

