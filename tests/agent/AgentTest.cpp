#include "CppUTest/TestHarness.h"

#include "Agent.h"
#include "SpyBehavior.h"

#include <vector>

static const int dummy_id_01 = 0x01;
static const int dummy_id_02 = 0x02;

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
    LONGS_EQUAL(0, agent->getNumBehaviors());
}

TEST(Agent, AttachSingleLayer)
{
    agent->addBehavior(new SpyBehavior(dummy_id_01));
    LONGS_EQUAL(1, agent->getNumBehaviors());
    LONGS_EQUAL(dummy_id_01, agent->getBehaviorAt(0)->getID())
}

TEST(Agent, AttachMaltipleLayer)
{
    agent->addBehavior(new SpyBehavior(dummy_id_01));
    agent->addBehavior(new SpyBehavior(dummy_id_02));
    LONGS_EQUAL(2, agent->getNumBehaviors());
    LONGS_EQUAL(dummy_id_01, agent->getBehaviorAt(0)->getID())
    LONGS_EQUAL(dummy_id_02, agent->getBehaviorAt(1)->getID())
}

TEST(Agent, SingleBehaviorStep)
{
    SpyBehavior* behavior = new SpyBehavior(dummy_id_01);
    agent->addBehavior(behavior);
    
    agent->step();
    CHECK(behavior->senced());
    CHECK(behavior->performed());
}

TEST(Agent, MultipleBehaviorStep)
{
    SpyBehavior* lawer_behavior = new SpyBehavior(dummy_id_01);
    SpyBehavior* higher_behavior = new SpyBehavior(dummy_id_02);
    
    agent->addBehavior(lawer_behavior);
    agent->addBehavior(higher_behavior);
    
    agent->step();
    
    CHECK_EQUAL(true, lawer_behavior->senced());
    CHECK_EQUAL(true, higher_behavior->senced());
    CHECK_EQUAL(false, lawer_behavior->performed());
    CHECK_EQUAL(true, higher_behavior->performed());
}

TEST(Agent, GetNotAttachedBehavior)
{
    CHECK_EQUAL(NULL, agent->getBehaviorAt(0));
}
