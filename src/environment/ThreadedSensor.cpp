#include "ThreadedSensor.h"

#include <iostream>

static const int MSEC_BASE = 1000 * 1000;

ThreadedSensor::ThreadedSensor(const std::string& name) : Sensor(name)
{
    this->ready_flag = false;
    this->active_flag = false;
}

ThreadedSensor::~ThreadedSensor()
{
}

void ThreadedSensor::init()
{
    ready_flag = true;
    active_flag = false;
}

void ThreadedSensor::start()
{
    requestStarting();
    waitStarting();
}

void ThreadedSensor::stop()
{
    requestStopping();
    waitStopping();
}

void ThreadedSensor::step()
{
}

void ThreadedSensor::main()
{
    UtilTime expect_time = getBaseTime();
    end_flag = false;

    /* スレッド開始 */
    notifyStarting();
    for(;;)
    {
        lock lk(message_guard);
        if(end_flag)
            break;

        step();

        expect_time = getNextTime(expect_time);
        if(end_request.timed_wait(lk, static_cast<boost::xtime>(expect_time)))
            break;
    }
    notifyStopping();
    /* スレッド終了 */
}

void ThreadedSensor::requestStarting()
{
    this->main_thread = ThreadPtr(new boost::thread(&ThreadedSensor::main, this));
}

void ThreadedSensor::waitStarting()
{
    lock lk(message_guard);
    while(!isActive())
        active_request.wait(lk);
}

void ThreadedSensor::notifyStarting()
{
    lock kl(message_guard);
    active_flag = true;
    active_request.notify_one();
}

void ThreadedSensor::requestStopping()
{
    lock kl(message_guard);
    end_flag = true;
    end_request.notify_one();
}

void ThreadedSensor::notifyStopping()
{
    lock kl(message_guard);
    active_flag = false;
    active_request.notify_one();
}

void ThreadedSensor::waitStopping()
{
    main_thread->join();
}

const bool ThreadedSensor::isReady() const
{
    return ready_flag;
}

const bool ThreadedSensor::isActive() const
{
    return active_flag;
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
