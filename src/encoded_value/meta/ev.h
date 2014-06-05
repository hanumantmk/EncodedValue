#pragma once

namespace encoded_value {
namespace Meta {

template <typename T>
class EV {
public:
    static const size_t size = T::_size;
    typedef typename T::Reference reference;
};

}
}
