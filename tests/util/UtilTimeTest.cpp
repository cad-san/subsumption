#include "CppUTest/TestHarness.h"
#include "UtilTime.h"

TEST_GROUP(UtilTime)
{
    void setup()
    {
    }
    void teardown()
    {
    }
};

TEST(UtilTime, SimpleAdd)
{
    UtilTime base;
    UtilTime addition;

    base.sec = 1;
    base.nsec = 1000;
    addition.sec = 1;
    addition.nsec = 1000;

    UtilTime result = base + addition;
    LONGS_EQUAL(2, result.sec);
    LONGS_EQUAL(2000, result.nsec);
}

TEST(UtilTime, AddEqual)
{
    UtilTime base;
    UtilTime addition;

    base.sec = 1;
    base.nsec = 1000;
    addition.sec = 1;
    addition.nsec = 1000;

    base += addition;
    LONGS_EQUAL(2, base.sec);
    LONGS_EQUAL(2000, base.nsec);
}

TEST(UtilTime, AddCarry)
{
    UtilTime base;
    UtilTime addition;

    base.sec = 0;
    base.nsec = 500 * 1000 * 1000;
    addition.sec = 0;
    addition.nsec = 500 * 1000 * 1000;

    base += addition;
    LONGS_EQUAL(1, base.sec);
    LONGS_EQUAL(0, base.nsec);
}
