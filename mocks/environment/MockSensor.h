#ifndef D_MOCK_SENSOR_H
#define D_MOCK_SENSOR_H

#include "Sensor.h"
#include <string>

class MockSensor : public Sensor
{
private:
    bool ready_flag;
    bool active_flag;
public:
    MockSensor(const std::string& name);
    ~MockSensor();

    void init();
    void start();
    void stop();

    const bool isReady() const;
    const bool isActive() const;
};

#endif
