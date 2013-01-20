#ifndef D_SENSOR_H
#define D_SENSOR_H

#include <string>

class Sensor
{
protected:
    std::string sensor_name;
    bool ready_flag;
    bool active_flag;
public:
    virtual ~Sensor() {};

    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    const std::string getName() const { return sensor_name; };
    const bool isReady() const { return ready_flag; };
    const bool isActive() const { return active_flag; };
};

#endif
