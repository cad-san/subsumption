#include "ThreadedSensor.h"

#include <iostream>

ThreadedSensor::ThreadedSensor(const std::string& name) : Sensor(name)
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
