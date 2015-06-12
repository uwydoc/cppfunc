// StreamTest.cpp
//
#include "Stream.h"

#include <iostream>

template<typename T>
void printUtil(Stream<T> seq, T end)
{
    T t = seq.get();
    if (t == end) {
        std::cout << std::endl;
        return;
    }
    std::cout << t << ' ';
    printUtil(seq.next(), end);
}

int main()
{
    Stream<int> seq = intsFrom(1);
    printUtil(seq, 10);
}
