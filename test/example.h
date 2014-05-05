#include "EncodedValue.h"


template <bool convertEndian = true>
class Complex {
public:

    static const int _size = 0 + sizeof(double) + sizeof(double);

    typedef EncodedValue::Impl::Pointer<EncodedValue::Meta::EV<Complex<convertEndian> > > Pointer;

    class Value;

    class Reference;

class Reference {
public:
    static const int _size = 0 + sizeof(double) + sizeof(double);

private:
    char * storage;
public:
    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    Reference& operator=(const Reference& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    Reference& operator=(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    typename EncodedValue::Reference<double, convertEndian> real() {
        return typename EncodedValue::Reference<double, convertEndian>(storage +0);
    }

    typename EncodedValue::Reference<double, convertEndian> imag() {
        return typename EncodedValue::Reference<double, convertEndian>(storage +0 + sizeof(double));
    }

    Reference(char * in) {
        storage = in;
    }

    Reference(const Value& p) {
        storage = p.ptr();
    }

    Pointer operator &() {
        return Pointer(storage);
    }

};

class Value {
public:
    static const int _size = 0 + sizeof(double) + sizeof(double);

private:
    char storage[_size];
public:
    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    Value& operator=(const Reference& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    Value& operator=(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    typename EncodedValue::Reference<double, convertEndian> real() {
        return typename EncodedValue::Reference<double, convertEndian>(storage +0);
    }

    typename EncodedValue::Reference<double, convertEndian> imag() {
        return typename EncodedValue::Reference<double, convertEndian>(storage +0 + sizeof(double));
    }

    Value() {}

    Value(char * in) {
        std::memcpy(storage, in, _size);
    }

    Value(const Reference & p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    Value(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    Pointer operator &() {
        return Pointer(storage);
    }

};

};
template <bool convertEndian = true>
class Type {
public:

    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex<convertEndian>::_size>::result >::result ;

    typedef EncodedValue::Impl::Pointer<EncodedValue::Meta::EV<Type<convertEndian> > > Pointer;

    class Value;

    class Reference;

class Reference {
public:
    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex<convertEndian>::_size>::result >::result ;

private:
    char * storage;
public:
    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    Reference& operator=(const Reference& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    Reference& operator=(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    typename EncodedValue::Reference<unsigned char, convertEndian> type() {
        return typename EncodedValue::Reference<unsigned char, convertEndian>(storage +0);
    }

    typename EncodedValue::Reference<int, convertEndian> i() {
        return typename EncodedValue::Reference<int, convertEndian>(storage +0 + sizeof(unsigned char));
    }

    typename EncodedValue::Reference<double, convertEndian> d() {
        return typename EncodedValue::Reference<double, convertEndian>(storage +0 + sizeof(unsigned char));
    }

    typename Complex<convertEndian>::Reference c() {
        return typename Complex<convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    Reference(char * in) {
        storage = in;
    }

    Reference(const Value& p) {
        storage = p.ptr();
    }

    Pointer operator &() {
        return Pointer(storage);
    }

};

class Value {
public:
    static const int _size = 0 + sizeof(unsigned char) + EncodedValue::_max< sizeof(int), EncodedValue::_max< sizeof(double), Complex<convertEndian>::_size>::result >::result ;

private:
    char storage[_size];
public:
    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    Value& operator=(const Reference& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    Value& operator=(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    typename EncodedValue::Reference<unsigned char, convertEndian> type() {
        return typename EncodedValue::Reference<unsigned char, convertEndian>(storage +0);
    }

    typename EncodedValue::Reference<int, convertEndian> i() {
        return typename EncodedValue::Reference<int, convertEndian>(storage +0 + sizeof(unsigned char));
    }

    typename EncodedValue::Reference<double, convertEndian> d() {
        return typename EncodedValue::Reference<double, convertEndian>(storage +0 + sizeof(unsigned char));
    }

    typename Complex<convertEndian>::Reference c() {
        return typename Complex<convertEndian>::Reference(storage +0 + sizeof(unsigned char));
    }

    Value() {}

    Value(char * in) {
        std::memcpy(storage, in, _size);
    }

    Value(const Reference & p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    Value(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    Pointer operator &() {
        return Pointer(storage);
    }

};

};
template <bool convertEndian = true>
class Expression {
public:

    static const int _size = 0 + sizeof(unsigned char) + (Type<convertEndian>::_size * 2);

    typedef EncodedValue::Impl::Pointer<EncodedValue::Meta::EV<Expression<convertEndian> > > Pointer;

    class Value;

    class Reference;

class Reference {
public:
    static const int _size = 0 + sizeof(unsigned char) + (Type<convertEndian>::_size * 2);

private:
    char * storage;
public:
    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    Reference& operator=(const Reference& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    Reference& operator=(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    typename EncodedValue::BitField::Reference<unsigned, unsigned char, 0, 4, convertEndian> op() {
        return typename EncodedValue::BitField::Reference<unsigned, unsigned char, 0, 4, convertEndian>(storage +0);
    }

    typename EncodedValue::BitField::Reference<unsigned, unsigned char, 4, 3, convertEndian> precedence() {
        return typename EncodedValue::BitField::Reference<unsigned, unsigned char, 4, 3, convertEndian>(storage +0);
    }

    typename EncodedValue::BitField::Reference<unsigned, unsigned char, 7, 1, convertEndian> is_infix() {
        return typename EncodedValue::BitField::Reference<unsigned, unsigned char, 7, 1, convertEndian>(storage +0);
    }

    typename Type<convertEndian>::Pointer args() {
        return typename Type<convertEndian>::Pointer(storage +0 + sizeof(unsigned char));
    }

    Reference(char * in) {
        storage = in;
    }

    Reference(const Value& p) {
        storage = p.ptr();
    }

    Pointer operator &() {
        return Pointer(storage);
    }

};

class Value {
public:
    static const int _size = 0 + sizeof(unsigned char) + (Type<convertEndian>::_size * 2);

private:
    char storage[_size];
public:
    void zero() {
        std::memset(storage, 0, _size);
    }

    char * ptr() const {
        return (char *)storage;
    }

    Value& operator=(const Reference& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    Value& operator=(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
        return *this;
    }

    typename EncodedValue::BitField::Reference<unsigned, unsigned char, 0, 4, convertEndian> op() {
        return typename EncodedValue::BitField::Reference<unsigned, unsigned char, 0, 4, convertEndian>(storage +0);
    }

    typename EncodedValue::BitField::Reference<unsigned, unsigned char, 4, 3, convertEndian> precedence() {
        return typename EncodedValue::BitField::Reference<unsigned, unsigned char, 4, 3, convertEndian>(storage +0);
    }

    typename EncodedValue::BitField::Reference<unsigned, unsigned char, 7, 1, convertEndian> is_infix() {
        return typename EncodedValue::BitField::Reference<unsigned, unsigned char, 7, 1, convertEndian>(storage +0);
    }

    typename Type<convertEndian>::Pointer args() {
        return typename Type<convertEndian>::Pointer(storage +0 + sizeof(unsigned char));
    }

    Value() {}

    Value(char * in) {
        std::memcpy(storage, in, _size);
    }

    Value(const Reference & p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    Value(const Value& p) {
        std::memcpy(storage, p.ptr(), _size);
    }

    Pointer operator &() {
        return Pointer(storage);
    }

};

};
