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
     * @brief Provides reverse-order iteration over elements in a MyContainer<T>.
     *
     * Iterates over the container elements in reverse of their insertion order.
     *
     * @tparam T The type of elements in the container.
     */
    template <typename T>
    class ReverseOrder
    {
    private:
        const MyContainer<T> &container; // Reference to the container being iterated.

    public:
        /**
         * @brief Constructs a ReverseOrder wrapper for the given container.
         *
         * @param cont The container to iterate over.
         */
        ReverseOrder(const MyContainer<T> &cont)
            : container(cont) {}

        /**
         * @brief Iterator class for reverse insertion order.
         */
        class Iterator : public AbstractIterator<T>
        {
        public:
            /**
             * @brief Constructs a reverse-order iterator.
             *
             * Starts from the last inserted element and moves backwards to the first.
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
                this->indices.resize(n);
                for (size_t i = 0; i < n; ++i)
                    this->indices[i] = n - 1 - i;

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
                return "ReverseOrder::Iterator";
            }
        };

        /**
         * @brief Returns an iterator pointing to the last inserted element.
         *
         * @return Iterator Iterator to the beginning of reverse order.
         */
        Iterator begin() const { return Iterator(container, false); }

        /**
         * @brief Returns an iterator pointing past the first inserted element.
         *
         * @return Iterator Iterator to the end.
         */
        Iterator end() const { return Iterator(container, true); }
    };

}
