#include "MockAgent.h"

MockAgent::MockAgent() : Agent()
{
    performed_flag = false;
    initialized_flag = false;
}

MockAgent::~MockAgent()
{
}

void MockAgent::init()
{
    initialized_flag = true;
}

void MockAgent::step()
{
    performed_flag = true;
    condition_performed.notify_one();
}

bool MockAgent::performed() const
{
    return performed_flag;
}

bool MockAgent::initialized() const
{
    return initialized_flag;
}

void MockAgent::waitPerforming()
{
    if(performed_flag)
        return;

    lock lk(message_guard);
    condition_performed.wait(lk);
}
