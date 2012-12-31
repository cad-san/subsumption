#include "Agent.h"

Agent::Agent()
{
}

Agent::~Agent()
{
}

int Agent::getNumBehaviors()
{
    return behaviors.size();
}

void Agent::addBehavior(Behavior* new_behavior)
{
    behaviors.push_back(BehaviorPtr(new_behavior));
}

Behavior& Agent::getBehaviorAt(int layer)
{
    return *behaviors.at(layer);
}
