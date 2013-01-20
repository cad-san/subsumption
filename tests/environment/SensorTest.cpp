#include "CppUTest/TestHarness.h"
#include "ThreadedSensor.h"

static const char* dummy_name = "dummy_sensor";

TEST_GROUP(Sensor)
{
    ThreadedSensor* sensor;

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
    CHECK_EQUAL(false, sensor->isReady());
    CHECK_EQUAL(false, sensor->isActive());
}

TEST(Sensor, Control)
{
    sensor->init();
    CHECK_EQUAL(true, sensor->isReady());

    sensor->start();
    CHECK_EQUAL(true, sensor->isActive());

    sensor->stop();
    CHECK_EQUAL(false, sensor->isActive());
}

TEST(Sensor, LoopTime)
{
    sensor->setIntervalMiliSec( 500 );
    UtilTime base_time = sensor->getBaseTime();
    UtilTime next_time = sensor->getNextTime(base_time);
    LONGS_EQUAL( 500, sensor->diffTimeMiliSec(base_time, next_time));
}
