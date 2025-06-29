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

    /**
     * @brief Provides ascending-order iteration over elements in a MyContainer<T>.
     *
     * This class generates an iterator that traverses elements in increasing order
     * based on the natural comparison of type T.
     *
     * @tparam T The type of elements in the container.
     */
    template <typename T>
    class AscendingOrder
    {
    private:
        const MyContainer<T> &container; // Reference to the container to be iterated.

    public:
        /**
         * @brief Constructs an AscendingOrder wrapper for the given container.
         *
         * @param cont The container to iterate over.
         */
        AscendingOrder(const MyContainer<T> &cont)
            : container(cont) {}

        /**
         * @brief Iterator class for ascending order.
         */
        class Iterator : public AbstractIterator<T>
        {
        public:
            /**
             * @brief Constructs an ascending iterator.
             *
             * Sorts the indices of the container elements in increasing order.
             *
             * @param cont The container to iterate over.
             * @param is_end If true, initializes to the end iterator.
             */
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

            /**
             * @brief Returns the type name of the iterator for identification.
             *
             * @return const char* Name of the iterator type.
             */
            const char *type_name() const override
            {
                return "AscendingOrder::Iterator";
            }
        };

        /**
         * @brief Returns an iterator pointing to the beginning (smallest element).
         *
         * @return Iterator Iterator to the beginning.
         */
        Iterator begin() const
        {
            return Iterator(container, false);
        }

        /**
         * @brief Returns an iterator pointing to the end (past the last element).
         *
         * @return Iterator Iterator to the end.
         */
        Iterator end() const
        {
            return Iterator(container, true);
        }
    };

}
