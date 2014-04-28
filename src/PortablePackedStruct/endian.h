#pragma once

#include <algorithm>
#include <stdint.h>

namespace PortablePackedStruct {
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

NEEDS_SWAB(int16_t)
NEEDS_SWAB(uint16_t)
NEEDS_SWAB(int32_t)
NEEDS_SWAB(uint32_t)
NEEDS_SWAB(int64_t)
NEEDS_SWAB(uint64_t)
NEEDS_SWAB(double)
NEEDS_SWAB(float)

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

    while (front < back) {
        std::swap(*front++, *back--);
    }

    return t;
}

}
}
