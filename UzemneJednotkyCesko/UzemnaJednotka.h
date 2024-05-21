#pragma once
#include <string>
#include <algorithm>
#include <locale>


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
	int consonantCount = -1;
	
public:
	UzemnaJednotka(std::string nnazov, std::string nkod, TypUzemia ntypU) : nazov(nnazov), kod(nkod), typUzemia(ntypU)
	{};

	friend std::ostream& operator<<(std::ostream& os, const UzemnaJednotka& obec);
	std::string getKod() { return this->kod; };
	std::string getNazov() { return this->nazov; };
	TypUzemia getType() { return this->typUzemia; };
	static void vypisHlavicku() { ; };

	bool nazovStartsWith(const std::string& predloha);
	bool nazovContains(const std::string& predloha);
	bool hasType(TypUzemia predloha);

	int countVowel();
	int countConsonant();

	bool compareAlphabetical(UzemnaJednotka* other)  // isBiggerAlphabetical
	{		
		static std::locale loc("");
		return std::use_facet<std::collate<char>>(loc).compare(
			this->nazov.data(), this->nazov.data() + this->nazov.size(),
			other->nazov.data(), other->nazov.data() + this->nazov.size()
		) > 0;
	}; 
	
	bool compareConsonantCount(UzemnaJednotka* other) { // isBiggerConsonantCount
		if (this->consonantCount == -1) {
			this->countConsonant();
		}
		if (other->consonantCount == -1) {
			other->countConsonant();
		}
		return this->consonantCount > other->consonantCount;
	};
	
	int getConsonantCount() { return this->consonantCount; };
};



