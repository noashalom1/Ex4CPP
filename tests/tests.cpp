
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"
#include <functional>

using namespace containers;

TEST_CASE("Add and size check") {
    MyContainer<int> c;
    CHECK(c.size() == 0);
    c.add(10);
    c.add(20);
    CHECK(c.size() == 2);
}

TEST_CASE("Remove all occurrences of each element") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    c.add(3);

    c.remove(1);
    c.remove(2);
    c.remove(3);

    CHECK(c.size() == 0);
}

TEST_CASE("Remove non-existing element") {
    MyContainer<int> c;
    c.add(10);
    c.add(20);
    CHECK_THROWS_AS(c.remove(30), std::runtime_error);
}

TEST_CASE("Remove element from empty container throws") {
    MyContainer<int> c;
    CHECK_THROWS_AS(c.remove(10), std::runtime_error);
}

TEST_CASE("Operator<< output") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    std::ostringstream oss;
    oss << c;
    CHECK(oss.str() == "[1, 2]");
}

TEST_CASE("AscendingOrder iteration") {
    MyContainer<int> c;
    c.add(3);
    c.add(1);
    c.add(2);
    std::vector<int> result;
    for (int x : c.Ascending()) {
        result.push_back(x);
    }
    CHECK(result == std::vector<int>{1, 2, 3});
}

TEST_CASE("DescendingOrder iteration") {
    MyContainer<int> c;
    c.add(3);
    c.add(1);
    c.add(2);
    std::vector<int> result;
    for (int x : c.Descending()) {
        result.push_back(x);
    }
    CHECK(result == std::vector<int>{3, 2, 1});
}

TEST_CASE("SideCrossOrder iteration") {
    MyContainer<int> c;
    c.add(10);
    c.add(1);
    c.add(5);
    c.add(20);
    std::vector<int> result;
    for (int x : c.SideCross()) {
        result.push_back(x);
    }
    CHECK(result.size() == 4);
}

TEST_CASE("ReverseOrder iteration") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);
    c.add(3);
    std::vector<int> result;
    for (int x : c.Reverse()) {
        result.push_back(x);
    }
    CHECK(result == std::vector<int>{3, 2, 1});
}

TEST_CASE("RegularOrder iteration") {
    MyContainer<int> c;
    c.add(5);
    c.add(10);
    c.add(15);
    std::vector<int> result;
    for (int x : c.Regular()) {
        result.push_back(x);
    }
    CHECK(result == std::vector<int>{5, 10, 15});
}

TEST_CASE("MiddleOutOrder iteration with odd count") {
    MyContainer<int> c;
    c.add(1);
    c.add(3);
    c.add(5);
    c.add(7);
    c.add(9);
    std::vector<int> result;
    for (int x : c.MiddleOut()) {
        result.push_back(x);
    }
    CHECK(result.size() == 5);
}

TEST_CASE("MiddleOutOrder iteration with even count") {
    MyContainer<int> c;
    c.add(2);
    c.add(4);
    c.add(6);
    c.add(8);
    std::vector<int> result;
    for (int x : c.MiddleOut()) {
        result.push_back(x);
    }
    CHECK(result.size() == 4);
}

TEST_CASE("Iterators on empty container do not crash")
{
    MyContainer<int> c;
    CHECK(c.Ascending().begin() == c.Ascending().end());
    CHECK(c.Descending().begin() == c.Descending().end());
    CHECK(c.SideCross().begin() == c.SideCross().end());
    CHECK(c.Reverse().begin() == c.Reverse().end());
    CHECK(c.Regular().begin() == c.Regular().end());
    CHECK(c.MiddleOut().begin() == c.MiddleOut().end());
}

TEST_CASE("Single item behaves the same in all iterators") {
    MyContainer<int> cont;
    cont.add(7);

    for (auto it : cont.Ascending())
        CHECK(it == 7);

    for (auto it : cont.Descending())
        CHECK(it == 7);

    for (auto it : cont.SideCross())
        CHECK(it == 7);

    for (auto it : cont.Reverse())
        CHECK(it == 7);

    for (auto it : cont.Regular())
        CHECK(it == 7);

    for (auto it : cont.MiddleOut())
        CHECK(it == 7);
}

TEST_CASE("Iterator equality and inequality") {
    MyContainer<int> cont;
    cont.add(1);
    cont.add(2);
    cont.add(3);

    auto ascBegin = cont.Ascending().begin();
    auto ascEnd = cont.Ascending().end();

    CHECK(ascBegin != ascEnd);  // תחילת איטרציה שונה מהסוף

    // נתקדם עד הסוף ונבדוק שהגענו לאנד
    ++ascBegin;
    ++ascBegin;
    ++ascBegin;
    CHECK(ascBegin == ascEnd);
}

TEST_CASE("Iterators from different strategies are not equal") {
    MyContainer<int> cont;
    cont.add(10);
    cont.add(20);

    auto ascIt = cont.Ascending().begin();
    auto descIt = cont.Descending().begin();

    CHECK(ascIt != descIt);  // למרות שהאיבר הראשון עשוי להיות זהה, האיטרטורים שונים
}

TEST_CASE("Copied iterator remains equal until incremented") {
    MyContainer<int> cont;
    cont.add(5);
    cont.add(9);

    auto it1 = cont.Regular().begin();
    auto it2 = it1;

    CHECK(it1 == it2);  // שווים לפני ההתקדמות

    ++it2;
    CHECK(it1 != it2);  // אחרי ההתקדמות – לא שווים
}

TEST_CASE("Iterator invalidation on container modification") {
    MyContainer<int> cont;
    cont.add(1);
    cont.add(2);
    cont.add(3);

    auto it = cont.Ascending().begin();

    // נזיז את האיטרטור צעד ראשון בהצלחה
    CHECK_NOTHROW(++it);

    // עכשיו נשנה את הקונטיינר
    cont.add(4);

    // ניסיון לגשת או להזיז את האיטרטור אחרי שינוי הקונטיינר אמור להיכשל
    CHECK_THROWS_AS(*it, std::runtime_error);
    CHECK_THROWS_AS(++it, std::runtime_error);
}

TEST_CASE("Iterator throws out_of_range when advancing past end") {
    MyContainer<int> cont;
    cont.add(10);
    cont.add(20);

    auto it = cont.Regular().begin();
    auto end = cont.Regular().end();

    // הזזות תקינות
    CHECK_NOTHROW(*it);
    ++it;
    CHECK_NOTHROW(*it);

    // עכשיו האיטרטור אמור להיות בנקודה האחרונה
    ++it;

    // ניסיון נוסף אמור לזרוק חריגת חורג מהתחום
    CHECK_THROWS_AS(*it, std::out_of_range);
    CHECK_THROWS_AS(++it, std::out_of_range);
}

TEST_CASE("Iterator throws when incrementing past end") {
    MyContainer<int> c;
    c.add(1);
    c.add(2);

    auto it = c.Ascending().end();  // איטרטור שנמצא בסוף

    CHECK_THROWS_AS(++it, std::out_of_range);  // ניסיון להגדיל מעבר לסוף
}

TEST_CASE("String iterator throws when incrementing past end") {
    MyContainer<std::string> c;
    c.add("apple");
    c.add("banana");

    auto it = c.Ascending().end();
    CHECK_THROWS_AS(++it, std::out_of_range);
}

TEST_CASE("Double iterator throws when incrementing past end") {
    MyContainer<double> c;
    c.add(1.1);
    c.add(2.2);

    auto it = c.Ascending().end();
    CHECK_THROWS_AS(++it, std::out_of_range);
}


TEST_CASE("All iterators throw when incrementing past end (multiple types)") {
    SUBCASE("int") {
        MyContainer<int> c;
        c.add(1);
        c.add(2);

        std::vector<std::function<void()>> tests = {
            [&]() {
                auto it = c.Ascending().end();
                CHECK_THROWS_AS(++it, std::out_of_range);
            },
            [&]() {
                auto it = c.Descending().end();
                CHECK_THROWS_AS(++it, std::out_of_range);
            },
            [&]() {
                auto it = c.Reverse().end();
                CHECK_THROWS_AS(++it, std::out_of_range);
            },
            [&]() {
                auto it = c.SideCross().end();
                CHECK_THROWS_AS(++it, std::out_of_range);
            },
            [&]() {
                auto it = c.MiddleOut().end();
                CHECK_THROWS_AS(++it, std::out_of_range);
            },
            [&]() {
                auto it = c.Regular().end();
                CHECK_THROWS_AS(++it, std::out_of_range);
            }
        };

        for (const auto& test_func : tests) {
            test_func();  // מריץ כל בדיקה
        }
    }
}

