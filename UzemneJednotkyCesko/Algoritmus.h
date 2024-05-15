#pragma once
#include <functional>

template<typename typVKontainery>
class Algoritmus
{
public:
	/*template<typename tIterator, typename tVyslednyKontainer, typename U>
	void filtruj(tIterator begin, tIterator end, std::function<bool(typVKontainery a)> predikat, tVyslednyKontainer& vyslednyKontainer, U naplnaciaFunkcia)
	{
		for (auto aktualny = begin; aktualny != end; aktualny++)
		{
			if ( predikat(*aktualny) )
			{
				naplnaciaFunkcia(vyslednyKontainer, *aktualny);
			}
		}
	};*/
	template<typename tIterator, typename U>
	void filtruj(tIterator begin, tIterator end, std::function<bool(typVKontainery)> predikat, U naplnaciaFunkcia); // U = std::function<void(typVKontainery)> naplnaciaFunkcia
};

template<typename typVKontainery>
template<typename tIterator, typename U>
inline void Algoritmus<typVKontainery>::filtruj(tIterator begin, tIterator end, std::function<bool(typVKontainery)> predikat, U naplnaciaFunkcia) 
{
	for (auto aktualny = begin; aktualny != end; aktualny++)
	{
		if (predikat(*aktualny))
		{
			naplnaciaFunkcia(*aktualny);
		}
	}
}



