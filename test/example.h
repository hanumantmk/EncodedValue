#include "EncodedValue.h"


template <bool convertEndian = true>
class Complex {
public:

    static const int _size = 0 + sizeof(double) + sizeof(double);

class Reference {
public:
    static const int _size = 0 + sizeof(double) + sizeof(double);

private:
    char * storage;
public:
    Reference() {}

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    typename EncodedValue::Pointer<double, convertEndian>::Reference real() {
        return typename EncodedValue::Pointer<double, convertEndian>::Reference(storage +0);
    }

    typename EncodedValue::Pointer<double, convertEndian>::Reference imag() {
        return typename EncodedValue::Pointer<double, convertEndian>::Reference(storage +0 + sizeof(double));
    }

    Reference(char * in) {
        storage = in;
    }

    EncodedValue::EVPointer<Complex> operator &() {
        return EncodedValue::EVPointer<Complex>(storage);
    }

};

class Value {
public:
    static const int _size = 0 + sizeof(double) + sizeof(double);

private:
    char storage[_size];
public:
    Value() {}

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    typename EncodedValue::Pointer<double, convertEndian>::Reference real() {
        return typename EncodedValue::Pointer<double, convertEndian>::Reference(storage +0);
    }

    typename EncodedValue::Pointer<double, convertEndian>::Reference imag() {
        return typename EncodedValue::Pointer<double, convertEndian>::Reference(storage +0 + sizeof(double));
    }

    Value(char * in) {
        std::memcpy(storage, in, _size);
    }

    Value(const Reference & p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    EncodedValue::EVPointer<Complex> operator &() {
        return EncodedValue::EVPointer<Complex>(storage);
    }

};

};
template <bool convertEndian = true>
class Type {
public:

    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex<convertEndian>::_size>::result >::result ;

class Reference {
public:
    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex<convertEndian>::_size>::result >::result ;

private:
    char * storage;
public:
    Reference() {}

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference type() {
        return typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference(storage +0);
    }

    typename EncodedValue::Pointer<int, convertEndian>::Reference i() {
        return typename EncodedValue::Pointer<int, convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    typename EncodedValue::Pointer<double, convertEndian>::Reference d() {
        return typename EncodedValue::Pointer<double, convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    typename Complex<convertEndian>::Reference c() {
        return typename Complex<convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    Reference(char * in) {
        storage = in;
    }

    EncodedValue::EVPointer<Type> operator &() {
        return EncodedValue::EVPointer<Type>(storage);
    }

};

class Value {
public:
    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex<convertEndian>::_size>::result >::result ;

private:
    char storage[_size];
public:
    Value() {}

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference type() {
        return typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference(storage +0);
    }

    typename EncodedValue::Pointer<int, convertEndian>::Reference i() {
        return typename EncodedValue::Pointer<int, convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    typename EncodedValue::Pointer<double, convertEndian>::Reference d() {
        return typename EncodedValue::Pointer<double, convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    typename Complex<convertEndian>::Reference c() {
        return typename Complex<convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    Value(char * in) {
        std::memcpy(storage, in, _size);
    }

    Value(const Reference & p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    EncodedValue::EVPointer<Type> operator &() {
        return EncodedValue::EVPointer<Type>(storage);
    }

};

};
template <bool convertEndian = true>
class Expression {
public:

    static const int _size = 0 + sizeof(unsigned char) + (Type<convertEndian>::_size * 2);

class Reference {
public:
    static const int _size = 0 + sizeof(unsigned char) + (Type<convertEndian>::_size * 2);

private:
    char * storage;
public:
    Reference() {}

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference op() {
        return typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference(storage +0);
    }

    EncodedValue::EVPointer<Type<convertEndian> > args() {
        return EncodedValue::EVPointer<Type<convertEndian> >(storage +0 + sizeof(unsigned char));
    }

    Reference(char * in) {
        storage = in;
    }

    EncodedValue::EVPointer<Expression> operator &() {
        return EncodedValue::EVPointer<Expression>(storage);
    }

};

class Value {
public:
    static const int _size = 0 + sizeof(unsigned char) + (Type<convertEndian>::_size * 2);

private:
    char storage[_size];
public:
    Value() {}

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference op() {
        return typename EncodedValue::Pointer<unsigned char, convertEndian>::Reference(storage +0);
    }

    EncodedValue::EVPointer<Type<convertEndian> > args() {
        return EncodedValue::EVPointer<Type<convertEndian> >(storage +0 + sizeof(unsigned char));
    }

    Value(char * in) {
        std::memcpy(storage, in, _size);
    }

    Value(const Reference & p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    EncodedValue::EVPointer<Expression> operator &() {
        return EncodedValue::EVPointer<Expression>(storage);
    }

};

};
