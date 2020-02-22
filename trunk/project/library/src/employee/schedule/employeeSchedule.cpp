#include "employee/schedule/employeeSchedule.h"
#include "shift/shift.h"

void
EmployeeSchedule::addShift(shiftPtr& shift)
{
  unsigned int it = shift->getDay() - 1;
  unsigned int i = 0;
  for (auto& s : shiftsInSchedule[it]) {
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
      shiftsInSchedule[it].erase(shiftsInSchedule[it].begin() + i);
      addShift(shift);
      return;
    }
    i += 1;
  }
  shiftsInSchedule[it].push_back(std::move(shift));
  std::sort(shiftsInSchedule[it].begin(),
            shiftsInSchedule[it].end(),
            compareShiftStartHour());
}

void
EmployeeSchedule::removeShift(unsigned int day, unsigned int shiftNumber)
{
  shiftsInSchedule[day - 1].erase(shiftsInSchedule[day - 1].begin() +
                                  shiftNumber - 1);
}

const Calendar<shifts>&
EmployeeSchedule::getSchedule() const
{
  return shiftsInSchedule;
}

std::string
EmployeeSchedule::scheduleInfo() const
{
  std::ostringstream out;
  for (const auto& shiftsInDay : shiftsInSchedule) {
    for (const auto& shift : shiftsInDay) {
      out << shift->shiftInfo();
      out << std::endl;
    }
  }
  return out.str();
}

void
EmployeeSchedule::addShift(unsigned int startHour,
                           unsigned int endHour,
                           unsigned int day)
{
  if (startHour >= endHour) {
    shiftPtr shift1(new Shift(startHour, 24, day));
    addShift(shift1);
    shiftPtr shift2(new Shift(0, endHour, day + 1));
    addShift(shift2);
  } else {
    shiftPtr shift(new Shift(startHour, endHour, day));
    addShift(shift);
  }
}
