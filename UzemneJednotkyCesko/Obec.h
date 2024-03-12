#pragma once
#include <string>
#include "UzemnaJednotka.h"

enum Kanalizacia { // COV = ÈOV = èistièka odpadových vôd
	nie, ano, COV, nezname
};

using namespace std;
class Obec : public UzemnaJednotka
{
private:
	string typObce = "nezadané";
	Kanalizacia kanalizacia = nezname;
	unsigned int katastralnaVymera = 0;
	unsigned int pocetObyvatelov = 0;
	bool vodovod = false;
	bool plynofikacia = false;


public:
	Obec(string nnazov, string nkod, string ntyp, unsigned int nKatastralnaVymera, unsigned int nPocetObyvatelov, Kanalizacia nKanalizacia, bool nVodovod, bool nPlyn) :
		UzemnaJednotka(nnazov, nkod, TypUzemia(obec)), typObce(ntyp), kanalizacia(nKanalizacia), katastralnaVymera(nKatastralnaVymera), pocetObyvatelov(nPocetObyvatelov),
			vodovod(nVodovod), plynofikacia(nPlyn) {};
	~Obec();


	friend ostream& operator<<(ostream& os, const Obec& obec);
};
	string parseKanalizaciaToStr(const Kanalizacia& kanalizacia);

