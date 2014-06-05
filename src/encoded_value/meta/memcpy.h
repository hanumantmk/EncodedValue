#pragma once

#include "encoded_value/reference.h"
#include "encoded_value/endian.h"
#include <cstring>

namespace encoded_value {
namespace Meta {

template <typename T, enum endian::ConvertEndian ce>
class Memcpy {
public:
    static const size_t size = sizeof(T);
    typedef T type;
    typedef Impl::Reference<Memcpy> reference;

    static inline void writeTo(const T& t, void * ptr) {
        if (endian::needsSwab<T, ce>::result) {
            T tmp = endian::swab<T, ce>(t);
            std::memcpy(ptr, &tmp, size);
        } else {
            std::memcpy(ptr, &t, size);
        }
    }

    static inline void readFrom(T& t, const void * ptr) {
        std::memcpy(&t, ptr, size);

        if (endian::needsSwab<T, ce>::result) {
            t = endian::swab<T, ce>(t);
        }
    }
};

}
}
