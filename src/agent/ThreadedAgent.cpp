#include "ThreadedAgent.h"

ThreadedAgent::ThreadedAgent(const AgentPtr& agent_ptr)
    : agent(agent_ptr),
      thread(agent)
{
}

ThreadedAgent::~ThreadedAgent()
{
}

bool ThreadedAgent::init()
{
    return thread.init();
}

bool ThreadedAgent::start()
{
    return thread.start();
}

bool ThreadedAgent::stop()
{
    return thread.stop();
}

bool ThreadedAgent::isReady() const
{
    return thread.isReady();
}

bool ThreadedAgent::isActive() const
{
    return thread.isActive();
}

void ThreadedAgent::setIntervalMiliSec(const int interval_msec)
{
    thread.setIntervalMiliSec(interval_msec);
}
