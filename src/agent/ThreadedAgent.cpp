#include "ThreadedAgent.h"

ThreadedAgent::ThreadedAgent(const AgentPtr& agent_ptr)
    : agent_(agent_ptr),
      thread_(agent_)
{
}

ThreadedAgent::~ThreadedAgent()
{
}

bool ThreadedAgent::init()
{
    return thread_.init();
}

bool ThreadedAgent::start()
{
    return thread_.start();
}

bool ThreadedAgent::stop()
{
    return thread_.stop();
}

bool ThreadedAgent::isReady() const
{
    return thread_.isReady();
}

bool ThreadedAgent::isActive() const
{
    return thread_.isActive();
}

void ThreadedAgent::setIntervalMiliSec(const int interval_msec)
{
    thread_.setIntervalMiliSec(interval_msec);
}
