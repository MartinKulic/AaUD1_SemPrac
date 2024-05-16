#pragma once
#include <Windows.h>

#include "../IGUI.h"
#include "../UzemnaJednotka.h"
#include "../Obec.h"
#include "MyBinaryTree.h"
#include "libds/adt/tree.h"
#include "libds//adt/table.h"

class GUI3 : public IGUI
{
private:
	HANDLE handle;
	
	/*ds::adt::Table<std::string, UzemnaJednotka*>* kraje;
	ds::adt::Table<std::string, UzemnaJednotka*>* okresy;
	ds::adt::Table<std::string, Obec*>* obce;*/
	
	MyBinaryTree<UzemnaJednotka*>* kraje;
	MyBinaryTree<UzemnaJednotka*>* okresy;
	MyBinaryTree<Obec*>* obce;


	void nacitavanie(const char vstupnySubor[]);

public:
	GUI3(const char vstupnySubor[]);
	~GUI3();
	void startLoop();

	static void printError(errorType et, std::string msg);
	void Progressed(int by);
};

