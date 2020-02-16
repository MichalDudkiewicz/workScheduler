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

const Calendar<shifts> &EmployeeSchedules::getDesiredSchedule() const {
    return desiredSchedule.getSchedule();
}

const Calendar<shifts> &EmployeeSchedules::getCurrentSchedule() const {
    return currentSchedule.getSchedule();
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

void EmployeeSchedules::addDesiredShift(shiftPtr &shift) {
    desiredSchedule.addShift(shift);
}

void EmployeeSchedules::addDesiredShift(unsigned int startHour, unsigned int endHour, unsigned int day) {
    shiftPtr shift(new Shift(startHour, endHour, day));
    desiredSchedule.addShift(shift);
}

void EmployeeSchedules::removeDesiredShift(unsigned int day, unsigned int shiftNumber) {
    desiredSchedule.removeShift(day, shiftNumber);
}

void EmployeeSchedules::addCurrentShift(shiftPtr &shift) {
    currentSchedule.addShift(shift);
}

void EmployeeSchedules::addCurrentShift(unsigned int startHour, unsigned int endHour, unsigned int day) {
    shiftPtr shift(new Shift(startHour, endHour, day));
    currentSchedule.addShift(shift);
}

void EmployeeSchedules::removeCurrentShift(unsigned int day, unsigned int shiftNumber) {
    currentSchedule.removeShift(day, shiftNumber);
}

bool EmployeeSchedules::isBusy(const shiftPtr &shift) const {
    for (const auto &s : currentSchedule.getSchedule()[shift->getDay() - 1]) {
        if ((*s) == (*shift)) {
            return true;
        }
    }
    return false;
}
std::string EmployeeSchedules::desiredScheduleInfo() const {
    return desiredSchedule.scheduleInfo();
}

std::string EmployeeSchedules::currentScheduleInfo() const {
    return currentSchedule.scheduleInfo();
}