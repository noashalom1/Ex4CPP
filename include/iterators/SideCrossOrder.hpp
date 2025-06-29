// Author : noapatito123@gmail.com
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

    /**
     * @brief Provides side-cross order iteration over elements in a MyContainer<T>.
     *
     * Iterates over the container in a zigzag pattern: smallest, largest, second-smallest, second-largest, etc.
     * Useful for alternating between extremes in a sorted view of the container.
     *
     * @tparam T The type of elements in the container.
     */
    template <typename T>
    class SideCrossOrder
    {
    private:
        const MyContainer<T> &container; // Reference to the container being iterated.

    public:
        /**
         * @brief Constructs a SideCrossOrder wrapper for the given container.
         *
         * @param cont The container to iterate over.
         */
        SideCrossOrder(const MyContainer<T> &cont)
            : container(cont) {}

        /**
         * @brief Iterator class for side-cross order.
         */
        class Iterator : public AbstractIterator<T>
        {
        public:
            /**
             * @brief Constructs a side-cross iterator.
             *
             * Sorts the elements in ascending order, then creates a zigzag traversal
             * pattern: first element, last, second, second-to-last, and so on.
             *
             * @param cont The container to iterate over.
             * @param is_end If true, initializes the iterator to the end position.
             */
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

            /**
             * @brief Returns the type name of the iterator for identification.
             *
             * @return const char* Name of the iterator type.
             */
            const char *type_name() const override
            {
                return "SideCrossOrder::Iterator";
            }
        };

        /**
         * @brief Returns an iterator pointing to the start of the side-cross order.
         *
         * @return Iterator Iterator to the beginning.
         */
        Iterator begin() const { return Iterator(container, false); }

        /**
         * @brief Returns an iterator pointing past the last element.
         *
         * @return Iterator Iterator to the end.
         */
        Iterator end() const { return Iterator(container, true); }
    };

}
