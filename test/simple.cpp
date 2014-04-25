#include "data.h"
#include <assert.h>

#include <iostream>

void test_simple(void)
{
    TestClass::Data tc;
    TestEmbed::Ptr te;
    TestEmbed::Data tec;

    assert(tc._size == 16);
    assert(tc._size == sizeof(tc));

    tc.type() = 5;

    assert(tc.type() == 5);

    tc.zero();

    char * base = tc.ptr().ptr();

    for (int i = 0; i < tc._size; i++) {
        assert(base[i] == 0);
    }

    tc.refCounter() = 1;
    tc.pada() = 12;
    tc.shortStr() = 0;
    tc.padb() = 2;

    assert(tc.refCounter() == 1);
    assert(tc.pada() == 12);
    assert(tc.shortStr() == 0);
    assert(tc.padb() == 2);

    tc.zero();

    tc.doubleValue() = 5.89;

    DoubleClass::Ptr dc(tc.doubleValue().ptr());

    assert(dc.doubleValue() == 5.89);

    tc.zero();

    tc.i64()[0] = 100;
    tc.i64()[1] = 5;

    assert(tc.i64()[0] == 100);
    assert(tc.i64()[1] == 5);

    tc.zero();

    te = tc.te_array()[0];
    te.shortValue() = 5;
    te.intValue() = 1023;

    assert(te.shortValue() == 5);
    assert(te.intValue() == 1023);

    te = tc.te();

    assert(te.shortValue() == 5);
    assert(te.intValue() == 1023);

    tec = TestEmbed::Data(tc.te());

    tc.zero();

    assert(tec.shortValue() == 5);
    assert(tec.intValue() == 1023);
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

    std::cout << "Tests finished..." << std::endl;
}
