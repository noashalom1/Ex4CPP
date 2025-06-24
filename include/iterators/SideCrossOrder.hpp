#pragma once
#include "AbstractIterator.hpp"
#include <vector>
#include <algorithm>

namespace containers
{
    template <typename T>
    class MyContainer;
}

namespace containers
{

    template <typename T>
    class SideCrossOrder
    {
    private:
        const MyContainer<T> &container;

    public:
        SideCrossOrder(const MyContainer<T> &cont)
            : container(cont) {}

        class Iterator : public AbstractIterator<T>
        {
        public:
            Iterator(const MyContainer<T> &cont, bool is_end = false)
                : AbstractIterator<T>(cont)
            {
                const auto &data = cont.get_data();
                size_t n = data.size();
                if (n == 0)
                    return;
                std::vector<size_t> temp(n);
                for (size_t i = 0; i < n; ++i)
                    temp[i] = i;

                std::sort(temp.begin(), temp.end(),
                          [&](size_t a, size_t b)
                          {
                              return data[a] < data[b];
                          });

                size_t left = 0, right = n - 1;
                while (left <= right)
                {
                    if (left == right)
                        this->indices.push_back(temp[left]);
                    else
                    {
                        this->indices.push_back(temp[left]);
                        this->indices.push_back(temp[right]);
                    }
                    ++left;
                    if (right > 0)
                        --right;
                }

                if (is_end)
                    this->current = this->indices.size();
            }
            
            const char *type_name() const override
            {
                return "SideCrossOrder::Iterator";
            }
        };

        Iterator begin() const { return Iterator(container, false); }
        Iterator end() const { return Iterator(container, true); }
    };

}
