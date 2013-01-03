#include "SpyBehavior.h"

SpyBehavior::SpyBehavior(int id)
{
    this->id = id;
    this->sencing_flag = false;
    this->perform_flag = false;
}

SpyBehavior::~SpyBehavior()
{
}

bool SpyBehavior::senced()
{
    return sencing_flag;
}

bool SpyBehavior::performed()
{
    return perform_flag;
}

void SpyBehavior::sencing()
{
    perform_flag = false;
    sencing_flag = true;
}

void SpyBehavior::perform()
{
    if(sencing_flag)
        perform_flag = true;
    else
        perform_flag = false;
}

const bool SpyBehavior::isActive() const
{
    return sencing_flag;
}
