#include "UzemnaJednotka.h"
#include <iostream>

UzemnaJednotka<class T>::~UzemnaJednotka()
{
	for (T* uzemnaPodjednotka : UzemnePodjednotky)
	{
		delete uzemnaPodjednotka;
	}
}

void UzemnaJednotka<class T>::addUzemnuPodjednotku(T* newUzemnaJednozka)
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

void UzemnaJednotka<class T>::acknowledgeUzemnuNadJednotku(UzemnaJednotka* nadJednotka)
{
	this->uzemnaNadJednotka = nadJednotka;
}
