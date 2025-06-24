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
    class MiddleOutOrder
    {
    private:
        const MyContainer<T> &container;

    public:
        MiddleOutOrder(const MyContainer<T> &cont)
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
                int mid = static_cast<int>(n) / 2;
                int left = mid - 1;
                int right = mid + 1;

                this->indices.push_back(mid);
                bool go_left = true;

                while (left >= 0 || right < static_cast<int>(n))
                {
                    if (go_left && left >= 0)
                    {
                        this->indices.push_back(left--);
                    }
                    else if (!go_left && right < static_cast<int>(n))
                    {
                        this->indices.push_back(right++);
                    }
                    go_left = !go_left;
                }

                if (is_end)
                    this->current = this->indices.size();
            }
            
            const char *type_name() const override
            {
                return "MiddleOutOrder::Iterator";
            }
        };

        Iterator begin() const { return Iterator(container, false); }
        Iterator end() const { return Iterator(container, true); }
    };

}
