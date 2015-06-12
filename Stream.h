// Stream.h
//
// List-like stream implemented using the 'pull' principle instead of 'push',
// to be lazy
//
#ifndef CPPFUNC_STREAM_H_
#define CPPFUNC_STREAM_H_

#include <functional>
#include <memory>

#include "Susp.h"

template<typename T>
class Stream
{
public:
    class Cell
    {
    public:
        Cell() {}
        Cell(T t) : t_(t) {}
        Cell(T t, Stream next) : t_(t), next_(next) {}
        T val() const { return t_; }
        Stream next() { return next_; }
    private:
        T t_;
        Stream next_;
    };

    Stream() {}
    Stream(std::function<Cell()> f)
        : lazyCell_(std::make_shared<Susp<Cell> >(f))
    {}

    bool isEmpty() const { return !lazyCell_; }
    T get() const { return lazyCell_->get().val(); }
    Stream<T> next() const { return lazyCell_->get().next(); }

private:
    std::shared_ptr<Susp<Cell> > lazyCell_;
};

template<typename T>
using Cell = typename Stream<T>::Cell;

///
Stream<int> intsFrom(int t)
{
    return Stream<int>([t]()
    {
        return Cell<int>(t, intsFrom(t+1));
    });
}

#endif // CPPFUNC_STREAM_H_
