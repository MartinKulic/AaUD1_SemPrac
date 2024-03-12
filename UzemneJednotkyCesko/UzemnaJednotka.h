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
	vector<UzemnaJednotka*> UzemnePodjednotky;
	UzemnaJednotka* uzemnaNadJednotka = nullptr;

public:

	UzemnaJednotka(string nnazov, string nkod, TypUzemia ntypU) : nazov(nnazov), kod(nkod), typUzemia(ntypU)
		{};
	UzemnaJednotka(string nnazov, TypUzemia ntypU) : nazov(nnazov), typUzemia(ntypU)
		{};
	UzemnaJednotka(UzemnaJednotka &ref);
	~UzemnaJednotka();

	void addUzemnuPodjednotku(UzemnaJednotka* newUzemnaJednotka);
	void acknowledgeUzemnuNadJednotku(UzemnaJednotka* nadJednotka);
	string getKod() { return this->kod; };
};

