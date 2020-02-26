#include "positions/driverN.h"

std::string DriverN::positionInfo() const
{
    return "driver (normal)";
}

unsigned int DriverN::positionID() const
{
    return 3;
}

std::string DriverN::shortcut() const
{
    return "K";
}