#pragma once
#include "libds/adt/table.h"
#include "libds/adt/list.h"
#include "../UzemnaJednotka.h"

//template < typename I>
//class MyTableItem
//{
//private:
//    ds::adt::ImplicitList<I>* prvky;
//public:
//    MyTableItem();
//    ~MyTableItem() { delete prvky; };
//    void add(I item);
//    size_t size();
//};
//
//template<typename I>
//inline MyTableItem<I>::MyTableItem()
//{
//    prvky = new ds::adt::ImplicitList<I>;
//};
//
//template<typename I>
//inline void MyTableItem<I>::add(I item)
//{
//    prvky->insert(item);
//}
//
//template<typename I>
//inline size_t MyTableItem<I>::size()
//{
//    return this->prvky.size();
//}
//




//template <typename K, typename I>
//class MyBinaryTree     
//{
//private:
//    ds::adt::BinarySearchTree<K, ds::amt::ImplicitSequence<I>*>* table;
//public:
//    MyBinaryTree();
//    void insert(const K& key, I data);
//};
//
//template<typename K, typename I>
//inline MyBinaryTree<K, I>::MyBinaryTree()
//{
//    table = new ds::adt::BinarySearchTree<K, ds::amt::ImplicitSequence<I>*>;
//}
//
//template<typename K, typename I>
//inline void MyBinaryTree<K, I>::insert(const K& key, I data)
//{
//    ds::amt::ImplicitSequence<I>* finded = nullptr;
//    if (table->tryFind(key, (finded))) {
//        finded->add(data);
//    }
//    else
//    {
//        finded = new ds::amt::ImplicitSequence<I>;
//        finded->add(data);
//    }
//    
//}
//class MyBinaryTree
//{
//private: 
//	ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* table;
//public:
//	MyBinaryTree();
//	~MyBinaryTree();
//	void insert(const std::string& key, UzemnaJednotka* data);
//	void tryFind(const std::string& key, ds::adt::ImplicitList<UzemnaJednotka*>**& result);
//	void deleteAll();
//};
template <typename Item>
class MyBinaryTree : public ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<Item>*>
{
private:
	//ds::adt::BinarySearchTree<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* table;
public:
	void insert(const std::string& key, Item data);
	//void tryFind(const std::string& key, ds::adt::ImplicitList<UzemnaJednotka*>**& result);
	void deleteAll();
};

//template<typename Item>
//void MyBinaryTree<Item>::insert(const std::string& key, Item data)
//{
//	ds::adt::ImplicitList<Item>* finded = nullptr;
//	ds::adt::ImplicitList<Item>** pfinded = &finded;
//	if (!this->tryFind(key, (pfinded))) {
//		finded = new ImplicitList<Item>;
//		finded->insertLast(data);
//		BinarySearchTree<std::string, ds::adt::ImplicitList<Item>*>::insert(data->getNazov(), finded);
//	}
//	else {
//		(*pfinded)->insertLast(data);
//	}
//};
//
//template<typename Item>
//void MyBinaryTree<Item>::deleteAll()
//{
//	for (auto zaznam = this->begin(); zaznam != this->end(); ++zaznam) {
//		auto end = (*zaznam).data_->end();
//		for (auto vZazname = (*zaznam).data_->begin(); vZazname != end; ++vZazname) {
//			delete (*vZazname);
//		}
//		delete (*zaznam).data_;
//	}
//}

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
	for (auto zaznam = this->begin(); zaznam != this->end(); ++zaznam) {
		auto end = (*zaznam).data_->end();
		for (auto vZazname = (*zaznam).data_->begin(); vZazname != end; ++vZazname) {
			delete (*vZazname);
		}
		delete (*zaznam).data_;
	}
}
