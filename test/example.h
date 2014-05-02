#include "EncodedValue.h"


class Complex {
public:

    static const int _size = 0 + sizeof(double) + sizeof(double);

template <typename T>
class Base {
protected:
    T storage;
public:
    static const int _size = Complex::_size;

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    EncodedValue::Pointer<double>::Reference real() {
        return EncodedValue::Pointer<double>::Reference(storage +0);
    }

    EncodedValue::Pointer<double>::Reference imag() {
        return EncodedValue::Pointer<double>::Reference(storage +0 + sizeof(double));
    }

};

class Reference : public Base<char *> {
public:
    Reference() {}

    char * ptr() const {
        return (char *)storage;
    }

    Reference(char * in) {
        storage = in;
    }

    EncodedValue::EVPointer<Complex> operator &() {
        return EncodedValue::EVPointer<Complex>(storage);
    }

};

class Value : public Base<char[Complex::_size]> {
public:
    Value() {}

    char * ptr() const {
        return (char *)storage;
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
class Type {
public:

    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex::_size>::result >::result ;

template <typename T>
class Base {
protected:
    T storage;
public:
    static const int _size = Type::_size;

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    EncodedValue::Pointer<unsigned char>::Reference type() {
        return EncodedValue::Pointer<unsigned char>::Reference(storage +0);
    }

    EncodedValue::Pointer<int>::Reference i() {
        return EncodedValue::Pointer<int>::Reference(storage +0 + sizeof(unsigned char));
    }

    EncodedValue::Pointer<double>::Reference d() {
        return EncodedValue::Pointer<double>::Reference(storage +0 + sizeof(unsigned char));
    }

    Complex::Reference c() {
        return Complex::Reference(storage +0 + sizeof(unsigned char));
    }

};

class Reference : public Base<char *> {
public:
    Reference() {}

    char * ptr() const {
        return (char *)storage;
    }

    Reference(char * in) {
        storage = in;
    }

    EncodedValue::EVPointer<Type> operator &() {
        return EncodedValue::EVPointer<Type>(storage);
    }

};

class Value : public Base<char[Type::_size]> {
public:
    Value() {}

    char * ptr() const {
        return (char *)storage;
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
class Expression {
public:

    static const int _size = 0 + sizeof(unsigned char) + (Type::_size * 2);

template <typename T>
class Base {
protected:
    T storage;
public:
    static const int _size = Expression::_size;

    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    EncodedValue::Pointer<unsigned char>::Reference op() {
        return EncodedValue::Pointer<unsigned char>::Reference(storage +0);
    }

    EncodedValue::EVPointer<Type> args() {
        return EncodedValue::EVPointer<Type>(storage +0 + sizeof(unsigned char));
    }

};

class Reference : public Base<char *> {
public:
    Reference() {}

    char * ptr() const {
        return (char *)storage;
    }

    Reference(char * in) {
        storage = in;
    }

    EncodedValue::EVPointer<Expression> operator &() {
        return EncodedValue::EVPointer<Expression>(storage);
    }

};

class Value : public Base<char[Expression::_size]> {
public:
    Value() {}

    char * ptr() const {
        return (char *)storage;
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
