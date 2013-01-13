#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Environment.h"
#include "MockSensor.h"

static const char* dummy_name_01 = "dummy_01";
static const char* dummy_name_02 = "dummy_02";

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
    MockSensor* sensor = new MockSensor(dummy_name_01);
    env->addSensor(dummy_name_01, sensor);
    LONGS_EQUAL(1, env->getNumSensor());
}

TEST(Environment, AddMultipleSensor)
{
    MockSensor* sensor_1 = new MockSensor(dummy_name_01);
    MockSensor* sensor_2 = new MockSensor(dummy_name_02);
    env->addSensor(dummy_name_01, sensor_1);
    env->addSensor(dummy_name_02, sensor_2);

    LONGS_EQUAL(2, env->getNumSensor());

    POINTERS_EQUAL(sensor_1, env->getSensorByName(dummy_name_01));
    POINTERS_EQUAL(sensor_2, env->getSensorByName(dummy_name_02));
}

TEST(Environment, SingleSensorControl)
{
    MockSensor* sensor = new MockSensor(dummy_name_01);
    env->addSensor(dummy_name_01, sensor);

    mock().expectOneCall("Sensor#init()").onObject(sensor);
    env->init();
    mock().expectOneCall("Sensor#start()").onObject(sensor);
    env->start();
    mock().expectOneCall("Sensor#stop()").onObject(sensor);
    env->stop();
    mock().checkExpectations();
}
