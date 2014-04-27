all: simple

test: simple
	./simple

PPSHEADERS = \
	src/PortablePackedStruct.h \
	src/PortablePackedStruct/endian.h \
	src/PortablePackedStruct/helpers.h \
	src/PortablePackedStruct/meta/bitfield.h \
	src/PortablePackedStruct/meta/memcpy.h \
	src/PortablePackedStruct/meta/pps.h \
	src/PortablePackedStruct/pointer.h \
	src/PortablePackedStruct/reference.h \
	src/PortablePackedStruct/utils.h

simple: test/simple.cpp test/data.h Makefile $(PPSHEADERS)
	g++ -Wall -Werror -ggdb3 -O0 test/simple.cpp -Itest -Isrc -o simple

test/data.h: test/gen_class.py lib/portable_packed_struct.py Makefile
	PYTHONPATH=lib python test/gen_class.py > test/data.h

clean:
	rm -f test/data.h simple lib/*.pyc
