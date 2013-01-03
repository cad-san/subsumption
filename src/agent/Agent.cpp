#include "Agent.h"

const int Agent::INVALID_INDEX = -1;

Agent::Agent()
{
}

Agent::~Agent()
{
}

void Agent::step()
{
    int active_behavior = INVALID_INDEX;
    for(unsigned int i = 0; i < behaviors.size(); i++)
    {
        // sencingの実行
        behaviors.at(i)->sencing();
        // 後のBehaviorを優先する
        if(behaviors.at(i)->isActive())
            active_behavior = i;
    }
   
    // ActiveなBehaviorが無いなら何もしない
    if(active_behavior == INVALID_INDEX)
        return;

    behaviors.at(active_behavior)->perform();
}

const int Agent::getNumBehaviors() const
{
    return behaviors.size();
}

void Agent::addBehavior(Behavior* const new_behavior)
{
    behaviors.push_back(BehaviorPtr(new_behavior));
}

const Behavior* Agent::getBehaviorAt(const unsigned int layer) const
{
    if( layer >= behaviors.size() )
        return NULL;

    return behaviors.at(layer).get();
}

const Behavior* Agent::getBehaviorByID(const unsigned int id) const
{
    for(unsigned int i = 0; i < behaviors.size(); i++)
    {
        if(behaviors.at(i)->getID() == id)
            return behaviors.at(i).get();
    }
    // ヒットしなかった
    return NULL;
}
