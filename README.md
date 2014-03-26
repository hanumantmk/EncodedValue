PortablePackedStruct
====================

Summary
-------

Portable packed struct provides a python library capable of converting
descriptions of memory into viable C++ classes.  The descriptions are provided
as a tree of python objects of particular type (those provided by the library)
and the memory is read to and written from via std::memcpy.  I.e. all memory
access is mediated through char \*'s.

The larger goal is to provide an alternative to packed structs, where a fixed
memory layout is accessible without aliasing and alignment issues.  This makes
APIs slightly more verbose, but ensures portability and correctness.
Additionally, classes may be placed on top of the same memory safely, since
reads and writes are via the same type and cannot alias.

A future expansion of this work might include annotations for endianness
conversions, mutex inclusion for shared memory concurrency or differentiation
between returns types and storage size.

Features
--------

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
    * base() - the root pointer
  * for provided fields:
    * get\_VALUE() - return by value
    * set\_VALUE() - memcpy into the buffer by value
    * ptr\_to\_VALUE()
    * size\_of\_VALUE() - in bytes
    * for array fields, get and set take an index, but otherwise work identically
    * for bit fields, an accessor is generated for the real byte(s) and the
      bitfields wraps this with appropriate bit twiddling


Future Work
-----------

* endian annotations
* mutex inclusion for thread safety
* explicit sizes in lieu of sizeof() everywhere
* optional asserts against out of bounds array access and assignment of overly
  large bitfields
* automatic generation of contained classes to allow for easily returning
  wrapped access to memory
