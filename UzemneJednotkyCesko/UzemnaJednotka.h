#pragma once
#include <string>
#include <vector>

enum TypUzemia { //SOORP = ekvivalent okresu
	kraj, soorp, obec, undef
};

//using namespace std;


class UzemnaJednotka
{
protected:
	std::string nazov;
	std::string kod;
private:
	TypUzemia typUzemia = undef;


public:

	UzemnaJednotka(std::string nnazov, std::string nkod, TypUzemia ntypU) : nazov(nnazov), kod(nkod), typUzemia(ntypU)
	{};

	friend std::ostream& operator<<(std::ostream& os, const UzemnaJednotka& obec);
	std::string getKod() { return this->kod; };
	std::string getNazov() { return this->nazov; };
	static void vypisHlavicku() { ; };
};



