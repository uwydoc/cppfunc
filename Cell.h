// Cell.h
//
#ifndef CPPFUNC_CELL_H_
#define CPPFUNC_CELL_H_

#include "Stream.h"

template<typename T>
class Cell
{
public:
    Cell() {}
    Cell(T t) : t_(t) {}
    Cell(T t, const Stream<T>& next)
        : t_(t), next_(tail)
    {}
    T val() const { return t_; }
    Stream<T> next() const { return tail_; }
private:
    T t_;
    Stream<T> next_;
};

#endif // CPPFUNC_CELL_H_
