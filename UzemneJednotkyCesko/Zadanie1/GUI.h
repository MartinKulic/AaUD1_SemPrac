#pragma once
#include<vector>
#include<string>
#include <Windows.h>
#include <functional>
#include <iostream>

#include "Algoritmus.h"
#include "UzemnaJednotka.h"
#include "Obec.h"

enum errorType {
	VseobecnyHelp,
	nespravneVstupnePar,
	nespravneSpustenie,
	chybaSoVstupnymSuborom
};

//using namespace std;
class GUI
{
private:
	std::vector<UzemnaJednotka*> kraje;
	std::vector<UzemnaJednotka*> okresy;
	std::vector<Obec*> obce;

	HANDLE handle;

	void nacitavanie(const char vstupnySubor[]);

public:
	GUI(const char vstupnySubor[]);
	void startLoop();
	static void printError(errorType et, std::string msg);
	
	void Progressed(int by);

	~GUI();
};

