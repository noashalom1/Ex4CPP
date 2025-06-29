// Author : noapatito123@gmail.com
#pragma once
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
     * @brief Provides descending-order iteration over elements in a MyContainer<T>.
     *
     * This class enables iteration over container elements from largest to smallest,
     * based on the natural ordering of type T.
     *
     * @tparam T The type of elements in the container.
     */
    template <typename T>
    class DescendingOrder
    {
    private:
        const MyContainer<T> &container; // Reference to the container being iterated.

    public:
        /**
         * @brief Constructs a DescendingOrder wrapper for the given container.
         *
         * @param cont The container to iterate over.
         */
        DescendingOrder(const MyContainer<T> &cont)
            : container(cont) {}

        /**
         * @brief Iterator class for descending order.
         */
        class Iterator : public AbstractIterator<T>
        {
        public:
            /**
             * @brief Constructs a descending iterator.
             *
             * Sorts the indices of the container elements in decreasing order.
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
                    this->indices[i] = i;

                std::sort(this->indices.begin(), this->indices.end(),
                          [&](size_t a, size_t b)
                          {
                              return data[a] > data[b];
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
                return "DescendingOrder::Iterator";
            }
        };

        /**
         * @brief Returns an iterator pointing to the beginning (largest element).
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
