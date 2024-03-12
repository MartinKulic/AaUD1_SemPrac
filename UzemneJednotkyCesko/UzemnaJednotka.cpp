#include "UzemnaJednotka.h"
#include <iostream>

UzemnaJednotka::~UzemnaJednotka()
{
	for (UzemnaJednotka* uzemnaPodjednotka : UzemnePodjednotky)
	{
		delete uzemnaPodjednotka;
	}
}

void UzemnaJednotka::addUzemnuPodjednotku(UzemnaJednotka* newUzemnaJednozka)
{
	if (this->typUzemia != obec)
	{
		this->UzemnePodjednotky.push_back(newUzemnaJednozka);
		newUzemnaJednozka->acknowledgeUzemnuNadJednotku(this);
	}
	else
	{
		throw ("Obec nemoze mat dalsie poduzemia");
	}
}

void UzemnaJednotka::acknowledgeUzemnuNadJednotku(UzemnaJednotka* nadJednotka)
{
	this->uzemnaNadJednotka = nadJednotka;
}
