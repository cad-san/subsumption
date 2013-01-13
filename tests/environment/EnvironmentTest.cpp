#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

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
        mock().clear();
        delete env;
    }
};

TEST(Environment, AddSensor)
{
    MockSensor* sensor = new MockSensor(dummy_id_01);
    env->addSensor(STR(dummy_id_01), sensor);
    LONGS_EQUAL(1, env->getNumSensor());
}

TEST(Environment, AddMultipleSensor)
{
    MockSensor* sensor_1 = new MockSensor(dummy_id_01);
    MockSensor* sensor_2 = new MockSensor(dummy_id_02);
    env->addSensor(STR(dummy_id_01), sensor_1);
    env->addSensor(STR(dummy_id_02), sensor_2);

    LONGS_EQUAL(2, env->getNumSensor());

    LONGS_EQUAL(dummy_id_01, env->getSensorByName(STR(dummy_id_01))->getId());
    LONGS_EQUAL(dummy_id_02, env->getSensorByName(STR(dummy_id_02))->getId());
}

TEST(Environment, SingleSensorControl)
{
    MockSensor* sensor = new MockSensor(dummy_id_01);
    env->addSensor(STR(dummy_id_01), sensor);

    mock().expectOneCall("Sensor#init()").onObject(sensor);
    env->init();
    mock().expectOneCall("Sensor#start()").onObject(sensor);
    env->start();
    mock().expectOneCall("Sensor#stop()").onObject(sensor);
    env->stop();
    mock().checkExpectations();
}
