#ifndef D_BEHAVIOR_H
#define D_BEHAVIOR_H

class Behavior {
protected:
    int id;
public:
    virtual ~Behavior(){}

    int getID(){ return id; }
};

#endif

