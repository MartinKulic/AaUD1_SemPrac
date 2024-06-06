#pragma once

#include "complexities/complexity_analyzer.h"
#include "libds/adt/table.h"
#include "list"
#include "../UzemneJednotkyCesko/Zadanie3/MyBinaryTree.h"
#include <random>

namespace ds::utils
{
    template<class Table>
    class TableAnalyzer : public ComplexityAnalyzer<Table>
    {
    protected:
        explicit TableAnalyzer(const std::string& name);

    protected:
        void growToSize(Table& structure, size_t size) override;
    protected:
        int key_;
        int data_;

    protected:
        std::default_random_engine rngData_;
        std::default_random_engine rngKey_;
    };

    /**
     * @brief Analyzes complexity of an insertion at the beginning.
     */
    template<class Table>
    class TableInsertAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableInsertAnalyzer(const std::string& name);

    protected:
        void executeOperation(Table& structure) override;
    };
    
    template<class Table>
    class TableFindAnalyzer : public TableAnalyzer<Table>
    {
    public:
        explicit TableFindAnalyzer(const std::string& name);

    protected:
        ds::adt::ImplicitList<int>* inded =nullptr;
        ds::adt::ImplicitList<int>** finded = &inded;
        //int* finded = nullptr;

        void executeOperation(Table& structure) override;
    };

    class TablesAnalyzer : public CompositeAnalyzer
    {
    public:
        TablesAnalyzer();
    };

    //----------

    template<class Table>
    TableAnalyzer<Table>::TableAnalyzer(const std::string& name) :
        ComplexityAnalyzer<Table>(name),
        rngData_(144),
        rngKey_(144),
        key_(0),
        data_(0)
    {
        this->registerBeforeOperation([this](Table& table) {
            std::uniform_int_distribution dist(1, 1000000);
            this->key_ = dist(this->rngKey_);
            while (table.contains(this->key_)) {
                this->key_ = dist(this->rngKey_);
            }

            this->data_ = this->rngData_();
            }
        );
    }

    template <class Table>
    void TableAnalyzer<Table>::growToSize(Table& structure, size_t size)
    {
        size_t count = size - structure.size();
        for (size_t i = 0; i < count; i++) {
            std::uniform_int_distribution dist(1, 100000);
            int key = dist(this->rngKey_);
            int data = this->rngData_();

            while (structure.contains(key)) {
                key = dist(this->rngKey_);
            }

            structure.insert(key, data);
        }
    }



    //----------

    template <class Table>
    TableInsertAnalyzer<Table>::TableInsertAnalyzer(const std::string& name) :
        TableAnalyzer<Table>(name)
    {
    }

    template <class Table>
    void TableInsertAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.insert(this->key_, this->data_);
    }


    //----------

    inline TablesAnalyzer::TablesAnalyzer() :
        CompositeAnalyzer("Tables")
    {
        this->addAnalyzer(std::make_unique<TableInsertAnalyzer<MyBinaryTree<int,int>>>("mybst-insert"));
        this->addAnalyzer(std::make_unique<TableFindAnalyzer<MyBinaryTree<int,int>>>("mybst-find"));
        //this->addAnalyzer(std::make_unique<TableInsertAnalyzer<ds::adt::BinarySearchTree<int,int>>>("bst-insert"));
        //this->addAnalyzer(std::make_unique<TableFindAnalyzer<ds::adt::BinarySearchTree<int,int>>>("bst-find"));

    }
   
    template<class Table>
    inline TableFindAnalyzer<Table>::TableFindAnalyzer(const std::string& name) : TableAnalyzer<Table>(name)
    {
        this->registerBeforeOperation([this](Table& table) {
            std::uniform_int_distribution dist(1, 1000000);
            this->key_ = dist(this->rngKey_);
            
            if (dist(this->rngKey_) % 2 == 0) { // testuje existujuce aj neexistujuce kuluce
                while (!table.contains(this->key_)) {
                    this->key_ = dist(this->rngKey_);
                }
            }
            }
        );
    }

    template<class Table>
    inline void TableFindAnalyzer<Table>::executeOperation(Table& structure)
    {
        structure.tryFind(this->key_, finded);
    }

}