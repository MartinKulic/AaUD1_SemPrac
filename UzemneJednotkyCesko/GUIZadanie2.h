#pragma once
#include<string>
#include <Windows.h>

#include "libds/adt/tree.h"
#include "libds/amt/explicit_hierarchy.h"
#include "UzemnaJednotka.h"

//using namespace ds::adt;

class GUIZadanie2
{
private:
	HANDLE handle;
	//MultiwayTree<UzemnaJednotka*>* hierarchia;
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchia;

	void nacitavanie(const char vstupnySubor[]);
public:
	GUIZadanie2(const char vstupnySubor[]);
	~GUIZadanie2();
	void startLoop() {};

	void Progressed(int by);
};



