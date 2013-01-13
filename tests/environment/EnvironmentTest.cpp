#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "Environment.h"
#include "MockSensor.h"

static const char* dummy_name_01 = "dummy_01";
static const char* dummy_name_02 = "dummy_02";

typedef std::vector<MockSensor *> MockSensorList;

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

    int createSensors(std::string names[], unsigned int size, MockSensorList* sensors)
    {
        if(names == NULL || size < 1)
            return -1;

        if(sensors == NULL)
            return -1;

        sensors->clear();
        for(unsigned int i = 0; i < size; i++)
            sensors->push_back( new MockSensor(names[i]) );
        return 0;
    }

    void addSensorsToEnv(MockSensorList* sensors)
    {
        for(unsigned int i = 0; i < sensors->size(); i++)
            env->addSensor(sensors->at(i)->getName(), sensors->at(i));
    }

    void checkSensorsInEnv(std::string names[], MockSensorList* sensors)
    {
        LONGS_EQUAL(sensors->size(), env->getNumSensor());

        for(unsigned int i = 0; i < sensors->size(); i++)
            POINTERS_EQUAL(sensors->at(i), env->getSensorByName(names[i]));
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
    MockSensorList sensors;
    std::string names[] = {dummy_name_01, dummy_name_02};

    createSensors(names, 2, &sensors);

    addSensorsToEnv(&sensors);

    checkSensorsInEnv(names, &sensors);
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
