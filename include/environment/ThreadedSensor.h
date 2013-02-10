#ifndef D_THREADED_SENSOR_H
#define D_THREADED_SENSOR_H

#include "Sensor.h"
#include "UtilTime.h"

#include <boost/thread.hpp>
#include <boost/shared_ptr.hpp>

class ThreadedSensor : public Sensor
{
private:
    typedef boost::mutex::scoped_lock lock;
    typedef boost::shared_ptr<boost::thread> ThreadPtr;

    UtilTime interval;
    bool end_flag;

    ThreadPtr main_thread;
    boost::mutex message_guard;
    boost::condition_variable_any active_request;
    boost::condition_variable_any end_request;

    void requestStarting();
    void notifyStarting();
    void waitStarting();

    void requestStopping();
    void notifyStopping();
    void waitStopping();

    void main();

public:
    ThreadedSensor(const std::string& name);
    virtual ~ThreadedSensor();

    virtual void init();
    virtual void start();
    virtual void stop();

    virtual void step();

    void setIntervalMiliSec(const int interval_msec);

    const UtilTime getBaseTime() const;
    const UtilTime getNextTime(const UtilTime& base) const;

    const int diffTimeMiliSec(const UtilTime& base, const UtilTime& next) const;
};

#endif