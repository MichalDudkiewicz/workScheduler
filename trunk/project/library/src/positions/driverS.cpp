#include "positions/driverS.h"

std::string
DriverS::positionInfo() const
{
  return "driver (special)";
}

unsigned int
DriverS::positionID() const
{
  return 2;
}

std::string
DriverS::shortcut() const
{
  return "K";
}