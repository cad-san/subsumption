#ifndef D_SPY_BEHAVIOR_H
#define D_SPY_BEHAVIOR_H

#include "Behavior.h"

class SpyBehavior : public Behavior
{
private:
    bool activation;
    bool sensing_state;
    bool perform_state;
public:
    explicit SpyBehavior(const unsigned int id);
    ~SpyBehavior();

    void sensing();
    void perform();

    const bool isActive() const;

    bool sensed();
    bool performed();

    void setActivation(const bool activation);
};

#endif

