#include "ThreadedSensor.h"

ThreadedSensor::ThreadedSensor(const std::string& name, const ControllerPtr& controller) : Sensor(name),
    controllPtr(controller),
    thread(controller)
{
}

ThreadedSensor::~ThreadedSensor()
{
}

bool ThreadedSensor::init()
{
    return thread.init();
}

bool ThreadedSensor::start()
{
    return thread.start();
}

bool ThreadedSensor::stop()
{
    return thread.stop();
}

bool ThreadedSensor::isReady() const
{
    return thread.isReady();
}

bool ThreadedSensor::isActive() const
{
    return thread.isActive();
}

void ThreadedSensor::setIntervalMiliSec(const int interval_msec)
{
    thread.setIntervalMiliSec(interval_msec);
}
