#include "data.h"
#include <assert.h>

#include <iostream>

void test_simple(void)
{
    TestClass tc;
    TestEmbed te;
    TestEmbedCopy tec;

    assert(tc.size() == 16);
    assert(tc.size() == sizeof(tc));

    tc.set_type( 5 );

    assert(tc.get_type() == 5);

    tc.zero();

    char * base = tc.base();

    for (int i = 0; i < tc.size(); i++) {
        assert(base[i] == 0);
    }

    tc.set_refCounter(1);
    tc.set_pada(12);
    tc.set_shortStr(0);
    tc.set_padb(2);

    assert(tc.get_refCounter() == 1);
    assert(tc.get_pada() == 12);
    assert(tc.get_shortStr() == 0);
    assert(tc.get_padb() == 2);

    tc.zero();

    tc.set_doubleValue(5.89);

    DoubleClass dc(tc.ptr_to_doubleValue());

    assert(dc.get_doubleValue() == 5.89);

    tc.zero();

    tc.set_i64(0, 100);
    tc.set_i64(1, 5);

    assert(tc.get_i64(0) == 100);
    assert(tc.get_i64(1) == 5);

    tc.zero();

    te = tc.get_te_array(0);
    te.set_shortValue(5);
    te.set_intValue(1023);

    assert(te.get_shortValue() == 5);
    assert(te.get_intValue() == 1023);

    te = tc.get_te();

    assert(te.get_shortValue() == 5);
    assert(te.get_intValue() == 1023);

    tec = tc.get_tec();

    tc.zero();

    assert(tec.get_shortValue() == 5);
    assert(tec.get_intValue() == 1023);
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
