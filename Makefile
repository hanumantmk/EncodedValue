all: simple

test: simple
	./simple

simple: test/simple.cpp test/data.h Makefile src/PortablePackedStruct.h
	g++ -Wall -Werror -ggdb3 -O0 test/simple.cpp -Itest -Isrc -o simple

test/data.h: test/gen_class.py lib/portable_packed_struct.py Makefile
	PYTHONPATH=lib python test/gen_class.py > test/data.h

clean:
	rm -f test/data.h simple lib/*.pyc
