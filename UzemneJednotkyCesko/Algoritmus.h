#pragma once
#include <iterator>
#include <vector>

using namespace std;

template<typename TypeOfContainer>
class Algoritmus
{
	//static_assert(std::is_same<typename TypeOfContainer::iterator, typename TypeOfContainer::iterator>::value, "TypeOfContainer must have a nested type named iterator");

	//using ContainerIterator = typename TypeOfContainer::iterator;
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

