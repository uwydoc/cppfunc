// OptionTest.cpp
//
#include "Option.h"

#include <iostream>

class Foo
{
public:
    Foo(int x) : x_(x) {}
    int x_;
};

int main()
{
    Option<int> opt(10);
    std::cout << opt.get() << std::endl;
    try {
        Option<int> empty;
        std::cout << empty.get() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "empty option" << std::endl;
    }
    Foo foo5(5);
    Option<Foo> of(foo5);
    std::cout << of.get().x_ << std::endl;
    Option<Foo> eof;
}
