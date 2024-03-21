#pragma once
#include<vector>
#include<string>
#include <Windows.h>
#include <functional>

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
	template< typename T > std::function<bool(T*)> getFuncion(string predslaOp, string vyhladavanyRetazec);
	void filtrujUJ(std::string druhVyhladavanie, string vyhladavanyRetazec, std::vector<UzemnaJednotka*>& zdroj);
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

template<typename T>
inline std::function<bool(T*)> GUI::getFuncion(string predslaOp, string vyhladavanyRetazec)
{
	if(predslaOp == "o")
		return [vyhladavanyRetazec](T* o) {return o->getNazov().find(vyhladavanyRetazec) != -1; };
	else
		return [vyhladavanyRetazec](T* o) {
		if (vyhladavanyRetazec.size() > o->getNazov().size())
			return false;

		for (int i = 0; i < vyhladavanyRetazec.size(); i++)
		{
			if (vyhladavanyRetazec[i] != o->getNazov()[i])
				return false;
		}
		return true;
		};
	
}
