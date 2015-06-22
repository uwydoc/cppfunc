// Triple.h
//
// Generate int triples lazily
//
#ifndef CPPFUNC_TRIPLE_INCLUDED
#define CPPFUNC_TRIPLE_INCLUDED

#include <iostream>
#include <tuple>
#include <type_traits>

#include "Stream.h"

using Triple = std::tuple<int,int,int>;

template<typename F,
    typename std::enable_if<std::is_convertible<F, std::function<bool(int,int,int)> >::value>::type* = nullptr>
Stream<Triple> triples(int maxz, F f)
{
    return mbind(range(1, maxz+1), [f](int z) {
            return mbind(range(1, z), [z,f](int y) {
                    return mbind(range(1, y+1), [y,z,f](int x) {
                            if (f(x, y, z))
                                return mreturn(std::make_tuple(x, y, z));
                            else
                                return Stream<Triple>();
                            });
                    });
            });
}
template<typename F,
    typename std::enable_if<std::is_convertible<F, std::function<bool(Triple)> >::value>::type* = nullptr>
Stream<Triple> triples(int maxz, F f)
{
    return triples(maxz, [f](int x, int y, int z) { return f(std::make_tuple(x, y, z)); });
}

Stream<Triple> triples(int maxz=INT_MAX-1)
{
    return triples(maxz, [](int,int,int) { return true; });
}

std::ostream& operator<<(std::ostream& os, const Triple& t)
{
    int x, y, z;
    std::tie(x, y, z) = t;
    return (os << '(' << x << ',' << y << ',' << z << ')');
}

#endif // CPPFUNC_TRIPLE_INCLUDED
