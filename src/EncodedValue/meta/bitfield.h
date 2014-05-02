#pragma once

#include "EncodedValue/reference.h"
#include "EncodedValue/endian.h"
#include <cstring>

namespace EncodedValue {
namespace Meta {

template <typename T, typename Base, int offset, int bits, bool convertEndian>
class BitField {
public:
    static const size_t size = sizeof(Base);
    typedef T type;
    typedef Impl::Reference<BitField> reference;

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

}
}
