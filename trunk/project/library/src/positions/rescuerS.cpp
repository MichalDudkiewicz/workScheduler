#include "positions/rescuerS.h"

std::string
RescuerS::positionInfo() const
{
  return "rescuer (special)";
}

unsigned int
RescuerS::positionID() const
{
  return 4;
}

std::string
RescuerS::shortcut() const
{
  return "R";
}