#include <cstring>

namespace PortablePackedStruct {
template <int A, int B>
class _max {
public:
    static const int result = A > B ? A : B;
};
static const int _size = 0 + sizeof(int) + sizeof(short);

template<class M>
class Pointer {
    char * _ptr;

    typedef typename M::type T;
public:

    class Reference {
        friend class Pointer;
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

    private:
        Reference(char * ptr) : _ptr(ptr) { }
        Reference() {}
        Reference& operator=(const Reference& other) {}

        char * _ptr;
    };

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

    Reference operator[](int x) {
        return Reference(_ptr + (x * M::size));
    }

    Pointer & operator=(const Pointer & other) {
        _ptr = other._ptr;

        return *this;
    }

    Reference operator*() const {
        return Reference(_ptr);
    }
};

namespace Impl {

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

    static inline void writeTo(const T& t, void * ptr) {
        std::memcpy(ptr, t.ptr(), T::_size);
    }

    static inline void readFrom(T& t, const void * ptr) {
        t = T((char *)ptr);
    }
};

}
}
