#ifndef D_SPY_BEHAVIOR_H
#define D_SPY_BEHAVIOR_H

#include "Behavior.h"

class SpyBehavior : public Behavior
{
private:
    bool sencing_flag;
    bool perform_flag;
public:
    explicit SpyBehavior(const unsigned int id);
    ~SpyBehavior();

    void sencing();
    void perform();

    const bool isActive() const;

    bool senced();
    bool performed();
};

#endif

