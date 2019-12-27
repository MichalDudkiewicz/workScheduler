#include "employeeSchedule.h"
#include "shift.h"
#include <algorithm>

EmployeeSchedule::EmployeeSchedule()
{
    for(unsigned int i=0; i<getNumberOfDays()+1; ++i)
    {
        shiftsInSchedule.emplace_back();
    }
}

void EmployeeSchedule::addShift(shiftPtr &shift)
{
    unsigned int it = shift->getDay()-1;
    shiftsInSchedule[it].push_back(std::move(shift));
    std::sort(shiftsInSchedule[it].begin(),shiftsInSchedule[it].end(),compareShiftStartHour());
}

void EmployeeSchedule::removeShift(unsigned int day, unsigned int shiftNumber)
{
    shiftsInSchedule[day-1].erase(shiftsInSchedule[day-1].begin()+shiftNumber-1);
}

const schedule& EmployeeSchedule::getSchedule() const
{
    return shiftsInSchedule;
}