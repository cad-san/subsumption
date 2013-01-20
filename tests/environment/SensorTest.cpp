#include "CppUTest/TestHarness.h"
#include "ThreadedSensor.h"

static const char* dummy_name = "dummy_sensor";

TEST_GROUP(Sensor)
{
    Sensor* sensor;

    void setup()
    {
        sensor = new ThreadedSensor(dummy_name);
    }
    void teardown()
    {
        delete sensor;
    }
};

TEST(Sensor, Create)
{
    CHECK_EQUAL(dummy_name, sensor->getName());
}
