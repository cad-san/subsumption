#include "MockSensor.h"
#include "CppUTestExt/MockSupport.h"

MockSensor::MockSensor(const unsigned int id)
{
    this->id = id;
}

MockSensor::~MockSensor()
{
}

void MockSensor::init()
{
    mock().actualCall("Sensor#init()").onObject(this);
}

void MockSensor::start()
{
    mock().actualCall("Sensor#start()").onObject(this);
}

void MockSensor::stop()
{
    mock().actualCall("Sensor#stop()").onObject(this);
}
