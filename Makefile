all: simple

test: simple example
	./simple
	./example

EVHEADERS = \
	src/encoded_value.h \
	src/encoded_value/endian.h \
	src/encoded_value/helpers.h \
	src/encoded_value/meta/bitfield.h \
	src/encoded_value/meta/memcpy.h \
	src/encoded_value/meta/ev.h \
	src/encoded_value/pointer.h \
	src/encoded_value/reference.h \
	src/encoded_value/utils.h

simple: test/simple.cpp test/data.h Makefile $(EVHEADERS)
	g++ -Wall -Werror -ggdb3 -O2 test/simple.cpp -Itest -Isrc -o simple

example: test/example.cpp test/example.h Makefile $(EVHEADERS)
	g++ -Wall -Werror -ggdb3 -O2 test/example.cpp -Itest -Isrc -o example

test/data.h: test/gen_class.py lib/encoded_value.py Makefile
	PYTHONPATH=lib python test/gen_class.py > test/data.h

test/example.h: test/gen_example.py lib/encoded_value.py Makefile
	PYTHONPATH=lib python test/gen_example.py > test/example.h

clean:
	rm -f test/data.h test/example.h simple lib/*.pyc

.PHONY: test clean
