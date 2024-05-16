#pragma once
#include "../INacitavac.h"
#include "../UzemnaJednotka.h"
#include "../IGUI.h"
#include "MyBinaryTree.h"
#include "libds/adt/table.h"
#include <string>

class Nacitavac3 :
    public INacitavac
{
public:
    //static void Nacitaj(const char vstupnySubor[], ds::adt::Table<std::string, UzemnaJednotka*>*& kraje, ds::adt::Table<std::string, UzemnaJednotka*>*& okresy, ds::adt::Table<std::string, Obec*>*& obce, IGUI* progBar, int freq);
    static void Nacitaj(const char vstupnySubor[], MyBinaryTree<UzemnaJednotka*>*& kraje, MyBinaryTree<UzemnaJednotka*>*& okresy, MyBinaryTree<Obec*>*& obce, IGUI* progBar, int freq);
};

