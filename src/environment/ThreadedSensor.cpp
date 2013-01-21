#include "ThreadedSensor.h"

#include <iostream>

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
    main_thread = ThreadPtr(new boost::thread(&ThreadedSensor::main, this));
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
    active_flag = true;
    notifyStarting();
    for(;;)
    {
        lock lk(message_guard);
        if(end_flag)
            break;

        step();

        expect_time = getNextTime(expect_time);
        if(stop_request.timed_wait(lk, static_cast<boost::xtime>(expect_time)))
            break;
    }
    active_flag = false;
    /* スレッド終了 */
}

void ThreadedSensor::waitStarting()
{
    lock lk(message_guard);
    while(!isActive())
        start_request.wait(lk);
}

void ThreadedSensor::notifyStarting()
{
    lock kl(message_guard);
    start_request.notify_one();
}

void ThreadedSensor::requestStopping()
{
    lock kl(message_guard);
    end_flag = true;
    stop_request.notify_one();
}

void ThreadedSensor::waitStopping()
{
    main_thread->join();
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
