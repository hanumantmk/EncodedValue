#pragma once

namespace PortablePackedStruct {
namespace Impl {

template <class M> class Pointer;

template <class M>
class Reference {
typedef typename M::type T;
public:
    Reference& operator=( const T& other ) {
        M::writeTo(other, _ptr);
        
        return *this;
    }

    operator T() {
        T t;
        M::readFrom(t, _ptr);

        return t;
    }

    Reference& operator+=(const T& other) {
        operator=(operator T() + other);

        return *this;
    }

    Reference& operator-=(const T& other) {
        operator=(operator T() - other);

        return *this;
    }

    Reference& operator*=(const T& other) {
        operator=(operator T() * other);

        return *this;
    }

    Reference& operator/=(const T& other) {
        operator=(operator T() / other);

        return *this;
    }

    Reference& operator%=(const T& other) {
        operator=(operator T() % other);

        return *this;
    }

    Reference& operator&=(const T& other) {
        operator=(operator T() & other);

        return *this;
    }

    Reference& operator|=(const T& other) {
        operator=(operator T() | other);

        return *this;
    }

    Reference& operator^=(const T& other) {
        operator=(operator T() ^ other);

        return *this;
    }

    Reference& operator<<=(const T& other) {
        operator=(operator T() << other);

        return *this;
    }

    Reference& operator>>=(const T& other) {
        operator=(operator T() >> other);

        return *this;
    }

    Reference& operator++() {
        operator+=(1);

        return *this;
    }

    T operator++(int) {
        T tmp = operator T();
        operator++();
        return tmp;
    }

    Reference& operator--() {
        operator-=(1);

        return *this;
    }

    T operator--(int) {
        T tmp = operator T();
        operator--();
        return tmp;
    }

    char * ptr() const {
        return _ptr;
    }

    Reference(const Reference& other) {
        _ptr = other._ptr;
    }

    Reference(char * ptr) : _ptr(ptr) { }

    Impl::Pointer<M> operator&() const {
        return Impl::Pointer<M>(_ptr);
    }

private:
    Reference() {}
    Reference& operator=(const Reference& other) {}

    char * _ptr;
};

}
}
