#include "data.h"
#include <assert.h>

#include <iostream>

void test_basic(void)
{
    char buf[20] = { 0 };

    PortablePackedStruct::Pointer<int> f(buf + 2);

    f += 2;
    *f = 55;
    f--;
    f++;
    assert(*f == 55);
}

void test_simple(void)
{
    TestClass::Data tc_data;
    TestEmbed::Ptr te_ptr;
    TestEmbed::Data te_data;

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

    DoubleClass::Ptr dc(tc_data.doubleValue().ptr());

    assert(dc.doubleValue() == 5.89);

    tc_data.zero();

    tc_data.i64()[0] = 100;
    tc_data.i64()[1] = 5;

    assert(tc_data.i64()[0] == 100);
    assert(tc_data.i64()[1] == 5);

    tc_data.zero();

    te_ptr = tc_data.te_array()[0];
    te_ptr.shortValue() = 5;
    te_ptr.intValue() = 1023;

    assert(te_ptr.shortValue() == 5);
    assert(te_ptr.intValue() == 1023);

    te_ptr = tc_data.te();

    assert(te_ptr.shortValue() == 5);
    assert(te_ptr.intValue() == 1023);

    te_data = tc_data.te();

    tc_data.zero();

    assert(te_data.shortValue() == 5);
    assert(te_data.intValue() == 1023);
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
    run_test("basic", &test_basic);

    std::cout << "Tests finished..." << std::endl;
}
