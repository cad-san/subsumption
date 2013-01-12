#include "Environment.h"

Environment::Environment()
{
}

Environment::~Environment()
{
}

void Environment::addSensor(std::string name, Sensor* sensor)
{
    sensor_list.insert(
        SensorList::value_type(name, SensorPtr(sensor)));
}

const int Environment::getNumSensor() const
{
    return sensor_list.size();
}

const Sensor* Environment::getSensorByName(std::string name) const
{
    SensorList::const_iterator it = sensor_list.find(name);
    if(it == sensor_list.end())
        return NULL;

    return it->second.get();
}
