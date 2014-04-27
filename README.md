PortablePackedStruct
====================

Summary
-------

Portable packed struct provides headers and a python library capable of
converting descriptions of memory into viable C++ classes.  The descriptions
are provided as a tree of python objects of particular type (those provided by
the library) and the memory is read to and written from via std::memcpy.  I.e.
all memory access is mediated through char \*'s.

The headers can somewhat standalone as template based implementations of more
complex memory acces.  The basic design is somewhat convuluted, but revolves
around providing a description of the access desired.  New implementations can
easily be provided and none of the implementation is really hidden.  See the
[MetaPointer](#meta_pointer) section for more info.

The larger goal is to provide an alternative to packed structs, where a fixed
memory layout is accessible without aliasing and alignment issues.  This makes
APIs slightly more verbose, but ensures portability and correctness.
Additionally, classes may be placed on top of the same memory safely, since
reads and writes are via the same type and cannot alias.

A future expansion of this work might include annotations for endianness
conversions or mutex inclusion for shared memory concurrency.

Features
--------

* Special Pointer and Reference types
  * Pointer< Type >
    * wraps a basic type
    * Template Args
      * Type - the underlying type
    * ::Reference
      * acts as the underlying type
      * has value semantics (all assignment overloads)
  * BitFieldPointer< Type, Base, offset, bits >
    * wraps bitfield access
    * Template Args
      * Type - the return type of the value
      * Base - the type of the underlying integer field that the bitfield is
        backed by.
      * offset - number of shifts to the pointed bits
      * bits - size of the bitfield
    * ::Reference
      * acts as the underlying type
      * value semantics are like the standard Pointer, but generate bit
        necessary bit arithmetic
  * PPSPointer< Type >
    * wraps Portable Packed Struct access
    * Template Args
      * Type - the PPS class
    * ::Reference
      * The actual PPS class
* python based description of a packed struct
  * descriptions can include:
    * bitfields
    * unions
    * arrays
    * nested structs (largely for layout in unions)
* generated classes provide accessor methods:
  * for the class:
    * size() - size of the underlying memory in bytes
    * zero() - zero the underlying memory
    * ptr() - the root pointer
  * for provided fields:
    * VALUE() - returns a Pointer< T > ::Reference
    * for array fields, returns one of the Pointer's
    * for bit fields, returns a BitFieldPointer< ... >
    * for portable packed struct, returns a PPSPointer< T > ::Reference.  Which
      is a PPS.  These work in arrays with indexing and pointer arithmetic.

<h2><a name="meta_pointer">Meta Pointer</a></h2>

Meta Pointers are classes that provide some specific symbols.

Here is the implementation of the Memcpy MetaPointer class:

    template <typename T>
    class Memcpy {
    public:
        static const size_t size = sizeof(T);
        typedef T type;
        typedef Reference<Memcpy> reference;
    
        static inline void writeTo(const T& t, void * ptr) {
            std::memcpy(ptr, &t, size);
        }
    
        static inline void readFrom(T& t, const void * ptr) {
            std::memcpy(&t, ptr, size);
        }
    };

* ::size - the size of the type in bytes in memory
* ::reference - the type to return on dereference

If you want to use the builtin Reference class, provide a typedef of Reference<
YourMetaClass > reference.  Additionally, you must provide some additional
symbols for Reference.

* ::type - the actual type to return when accessing the value
* ::writeTo - a function that writes t to ptr
* ::readFrom - a function that instantiates t from ptr

Future Work
-----------

* endian annotations
* mutex inclusion for thread safety
* explicit sizes in lieu of sizeof() everywhere
* optional asserts against out of bounds array access and assignment of overly
  large bitfields
