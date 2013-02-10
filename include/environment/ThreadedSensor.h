#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"
#include "Thread.h"

class ThreadedSensor : public Sensor
{
private:
    Thread thread;

public:
    ThreadedSensor(const std::string& name);
    virtual ~ThreadedSensor();

    void init();
    void start();
    void stop();

    const bool isReady() const;
    const bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);
};

#endif