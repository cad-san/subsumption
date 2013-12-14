#include "MockAgent.h"

MockAgent::MockAgent() : Agent()
{
    performed_flag_ = false;
    initialized_flag_ = false;
}

MockAgent::~MockAgent()
{
}

void MockAgent::init()
{
    initialized_flag_ = true;
}

void MockAgent::step()
{
    performed_flag_ = true;
    condition_performed_.notify_one();
}

bool MockAgent::performed() const
{
    return performed_flag_;
}

bool MockAgent::initialized() const
{
    return initialized_flag_;
}

void MockAgent::waitPerforming()
{
    if(performed_flag_)
        return;

    lock lk(message_guard_);
    condition_performed_.wait(lk);
}
