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