// SuspTest.cpp
//
#include "Susp.h"

#include <iostream>

int main()
{
    int n = 10;
    Susp<int> susp([&n]() {
        std::cout << "function evaluated" << std::endl;
        return n++;
    });
    int i = susp.get();
    int j = susp.get();
    std::cout << i << ' ' << j << ' ' << n << std::endl;
}
