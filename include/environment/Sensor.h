#ifndef D_SENSOR_H
#define D_SENSOR_H

class Sensor
{
protected:
    unsigned int id;
public:
    virtual ~Sensor() {};
    const unsigned int getId() const { return id; };
};

#endif
