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
