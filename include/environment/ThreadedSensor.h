#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"
#include "UtilTime.h"

#include <boost/thread.hpp>

class ThreadedSensor : public Sensor
{
private:
    UtilTime interval;
public:
    ThreadedSensor(const std::string& name);
    virtual ~ThreadedSensor();

    virtual void init();
    virtual void start();
    virtual void stop();

    void setIntervalMiliSec(const int interval_msec);

    const UtilTime getBaseTime() const;
    const UtilTime getNextTime(const UtilTime& base) const;

    const int diffTimeMiliSec(const UtilTime& base, const UtilTime& next) const;
};

#endif