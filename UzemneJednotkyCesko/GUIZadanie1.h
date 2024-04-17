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

using namespace std;
class GUIZadanie1
{
private:
	std::vector<UzemnaJednotka*> kraje;
	std::vector<UzemnaJednotka*> okresy;
	std::vector<Obec*> obce;

	HANDLE handle;

	void nacitavanie(const char vstupnySubor[]);
	template< typename T > std::function<bool(T)> getFuncion(string predslaOp, string vyhladavanyRetazec);
	template<typename Con, typename of> Con filtruj(string predslaOp, string vyhladavanyRetazec, Con* v);

public:
	GUIZadanie1(const char vstupnySubor[]);
	void startLoop();
	static void printError(errorType et, std::string msg);
	
	void Progressed(int by);

	~GUIZadanie1();
};

template<typename T>
inline std::function<bool(T)> GUIZadanie1::getFuncion(string predslaOp, string vyhladavanyRetazec)
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
inline Con GUIZadanie1::filtruj(string op, string vyhladavanyRetazec, Con* v )
{
	Con vyfiltrovane;	

	std::function<bool(of*)> fun;
	fun = GUIZadanie1::getFuncion<of*>(op, vyhladavanyRetazec);

	Algoritmus<Con>::filtruj(v->begin(), v->end(), vyfiltrovane, fun);
	
	if (vyfiltrovane.size() == 0)
	{
		SetConsoleTextAttribute(handle, 158);
		cout << "\nNeboli najdene ziadne zhody.\n";
		SetConsoleTextAttribute(handle, 15);
	}


	of::vypisHlavicku();
	for (of* el : vyfiltrovane)
	{
		cout << *el;
	}
	SetConsoleTextAttribute(handle, 22);
	cout << "\nNajdenych " << vyfiltrovane.size() << " zhod\n";
	SetConsoleTextAttribute(handle, 9);
	cout << "\n====================================================================================================================================\n\n";
	SetConsoleTextAttribute(handle, 15);

	return vyfiltrovane;
	
	
}
