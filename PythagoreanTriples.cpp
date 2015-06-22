// PythagoreanTriples.cpp
//
// Solving the classic Pythagorean triples problem with lazy Stream
//
#include <iostream>

#include <boost/timer/timer.hpp>

#include "Stream.h"
#include "Triple.h"

int main(int argc, char* argv[])
{
    std::cout << "--- triples(first 10)" << std::endl;
    std::cout << take(triples(), 10) << std::endl;
    std::cout << "--- pythagorean triples(within 20)" << std::endl;
    std::cout << triples(20, [](int x, int y, int z) { return (x*x + y*y == z*z); }) << std::endl;
    /// benchmark
    int count = argc > 1 ? std::atoi(argv[1]) : 50;
    std::cout << "--- benchmark (with lazy Stream)" << std::endl;
    int sum = 0;
    boost::timer::cpu_timer t;
    forEach(take(triples(INT_MAX-1, [&sum](int x, int y, int z) { return (x*x + y*y == z*z); }), count), [&sum](Triple t) { sum += (std::get<0>(t) + std::get<1>(t) + std::get<2>(t)); });
    std::cout << t.format() << std::endl;
    std::cout << "sum: " << sum << std::endl;
    /// nested loops
    std::cout << "--- benchmark (with nested loops)" << std::endl;
    sum = 0;
    int found = 0;
    bool done = false;
    boost::timer::cpu_timer t1;
    for (int z = 1; !done && z < INT_MAX; ++z) {
        for (int y = 1; !done && y < z; ++y) {
            for (int x = 1; !done && x <= y; ++x) {
                if (x*x + y*y == z*z) {
                    sum += (x + y + z);
                    if (++found == count)
                        done = true;
                }
            }
        }
    }
    std::cout << t1.format() << std::endl;
    std::cout << "sum: " << sum << std::endl;

    return 0;
}
