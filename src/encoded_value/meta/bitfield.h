#pragma once

#include "encoded_value/reference.h"
#include "encoded_value/endian.h"
#include <cstring>

namespace encoded_value {
namespace Meta {

template <typename T, typename Base, int offset, int bits, enum endian::ConvertEndian ce>
class BitField {
public:
    static const size_t size = sizeof(Base);
    typedef T type;
    typedef Impl::Reference<BitField> reference;

    static inline void writeTo(const T& t, void * ptr) {
        Base b;
        std::memcpy(&b, ptr, sizeof(Base));

        if (endian::needsSwab<Base, ce>::result) {
            b = endian::swab<Base, ce>(b);
        }

        b &= ~(((1 << bits) - 1) << offset);
        b |= t << offset;

        if (endian::needsSwab<Base, ce>::result) {
            b = endian::swab<Base, ce>(b);
        }

        std::memcpy(ptr, &b, sizeof(Base));
    }

    static inline void readFrom(T& t, const void * ptr) {
        Base b;
        T tmp;

        std::memcpy(&b, ptr, sizeof(Base));
        if (endian::needsSwab<Base, ce>::result) {
            b = endian::swab<Base, ce>(b);
        }

        tmp = (b >> offset) & ((1 << bits) - 1);

        t = tmp;
    }
};

}
}
