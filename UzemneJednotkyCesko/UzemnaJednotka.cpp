#include "UzemnaJednotka.h"
#include <iostream>
#include <iomanip>
#include "Zadanie4/GUI4.h" 

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

int UzemnaJednotka::countVowel()
{
	this->consonantCount = 0;

	char* nzv = this->nazov.data();
	char* next;
	for (char* current = nzv; *current != '\0'; current++) {
		
		if (*current == 'i') // ia ie iu
		{
			next = current + 1;
			bool je = false;
			for (int i = 0; i < 3; i++) {
				if (*next == GUI4::Vowels[i]) {
					this->consonantCount++;
					je = true;
					break;
				}
			}
			if (je) {
				current++;
				continue;
			}
			else {
				this->consonantCount++;
				continue;
			}
		}
		else {
			for (const char spoluhlaska : GUI4::Vowels) {
				if (*current == spoluhlaska) {
					this->consonantCount++;
					break;
				}
			}
		}
	}
	return this->consonantCount;
}

int UzemnaJednotka::countConsonant()
{
	this->consonantCount = 0;

	char* nzv = this->nazov.data();
	char* next;
	for (char* current = nzv; *current != '\0'; current++) {
		next = current + 1;

		if (*current == 'c' || *current == 'C' ) // ch
		{
			if (*next == 'h') {
				current++;
			}
			this->consonantCount++;
			continue;
		}
		if (*current == 'd' || *current == 'D') { // dz
			if (*next == 'z' || *next == 'ž') {
				current++;
			}
			this->consonantCount++;
			continue;
		}
		
		for (const char spoluhlaska : GUI4::Consonant) {
			if (*current == spoluhlaska) {
				this->consonantCount++;
				break;
			}
		}
		
	}
	return this->consonantCount;
}
