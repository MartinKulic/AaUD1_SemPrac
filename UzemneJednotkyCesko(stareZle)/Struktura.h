#pragma once
#include <vector>
#include <string>
#include"UzemnaJednotka.h"
#include"Obec.h"

class Struktura
{
	std::vector<UzemnaJednotka*> kraje;

	UzemnaJednotka* pridajKraj(std::string polozky[]);

public:
	Struktura(const char vstupnySubor[]);
};

