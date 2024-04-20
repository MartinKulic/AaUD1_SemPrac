#pragma once
#include <iterator>


//using namespace std;

template<typename DruhKontaineru>
class Algoritmus
{
public:
	template<typename F, typename iter>
	static void filtruj(iter begin, iter end, DruhKontaineru& vyfiltrovane, std::function<bool(F)> filter);
	
	template<typename F, typename iter>
	static void filtruj(iter begin, iter end, std::function<bool(F)> filter, std::function<void(typename F)> naplnaciaFunkcia);
};

template<typename DruhKontaineru>
template<typename F, typename iter>
inline void Algoritmus<DruhKontaineru>::filtruj(iter begin, iter end, typename DruhKontaineru& vyfiltrovane, std::function<bool(F)> filter)
{
	for (iter aktualny = begin ; aktualny != end; aktualny++)
	{
		if (filter(*aktualny))
			vyfiltrovane.push_back(*aktualny);
	}
}

template<typename DruhKontaineru>
template<typename F, typename iter>
inline void Algoritmus<DruhKontaineru>::filtruj(iter begin, iter end, std::function<bool(F)> filter, std::function<void(F)> naplnaciaFunkcia)
{
	iter aktualny = begin;
	while (aktualny != end)
	{
		if (filter(*aktualny))
			naplnaciaFunkcia(*aktualny);
		aktualny++;
	}
}
