// Author : noapatito123@gmail.com
#include "MyContainer.hpp"
#include <iostream>
using namespace containers;

int main()
{
    std::cout << "\n--- Default Container --- \n";
    MyContainer<> default_container; // default type is int
    default_container.add(7.3);
    std::cout << default_container << "\n";

    MyContainer<int> int_container;
    int_container.add(3);
    int_container.add(3);
    int_container.add(7);
    int_container.add(15);
    int_container.add(3);
    int_container.add(6);
    int_container.add(3);
    int_container.add(1);
    int_container.add(2);
    int_container.add(3);

    std::cout << "\nData in the container before remove: ";
    std::cout << int_container << "\n";

    int_container.remove(3);

    std::cout << "\nData in the container after remove: ";
    std::cout << int_container << "\n";

    std::cout << "\n--- Trying to remove non-existent element 8 --- \n\n";
    try
    {
        int_container.remove(8);
    }
    catch (const std::exception &e)
    {
        std::cout << "Caught exception: " << e.what() << "\n\n";
    }

    std::cout << "\n--- Integers Container --- \n";
    std::cout << "\nData in the container: ";
    std::cout << int_container << "\n"; 

    std::cout << "Integers - Ascending: ";
    for (const auto &it : int_container.Ascending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - Descending: ";
    for (const auto &it : int_container.Descending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - SideCross: ";
    for (const auto &it : int_container.SideCross())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - Reverse: ";
    for (const auto &it : int_container.Reverse())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - Regular: ";
    for (const auto &it : int_container.Regular())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Integers - MiddleOut: ";
    for (const auto &it : int_container.MiddleOut())
        std::cout << it << " ";
    std::cout << "\n\n";

    std::cout << "\n--- Strings Container --- \n";
    MyContainer<std::string> str_container;
    str_container.add("banana");
    str_container.add("apple");
    str_container.add("cherry");
    str_container.add("date");

    std::cout << "\nData in the container: ";
    std::cout << str_container << "\n";

    std::cout << "Strings - Ascending: ";
    for (const auto &it : str_container.Ascending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Strings - Descending: ";
    for (const auto &it : str_container.Descending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Strings - SideCross: ";
    for (const auto &it : str_container.SideCross())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Strings - Reverse: ";
    for (const auto &it : str_container.Reverse())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Strings - Regular: ";
    for (const auto &it : str_container.Regular())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Strings - MiddleOut: ";
    for (const auto &it : str_container.MiddleOut())
        std::cout << it << " ";
    std::cout << "\n\n";

    std::cout << "\n--- Doubles Container --- \n";
    MyContainer<double> dbl_container;
    dbl_container.add(3.14);
    dbl_container.add(3.11);
    dbl_container.add(2.718);
    dbl_container.add(0.577);

    std::cout << "\nData in the container: ";
    std::cout << dbl_container << "\n";

    std::cout << "Doubles - Ascending: ";
    for (const auto &it : dbl_container.Ascending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - Descending: ";
    for (const auto &it : dbl_container.Descending())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - SideCross: ";
    for (const auto &it : dbl_container.SideCross())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - Reverse: ";
    for (const auto &it : dbl_container.Reverse())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - Regular: ";
    for (const auto &it : dbl_container.Regular())
        std::cout << it << " ";
    std::cout << "\n";

    std::cout << "Doubles - MiddleOut: ";
    for (const auto &it : dbl_container.MiddleOut())
        std::cout << it << " ";
    std::cout << "\n\n";

    return 0;
}
