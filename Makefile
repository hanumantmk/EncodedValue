all: simple

test: simple
	./simple

EVHEADERS = \
	src/EncodedValue.h \
	src/EncodedValue/endian.h \
	src/EncodedValue/helpers.h \
	src/EncodedValue/meta/bitfield.h \
	src/EncodedValue/meta/memcpy.h \
	src/EncodedValue/meta/ev.h \
	src/EncodedValue/pointer.h \
	src/EncodedValue/reference.h \
	src/EncodedValue/utils.h

simple: test/simple.cpp test/data.h Makefile $(EVHEADERS)
	g++ -Wall -Werror -ggdb3 -O0 test/simple.cpp -Itest -Isrc -o simple

test/data.h: test/gen_class.py lib/encoded_value.py Makefile
	PYTHONPATH=lib python test/gen_class.py > test/data.h

clean:
	rm -f test/data.h simple lib/*.pyc
