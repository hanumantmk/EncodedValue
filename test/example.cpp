#include "example.h"
#include <assert.h>

#include <iostream>

typedef enum {
    TYPE_PLUS = 1,
    TYPE_MINUS,
} op_type_t;

typedef enum {
    KIND_INT = 1,
    KIND_DOUBLE,
    KIND_COMPLEX,
} kind_t;

void modify_int(EncodedValue::Reference<int> i)
{
    i = 100;
}

void modify_complex(Complex<>::Reference c)
{
    c.imag() = 10;
    c.real() = 5;
}

int main(int argc, char ** argv)
{
    Expression<>::Value storage[2];
    Expression<>::Reference v(storage[0].ptr());
    Expression<>::Pointer vp(storage[0].ptr());

    v.op() = TYPE_PLUS;
    v.args()[0].type() = KIND_INT;
    v.args()[0].i() = 10;
    v.args()[1].type() = KIND_COMPLEX;
    v.args()[1].c().real() = 10;
    v.args()[1].c().imag() = 5;

    assert(v.op() == TYPE_PLUS);
    assert(v.args()[0].type() == KIND_INT);
    assert(v.args()[0].i() == 10);
    assert(v.args()[1].type() == KIND_COMPLEX);
    assert(v.args()[1].c().real() == 10);
    assert(v.args()[1].c().imag() == 5);

    modify_complex(v.args()[1].c());
    modify_int(v.args()[0].i());

    assert(v.args()[0].i() == 100);
    assert(v.args()[1].c().real() == 5);
    assert(v.args()[1].c().imag() == 10);

    vp[1] = v;

    assert(vp[1].args()[0].i() == 100);
    assert(vp[1].args()[1].c().real() == 5);
    assert(vp[1].args()[1].c().imag() == 10);

    vp[1].args()[0].i() = 1;
    assert(vp[1].args()[0].i() == 1);
    assert(vp[0].args()[0].i() == 100);

    vp[0] = vp[1];
    assert(vp[0].args()[0].i() == 1);

    return 0;
}
