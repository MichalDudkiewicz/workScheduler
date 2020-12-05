#include "employee/factors/availability/availability.h"
#include "shift/shift.h"

Availability::Availability()
    : desiredSchedule()
    , currentSchedule()
{
}

unsigned int Availability::getWorkHours() const
{
    unsigned int workHours = 0;
    for (const auto& day : currentSchedule.getSchedule()) {
        for (const auto& assignment : day) {
            workHours += assignment.shift->getLength();
        }
    }
    return workHours;
}

unsigned int Availability::getShiftsQuantity() const
{
    unsigned int shiftsQuantity = 0;
    for (const auto& shifts : currentSchedule.getSchedule()) {
        shiftsQuantity += shifts.size();
    }
    return shiftsQuantity;
}

bool Availability::isAvailable(const shiftPtr& shift) const
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
        if (!desiredSchedule.getSchedule()[shift->getDay() - 1].empty() and !desiredSchedule.getSchedule()[shift->getDay()].empty()) {
            auto nightShift = ((*desiredSchedule.getSchedule()[shift->getDay() - 1].back()) + (*desiredSchedule.getSchedule()[shift->getDay()][0]));
            return nightShift >= (*shift);
        }
    }
    return false;
}

bool Availability::isBusy(const shiftPtr& shift) const
{
    for (const auto& assignment : currentSchedule.getSchedule()[shift->getDay() - 1]) {
        if ((*assignment.shift) == (*shift)) {
            return true;
        }
    }
    return false;
}

CurrentEmployeeSchedule& Availability::getCurrentSchedule()
{
    return currentSchedule;
}

DesiredEmployeeSchedule& Availability::getDesiredSchedule()
{
    return desiredSchedule;
}
