#ifndef D_AGENT_H
#define D_AGENT_H

#include "Behavior.h"

#include <vector>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Behavior> BehaviorPtr;

class Agent
{
private:
    std::vector< BehaviorPtr > behaviors;
public:
    Agent();
    ~Agent();
    
    int getNumBehaviors();
    void addBehavior(Behavior* new_behavior);
    Behavior& getBehaviorAt(int layer);
};

#endif
