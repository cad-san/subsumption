#include "MockSensor.h"
#include "CppUTestExt/MockSupport.h"

MockSensor::MockSensor(const std::string& name) : Sensor(name)
{
    this->ready_flag = false;
    this->active_flag = false;
}

MockSensor::~MockSensor()
{
}

void MockSensor::init()
{
    ready_flag = true;
    active_flag = false;
    mock().actualCall("Sensor#init()").onObject(this);
}

void MockSensor::start()
{
    active_flag = true;
    mock().actualCall("Sensor#start()").onObject(this);
}

void MockSensor::stop()
{
    active_flag = false;
    mock().actualCall("Sensor#stop()").onObject(this);
}

const bool MockSensor::isReady() const
{
    return ready_flag;
}

const bool MockSensor::isActive() const
{
    return active_flag;
}
