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

void modify_complex(Complex::Reference c)
{
    c.imag() = 10;
    c.real() = 5;
}

int main(int argc, char ** argv)
{
    Expression::Value v;

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

    assert(v.args()[1].c().real() == 5);
    assert(v.args()[1].c().imag() == 10);

    return 0;
}
