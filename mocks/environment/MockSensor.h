#ifndef D_MOCK_SENSOR_H
#define D_MOCK_SENSOR_H

#include "Sensor.h"
#include <string>

class MockSensor : public Sensor
{
public:
    MockSensor(const unsigned int id);
    ~MockSensor();
};

#endif