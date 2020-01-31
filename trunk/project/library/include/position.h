#ifndef positionClass
#define positionClass

#include <string>
#include "typeDefinitions.h"

class Position{
public:
    Position()= default;
    virtual ~Position()= default;
    virtual std::string positionInfo() const=0;
    virtual unsigned int positionID() const=0;
    virtual std::string shortcut() const=0;
};

struct comparePositionID{
    bool operator()(const positionPtr& p1, const positionPtr& p2) const{
        return p1->positionID()<p2->positionID();
    }
};

#endif