#pragma once
#include <iterator>


using namespace std;

template<typename TypeOfContainer>
class Algoritmus
{
public:
	template<typename F>
	static void filtruj(typename TypeOfContainer::iterator begin, typename TypeOfContainer::iterator end, TypeOfContainer& vyfiltrovane, F filter);
};

template<typename TypeOfContainer>
template<typename F>
inline void Algoritmus<TypeOfContainer>::filtruj(typename TypeOfContainer::iterator begin, typename TypeOfContainer::iterator end, typename TypeOfContainer& vyfiltrovane, F filter)
{
	typename TypeOfContainer::iterator current = begin;
	
	for (; current != end; current++)
	{
		if (filter(*current))
			vyfiltrovane.push_back(*current);
	}
}

