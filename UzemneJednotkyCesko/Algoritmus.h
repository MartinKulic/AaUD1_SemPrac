#pragma once
#include <iterator>


using namespace std;

template<typename DruhKontaineru>
class Algoritmus
{
public:
	template<typename F>
	static void filtruj(typename DruhKontaineru::iterator begin, typename DruhKontaineru::iterator end, DruhKontaineru& vyfiltrovane, F filter);
};

template<typename DruhKontaineru>
template<typename F>
inline void Algoritmus<DruhKontaineru>::filtruj(typename DruhKontaineru::iterator begin, typename DruhKontaineru::iterator end, typename DruhKontaineru& vyfiltrovane, F filter)
{
	for (typename DruhKontaineru::iterator aktualny = begin ; aktualny != end; aktualny++)
	{
		if (filter(*aktualny))
			vyfiltrovane.push_back(*aktualny);
	}
}

