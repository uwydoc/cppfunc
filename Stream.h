// Stream.h
//
// List-like stream implemented using the 'pull' principle instead of 'push',
// to be lazy
//
#ifndef CPPFUNC_STREAM_H_
#define CPPFUNC_STREAM_H_

#include <functional>
#include <memory>

#include "Cell.h"
#include "Susp.h"

template<typename T>
class Stream
{
    std::shared_ptr<Susp<Cell<T> > > lazyCell_;
public:
    Stream() {}
    Stream(std::function<Cell<T>()> f)
        : lazyCell_(std::make_shared<Susp<Cell<T> > >(f))
    {}

    bool isEmpty() const { return !lazyCell_; }
    T get() const { return lazyCell_->get().val(); }
    Stream<T> next() const { return lazyCell_->get().next(); }
};

///
template<typename T>
Stream<T> seqFrom(T t)
{
    return Stream<T>([t]()
    {
        return Cell<T>(t, seqFrom(++t));
    });
}

#endif // CPPFUNC_STREAM_H_
