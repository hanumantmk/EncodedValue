#include <cstring>
#include <algorithm>
#include <iostream>

namespace PortablePackedStruct {
template <int A, int B>
class _max {
public:
    static const int result = A > B ? A : B;
};

namespace endian {

template<typename T>
class needsSwab {
public:
    static const bool result = false;
};

#pragma push_macro("NEEDS_SWAB")
#define NEEDS_SWAB(type) \
    template<> \
    class needsSwab<type> { \
    public: \
        static const bool result = true; \
    };

NEEDS_SWAB(int16_t);
NEEDS_SWAB(uint16_t);
NEEDS_SWAB(int32_t);
NEEDS_SWAB(uint32_t);
NEEDS_SWAB(int64_t);
NEEDS_SWAB(uint64_t);
NEEDS_SWAB(double);
NEEDS_SWAB(float);

#undef NEEDS_SWAB
#pragma pop_macro("NEEDS_SWAB")

template<typename T>
inline T swab(T t) {
    char * front, * back;

    if (! needsSwab<T>::result) {
        return t;
    }

    front = (char *)&t;
    back = front + sizeof(T) - 1;

    for (; front < back; ++front, --back) {
        std::swap(*front, *back);
    }

    return t;
}

}

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
};

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

private:
    Reference() {}
    Reference& operator=(const Reference& other) {}

    char * _ptr;
};

template <typename T, bool convertEndian>
class Memcpy {
public:
    static const size_t size = sizeof(T);
    typedef T type;
    typedef Reference<Memcpy> reference;

    static inline void writeTo(const T& t, void * ptr) {
        if (endian::needsSwab<T>::result && convertEndian) {
            T tmp = endian::swab(t);
            std::memcpy(ptr, &tmp, size);
        } else {
            std::memcpy(ptr, &t, size);
        }
    }

    static inline void readFrom(T& t, const void * ptr) {
        std::memcpy(&t, ptr, size);

        if (endian::needsSwab<T>::result && convertEndian) {
            t = endian::swab(t);
        }
    }
};

template <typename T, typename Base, int offset, int bits, bool convertEndian>
class BitField {
public:
    static const size_t size = sizeof(Base);
    typedef T type;
    typedef Reference<BitField> reference;

    static inline void writeTo(const T& t, void * ptr) {
        Base b;
        std::memcpy(&b, ptr, sizeof(Base));

        if (endian::needsSwab<Base>::result && convertEndian) {
            b = endian::swab(b);
        }

        b &= ~(((1 << bits) - 1) << offset);
        b |= t << offset;

        if (endian::needsSwab<Base>::result && convertEndian) {
            b = endian::swab(b);
        }

        std::memcpy(ptr, &b, sizeof(Base));
    }

    static inline void readFrom(T& t, const void * ptr) {
        Base b;
        T tmp;

        std::memcpy(&b, ptr, sizeof(Base));
        if (endian::needsSwab<Base>::result && convertEndian) {
            b = endian::swab(b);
        }

        tmp = (b >> offset) & ((1 << bits) - 1);

        t = tmp;
    }
};

template <typename T>
class PPS {
public:
    static const size_t size = T::_size;
    typedef typename T::Ptr reference;
};

}

template <class T, bool convertEndian = true>
class Pointer : public Impl::Pointer<Impl::Memcpy<T, convertEndian> > {
public:
    Pointer(char * in) : Impl::Pointer<Impl::Memcpy<T, convertEndian> >(in) {}
};

template <typename T, typename Base, int offset, int bits, bool convertEndian = true>
class BitFieldPointer : public Impl::Pointer<Impl::BitField<T, Base, offset, bits, convertEndian> > {
public:
    BitFieldPointer(char * in) : Impl::Pointer<Impl::BitField<T, Base, offset, bits, convertEndian> >(in) {}
};

template <class T>
class PPSPointer : public Impl::Pointer<Impl::PPS<T> > {
public:
    PPSPointer(char * in) : Impl::Pointer<Impl::PPS<T> >(in) {}
};

}
