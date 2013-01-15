#ifndef D_ENVIRONMENT_H
#define D_ENVIRONMENT_H

#include "Sensor.h"
#include <string>
#include <map>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Sensor> SensorPtr;
typedef std::map< std::string, SensorPtr > SensorList;

class Environment
{
private:
    SensorList sensor_list;
public:
    Environment();
    ~Environment();

    void init();
    void start();
    void stop();

    void addSensor(const std::string& name, Sensor* const sensor);

    const Sensor* getSensorByName(const std::string& name) const;
    const int getNumSensor() const;
};
#endif
