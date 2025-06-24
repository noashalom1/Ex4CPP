#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "iterators/AscendingOrder.hpp"
#include "iterators/DescendingOrder.hpp"
#include "iterators/SideCrossOrder.hpp"
#include "iterators/ReverseOrder.hpp"
#include "iterators/RegularOrder.hpp"
#include "iterators/MiddleOutOrder.hpp"

namespace containers
{

    template <typename T = int>
    class MyContainer
    {
    private:
        std::vector<T> data;
        size_t index = 0;

    public:
        void add(const T &value)
        {
            data.push_back(value);
            ++index;
        }

        void remove(const T &value)
        {
            auto original_size = data.size();
            data.erase(std::remove(data.begin(), data.end(), value), data.end());
            if (data.size() == original_size)
            {
                throw std::runtime_error("Element not found");
            }
            ++index;
        }

        size_t size() const
        {
            return data.size();
        }

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

        const std::vector<T> &get_data() const
        {
            return data;
        }

        std::vector<T> &get_data()
        {
            return data;
        }

        size_t get_index() const
        {
            return index;
        }

        AscendingOrder<T> Ascending() const
        {
            return AscendingOrder<T>(*this);
        }

        DescendingOrder<T> Descending() const
        {
            return DescendingOrder<T>(*this);
        }

        SideCrossOrder<T> SideCross() const
        {
            return SideCrossOrder<T>(*this);
        }

        ReverseOrder<T> Reverse() const
        {
            return ReverseOrder<T>(*this);
        }

        RegularOrder<T> Regular() const
        {
            return RegularOrder<T>(*this);
        }

        MiddleOutOrder<T> MiddleOut() const
        {
            return MiddleOutOrder<T>(*this);
        }
    };

}
