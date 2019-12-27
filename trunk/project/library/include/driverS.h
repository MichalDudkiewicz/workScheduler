#ifndef driverSClass
#define driverSClass

#include "sTeam.h"

class DriverS : public STeam
{
public:
    DriverS()= default;
    ~DriverS() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
};

#endif