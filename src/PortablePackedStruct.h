#include <cstring>

namespace PortablePackedStruct {
template <int A, int B>
class _max {
public:
    static const int result = A > B ? A : B;
};
static const int _size = 0 + sizeof(int) + sizeof(short);

namespace Impl {

template<class M, class R>
class Pointer {
    char * _ptr;

public:
    typedef R Reference;

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

    R operator[](int x) {
        return R (_ptr + (x * M::size));
    }

    R operator*() const {
        return R(_ptr);
    }
};

template <typename T>
class Memcpy {
public:
    static const size_t size = sizeof(T);
    typedef T type;

    static inline void writeTo(const T& t, void * ptr) {
        std::memcpy(ptr, &t, size);
    }

    static inline void readFrom(T& t, const void * ptr) {
        std::memcpy(&t, ptr, size);
    }
};

template <typename T, typename Base, int offset, int bits>
class BitField {
public:
    static const size_t size = sizeof(Base);
    typedef T type;

    static inline void writeTo(const T& t, void * ptr) {
        Base b;
        Memcpy<Base>::readFrom(b, ptr);
        b &= ~(((1 << bits) - 1) << offset);
        b |= t << offset;

        Memcpy<Base>::writeTo(b, ptr);
    }

    static inline void readFrom(T& t, const void * ptr) {
        Base b;
        T tmp;
        Memcpy<Base>::readFrom(b, ptr);

        tmp = (b >> offset) & ((1 << bits) - 1);

        t = tmp;
    }
};

template <typename T>
class PPS {
public:
    static const size_t size = T::_size;
    typedef T type;
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

}

template <class T>
class Pointer : public Impl::Pointer<Impl::Memcpy<T>, Impl::Reference<Impl::Memcpy<T> > > {
public:
    Pointer(char * in) : Impl::Pointer<Impl::Memcpy<T>, Impl::Reference<Impl::Memcpy<T> > >(in) {}
};

template <typename T, typename Base, int offset, int bits>
class BitFieldPointer : public Impl::Pointer<Impl::BitField<T, Base, offset, bits>, Impl::Reference<Impl::BitField<T, Base, offset, bits> > > {
public:
    BitFieldPointer(char * in) : Impl::Pointer<Impl::BitField<T, Base, offset, bits>, Impl::Reference<Impl::BitField<T, Base, offset, bits> > >(in) {}
};

template <class T>
class PPSPointer : public Impl::Pointer<Impl::PPS<T>, typename T::Ptr> {
public:
    PPSPointer(char * in) : Impl::Pointer<Impl::PPS<T>, typename T::Ptr>(in) {}
};

}
