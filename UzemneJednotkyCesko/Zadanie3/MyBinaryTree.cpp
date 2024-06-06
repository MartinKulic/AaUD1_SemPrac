#include "MyBinaryTree.h"
#include "../Obec.h"

using namespace std;
using namespace ds::adt;
//MyBinaryTree::MyBinaryTree()
//{
//	table = new ds::adt::BinarySearchTree<string, ds::adt::ImplicitList<UzemnaJednotka*>*>;
//}

//MyBinaryTree::~MyBinaryTree()
//{
//	delete table;
//}

//void MyBinaryTree::insert(const string& key, UzemnaJednotka* data)
//{
//	ds::adt::ImplicitList<UzemnaJednotka*>* finded = nullptr;
//	ds::adt::ImplicitList<UzemnaJednotka*>** pfinded = &finded;
//	if (! this->tryFind(key, (pfinded))) {
//		finded = new ImplicitList<UzemnaJednotka*>;
//		finded->insertLast(data);
//		BinarySearchTree<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>::insert(data->getNazov(), finded);
//	}
//	else {
//		(*pfinded)->insertLast(data);
//	}
//}

//void MyBinaryTree::tryFind(const std::string& key, ds::adt::ImplicitList<UzemnaJednotka*>**& result)
//{
//	table->tryFind(key, result);
//}




//void MyBinaryTree::deleteAll()
//{
//	for (auto zaznam = table->begin(); zaznam != table->end(); ++zaznam) {
//		auto end = (*zaznam).data_->end();
//		for (auto vZazname = (*zaznam).data_->begin(); vZazname != end; ++vZazname) {
//			if ((*vZazname)->getType() == TypUzemia(obec)) {
//				delete (Obec*)(*vZazname);
//			}
//			else
//			{
//				delete (*vZazname);
//			}
//		}
//		delete (*zaznam).data_;
//	}
//}

