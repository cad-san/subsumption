#ifndef D_MOCK_RUNNER_H
#define D_MOCK_RUNNER_H

#include "Runner.h"

class MockRunner : public Runner
{
private:
    bool called_flag;

public:
    MockRunner()
    {
        called_flag = false;
    }
    void step()
    {
        called_flag = true;
    }

    bool isCalled()
    {
        return called_flag;
    }
};
typedef boost::shared_ptr<MockRunner> MockRunnerPtr;

#endif
