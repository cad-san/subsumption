#ifndef D_AGENT_H
#define D_AGENT_H

#include "Behavior.h"

#include <vector>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Behavior> BehaviorPtr;

class Agent
{
public:
    static const int INVALID_INDEX;
private:
    std::vector< BehaviorPtr > behaviors;
public:
    Agent();
    ~Agent();
    
    void step();
    
    const int getNumBehaviors() const;
    void addBehavior(Behavior* const new_behavior);
    const Behavior* getBehaviorAt(const unsigned int layer) const;
    const Behavior* getBehaviorByID(const unsigned int id) const;
};

#endif
