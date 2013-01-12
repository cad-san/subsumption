#include "cpputest/TestHarness.h"

#include "Environment.h"
#include "MockSensor.h"

static const unsigned int dummy_id_01 = 0x01;
static const unsigned int dummy_id_02 = 0x02;

#define STR(value) #value

TEST_GROUP(Environment)
{
    Environment* env;
    void setup()
    {
        env = new Environment();
    }
    void teardown()
    {
        delete env;
    }
};

TEST(Environment, AddSensor)
{
    MockSensor* senser = new MockSensor(dummy_id_01);
    env->addSensor(STR(dummy_id_01), senser);
    LONGS_EQUAL(1, env->getNumSensor());
}

TEST(Environment, AddMultipleSensor)
{
    MockSensor* senser_1 = new MockSensor(dummy_id_01);
    MockSensor* senser_2 = new MockSensor(dummy_id_02);
    env->addSensor(STR(dummy_id_01), senser_1);
    env->addSensor(STR(dummy_id_02), senser_2);

    LONGS_EQUAL(2, env->getNumSensor());

    LONGS_EQUAL(dummy_id_01, env->getSensorByName(STR(dummy_id_01))->getId());
    LONGS_EQUAL(dummy_id_02, env->getSensorByName(STR(dummy_id_02))->getId());
}
