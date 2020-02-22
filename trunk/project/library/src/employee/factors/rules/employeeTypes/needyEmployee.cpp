#include "employee/factors/rules/employeeTypes/needyEmployee.h"

std::string
NeedyEmployee::getType() const
{
  return "needy";
}

unsigned int
NeedyEmployee::getPriority() const
{
  return 2;
}