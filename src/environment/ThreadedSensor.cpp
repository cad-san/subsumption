#include "ThreadedSensor.h"

ThreadedSensor::ThreadedSensor(const std::string& name)
{
    this->sensor_name = name;
    this->ready_flag = false;
    this->active_flag = false;
}

ThreadedSensor::~ThreadedSensor()
{
}

void ThreadedSensor::init()
{
    ready_flag = true;
}

void ThreadedSensor::start()
{
    active_flag = true;
}

void ThreadedSensor::stop()
{
    active_flag = false;
}
