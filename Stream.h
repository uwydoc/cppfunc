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
#include <type_traits>

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
Stream<int> intsFrom(int t, int step=1)
{
    return Stream<int>([t, step]()
    {
        return Cell<int>(t, intsFrom(t+step));
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
Stream<T> range(T begin, T end, T step=T(1));
template<>
Stream<int> range<int>(int begin, int end, int step)
{
    if (begin >= end)
        return Stream<int>();
    else
        return Stream<int>([begin, end, step]() {
            return Cell<int>(begin, range<int>(begin+step, end));
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
/// forEach
template<typename T, typename F>
void forEach(Stream<T> s, F f)
{
    while (!s.isEmpty()) {
        f(s.get());
        s = s.next();
    }
}
/// concat
template<typename T>
Stream<T> concat(Stream<T> s1, Stream<T> s2)
{
    if (s1.isEmpty())
        return s2;
    return Stream<T>([s1, s2]() {
        return Cell<T>(s1.get(), concat(s1.next(), s2));
    });
}
/// @group Functor fmap
template<typename T, typename F, typename R = typename std::result_of<F(T)>::type>
Stream<R> fmap(Stream<T> s, F f)
{
    if (s.isEmpty())
        return Stream<R>();

    return Stream<R>([s, f]()
    {
        return Cell<R>(f(s.get()), fmap(s.next(), f));
    });
}
/// @group Monad mjoin
template<typename T>
Stream<T> mjoin(Stream<Stream<T> > ss)
{
    if (ss.isEmpty())
        return Stream<T>();
    if (ss.get().isEmpty())
        return mjoin(ss.next());
    return Stream<T>([ss]()
    {
        Stream<T> hd = ss.get();
        return Cell<T>(hd.get(),
            mjoin(Stream<Stream<T> >([hd, ss]() {
                    return Cell<Stream<T> >(hd.next(), ss.next());
            }))
        );
    });
}
/// @group Monad mbind
template<typename T, typename F, typename StreamR = typename std::result_of<F(T)>::type>
StreamR mbind(Stream<T> s, F f)
{
    return mjoin(fmap(s, f));
}
/// @group Monad mreturn
template<typename T>
Stream<T> mreturn(T t)
{
    return Stream<T>([t]() { return Cell<T>(t); });
}

#endif // CPPFUNC_STREAM_H_
