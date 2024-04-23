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
