#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <unordered_set>

#include "iterators/AscendingOrder.hpp"
#include "iterators/DescendingOrder.hpp"
#include "iterators/SideCrossOrder.hpp"
#include "iterators/ReverseOrder.hpp"
#include "iterators/RegularOrder.hpp"
#include "iterators/MiddleOutOrder.hpp"

namespace containers
{

    /**
     * @brief A generic container class that supports multiple custom iteration orders.
     *
     * @tparam T The type of elements stored in the container (default is int).
     */
    template <typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> data;                    // Internal storage of elements.
        size_t index = 0;                       // Version counter to detect modifications during iteration.
        std::unordered_multiset<T> fast_lookup; // Fast lookup structure for element existence check.

        friend class AbstractIterator<T>; // Allows AbstractIterator to access private members.

    public:
        /**
         * @brief Adds a new element to the container.
         *
         * @param value The value to be added.
         */
        void add(const T &value)
        {
            data.push_back(value);
            fast_lookup.insert(value);
            ++index;
        }

        /**
         * @brief Removes an element from the container.
         *
         * If the element is not found, throws std::runtime_error.
         *
         * @param value The value to be removed.
         * @throws std::runtime_error if element is not found.
         */
        void remove(const T &value)
        {
            if (fast_lookup.count(value) == 0)
            {
                throw std::runtime_error("Element was not found");
            }

            data.erase(std::remove(data.begin(), data.end(), value), data.end());

            fast_lookup.erase(value);

            ++index;
        }

        /**
         * @brief Returns the number of elements in the container.
         *
         * @return size_t Number of elements.
         */
        size_t size() const
        {
            return data.size();
        }

        /**
         * @brief Prints the container's elements in insertion order.
         *
         * @param os Output stream.
         * @param container Container to be printed.
         * @return std::ostream& Reference to the output stream.
         */
        friend std::ostream &operator<<(std::ostream &os, const MyContainer<T> &container)
        {
            os << "[";
            for (size_t i = 0; i < container.data.size(); ++i)
            {
                os << container.data[i];
                if (i < container.data.size() - 1)
                    os << ", ";
            }
            os << "]";
            return os;
        }

        /**
         * @brief Returns a reference to the container's data (read-only).
         *
         * @return const std::vector<T>& Reference to internal data.
         */
        const std::vector<T> &get_data() const
        {
            return data;
        }

        /**
         * @brief Returns an iterable object for ascending order iteration.
         *
         * @return AscendingOrder<T> Iterator wrapper.
         */
        AscendingOrder<T> Ascending() const
        {
            return AscendingOrder<T>(*this);
        }

        /**
         * @brief Returns an iterable object for descending order iteration.
         *
         * @return DescendingOrder<T> Iterator wrapper.
         */
        DescendingOrder<T> Descending() const
        {
            return DescendingOrder<T>(*this);
        }

        /**
         * @brief Returns an iterable object for side-cross order iteration (min, max, min+1, max-1...).
         *
         * @return SideCrossOrder<T> Iterator wrapper.
         */
        SideCrossOrder<T> SideCross() const
        {
            return SideCrossOrder<T>(*this);
        }

        /**
         * @brief Returns an iterable object for reverse insertion order iteration.
         *
         * @return ReverseOrder<T> Iterator wrapper.
         */
        ReverseOrder<T> Reverse() const
        {
            return ReverseOrder<T>(*this);
        }

        /**
         * @brief Returns an iterable object for regular insertion order iteration.
         *
         * @return RegularOrder<T> Iterator wrapper.
         */
        RegularOrder<T> Regular() const
        {
            return RegularOrder<T>(*this);
        }

        /**
         * @brief Returns an iterable object for middle-out order iteration (middle, left, right...).
         *
         * @return MiddleOutOrder<T> Iterator wrapper.
         */
        MiddleOutOrder<T> MiddleOut() const
        {
            return MiddleOutOrder<T>(*this);
        }
    };

}
