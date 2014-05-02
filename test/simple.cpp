#include "data.h"
#include <assert.h>

#include <iostream>

using namespace EncodedValue;

void test_pointer(void)
{
    char buf[20] = { 0 };

    Pointer<int> f(buf + 2);

    f += 2;
    *f = 55;
    f--;
    f++;
    assert(*f == 55);
}

void test_reference(void)
{
    char buf[20] = { 0 };

    Pointer<int>::Reference f(buf + 2);

    f = 10;
    assert(f == 10);

    f = 10;
    f += 2;
    assert(f == 12);

    f = 12;
    f -= 2;
    assert(f == 10);

    f = 10;
    f *= 2;
    assert(f == 20);

    f = 20;
    f /= 2;
    assert(f == 10);

    f = 15;
    f %= 8;
    assert(f == 7);

    f = 5;
    f &= 3;
    assert(f == 1);

    f = 8;
    f |= 3;
    assert(f == 11);

    f = 2;
    f ^= 10;
    assert(f == 8);

    f = 1;
    f <<= 3;
    assert(f == 8);

    f = 16;
    f >>= 3;
    assert(f == 2);

    f = 16;
    assert(f++ == 16);
    assert(f == 17);

    f = 16;
    assert(f-- == 16);
    assert(f == 15);

    f = 16;
    assert(++f == 17);
    assert(f == 17);

    f = 16;
    assert(--f == 15);
    assert(f == 15);

    (&f)[1] = 10;
    assert((&f)[1] == 10);
}

void test_simple(void)
{
    TestClass::Value tc_data;
    TestEmbed::Reference te_ref;
    TestEmbed::Value te_data;

    assert(tc_data._size == 16);
    assert(tc_data._size == sizeof(tc_data));

    tc_data.type() = 5;

    assert(tc_data.type() == 5);

    tc_data.zero();

    char * base = tc_data.ptr();

    for (int i = 0; i < tc_data._size; i++) {
        assert(base[i] == 0);
    }

    tc_data.refCounter() = 1;
    tc_data.pada() = 12;
    tc_data.shortStr() = 0;
    tc_data.padb() = 2;

    assert(tc_data.refCounter() == 1);
    assert(tc_data.pada() == 12);
    assert(tc_data.shortStr() == 0);
    assert(tc_data.padb() == 2);

    tc_data.zero();

    tc_data.doubleValue() = 5.89;

    DoubleClass::Reference dc(tc_data.doubleValue().ptr());

    assert(dc.doubleValue() == 5.89);

    tc_data.zero();

    tc_data.i64()[0] = 100;
    tc_data.i64()[1] = 5;

    assert(tc_data.i64()[0] == 100);
    assert(tc_data.i64()[1] == 5);

    tc_data.zero();

    te_ref = tc_data.te_array()[0];
    te_ref.shortValue() = 5;
    te_ref.shortValue() += 10;
    te_ref.intValue() = 1023;

    assert(te_ref.shortValue() == 15);
    assert(te_ref.intValue() == 1023);

    te_ref = tc_data.te();

    assert(te_ref.shortValue() == 15);
    assert(te_ref.intValue() == 1023);

    te_data = tc_data.te();

    tc_data.zero();

    assert(te_data.shortValue() == 15);
    assert(te_data.intValue() == 1023);
}

void test_evpointer(void)
{
    TestEmbed::Value values[10];

    EVPointer<TestEmbed> v = &(values[0]);

    v->intValue() = 10;
    v->shortValue() = 20;

    assert(values[0].intValue() == 10);
    assert(values[0].shortValue() == 20);

    v[1].intValue() = 20;
    v[1].shortValue() = 40;

    assert(values[1].intValue() == 20);
    assert(values[1].shortValue() == 40);

    v++;

    assert(v->intValue() == 20);
    assert(v->shortValue() == 40);
}

void run_test(const char * name, void (* test)(void))
{
    std::cout << name << " - ";
    test();
    std::cout << "SUCCESS" << std::endl;
}

int main(int argc, char ** argv)
{
    std::cout << "Running tests..." << std::endl;

    run_test("simple", &test_simple);
    run_test("pointer", &test_pointer);
    run_test("reference", &test_reference);
    run_test("evpointer", &test_evpointer);

    std::cout << "Tests finished..." << std::endl;
}
