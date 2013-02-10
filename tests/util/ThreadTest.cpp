#include "CppUTest/TestHarness.h"
#include "Thread.h"

TEST_GROUP(Thread)
{
    Thread* thread;

    void setup()
    {
        thread = new Thread();
    }
    void teardown()
    {
        delete thread;
    }
};

TEST(Thread, Create)
{
    CHECK_EQUAL(false, thread->isReady());
    CHECK_EQUAL(false, thread->isActive());
}

TEST(Thread, Control)
{
    thread->setIntervalMiliSec( 500 );

    thread->init();
    CHECK_EQUAL(true, thread->isReady());

    thread->start();
    CHECK_EQUAL(true, thread->isActive());

    thread->stop();
    CHECK_EQUAL(false, thread->isActive());
}

TEST(Thread, LoopTime)
{
    thread->setIntervalMiliSec( 500 );
    UtilTime base_time = thread->getBaseTime();
    UtilTime next_time = thread->getNextTime(base_time);
    LONGS_EQUAL( 500, thread->diffTimeMiliSec(base_time, next_time));
}
