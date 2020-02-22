#include "shift/shift.h"
#include <sstream>

Shift::Shift(unsigned int start, unsigned int end, unsigned int d)
  : startHour(start)
  , endHour(end)
  , day(d)
  , nightShift(startHour > endHour)
{}

Shift::Shift(unsigned int d)
  : startHour(0)
  , endHour(0)
  , day(d)
  , nightShift(false)
{}

unsigned int
Shift::getLength() const
{
  if (isNightShift()) {
    return 24 - startHour + endHour;
  }
  return endHour - startHour;
}

std::string
Shift::shiftInfo() const
{
  std::ostringstream out;
  out << "day: " << day << ", ";
  out << startHour << " - " << endHour;
  if (isNightShift()) {
    out << " (night)";
  }
  return out.str();
}

unsigned int
Shift::getEndHour() const
{
  return endHour;
}

unsigned int
Shift::getStartHour() const
{
  return startHour;
}

void
Shift::setStartHour(unsigned int hour)
{
  startHour = hour;
}

void
Shift::setEndHour(unsigned int hour)
{
  endHour = hour;
}

bool
Shift::operator>=(const Shift& shift) const
{
  return this->startHour <= shift.startHour and
         this->endHour >= shift.endHour and this->day == shift.day and
         shift.isNightShift() == this->isNightShift();
}

bool
Shift::isNightShift() const
{
  return nightShift;
}

Shift
Shift::operator+(const Shift& shift) const
{
  if (this->endHour == 24 and shift.startHour == 0 and
      this->day + 1 == shift.day) {
    Shift night(this->startHour, shift.endHour, this->day);
    night.nightShift = true;
    return night;
  } else if (this->startHour == 0 and shift.endHour == 24 and
             shift.day + 1 == this->day) {
    Shift night(shift.startHour, this->endHour, shift.day);
    night.nightShift = true;
    return night;
  }
  return *this;
}

unsigned int
Shift::getDay() const
{
  return day;
}

bool
Shift::operator==(const Shift& shift) const
{
  if (shift >= *this or *this >= shift) {
    return true;
  } else if (!this->isNightShift() and !shift.isNightShift()) {
    return (this->endHour > shift.startHour and
            this->startHour < shift.startHour) or
           (shift.endHour > this->startHour and
            shift.startHour < this->startHour);
  } else if (this->isNightShift() and shift.isNightShift()) {
    return (this->endHour < shift.endHour and
            shift.startHour > this->startHour) or
           (shift.endHour < this->endHour and
            this->startHour > shift.startHour);
  } else if (this->isNightShift() and !shift.isNightShift()) {
    return this->startHour < shift.endHour or shift.startHour > this->startHour;
  } else if (!this->isNightShift() and shift.isNightShift()) {
    return this->endHour > shift.startHour or this->startHour > shift.startHour;
  } else {
    return false;
  }
}

void
Shift::setDay(unsigned int d)
{
  day = d;
}

bool
compareShiftStartHour::operator()(const shiftPtr& s1, const shiftPtr& s2) const
{
  return s1->getStartHour() < s2->getStartHour();
}

bool
Shift::isDayOff() const
{
  return startHour == 0 and endHour == 0;
}