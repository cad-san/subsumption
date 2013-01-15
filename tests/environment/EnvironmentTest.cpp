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

    void expectOneCallOfInitIn(MockSensor* sensor)
    {
        mock().expectOneCall("Sensor#init()").onObject(sensor);
    }

    void expectOneCallOfStartIn(MockSensor* sensor)
    {
        mock().expectOneCall("Sensor#start()").onObject(sensor);
    }

    void expectOneCallOfStopIn(MockSensor* sensor)
    {
        mock().expectOneCall("Sensor#stop()").onObject(sensor);
    }

    void checkExpectations()
    {
        mock().checkExpectations();
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

TEST(Environment, NoSensorInEnvironment)
{
    LONGS_EQUAL(0, env->getNumSensor());
    POINTERS_EQUAL(NULL, env->getSensorByName("not_exist_sensor"));
}

TEST(Environment, AddNullSensor)
{
    env->addSensor(dummy_name_01, NULL);
    LONGS_EQUAL(0, env->getNumSensor());
    POINTERS_EQUAL(NULL, env->getSensorByName(dummy_name_01));
}

TEST(Environment, SingleSensorControl)
{
    MockSensor* sensor = new MockSensor(dummy_name_01);
    env->addSensor(dummy_name_01, sensor);

    expectOneCallOfInitIn(sensor);
    env->init();

    expectOneCallOfStartIn(sensor);
    env->start();

    expectOneCallOfStopIn(sensor);
    env->stop();

    checkExpectations();
}

TEST(Environment, MultipleSensorControl)
{
    MockSensorList sensors;
    std::string names[] = {dummy_name_01, dummy_name_02};

    createSensors(names, 2, &sensors);

    addSensorsToEnv(&sensors);

    expectOneCallOfInitIn(sensors[0]);
    expectOneCallOfInitIn(sensors[1]);
    env->init();

    expectOneCallOfStartIn(sensors[0]);
    expectOneCallOfStartIn(sensors[1]);
    env->start();

    expectOneCallOfStopIn(sensors[0]);
    expectOneCallOfStopIn(sensors[1]);
    env->stop();

    checkExpectations();
}

