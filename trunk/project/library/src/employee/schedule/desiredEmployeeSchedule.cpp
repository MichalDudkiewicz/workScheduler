#include "employee/schedule/desiredEmployeeSchedule.h"
#include "shift/shift.h"

void DesiredEmployeeSchedule::addShift(shiftPtr& shift)
{
    unsigned int it = shift->getDay() - 1;
    unsigned int i = 0;
    for (auto& s : schedule[it]) {
        if ((*shift) == (*s)) {
            if ((*s) >= (*shift)) {
                shift.reset();
                return;
            } else if ((*shift) >= (*s)) {
            } else if ((*s).getStartHour() > (*shift).getStartHour()) {
                (*shift).setEndHour((*s).getEndHour());
            } else {
                (*shift).setStartHour((*s).getStartHour());
            }
            schedule[it].erase(schedule[it].begin() + i);
            addShift(shift);
            return;
        }
        i += 1;
    }
    schedule[it].push_back(std::move(shift));
    std::sort(schedule[it].begin(), schedule[it].end(),
        compareShiftStartHour());
}

void DesiredEmployeeSchedule::removeShift(unsigned int day, unsigned int shiftNumber)
{
    schedule[day - 1].erase(schedule[day - 1].begin() + shiftNumber - 1);
}

std::string DesiredEmployeeSchedule::scheduleInfo() const
{
    std::ostringstream out;
    for (const auto& shiftsInDay : schedule) {
        for (const auto& shift : shiftsInDay) {
            out << shift->shiftInfo();
            out << std::endl;
        }
    }
    return out.str();
}

void DesiredEmployeeSchedule::addShift(unsigned int startHour,
    unsigned int endHour,
    unsigned int day)
{
    if (startHour >= endHour) {
        if (startHour == endHour and (startHour == 0 or startHour == 24)) {
            shiftPtr shift0(new Shift(0, 24, day));
            addShift(shift0);
        } else {
            shiftPtr shift1(new Shift(startHour, 24, day));
            addShift(shift1);
            shiftPtr shift2(new Shift(0, endHour, day + 1));
            addShift(shift2);
        }
    } else {
        shiftPtr shift(new Shift(startHour, endHour, day));
        addShift(shift);
    }
}
