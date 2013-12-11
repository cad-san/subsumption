#ifndef D_THREADED_AGENT_H
#define D_THREADED_AGENT_H

#include "Thread.h"
#include "Agent.h"

#include <vector>
#include <boost/shared_ptr.hpp>

class ThreadedAgent
{
private:
    AgentPtr agent;
    Thread thread;

public:
    ThreadedAgent(const AgentPtr& agent_ptr);
    virtual ~ThreadedAgent();

    bool init();
    bool start();
    bool stop();

    bool isReady() const;
    bool isActive() const;

    void setIntervalMiliSec(const int interval_msec);
};

typedef boost::shared_ptr<ThreadedAgent> ThreadedAgentPtr;

#endif
