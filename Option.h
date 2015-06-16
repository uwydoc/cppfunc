// Option.h
//
// Haskell 'Option' implementation
//
#ifndef CPPFUNC_OPTION_H_
#define CPPFUNC_OPTION_H_

#include <stdexcept>
#include <type_traits>

template<typename T>
class Option
{
private:
    bool inited_;
    union {
        char data[sizeof(T)];
        typename std::aligned_storage<sizeof(T), alignof(T)>::type aligner;
    } storage;

public:
    Option() : inited_(false) {}
    Option(T t) : inited_(true) { new (storage.data) T(t); }

    bool isEmpty() const { return !inited_; }
    T get() const {
        if (!isEmpty())
            return *((T*)storage.data);
        throw std::runtime_error("empty option!");
    }
    bool operator!() const { return isEmpty(); }
};

#endif // CPPFUNC_OPTION_H_
