#ifndef D_MOCK_SENSOR_H
#define D_MOCK_SENSOR_H

#include "Sensor.h"
#include <string>

class MockSensor : public Sensor
{
public:
    MockSensor(const std::string name);
    ~MockSensor();

    void init();
    void start();
    void stop();


};

#endif
