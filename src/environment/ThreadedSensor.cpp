#include "ThreadedSensor.h"

ThreadedSensor::ThreadedSensor(const std::string& name, SensorController* const controller) : Sensor(name),
    controllPtr(controller),
    thread(controllPtr)
{
}

ThreadedSensor::~ThreadedSensor()
{
}

void ThreadedSensor::init()
{
    thread.init();
}

void ThreadedSensor::start()
{
    thread.start();
}

void ThreadedSensor::stop()
{
    thread.stop();
}

const bool ThreadedSensor::isReady() const
{
    return thread.isReady();
}

const bool ThreadedSensor::isActive() const
{
    return thread.isActive();
}

void ThreadedSensor::setIntervalMiliSec(const int interval_msec)
{
    thread.setIntervalMiliSec(interval_msec);
}
