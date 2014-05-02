#include "EncodedValue/meta/memcpy.h"
#include "EncodedValue/meta/bitfield.h"
#include "EncodedValue/pointer.h"
#include "EncodedValue/meta/ev.h"

namespace EncodedValue {

template <class T, bool convertEndian = true>
class Pointer : public Impl::Pointer<Meta::Memcpy<T, convertEndian> > {
public:
    Pointer(char * in) : Impl::Pointer<Meta::Memcpy<T, convertEndian> >(in) {}
};

template <class T, bool convertEndian = true>
class Reference : public Impl::Pointer<Meta::Memcpy<T, convertEndian> >::Reference {
public:
    Reference(char * in) : Impl::Pointer<Meta::Memcpy<T, convertEndian> >::Reference(in) {}

    Reference& operator=(const T& t) {
        Impl::Pointer<Meta::Memcpy<T, convertEndian> >::Reference::operator=(t);
        return *this;
    };
};

namespace BitField {

template <typename T, typename Base, int offset, int bits, bool convertEndian = true>
class Pointer : public Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> > {
public:
    Pointer(char * in) : Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> >(in) {}
};

template <typename T, typename Base, int offset, int bits, bool convertEndian = true>
class Reference : public Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> >::Reference {
public:
    Reference(char * in) : Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> >::Reference(in) {}

    Reference& operator=(const T& t) {
        Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> >::Reference::operator=(t);
        return *this;
    };
};

}

}
