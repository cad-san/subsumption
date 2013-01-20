#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"

class ThreadedSensor : public Sensor
{
public:
    ThreadedSensor(const std::string& name);
    virtual ~ThreadedSensor();

    virtual void init();
    virtual void start();
    virtual void stop();
};

#endif