#pragma once
#include "libds/adt/table.h"
#include "libds/adt/list.h"
#include <libds/amt/implicit_sequence.h>
//#include "libds/amt/explicit_hierarchy.h"
#include "../UzemnaJednotka.h"



template <typename Item>
class MyBinaryTree : public ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<Item>*>
{
	using ItemType = typename ds::adt::TableItem<std::string, ds::adt::ImplicitList<Item>*>;
	using tableIterator = typename ds::amt::BinaryHierarchy<ds::amt::BinaryExplicitHierarchyBlock<ItemType>>::InOrderHierarchyIterator;
	using keyIterator = typename ds::amt::ImplicitSequence<Item>::ImplicitSequenceIterator;
private:
	ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<Item>*> getBegin() { ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<Item>*>::begin(); };
public:

	class MBTIterator
	{
	private: 
		tableIterator kluce;
		tableIterator kluceEnd;
		keyIterator* vKluci;
		keyIterator* vKluciEnd;
		
	public:
		MBTIterator(tableIterator iterStart, MyBinaryTree& table) : kluce(iterStart), kluceEnd(table.getHierarchy()->end())
		{			
			if (kluce != kluceEnd) {
				vKluci = new keyIterator((*kluce).data_->begin());
				vKluciEnd = new keyIterator((*kluce).data_->end());
			}
		};
		~MBTIterator() {
			if (vKluci) {
				delete vKluci;
				delete vKluciEnd;
			}
		};
		MBTIterator& operator++();
		bool operator!=(const MBTIterator& other);
		Item& operator*();

		
	};


	void insert(const std::string& key, Item data);
	void deleteAll();
	MBTIterator begin();
	MBTIterator end();
	tableIterator beginThroughtTabItem() { return this->getHierarchy()->begin(); };
	tableIterator endThroughtTabItem() { return this->getHierarchy()->end(); };


};



template<typename Item>
inline void MyBinaryTree<Item>::insert(const std::string& key, Item data)
{
	ds::adt::ImplicitList<Item>* finded = nullptr;
	ds::adt::ImplicitList<Item>** pfinded = &finded;
	if (!this->tryFind(key, (pfinded))) {
		finded = new ds::adt::ImplicitList<Item>;
		finded->insertLast(data);
		ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<Item>*>::insert(key, finded);
	}
	else {
		(*pfinded)->insertLast(data);
	}

}

template<typename Item>
inline void MyBinaryTree<Item>::deleteAll()
{
	for (auto zaznam = this->getHierarchy()->begin(); zaznam != this->getHierarchy()->end(); ++zaznam) {
		auto end = (*zaznam).data_->end();
		for (auto vZazname = (*zaznam).data_->begin(); vZazname != end; ++vZazname) {
			delete (*vZazname);
		}
		delete (*zaznam).data_;
	}
}

template<typename Item>
inline typename MyBinaryTree<Item>::MBTIterator MyBinaryTree<Item>::begin()
{
	return MBTIterator(this->getHierarchy()->begin(), *this);
}

template<typename Item>
inline typename MyBinaryTree<Item>::MBTIterator MyBinaryTree<Item>::end()
{
	return MBTIterator(this->getHierarchy()->end(), *this);
}




//template<typename Item>
//inline MyBinaryTree<Item>::MBTIterator::MBTIterator(tableIterator TableIter)
//{
//
//	kluce = new tableIterator(TableIter);
//	/*vKluci = new keyIterator((**kluce).data_->begin());
//	vKluciEnd = new keyIterator((*TableIter).data_->end());*/
//}

template<typename Item>
inline typename MyBinaryTree<Item>::MBTIterator& MyBinaryTree<Item>::MBTIterator::operator++()
{
	++(*vKluci);
	if (*vKluci == *vKluciEnd)
	{
		++kluce;
		if (kluce != kluceEnd)
		{
			delete vKluci;
			vKluci = new keyIterator((*kluce).data_->begin());
			delete vKluciEnd;
			vKluciEnd = new keyIterator((*kluce).data_->end());
		}
	}

	return *this;
}

template<typename Item>
inline bool MyBinaryTree<Item>::MBTIterator::operator!=(const MBTIterator& other)
{
	return kluce!=other.kluce;
}

template<typename Item>
inline Item& MyBinaryTree<Item>::MBTIterator::operator*()
{
	return *(*vKluci);
}
