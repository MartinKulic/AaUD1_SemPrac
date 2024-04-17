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
	template< typename T > std::function<bool(T)> getFuncion(std::string predslaOp, std::string vyhladavanyRetazec);
	template<typename Con, typename of> Con filtruj(std::string predslaOp, std::string vyhladavanyRetazec, Con* v);

public:
	GUI(const char vstupnySubor[]);
	void startLoop();
	static void printError(errorType et, std::string msg);
	
	void Progressed(int by);

	~GUI();
};

template<typename T>
inline std::function<bool(T)> GUI::getFuncion(std::string predslaOp, std::string vyhladavanyRetazec)
{
	if (vyhladavanyRetazec == "*")
	{
		return [](T o) {return true; };
	}

	if(predslaOp == "o")
		return [vyhladavanyRetazec](T o) {return o->getNazov().find(vyhladavanyRetazec) != -1; };
	else
		return [vyhladavanyRetazec](T o) {
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

template<typename Con, typename of>
inline Con GUI::filtruj(std::string op, std::string vyhladavanyRetazec, Con* v )
{
	Con vyfiltrovane;	

	std::function<bool(of*)> fun;
	fun = GUI::getFuncion<of*>(op, vyhladavanyRetazec);

	Algoritmus<Con>::filtruj(v->begin(), v->end(), vyfiltrovane, fun);
	
	if (vyfiltrovane.size() == 0)
	{
		SetConsoleTextAttribute(handle, 158);
		std::cout << "\nNeboli najdene ziadne zhody.\n";
		SetConsoleTextAttribute(handle, 15);
	}


	of::vypisHlavicku();
	for (of* el : vyfiltrovane)
	{
		std::cout << *el;
	}
	SetConsoleTextAttribute(handle, 22);
	std::cout << "\nNajdenych " << vyfiltrovane.size() << " zhod\n";
	SetConsoleTextAttribute(handle, 9);
	std::cout << "\n====================================================================================================================================\n\n";
	SetConsoleTextAttribute(handle, 15);

	return vyfiltrovane;
	
	
}
