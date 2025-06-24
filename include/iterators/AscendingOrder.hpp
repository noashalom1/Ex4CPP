#pragma once
#include "AbstractIterator.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace containers
{
    template <typename T>
    class MyContainer;
}

namespace containers
{

    template <typename T>
    class AscendingOrder
    {
    private:
        const MyContainer<T> &container;

    public:
        AscendingOrder(const MyContainer<T> &cont)
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
                this->indices.resize(n);
                for (size_t i = 0; i < n; ++i)
                    this->indices[i] = i;

                std::sort(this->indices.begin(), this->indices.end(),
                          [&](size_t a, size_t b)
                          {
                              return data[a] < data[b];
                          });

                if (is_end)
                    this->current = n;
            }

            const char *type_name() const override
            {
                return "AscendingOrder::Iterator";
            }
        };

        Iterator begin() const
        {
            return Iterator(container, false);
        }

        Iterator end() const
        {
            return Iterator(container, true);
        }
    };

}
