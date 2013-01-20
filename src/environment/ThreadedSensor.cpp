#include "ThreadedSensor.h"

static const int MSEC_BASE = 1000 * 1000;

ThreadedSensor::ThreadedSensor(const std::string& name)
{
    this->sensor_name = name;
    this->ready_flag = false;
    this->active_flag = false;
}

ThreadedSensor::~ThreadedSensor()
{
}

void ThreadedSensor::init()
{
    ready_flag = true;
}

void ThreadedSensor::start()
{
    active_flag = true;
}

void ThreadedSensor::stop()
{
    active_flag = false;
}

void ThreadedSensor::setIntervalMiliSec(const int interval_msec)
{
    this->interval.sec = 0;
    this->interval.nsec = interval_msec * 1000;
}

const UtilTime ThreadedSensor::getBaseTime() const
{
    UtilTime base;
    boost::xtime_get(&base, boost::TIME_UTC);
    return base;
}

const UtilTime ThreadedSensor::getNextTime(const UtilTime& base) const
{
    return base + interval;
}

const int ThreadedSensor::diffTimeMiliSec(const UtilTime& base, const UtilTime& next) const
{
    return (next.sec - base.sec) * MSEC_BASE + (next.nsec - base.nsec) / 1000;
}
