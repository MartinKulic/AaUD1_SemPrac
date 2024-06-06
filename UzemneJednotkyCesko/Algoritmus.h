#pragma once
#include <functional>
#include "libds/adt/priority_queue.h"

template<typename typVKontainery>
class Algoritmus
{
public:
	template<typename tIterator, typename U>
	void filtruj(tIterator begin, tIterator end, std::function<bool(typVKontainery)> predikat, U naplnaciaFunkcia); // U = std::function<void(typVKontainery)> naplnaciaFunkcia

};

template<typename typVKontainery>
template<typename tIterator, typename U>
inline void Algoritmus<typVKontainery>::filtruj(tIterator begin, tIterator end, std::function<bool(typVKontainery)> predikat, U naplnaciaFunkcia)
{
	/*for (auto aktualny = begin; aktualny != end; ++aktualny)
	{
		if (predikat(*aktualny))
		{
			naplnaciaFunkcia(*aktualny);
		} 
	}*/
	for (; begin != end; ++begin)
	{
		if (predikat(*begin))
		{
			naplnaciaFunkcia(*begin);
		}
	}
}
