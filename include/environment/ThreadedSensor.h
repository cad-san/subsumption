#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"
#include "SensorController.h"
#include "Thread.h"

class ThreadedSensor : public Sensor
{
private:
    typedef boost::shared_ptr<SensorController> ControllerPtr;

    ControllerPtr controllPtr;
    Thread thread;

public:
    ThreadedSensor(const std::string& name, SensorController* const controller);
    virtual ~ThreadedSensor();

    void init();
    void start();
    void stop();

    const bool isReady() const;
    const bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);
};

#endif
