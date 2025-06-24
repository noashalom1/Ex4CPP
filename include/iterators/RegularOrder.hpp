#pragma once
#include "AbstractIterator.hpp"
#include <vector>

namespace containers
{
    template <typename T>
    class MyContainer;
}

namespace containers
{

    template <typename T>
    class RegularOrder
    {
    private:
        const MyContainer<T> &container;

    public:
        RegularOrder(const MyContainer<T> &cont)
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

                if (is_end)
                    this->current = n;
            }
            
            const char *type_name() const override
            {
                return "RegularOrder::Iterator";
            }
        };

        Iterator begin() const { return Iterator(container, false); }
        Iterator end() const { return Iterator(container, true); }
    };

}
