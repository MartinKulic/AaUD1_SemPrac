#pragma once
#include <string>
#include <Windows.h>

enum errorType {
	VseobecnyHelp,
	nespravneVstupnePar,
	nespravneSpustenie,
	chybaSoVstupnymSuborom,
	nespravnyArgument
};
class IGUI {
protected:
	HANDLE handle;
public:
	virtual void startLoop() = 0;
	static void printError(errorType et, std::string msg);

	virtual void Progressed(int by) = 0;
	IGUI() {
		handle = GetStdHandle(STD_OUTPUT_HANDLE);
	};
	virtual ~IGUI() {};
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
