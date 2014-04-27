#pragma once

namespace PortablePackedStruct {
namespace Meta {

template <typename T>
class PPS {
public:
    static const size_t size = T::_size;
    typedef typename T::Reference reference;
};

}
}
