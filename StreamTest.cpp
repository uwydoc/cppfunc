// StreamTest.cpp
//
#include "Stream.h"

#include <iostream>

int main()
{
    std::cout << take(intsFrom(1), 10) << std::endl;
    std::cout << take(range(10, 20), 5) << std::endl;
}
