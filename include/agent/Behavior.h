#ifndef D_BEHAVIOR_H
#define D_BEHAVIOR_H

class Behavior {
protected:
    int id;
public:
    virtual ~Behavior(){}

    virtual void sencing() = 0;
    virtual void perform() = 0;

    virtual bool isActive() = 0;

    int getID(){ return id; }
};

#endif

