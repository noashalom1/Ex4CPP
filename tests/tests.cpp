
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../include/MyContainer.hpp"
#include <sstream>

using namespace containers;

TEST_CASE("Test add and size")
{
    MyContainer<int> c;
    CHECK(c.size() == 0);
    c.add(5);
    c.add(10);
    CHECK(c.size() == 2);
}

TEST_CASE("Test remove existing and non-existing")
{
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(2);
    c.add(3);
    CHECK(c.size() == 4);
    c.remove(2);
    CHECK(c.size() == 2);
    CHECK_THROWS_WITH(c.remove(42), "Element was not found");
    CHECK_NOTHROW(c.remove(3));
}

TEST_CASE("Test printing output")
{
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    std::ostringstream os;
    os << c;
    CHECK(os.str() == "[1, 2]");
}

template <typename T>
void check_iterator(MyContainer<T>& c, std::vector<T> expected, const std::string& type) {
    std::vector<T> result;
    if (type == "Ascending") for (auto val : c.Ascending()) result.push_back(val);
    else if (type == "Descending") for (auto val : c.Descending()) result.push_back(val);
    else if (type == "SideCross") for (auto val : c.SideCross()) result.push_back(val);
    else if (type == "Reverse") for (auto val : c.Reverse()) result.push_back(val);
    else if (type == "Regular") for (auto val : c.Regular()) result.push_back(val);
    else if (type == "MiddleOut") for (auto val : c.MiddleOut()) result.push_back(val);

    CHECK(result == expected);
}

TEST_CASE("Test iterators with int")
{
    MyContainer<int> c;
    c.add(7);
    c.add(15);
    c.add(6);
    c.add(1);
    c.add(2);

    check_iterator(c, {1, 2, 6, 7, 15}, "Ascending");
    check_iterator(c, {15, 7, 6, 2, 1}, "Descending");
    check_iterator(c, {1, 15, 2, 7, 6}, "SideCross");
    check_iterator(c, {2, 1, 6, 15, 7}, "Reverse");
    check_iterator(c, {7, 15, 6, 1, 2}, "Regular");
    check_iterator(c, {6, 15, 1, 7, 2}, "MiddleOut");
}

TEST_CASE("Test iterators with double")
{
    MyContainer<double> c;
    c.add(3.14);
    c.add(3.11);
    c.add(2.718);
    c.add(0.577);

    check_iterator(c, {0.577, 2.718, 3.11, 3.14}, "Ascending");
    check_iterator(c, {3.14, 3.11, 2.718, 0.577}, "Descending");
    check_iterator(c, {0.577, 3.14, 2.718, 3.11}, "SideCross");
    check_iterator(c, {0.577, 2.718, 3.11, 3.14}, "Reverse");
    check_iterator(c, {3.14, 3.11, 2.718, 0.577}, "Regular");
    check_iterator(c, {2.718, 3.11, 0.577, 3.14}, "MiddleOut");
}

TEST_CASE("Test iterators with strings")
{
    MyContainer<std::string> c;
    c.add("banana");
    c.add("apple");
    c.add("cherry");
    c.add("date");

    check_iterator(c, {"apple", "banana", "cherry", "date"}, "Ascending");
    check_iterator(c, {"date", "cherry", "banana", "apple"}, "Descending");
    check_iterator(c, {"apple", "date", "banana", "cherry"}, "SideCross");
    check_iterator(c, {"date", "cherry", "apple", "banana"}, "Reverse");
    check_iterator(c, {"banana", "apple", "cherry", "date"}, "Regular");
    check_iterator(c, {"cherry", "apple", "date", "banana"}, "MiddleOut");
}

TEST_CASE("Iterator throws when incrementing past end") {
    MyContainer<int> c;
    c.add(1); c.add(2);
    auto it = c.Ascending().begin();
    ++it;
    ++it;
    CHECK_THROWS(++it);  
}

TEST_CASE("Different iterator types are not equal") {
    MyContainer<int> c;
    c.add(1); c.add(2);

    auto asc = c.Ascending().begin();
    auto desc = c.Descending().begin();

    CHECK_FALSE(asc == desc);  
}

TEST_CASE("Removing all elements makes container empty") {
    MyContainer<std::string> c;
    c.add("a");
    c.remove("a");
    CHECK(c.size() == 0);
}

TEST_CASE("Output formatting with one element") {
    MyContainer<double> c;
    c.add(3.14);
    std::ostringstream os;
    os << c;
    CHECK(os.str() == "[3.14]");
}

TEST_CASE("Iterator throws when incremented past end") {
    MyContainer<int> c;
    c.add(1);
    auto it = c.Ascending().end();
    CHECK_THROWS(++it);
}



