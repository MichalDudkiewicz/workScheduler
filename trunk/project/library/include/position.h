#ifndef positionClass
#define positionClass

#include <string>
#include <memory>

class Position
{
public:
    Position()= default;
    virtual ~Position()= default;
    virtual std::string positionInfo() const=0;
    virtual unsigned int positionID() const=0;
};

typedef std::shared_ptr<Position> positionPtr;

struct comparePositionID
{
    bool operator()(const positionPtr& p1, const positionPtr& p2) const
    {
        return p1->positionID()<p2->positionID();
    }
};

#endif