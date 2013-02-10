#include "CppUTest/TestHarness.h"
#include "Thread.h"
#include "MockRunner.h"

TEST_GROUP(Thread)
{
    MockRunnerPtr runner;
    Thread* thread;

    void setup()
    {
        runner = MockRunnerPtr(new MockRunner());
        thread = new Thread(runner);
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

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(true, runner->performed());
}
