#include "SpyBehavior.h"

SpyBehavior::SpyBehavior(const unsigned int id)
{
    this->id = id;
    this->activation = true;
    this->sencing_state = false;
    this->perform_state = false;
}

SpyBehavior::~SpyBehavior()
{
}

bool SpyBehavior::senced()
{
    return sencing_state;
}

bool SpyBehavior::performed()
{
    return perform_state;
}

void SpyBehavior::sencing()
{
    perform_state = false;
    sencing_state = true;
}

void SpyBehavior::perform()
{
    if(sencing_state)
        perform_state = true;
    else
        perform_state = false;
}

const bool SpyBehavior::isActive() const
{
    return activation && sencing_state;
}

void SpyBehavior::setActivation(const bool activation)
{
    this->activation = activation;
}