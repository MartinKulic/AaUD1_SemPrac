#pragma once
#include<vector>
#include<string>
#include <Windows.h>

#include "Algoritmus.h"
#include "UzemnaJednotka.h"
#include "Obec.h"

enum errorType {
	VseobecnyHelp,
	nespravneVstupnePar
};

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
	COORD getCursorPos();
	void setCursorPos(COORD newpos);
	HANDLE& getHandle() { return this->handle; };
	void vykreskyFiggle(const char pothToFile[], COORD startPos);
	~GUI();
};

class GUIProgressBar
{
private:
	int totalLength;
	int progressed = 0;
	
	GUI* gui;
	COORD progressedPartOfProgressBar;
	COORD endOfProggressBar;

public:
	GUIProgressBar(GUI* ngui, string caption, int ntotalLength);
	void Progressed(int by);
	void Finished();
};

