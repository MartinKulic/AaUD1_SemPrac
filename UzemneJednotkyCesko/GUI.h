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
enum operationType {
	obsahuje,
	zacina
};
using namespace std;
class GUI
{
private:
	std::vector<UzemnaJednotka*> kraje;
	std::vector<UzemnaJednotka*> okresy;
	std::vector<Obec*> obce;

	HANDLE handle;

	void nacitavanie(const char vstupnySubor[]);
	template< typename T > std::function<bool(T)> getFuncion(string predslaOp, string vyhladavanyRetazec);
	template<typename Con, typename of> void filtruj(string predslaOp, string vyhladavanyRetazec, Con* v);

public:
	GUI(const char vstupnySubor[]);
	void startLoop();
	static void printError(errorType et, std::string msg);
	COORD getCursorPos();
	void setCursorPos(COORD newpos);
	HANDLE& getHandle() { return this->handle; };
	
	void Progressed(int by);

	~GUI();
};

template<typename T>
inline std::function<bool(T)> GUI::getFuncion(string predslaOp, string vyhladavanyRetazec)
{
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
inline void GUI::filtruj(string op, string vyhladavanyRetazec, Con* v )
{
	Con vyfiltrovane;	

	std::function<bool(of*)> fun;
	fun = GUI::getFuncion<of*>(op, vyhladavanyRetazec);

	Algoritmus<Con>::filtruj(v->begin(), v->end(), vyfiltrovane, fun);
	
	if (vyfiltrovane.size() == 0)
	{
		cout << "\nNeboli najdene ziadne zhody.\n";
	}

	of::vypisHlavicku();
	for (of* el : vyfiltrovane)
	{
		cout << *el;
	}
	cout << "\nNajdenych " << vyfiltrovane.size() << " zhod\n";
	cout << "\n==========================================================\n\n";
	
}
