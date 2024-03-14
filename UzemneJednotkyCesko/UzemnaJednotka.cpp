#include "UzemnaJednotka.h"
#include <iostream>

using namespace std;
ostream& operator<<(ostream& os, const UzemnaJednotka& uj)
{
	switch (uj.typUzemia)
	{
	case kraj:
		os << "KKKKKKKK-~-~-~-~-~{ ~" << uj.nazov << "~ }~-~-~-~-~-KKKKKKKK " << uj.kod << endl;
		break;
	case soorp:
		os << "oooooooo-~-~-~-~-~< ~" << uj.nazov << "~ >~-~-~-~-~-oooooooo " << uj.kod << endl;
		break;
	default:
		os << uj.typUzemia << "\t" << uj.nazov << " " << uj.kod;
		break;
	}
	return os;
}
