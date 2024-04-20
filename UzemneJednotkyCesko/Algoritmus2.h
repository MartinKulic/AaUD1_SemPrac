#pragma once
//#include <functional>
//#include <iterator>

class Algoritmus2
{
public:
	template<typename iter, typename zoznam, typename F, typename G>
	static void filtruj(typename iter begin, typename iter end, zoznam& z, F filter, G naplnaciaFunkcia);
};

template<typename iter, typename zoznam, typename F, typename G>
inline void Algoritmus2::filtruj(typename iter begin, typename iter end, zoznam& z, F filter, G naplnaciaFunkcia)
{
	for (iter aktualny = begin; aktualny != end; aktualny++)
	{
		if (filter(*aktualny))
			naplnaciaFunkcia(*aktualny,z);
	}
}
