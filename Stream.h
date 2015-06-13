// Stream.h
//
// List-like stream implemented using the 'pull' principle instead of 'push',
// to be lazy
//
#ifndef CPPFUNC_STREAM_H_
#define CPPFUNC_STREAM_H_

#include <functional>
#include <iostream>
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

/// Expose inner class 'Cell', to make 'Cell' instantiation less verbose
template<typename T>
using Cell = typename Stream<T>::Cell;

/// intsFrom
Stream<int> intsFrom(int t)
{
    return Stream<int>([t]()
    {
        return Cell<int>(t, intsFrom(t+1));
    });
}
/// take
template<typename T>
Stream<T> take(Stream<T> s, int n)
{
    if (n == 0 || s.isEmpty())
        return Stream<T>();
    return Stream<T>([s, n]() {
        return Cell<T>(s.get(), take(s.next(), n-1));
    });
}
/// range
template<typename T>
Stream<T> range(T begin, T end);
template<>
Stream<int> range<int>(int begin, int end)
{
    if (begin == end)
        return Stream<int>();
    else
        return Stream<int>([begin, end]() {
            return Cell<int>(begin, range<int>(begin+1, end));
        });
}
/// output
template<typename T>
std::ostream& operator<<(std::ostream& os, const Stream<T>& s)
{
    if (s.isEmpty())
        return os;
    os << s.get() << ' ';
    return (os << s.next());
}

#endif // CPPFUNC_STREAM_H_
