#pragma once
#include <string>
#include <vector>

enum TypUzemia { //SOORP = ekvivalent okresu
	kraj, soorp, obec, undef
};

using namespace std;


class UzemnaJednotka
{
protected:
	string nazov;
	string kod;
private:
	TypUzemia typUzemia = undef;


public:

	UzemnaJednotka(string nnazov, string nkod, TypUzemia ntypU) : nazov(nnazov), kod(nkod), typUzemia(ntypU)
	{};

	friend ostream& operator<<(ostream& os, const UzemnaJednotka& obec);
	string getKod() { return this->kod; };
	string getNazov() { return this->nazov; };
	static void vypisHlavicku() { ; };
};



