#ifndef D_SENSOR_H
#define D_SENSOR_H

class Sensor
{
protected:
    unsigned int id;
public:
    virtual ~Sensor() {};

    virtual void init() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;

    const unsigned int getId() const { return id; };
};

#endif
