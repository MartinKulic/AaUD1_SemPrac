#pragma once
#include<string>
#include <Windows.h>

#include "libds/adt/tree.h"
#include "UzemnaJednotka.h"

using namespace ds::adt;

class GUIZadanie2
{
private:
	HANDLE handle;
	MultiwayTree<UzemnaJednotka*>* hierarchia;

	void nacitavanie(const char vstupnySubor[]);
public:
	GUIZadanie2(const char vstupnySubor[]);
	void startLoop() {};

	void Progressed(int by);
};



