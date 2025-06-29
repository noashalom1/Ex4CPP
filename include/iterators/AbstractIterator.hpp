// Author : noapatito123@gmail.com
#pragma once
#include <vector>
#include <stdexcept>

namespace containers
{
    template <typename T>
    class MyContainer;
}

namespace containers
{

    /**
     * @brief Abstract base class for implementing custom iterators over MyContainer<T>.
     *
     * Provides core logic for iteration, modification detection, and bounds checking.
     * Derived classes must implement the type_name() method.
     *
     * @tparam T Type of the elements in the container.
     */
    template <typename T>
    class AbstractIterator
    {
    protected:
        const MyContainer<T> &container; // Reference to the container being iterated.
        std::vector<size_t> indices;     // A list of indices defining the order of iteration.
        size_t current;                  // Current position in the indices vector.
        size_t expected_index;           // Version of the container at the time of iterator creation.

    public:
        /**
         * @brief Constructs an iterator for the given container starting at index 0.
         *
         * @param cont The container to iterate over.
         */
        AbstractIterator(const MyContainer<T> &cont)
            : container(cont), current(0), expected_index(cont.index) {}

        virtual ~AbstractIterator() = default; // Virtual destructor.

        /**
         * @brief Dereference operator to access the current element.
         *
         * @return const T& Reference to the current element.
         * @throws std::runtime_error If the container was modified during iteration.
         * @throws std::out_of_range If the iterator is out of bounds.
         */
        const T &operator*() const
        {
            if (expected_index != container.index)
            {
                throw std::runtime_error("Container was modified during iteration");
            }
            if (indices.empty() || current >= indices.size())
            {
                throw std::out_of_range("Iterator out of bounds");
            }
            return container.data[indices[current]];
        }

        /**
         * @brief Prefix increment operator to advance to the next element.
         *
         * @return AbstractIterator& Reference to this iterator.
         * @throws std::runtime_error If the container was modified during iteration.
         * @throws std::out_of_range If the iterator is out of bounds.
         */
        AbstractIterator &operator++()
        {
            if (expected_index != container.index)
            {
                throw std::runtime_error("Container was modified during iteration");
            }
            if (indices.empty() || current >= indices.size())
            {
                throw std::out_of_range("Iterator out of bounds");
            }
            ++current;
            return *this;
        }

        /**
         * @brief Returns the type name of the concrete iterator.
         *
         * @return const char* The name of the derived iterator type.
         */
        virtual const char *type_name() const = 0;

        /**
         * @brief Equality operator to compare two iterators.
         *
         * @param other Another iterator to compare with.
         * @return true If both iterators are at the same position, on the same container, and of the same type.
         * @return false Otherwise.
         */
        bool operator==(const AbstractIterator &other) const
        {
            return current == other.current &&
                   typeid(*this) == typeid(other) &&
                   &container == &(other.container);
        }

        /**
         * @brief Inequality operator to compare two iterators.
         *
         * @param other Another iterator to compare with.
         * @return true If the iterators are not equal.
         * @return false If the iterators are equal.
         */
        bool operator!=(const AbstractIterator &other) const
        {
            return !(*this == other);
        }
    };

}
