#include "MyContainer.hpp"
#include <iostream>
using namespace containers;

int main()
{
    MyContainer<> default_container; // default type is int
    std::cout << default_container << "\n";

    MyContainer<int> int_container;
    int_container.add(7);
    int_container.add(15);
    int_container.add(6);
    int_container.add(1);
    int_container.add(2);

    std::cout << "\nTrying to remove non-existent element 8: \n" ;
    try {
        int_container.remove(8);
    } catch (const std::exception& e) {
        std::cout << "Caught exception: " << e.what();
    }

    std::cout << "Data in the container: ";
    std::cout << int_container << "\n"; // יציג עם סוגריים

    std::cout << "Integers - Ascending: ";
    for (auto it : int_container.Ascending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - Descending: ";
    for (auto it : int_container.Descending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - SideCross: ";
    for (auto it : int_container.SideCross())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - Reverse: ";
    for (auto it : int_container.Reverse())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - Regular: ";
    for (auto it : int_container.Regular())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - MiddleOut: ";
    for (auto it : int_container.MiddleOut())
        std::cout << it << " ";
    std::cout << "\n\n";

    // Test with strings
    MyContainer<std::string> str_container;
    str_container.add("banana");
    str_container.add("apple");
    str_container.add("cherry");
    str_container.add("date");

    std::cout << "Strings - Ascending: ";
    for (auto it : str_container.Ascending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Strings - Descending: ";
    for (auto it : str_container.Descending())
        std::cout << it << " ";
    std::cout << "\n\n";

    // Test with doubles
    MyContainer<double> dbl_container;
    dbl_container.add(3.14);
    dbl_container.add(3.11);
    dbl_container.add(2.718);
    dbl_container.add(0.577);

    std::cout << "Doubles - Ascending: ";
    for (auto it : dbl_container.Ascending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - Descending: ";
    for (auto it : dbl_container.Descending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - SideCross: ";
    for (auto it : dbl_container.SideCross())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - Reverse: ";
    for (auto it : dbl_container.Reverse())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - Regular: ";
    for (auto it : dbl_container.Regular())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - MiddleOut: ";
    for (auto it : dbl_container.MiddleOut())
        std::cout << it << " ";
    std::cout << "\n\n";

    return 0;
}
