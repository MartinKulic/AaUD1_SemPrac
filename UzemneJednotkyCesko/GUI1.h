#pragma once
#include<vector>
#include<string>
#include <Windows.h>
#include <functional>
#include <iostream>

#include "Algoritmus.h"
#include "UzemnaJednotka.h"
#include "Obec.h"
#include "IGUI.h"




	class GUI1 : public IGUI
	{
	private:
		std::vector<UzemnaJednotka*> kraje;
		std::vector<UzemnaJednotka*> okresy;
		std::vector<Obec*> obce;

		HANDLE handle;

		void nacitavanie(const char vstupnySubor[]);

	public:
		GUI1(const char vstupnySubor[]);
		void startLoop();
		static void printError(errorType et, std::string msg);

		void Progressed(int by);

		~GUI1();
	};

