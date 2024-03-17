#include "UzemnaJednotka.h"
#include <iostream>
#include <iomanip>

using namespace std;
ostream& operator<<(ostream& os, const UzemnaJednotka& uj)
{
	switch (uj.typUzemia)
	{
	case kraj:
		os << "K~-~-~{ ~"<< setw(30) << uj.nazov << " ~ }~-~-~ " << uj.kod << endl;
		break;
	case soorp:
		os << "o-~-~-<~ " << left << setw(20) << uj.nazov << "~>-~-~-" << uj.kod << endl;
		break;
	default:
		os << uj.typUzemia << "\t" << uj.nazov << " " << uj.kod;
		break;
	}
	return os;
}
