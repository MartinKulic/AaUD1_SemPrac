#pragma once
#include <string>
enum errorType {
	VseobecnyHelp,
	nespravneVstupnePar,
	nespravneSpustenie,
	chybaSoVstupnymSuborom
};
class IGUI {
public:
	virtual void startLoop() = 0;
	static void printError(errorType et, std::string msg);

	virtual void Progressed(int by) = 0;
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
