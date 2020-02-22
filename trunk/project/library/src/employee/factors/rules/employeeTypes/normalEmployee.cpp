#include "employee/factors/rules/employeeTypes/normalEmployee.h"

std::string
NormalEmployee::getType() const
{
  return "normal";
}

unsigned int
NormalEmployee::getPriority() const
{
  return 1;
}