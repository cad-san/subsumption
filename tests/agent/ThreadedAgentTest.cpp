#include "CppUTest/TestHarness.h"
#include "UtilAssert.h"

#include "MockAgent.h"
#include "UtilTime.h"
#include "ThreadedAgent.h"

#include <boost/make_shared.hpp>

TEST_GROUP(ThreadedAgent)
{
    MockAgentPtr agent;
    ThreadedAgent* threaded_agent;
    void setup()
    {
        agent = boost::make_shared<MockAgent>();
        threaded_agent = new ThreadedAgent(agent);
    }

    void teardown()
    {
        delete threaded_agent;
    }

    void waitFirstStep()
    {
        agent->waitPerforming();
    }

};

TEST(ThreadedAgent, Init)
{
    CHECK_EQUAL(false, agent->initialized());
    CHECK_EQUAL(false, agent->performed());
}

TEST(ThreadedAgent, Control)
{
    threaded_agent->setIntervalMiliSec( 500 );

    CHECK_EQUAL(true, threaded_agent->init());
    CHECK_EQUAL(true, threaded_agent->isReady());

    CHECK_EQUAL(true, threaded_agent->start());
    CHECK_EQUAL(true, threaded_agent->isActive());

    waitFirstStep();

    CHECK_EQUAL(true, agent->initialized());
    CHECK_EQUAL(true, agent->performed());

    CHECK_EQUAL(true, threaded_agent->stop());
    CHECK_EQUAL(false, threaded_agent->isActive());
}
