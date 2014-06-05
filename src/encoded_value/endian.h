#pragma once

#include <algorithm>
#include <stdint.h>

namespace encoded_value {
namespace endian {

#define ENCODED_VALUE_HOST_ENDIAN 1234

enum ConvertEndian {
    Noop = 0,
    Big,
    Little
};

template<typename T, enum ConvertEndian e>
class needsSwab {
public:
    static const bool result = false;
};

#pragma push_macro("NEEDS_SWAB")

#if ENCODED_VALUE_HOST_ENDIAN == 4321
#define NEEDS_SWAB(type) \
    template<> \
    class needsSwab<type, Little> { \
    public: \
        static const bool result = true; \
    };
#elif ENCODED_VALUE_HOST_ENDIAN == 1234
#define NEEDS_SWAB(type) \
    template<> \
    class needsSwab<type, Big> { \
    public: \
        static const bool result = true; \
    };
#else
#  error "Unknown host endianness"
#endif

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

template<typename T, enum ConvertEndian ce>
inline T swab(T t) {
    char * front, * back;

    if (! needsSwab<T, ce>::result) {
        return t;
    }

    front = (char *)&t;
    back = front + sizeof(T) - 1;

    std::reverse(front, back);

    return t;
}

}
}
