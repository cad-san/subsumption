#ifndef D_MOCK_AGENT_H
#define D_MOCK_AGENT_H

#include <boost/thread.hpp>
#include "Agent.h"
#include "UtilTime.h"

class MockAgent : public Agent
{
private:
    typedef boost::mutex::scoped_lock lock;

    boost::mutex message_guard_;
    boost::condition_variable_any condition_performed_;

    bool performed_flag_;
    bool initialized_flag_;

public:
    MockAgent();
    ~MockAgent();

    virtual void init();
    virtual void step();

    bool performed() const;
    bool initialized() const;

    void waitPerforming();
};

typedef boost::shared_ptr<MockAgent> MockAgentPtr;

#endif
