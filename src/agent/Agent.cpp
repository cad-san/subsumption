#include "Agent.h"

#include <algorithm>

const int Agent::INVALID_LAYER = -1;

Agent::Agent()
{
}

Agent::~Agent()
{
}

void Agent::init()
{
    for(unsigned int i = 0; i < behaviors.size(); i++)
    {
        behaviors.at(i)->init();
    }
}

void Agent::step()
{
    Behavior* active_behavior = NULL;
    for(unsigned int i = 0; i < behaviors.size(); i++)
    {
        // sensingの実行
        behaviors.at(i)->sensing();
        // 後のBehaviorを優先する
        if(behaviors.at(i)->isActive())
            active_behavior = behaviors.at(i).get();
    }

    // ActiveなBehaviorが無いなら何もしない
    if(active_behavior == NULL)
        return;

    active_behavior->perform();
}

int Agent::getNumBehaviors() const
{
    return static_cast<int>(behaviors.size());
}

void Agent::addBehavior(const BehaviorPtr& new_behavior)
{
    if(new_behavior.get() == NULL)
        return;

    int layer = convertFromIDtoLayer(new_behavior->getID());

    if(layer != INVALID_LAYER)
        removeBehaviorAt(static_cast<unsigned int>(layer));

    behaviors.push_back(new_behavior);
}

void Agent::removeBehaviorAt(unsigned int layer)
{
    if( !isValidLayer(layer) )
        return;

    BehaviorPtr target = behaviors.at(layer);
    behaviors.erase(std::remove(behaviors.begin(), behaviors.end(), target),
                    behaviors.end());
}

const BehaviorPtr Agent::getBehaviorAt(const unsigned int layer) const
{
    if(!isValidLayer(layer))
        return BehaviorPtr();

    return behaviors.at(layer);
}

const BehaviorPtr Agent::getBehaviorByID(const unsigned int id) const
{
    int layer = convertFromIDtoLayer(id);

    if(layer == INVALID_LAYER)
        return BehaviorPtr();

    return behaviors.at(static_cast<unsigned int>(layer));
}

int Agent::convertFromIDtoLayer(unsigned int id) const
{
    // 対象のIDを走査する
    for(unsigned int i = 0; i < behaviors.size(); i++)
    {
        if(behaviors.at(i)->getID() == id)
            return static_cast<int>(i);
    }
    // ヒットしなかった
    return INVALID_LAYER;
}

bool Agent::isValidLayer(const unsigned int layer) const
{
    return (layer < behaviors.size());
}

