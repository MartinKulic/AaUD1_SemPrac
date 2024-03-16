#pragma once
#include <iterator>
#include <vector>

using namespace std;

template<typename T>
class Algoritmus
{
public:
	template<typename F>
	void filtruj(typename vector<T>::iterator begin, typename vector<T>::iterator end, typename vector<T>& vyfiltrovane, F filter);
};

//template<typename T>
//inline void Algoritmus<T>::filtruj(typename vector<T>::iterator begin, typename vector<T>::iterator end, vector<T>& vyfiltrovane, bool(*Plati)(T kde))
//{
//}

template<typename T>
template<typename F>
inline void Algoritmus<T>::filtruj(typename vector<T>::iterator begin, typename vector<T>::iterator end, typename vector<T>& vyfiltrovane, F filter)
{
	typename vector<T>::iterator current = begin;
	
	for (; current != end; current++)
	{
		if (filter(*current))
			vyfiltrovane.push_back(*current);
	}
}
