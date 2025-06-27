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
     * @brief Abstract base class for common iterator functionality.
     */
    template <typename T>
    class AbstractIterator
    {
    protected:
        const MyContainer<T> &container;
        std::vector<size_t> indices;
        size_t current;
        size_t expected_index;

    public:
        AbstractIterator(const MyContainer<T> &cont)
            : container(cont), current(0), expected_index(cont.index) {}

        AbstractIterator(const MyContainer<T> &cont, const std::vector<size_t> &idx, size_t pos)
            : container(cont), indices(idx), current(pos), expected_index(cont.index) {}

        virtual ~AbstractIterator() = default;

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
            return container.get_data()[indices[current]];
        }

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

        virtual const char *type_name() const = 0;

        bool operator==(const AbstractIterator &other) const
        {
            return current == other.current &&
                   typeid(*this) == typeid(other) &&
                   &container == &(other.container);
        }

        bool operator!=(const AbstractIterator &other) const
        {
            return !(*this == other);
        }
    };

}
