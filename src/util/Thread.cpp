#include "Thread.h"

static const int INTERVAL_TIME = 500;
static const int MSEC_BASE = 1000 * 1000;

Thread::Thread(const RunnerPtr& runner)
{
    this->ready_flag = false;
    this->active_flag = false;
    this->setIntervalMiliSec(INTERVAL_TIME);
    this->runner = runner;
}

Thread::~Thread()
{
}

void Thread::init()
{
    this->ready_flag = true;
    this->active_flag = false;
}

void Thread::start()
{
    requestStarting();
    waitStarting();
}

void Thread::stop()
{
    requestStopping();
    waitStopping();
}

void Thread::main()
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

        if(runner != NULL)
            runner->step();

        expect_time = getNextTime(expect_time);
        if(end_request.timed_wait(lk, static_cast<boost::xtime>(expect_time)))
            break;
    }
    notifyStopping();
    /* スレッド終了 */
}

void Thread::requestStarting()
{
    this->main_thread = ThreadPtr(new boost::thread(&Thread::main, this));
}

void Thread::waitStarting()
{
    lock lk(message_guard);
    while(!isActive())
        active_request.wait(lk);
}

void Thread::notifyStarting()
{
    lock kl(message_guard);
    active_flag = true;
    active_request.notify_one();
}

void Thread::requestStopping()
{
    lock kl(message_guard);
    end_flag = true;
    end_request.notify_one();
}

void Thread::notifyStopping()
{
    lock kl(message_guard);
    active_flag = false;
    active_request.notify_one();
}

void Thread::waitStopping()
{
    main_thread->join();
}

const bool Thread::isReady() const
{
    return ready_flag;
}

const bool Thread::isActive() const
{
    return active_flag;
}

void Thread::setIntervalMiliSec(const int interval_msec)
{
    this->interval.sec = 0;
    this->interval.nsec = interval_msec * 1000;
}

const UtilTime Thread::getBaseTime() const
{
    UtilTime base;
    boost::xtime_get(&base, boost::TIME_UTC);
    return base;
}

const UtilTime Thread::getNextTime(const UtilTime& base) const
{
    return base + interval;
}
