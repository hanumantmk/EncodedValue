#include "EncodedValue/meta/memcpy.h"
#include "EncodedValue/meta/bitfield.h"
#include "EncodedValue/pointer.h"
#include "EncodedValue/meta/ev.h"

namespace EncodedValue {

template <class T, enum endian::ConvertEndian ce = endian::Noop>
class Pointer : public Impl::Pointer<Meta::Memcpy<T, ce> > {
public:
    Pointer(char * in) : Impl::Pointer<Meta::Memcpy<T, ce> >(in) {}
};

template <class T, enum endian::ConvertEndian ce = endian::Noop>
class Reference : public Impl::Pointer<Meta::Memcpy<T, ce> >::Reference {
public:
    Reference(char * in) : Impl::Pointer<Meta::Memcpy<T, ce> >::Reference(in) {}

    Reference& operator=(const T& t) {
        Impl::Pointer<Meta::Memcpy<T, ce> >::Reference::operator=(t);
        return *this;
    };
};

namespace BitField {

template <typename T, typename Base, int offset, int bits, enum endian::ConvertEndian ce = endian::Noop>
class Pointer : public Impl::Pointer<Meta::BitField<T, Base, offset, bits, ce> > {
public:
    Pointer(char * in) : Impl::Pointer<Meta::BitField<T, Base, offset, bits, ce> >(in) {}
};

template <typename T, typename Base, int offset, int bits, enum endian::ConvertEndian ce = endian::Noop>
class Reference : public Impl::Pointer<Meta::BitField<T, Base, offset, bits, ce> >::Reference {
public:
    Reference(char * in) : Impl::Pointer<Meta::BitField<T, Base, offset, bits, ce> >::Reference(in) {}

    Reference& operator=(const T& t) {
        Impl::Pointer<Meta::BitField<T, Base, offset, bits, ce> >::Reference::operator=(t);
        return *this;
    };
};

}

}
