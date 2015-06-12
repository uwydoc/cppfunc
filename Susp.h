// Susp.h
//
// Thin wrapper around function-like objects to make them lazily evaluated
// only when the value is needed.
//
// @note Instead of caching the return value directly, use the thunk-pattern
// to do return value memoization
//
#ifndef CPPFUNC_SUSP_H_
#define CPPFUNC_SUSP_H_

#include <functional>

template<typename T>
class Susp
{
    // thunks
    static const T& thunkForce(Susp* susp) { return susp->setMemo(); }
    static const T& thunkGet(Susp* susp) { return susp->getMemo(); }
    const T& getMemo() { return memo_; }
    const T& setMemo()
    {
        memo_ = f_();
        thunk_ = &thunkGet;
        return memo_;
    }
public:
    explicit Susp(std::function<T()> f)
        : f_(f), thunk_(&thunkForce)
    {}
    T get() { return thunk_(this);  }
private:
    std::function<T()> f_;
    const T& (*thunk_)(Susp*);
    mutable T memo_;
};

#endif // CPPFUNC_SUSP_H_
