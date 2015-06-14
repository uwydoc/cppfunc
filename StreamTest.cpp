// StreamTest.cpp
//
#include "Stream.h"

#include <iostream>

int main()
{
    std::cout << "--- intsFrom" << std::endl;
    std::cout << take(intsFrom(1), 10) << std::endl;
    std::cout << "--- range" << std::endl;
    std::cout << take(range(10, 20), 5) << std::endl;
    std::cout << "--- forEach" << std::endl;
    forEach(range(30, 33), [](int t) {
        std::cout << t << std::endl;
    });
    std::cout << "--- concat" << std::endl;
    std::cout << concat(range(1, 5), range(5, 10)) << std::endl;
    // Functor
    std::cout << "--- fmap" << std::endl;
    std::cout << fmap(range(10, 15), [](int t) { return t+1; }) << std::endl;
    // Monad
    std::cout << "--- mreturn" << std::endl;
    std::cout << mreturn(3) << std::endl;
    std::cout << "--- mbind" << std::endl;
    std::cout << mbind(range(1, 4), [](int x) { return range(1, x+1); }) << std::endl;
}
