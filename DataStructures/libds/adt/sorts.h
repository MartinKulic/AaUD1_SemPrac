#pragma once

#include <libds/amt/implicit_sequence.h>
#include <libds/adt/queue.h>
#include <libds/adt/array.h>
#include <functional>
#include <cmath>
#include <algorithm>
#include <type_traits>

namespace ds::adt
{
    template <typename T>
    struct Sort
    {
    public:
        virtual void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) = 0;
        void sort(amt::ImplicitSequence<T>& is) { sort(is, [](const T& a, const T& b)->bool {return a < b; }); }
    };

    //----------

    template <typename T>
    class SelectSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class InsertSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class BubbleSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
    };

    //----------

    template <typename T>
    class QuickSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max);
    };

    //----------

    template <typename T>
    class HeapSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;
        void sort(adt::ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare);
    };

    //----------

    template <typename T>
    class ShellSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k);
    };

    //----------

    template <typename Key, typename T>
    class RadixSort :
        public Sort<T>
    {
        static_assert(std::is_integral_v<Key>, "Radix sort supports only integral types.");

    public:
        RadixSort();
        RadixSort(std::function<Key(const T&)> getKey);

        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        std::function<Key(const T&)> getKey_;
    };

    //----------

    template <typename T>
    class MergeSort :
        public Sort<T>
    {
    public:
        void sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare) override;

    private:
        void split(size_t n);
        void merge(std::function<bool(const T&, const T&)> compare, size_t n);

    private:
        ImplicitQueue<T>* queue1_ {nullptr};
        ImplicitQueue<T>* queue2_ {nullptr};
        ImplicitQueue<T>* mergeQueue_ {nullptr};
    };

    //----------

    template<typename T>
    void SelectSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void InsertSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void BubbleSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void QuickSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        if (!is.isEmpty())
        {
            quick(is, compare, 0, is.size() - 1);
        }
    }

    template<typename T>
    void QuickSort<T>::quick(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t min, size_t max)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void HeapSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        for (int i = 1; i < is.size(); i++)
        {
            bool vymena;
            int aktualny = i;

            do {
                vymena = false;
                int otec = (aktualny - 1) / 2;
                if (aktualny > 0 && compare(is.access(otec)->data_, is.access(aktualny)->data_))
                {
                    std::swap(is.access(aktualny)->data_, is.access(otec)->data_);
                    aktualny = otec;
                    vymena = true;
                }
            } while (vymena);
        }
        for (int i = is.size() - 1; i > 0; i--)
        {
            std::swap(is.access(0)->data_, is.access(i)->data_);
            bool vymena;
            int aktualny = 0;
            do {
                vymena = false;
                int lavy = (2 * aktualny) + 1;
                int pravy = (2 * aktualny) + 2;
                int max;

                if (lavy < i && pravy < i) {
                    max = compare(is.access(pravy)->data_, is.access(lavy)->data_) ? lavy : pravy;
                }
                else {
                    max = lavy < i ? lavy : pravy;
                }

                if (max < i && compare(is.access(aktualny)->data_, is.access(max)->data_)) {
                    std::swap(is.access(aktualny)->data_, is.access(max)->data_);
                    aktualny = max;
                    vymena = true;
                }

            } while (vymena);
        }
    }
    template<typename T>
    void HeapSort<T>::sort(adt::ImplicitList<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        for (int i = 1; i < is.size(); i++)
        {
            bool vymena;
            int aktualny = i;

            do {
                vymena = false;
                int otec = (aktualny - 1) / 2;
                if (aktualny > 0 && compare(is.access(aktualny), is.access(otec)))
                {
                    //std::swap(is.access(aktualny), is.access(otec));
                    T pom = is.access(aktualny);
                    is.set(aktualny, is.access(otec));
                    is.set(otec, pom);
                    aktualny = otec;
                    vymena = true;
                }
            } while (vymena);
        }
        for (int i = is.size() - 1; i > 1; i--)
        {
            //std::swap(is.access(0), is.access(i));
            T pom = is.access(i);
            is.set(i, is.access(0));
            is.set(0, pom);

            bool vymena = false;
            int aktualny = 0;
            do {
                vymena = false;
                int lavy = (2 * aktualny) + 1;
                int pravy = (2 * aktualny) + 2;
                int max;

                if (lavy < i && pravy < i) {
                    max = compare(is.access(pravy), is.access(lavy)) ? lavy : pravy;
                }
                else {
                    max = lavy < i ? lavy : pravy;
                }

                if (max < i && compare(is.access(aktualny), is.access(max))) {
                    //std::swap(is.access(aktualny), is.access(max));
                    T pom = is.access(aktualny);
                    is.set(aktualny, is.access(max));
                    is.set(max, pom);
                    
                    aktualny = max;
                    vymena = true;
                }

            } while (vymena);
        }
    }

    template<typename T>
    void ShellSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        shell(is, compare, static_cast<size_t>(std::ceil(std::log10(is.size()))));
    }

    template<typename T>
    void ShellSort<T>::shell(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare, size_t k)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort() :
        getKey_([](auto const& x) { return x; })
    {
    }

    template<typename Key, typename T>
    RadixSort<Key, T>::RadixSort(std::function<Key(const T&)> getKey) :
        getKey_(getKey)
    {
    }

    template<typename Key, typename T>
    void RadixSort<Key, T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::sort(amt::ImplicitSequence<T>& is, std::function<bool(const T&, const T&)> compare)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::split(size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }

    template<typename T>
    void MergeSort<T>::merge(std::function<bool(const T&, const T&)> compare, size_t n)
    {
        // TODO 12
        // po implementacii vymazte vyhodenie vynimky!
        throw std::runtime_error("Not implemented yet");
    }
}