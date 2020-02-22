#include "employee/factors/availability/availability.h"
#include "shift/shift.h"

Availability::Availability()
  : desiredSchedule()
  , currentSchedule()
{}

unsigned int
Availability::getWorkHours() const
{
  unsigned int workHours = 0;
  for (const auto& shifts : currentSchedule.getSchedule()) {
    for (const auto& shift : shifts) {
      workHours += shift->getLength();
    }
  }
  return workHours;
}

unsigned int
Availability::getShiftsQuantity() const
{
  unsigned int shiftsQuantity = 0;
  for (const auto& shifts : currentSchedule.getSchedule()) {
    shiftsQuantity += shifts.size();
  }
  return shiftsQuantity;
}

bool
Availability::isAvailable(const shiftPtr& shift) const
{
  if (shift->isDayOff()) {
    return false;
  }
  if (!shift->isNightShift()) {
    for (const auto& s : desiredSchedule.getSchedule()[shift->getDay() - 1]) {
      if ((*s) >= (*shift)) {
        return true;
      }
    }
    return false;
  }
  if (shift->getDay() != desiredSchedule.getSchedule().size()) {
    if (!desiredSchedule.getSchedule()[shift->getDay() - 1].empty() and
        !desiredSchedule.getSchedule()[shift->getDay()].empty()) {
      return ((*desiredSchedule.getSchedule()[shift->getDay() - 1].back()) +
              (*desiredSchedule.getSchedule()[shift->getDay()][0])) >= (*shift);
    }
  }
  return false;
}

bool
Availability::isBusy(const shiftPtr& shift) const
{
  for (const auto& s : currentSchedule.getSchedule()[shift->getDay() - 1]) {
    if ((*s) == (*shift)) {
      return true;
    }
  }
  return false;
}

EmployeeSchedule&
Availability::getCurrentSchedule()
{
  return currentSchedule;
}

EmployeeSchedule&
Availability::getDesiredSchedule()
{
  return desiredSchedule;
}
