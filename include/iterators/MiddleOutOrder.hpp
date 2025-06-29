// Author : noapatito123@gmail.com
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

    /**
     * @brief Provides middle-out order iteration over elements in a MyContainer<T>.
     *
     * Starts from the middle element and alternates outward: center, left, right, left, right...
     * Works for containers with both even and odd number of elements.
     *
     * @tparam T The type of elements in the container.
     */
    template <typename T>
    class MiddleOutOrder
    {
    private:
        const MyContainer<T> &container; // Reference to the container being iterated.

    public:
        /**
         * @brief Constructs a MiddleOutOrder wrapper for the given container.
         *
         * @param cont The container to iterate over.
         */
        MiddleOutOrder(const MyContainer<T> &cont)
            : container(cont) {}

        /**
         * @brief Iterator class for middle-out order.
         */
        class Iterator : public AbstractIterator<T>
        {
        public:
            /**
             * @brief Constructs a middle-out iterator.
             *
             * Starts from the middle index and expands outward by alternating left and right.
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

            /**
             * @brief Returns the type name of the iterator for identification.
             *
             * @return const char* Name of the iterator type.
             */
            const char *type_name() const override
            {
                return "MiddleOutOrder::Iterator";
            }
        };

        /**
         * @brief Returns an iterator pointing to the first element in middle-out order.
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
