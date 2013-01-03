#include "Agent.h"

Agent::Agent()
{
}

Agent::~Agent()
{
}

void Agent::step()
{
    int active_behavior = -1;
    for(unsigned int i = 0; i < behaviors.size(); i++)
    {
        // sencingの実行
        behaviors.at(i)->sencing();
        // 後のBehaviorを優先する
        if(behaviors.at(i)->isActive())
            active_behavior = i;
    }
   
    // ActiveなBehaviorが無いなら何もしない
    if(active_behavior == -1)
        return;

    behaviors.at(active_behavior)->perform();
}

int Agent::getNumBehaviors()
{
    return behaviors.size();
}

void Agent::addBehavior(Behavior* new_behavior)
{
    behaviors.push_back(BehaviorPtr(new_behavior));
}

Behavior* Agent::getBehaviorAt(unsigned int layer)
{
    if( layer >= behaviors.size() )
        return NULL;
    
    return behaviors.at(layer).get();
}
