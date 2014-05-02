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

template <typename T, typename Base, int offset, int bits, bool convertEndian = true>
class BitFieldPointer : public Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> > {
public:
    BitFieldPointer(char * in) : Impl::Pointer<Meta::BitField<T, Base, offset, bits, convertEndian> >(in) {}
};

template <class T>
class EVPointer : public Impl::Pointer<Meta::EV<T> > {
public:
    EVPointer(char * in) : Impl::Pointer<Meta::EV<T> >(in) {}
};

template <class T, bool convertEndian = true>
class Reference : public Pointer<T, convertEndian>::Reference {
public:
    Reference(char * in) : Pointer<T, convertEndian>::Reference(in) {}
};

template <typename T, typename Base, int offset, int bits, bool convertEndian = true>
class BitFieldReference : public BitFieldPointer<T, Base, offset, bits, convertEndian>::Reference {
public:
    BitFieldReference(char * in) : BitFieldPointer<T, Base, offset, bits, convertEndian>::Reference(in) {}
};

template <class T>
class EVReference : public EVPointer<T>::Reference {
public:
    EVReference(char * in) : EVPointer<T>::Reference(in) {}
};

}
