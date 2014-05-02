#pragma once

#include <cstddef>

namespace EncodedValue {
namespace Impl {

template<class M>
class Pointer {
    char * _ptr;

public:
    typedef typename M::reference Reference;

    Pointer(char * ptr) : _ptr(ptr) { }

    char * ptr() const {
        return _ptr;
    }

    Pointer operator+(size_t s) const {
        return Pointer(_ptr + (M::size * s));
    }

    Pointer& operator+=(size_t s) {
        _ptr += (M::size * s);
        return *this;
    }

    Pointer operator-(size_t s) const {
        return Pointer(_ptr - (M::size * s));
    }

    Pointer& operator-=(size_t s) {
        _ptr -= (M::size * s);
        return *this;
    }

    Pointer& operator++() {
        _ptr += M::size;
        return *this;
    }

    Pointer operator++(int) {
        Pointer tmp(_ptr);
        operator++();
        return tmp;
    }

    Pointer& operator--() {
        _ptr -= M::size;
        return *this;
    }

    Pointer operator--(int) {
        Pointer tmp(_ptr);
        operator--();
        return tmp;
    }

    Pointer & operator=(const Pointer & other) {
        _ptr = other._ptr;

        return *this;
    }

    Reference operator[](int x) {
        return Reference(_ptr + (x * M::size));
    }

    Reference operator*() const {
        return Reference(_ptr);
    }

    Reference * operator->() {
        return (Reference *)this;
    }
};

}
}
