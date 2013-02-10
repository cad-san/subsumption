#ifndef D_MOCK_RUNNER_H
#define D_MOCK_RUNNER_H

#include "Runner.h"

class MockRunner : public Runner
{
private:
    bool performed_flag;
    bool initialized_flag;

public:
    MockRunner()
    {
        performed_flag = false;
        initialized_flag = false;
    }

    void init()
    {
        initialized_flag = true;
    }

    void step()
    {
        performed_flag = true;
    }

    bool performed()
    {
        return performed_flag;
    }

    bool initialized()
    {
        return initialized_flag;
    }
};
typedef boost::shared_ptr<MockRunner> MockRunnerPtr;

#endif
