#include "PortablePackedStruct/meta/memcpy.h"
#include "PortablePackedStruct/meta/bitfield.h"
#include "PortablePackedStruct/pointer.h"
#include "PortablePackedStruct/meta/pps.h"

namespace PortablePackedStruct {

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
class PPSPointer : public Impl::Pointer<Meta::PPS<T> > {
public:
    PPSPointer(char * in) : Impl::Pointer<Meta::PPS<T> >(in) {}
};

}
