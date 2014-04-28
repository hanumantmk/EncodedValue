#pragma once

#include "PortablePackedStruct/reference.h"
#include "PortablePackedStruct/endian.h"
#include <cstring>

namespace PortablePackedStruct {
namespace Meta {

template <typename T, bool convertEndian>
class Memcpy {
public:
    static const size_t size = sizeof(T);
    typedef T type;
    typedef Impl::Reference<Memcpy> reference;

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

}
}
