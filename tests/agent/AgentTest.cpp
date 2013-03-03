#include "CppUTest/TestHarness.h"

#include "Agent.h"
#include "SpyBehavior.h"

#include <vector>

static const unsigned int dummy_id_01 = 0x01;
static const unsigned int dummy_id_02 = 0x02;
static const unsigned int dummy_layer_01 = 0;
static const unsigned int dummy_layer_02 = 1;

typedef std::vector<SpyBehavior *> SpyBehaviorList;

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

    int createBehaviors( unsigned int id_list[], unsigned int size,
                         SpyBehaviorList* behavior_list)
    {
        if(id_list == NULL || size < 1)
            return -1;

        if(behavior_list == NULL)
            return -1;

        behavior_list->clear();
        for(unsigned int i = 0; i < size; i++)
        {
            behavior_list->push_back( new SpyBehavior(id_list[i]) );
        }
        return 0;
    }

    void setBehaviorsToAgent(SpyBehaviorList* behaviors)
    {
        for(unsigned int i = 0; i < behaviors->size(); i++)
            agent->addBehavior(behaviors->at(i));
    }

    void checkAllBehaviorsInitialied(SpyBehaviorList* behaviors)
    {
        for(unsigned int i = 0; i < behaviors->size(); i++)
            CHECK(behaviors->at(i)->initialized());
    }

    void checkAllBehaviorsSensed(SpyBehaviorList* behaviors)
    {
        for(unsigned int i = 0; i < behaviors->size(); i++)
            CHECK(behaviors->at(i)->sensed());
    }

    void checkOneBehaviorPerformedAt(SpyBehaviorList* behaviors,
                                     unsigned int layer)
    {
        for(unsigned int i = 0; i < behaviors->size(); i++)
        {
            if(i == layer) {
                CHECK_EQUAL(true, behaviors->at(i)->performed());
            }
            else{
                CHECK_EQUAL(false, behaviors->at(i)->performed());
            }
        }
    }

    void checkNoBehaviorPerformed(SpyBehaviorList* behaviors)
    {
        for(unsigned int i = 0; i < behaviors->size(); i++)
            CHECK_EQUAL(false, behaviors->at(i)->performed());
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
    LONGS_EQUAL(dummy_id_01, agent->getBehaviorAt(dummy_layer_01)->getID())
}

TEST(Agent, AttachMaltipleLayer)
{
    unsigned int id_list[] = {dummy_id_01, dummy_id_02};
    SpyBehaviorList behaviors;

    createBehaviors(id_list, 2, &behaviors);
    setBehaviorsToAgent(&behaviors);

    LONGS_EQUAL(2, agent->getNumBehaviors());
    LONGS_EQUAL(dummy_id_01, agent->getBehaviorAt(dummy_layer_01)->getID());
    LONGS_EQUAL(dummy_id_02, agent->getBehaviorAt(dummy_layer_02)->getID());
}

TEST(Agent, AttachNullLayer)
{
    agent->addBehavior(NULL);
    LONGS_EQUAL(0, agent->getNumBehaviors());
    POINTERS_EQUAL(NULL, agent->getBehaviorAt(0));
}

TEST(Agent, SingleBehaviorStep)
{
    SpyBehavior* behavior = new SpyBehavior(dummy_id_01);
    agent->addBehavior(behavior);

    agent->init();
    agent->step();

    CHECK(behavior->initialized());
    CHECK(behavior->sensed());
    CHECK(behavior->performed());
}

TEST(Agent, MultipleBehaviorStep)
{
    unsigned int id_list[] = {dummy_id_01, dummy_id_02};
    SpyBehaviorList behaviors;

    createBehaviors(id_list, 2, &behaviors);
    setBehaviorsToAgent(&behaviors);

    agent->init();
    agent->step();

    checkAllBehaviorsInitialied(&behaviors);
    checkAllBehaviorsSensed(&behaviors);
    checkOneBehaviorPerformedAt(&behaviors, dummy_layer_02);
}

TEST(Agent, FirstBehaviorActivatedStep)
{
    unsigned int id_list[] = {dummy_id_01, dummy_id_02};
    SpyBehaviorList behaviors;

    createBehaviors(id_list, 2, &behaviors);
    setBehaviorsToAgent(&behaviors);

    behaviors[dummy_layer_01]->setActivation(true);
    behaviors[dummy_layer_02]->setActivation(false);

    agent->init();
    agent->step();

    checkAllBehaviorsInitialied(&behaviors);
    checkAllBehaviorsSensed(&behaviors);
    checkOneBehaviorPerformedAt(&behaviors, dummy_layer_01);
}

TEST(Agent, NoActivatedBehaviorStep)
{
    unsigned int id_list[] = {dummy_id_01, dummy_id_02};
    SpyBehaviorList behaviors;

    createBehaviors(id_list, 2, &behaviors);
    setBehaviorsToAgent(&behaviors);

    behaviors[dummy_layer_01]->setActivation(false);
    behaviors[dummy_layer_02]->setActivation(false);

    agent->init();
    agent->step();

    checkAllBehaviorsInitialied(&behaviors);
    checkAllBehaviorsSensed(&behaviors);
    checkNoBehaviorPerformed(&behaviors);
}

TEST(Agent, GetWithBehaviorID)
{
    unsigned int id_list[] = {dummy_id_01, dummy_id_02};
    SpyBehaviorList behaviors;

    createBehaviors(id_list, 2, &behaviors);
    setBehaviorsToAgent(&behaviors);

    POINTERS_EQUAL(behaviors.at(dummy_layer_01), agent->getBehaviorByID(dummy_id_01));
    POINTERS_EQUAL(behaviors.at(dummy_layer_02), agent->getBehaviorByID(dummy_id_02));
}

TEST(Agent, GetNotAttachedBehavior)
{
    POINTERS_EQUAL(NULL, agent->getBehaviorAt(0));
    POINTERS_EQUAL(NULL, agent->getBehaviorByID(dummy_id_01));
}

TEST(Agent, DisableToAttachSameID)
{
    SpyBehavior* first_behavior = new SpyBehavior(dummy_id_01);
    SpyBehavior* second_behavior = new SpyBehavior(dummy_id_01);

    agent->addBehavior(first_behavior);
    POINTERS_EQUAL(first_behavior, agent->getBehaviorByID(dummy_id_01));

    agent->addBehavior(second_behavior);
    POINTERS_EQUAL(second_behavior, agent->getBehaviorByID(dummy_id_01));
}
