#include "UzemnaJednotka.h"
#include <iostream>
#include <iomanip>

using namespace std;
ostream& operator<<(ostream& os, const UzemnaJednotka& uj)
{
	switch (uj.typUzemia)
	{
	case kraj:
		os << " KRAJ - " << uj.kod << " - " << setw(30) << uj.nazov << endl;
		break;
	case soorp:
		os << "   OKRES - " << uj.kod << " ~ " << left << setw(30) << uj.nazov << endl;
		break;
	default:
		os << "      " << uj.kod << " " <<  uj.nazov  << endl; //<< uj.typUzemia;
		break;
	}
	return os;
}

bool UzemnaJednotka::nazovStartsWith(const std::string& predloha)
{
	for (int i = 0; i < predloha.length();i++) {
		if (predloha[i] != this->nazov[i]) {
			return false;
		}
	}
	return true;
}

bool UzemnaJednotka::nazovContains(const std::string& predloha)
{
	return this->nazov.find(predloha) != -1;
}

bool UzemnaJednotka::hasType(TypUzemia predloha)
{
	return this->typUzemia == predloha;
}
