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
        destroyThead();
    }

    void destroyThead()
    {
        if(thread == NULL)
            return;
        delete thread;
        thread = NULL;
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

    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->isActive());

    CHECK_EQUAL(true, thread->stop());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(true, runner->performed());
}

TEST(Thread, StartWithoutInit)
{
    CHECK_EQUAL(false, thread->start());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(false, thread->stop());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(false, runner->initialized());
    CHECK_EQUAL(false, runner->performed());
}

TEST(Thread, StopWithoutStart)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(false, thread->stop());
    CHECK_EQUAL(false, thread->isActive());

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(false, runner->performed());
}

TEST(Thread, WithoutStop)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->isReady());

    CHECK_EQUAL(true, thread->start());
    CHECK_EQUAL(true, thread->isActive());

    destroyThead(); // stop()を呼ばずにdelete

    CHECK_EQUAL(true, runner->initialized());
    CHECK_EQUAL(true, runner->performed());
}

TEST(Thread, InitAfterStarted)
{
    CHECK_EQUAL(true, thread->init());
    CHECK_EQUAL(true, thread->start());

    CHECK_EQUAL(false, thread->init());

    CHECK_EQUAL(true, thread->stop());
}
