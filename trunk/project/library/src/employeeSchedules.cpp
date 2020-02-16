#include "employeeSchedules.h"
#include "shift.h"

EmployeeSchedules::EmployeeSchedules() : desiredSchedule(), currentSchedule()
{}

unsigned int EmployeeSchedules::getWorkHours() const {
    unsigned int workHours = 0;
    for (const auto &shifts : currentSchedule.getSchedule()) {
        for (const auto &shift : shifts) {
            workHours += shift->getLength();
        }
    }
    return workHours;
}

unsigned int EmployeeSchedules::getShiftsQuantity() const {
    unsigned int shiftsQuantity = 0;
    for (const auto &shifts : currentSchedule.getSchedule()) {
        shiftsQuantity += shifts.size();
    }
    return shiftsQuantity;
}

bool EmployeeSchedules::isAvailable(const shiftPtr &shift) const {
    if (shift->isDayOff()) {
        return false;
    }
    if (!shift->isNightShift()) {
        for (const auto &s : desiredSchedule.getSchedule()[shift->getDay() - 1]) {
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


bool EmployeeSchedules::isBusy(const shiftPtr &shift) const {
    for (const auto &s : currentSchedule.getSchedule()[shift->getDay() - 1]) {
        if ((*s) == (*shift)) {
            return true;
        }
    }
    return false;
}

EmployeeSchedule &EmployeeSchedules::getCurrentSchedule() {
    return currentSchedule;
}

EmployeeSchedule &EmployeeSchedules::getDesiredSchedule() {
    return desiredSchedule;
}

