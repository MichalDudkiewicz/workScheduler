#ifndef driverNClass
#define driverNClass

#include "nTeam.h"

class DriverN : public NTeam
{
public:
    DriverN() = default;
    ~DriverN() override = default;
    std::string positionInfo() const override;
    unsigned int positionID() const override;
};

#endif