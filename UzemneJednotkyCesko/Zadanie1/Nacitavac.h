#pragma once
#include <vector>
#include <fstream>

#include "UzemnaJednotka.h"
#include "Obec.h"
#include "GUI.h"

//using namespace std;
class Nacitavac
{
private:
	std::ifstream prud;

public:
	 Nacitavac(const char subor[]);
	std::istream& dajRiadok(std::string& line);
	static void Nacitaj(const char vstupnySubor[], std::vector<UzemnaJednotka*>& kraje, std::vector<UzemnaJednotka*>& okresy, std::vector<Obec*>& obce, GUI* gui, int freq);
	
	
	static Obec* vytvorNovuObec(std::string polozky[]);
	static UzemnaJednotka* vytvorNovuUzemnuJednotku(std::string polozky[], TypUzemia typ);
	static void odstranMedzery(std::string& textNaSpeacovanie);
};

class problemZoSuborumExeption : public std::exception
{
private:
	std::string message;
public:
	problemZoSuborumExeption(std::string msg) : message(msg) {};
	char* what() { return &message[0]; };
	std::string  getMsg() { return this->message; };
};

