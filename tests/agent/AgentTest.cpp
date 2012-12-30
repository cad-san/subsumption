#include "CppUTest/TestHarness.h"

#include "Agent.h"

TEST_GROUP(Agent)
{
    Agent *agent;
    void setup()
    {
        agent = new Agent();
    }

    void teardown()
    {
        delete agent;
    }
};

TEST(Agent, Create)
{
    LONGS_EQUAL(0, agent->getNumLayers());

}
