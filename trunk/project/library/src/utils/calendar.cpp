#include "utils/calendar.h"

unsigned int calendar::getNumberOfDays()
{
    boost::gregorian::date currentDate(boost::gregorian::day_clock::local_day());
    ;
    boost::gregorian::date nextMonthDate(currentDate);
    nextMonthDate += boost::gregorian::months(1);
    return boost::gregorian::gregorian_calendar::end_of_month_day(
        nextMonthDate.year(), nextMonthDate.month());
}

boost::gregorian::date calendar::getCurrentDate()
{
    return boost::gregorian::day_clock::local_day();
}

boost::gregorian::date calendar::getStartDate()
{
    boost::gregorian::date currentDate(boost::gregorian::day_clock::local_day());
    ;
    boost::gregorian::date nextMonthDate(currentDate);
    nextMonthDate += boost::gregorian::months(1);
    boost::gregorian::date startDate(nextMonthDate.year(), nextMonthDate.month(),
        1);
    return startDate;
}

std::string calendar::getWeekDay(unsigned int indeks)
{
    std::vector<std::string> weekDay{ 7 };
    weekDay[0] = "Monday";
    weekDay[1] = "Tuesday";
    weekDay[2] = "Wednesday";
    weekDay[3] = "Thursday";
    weekDay[4] = "Friday";
    weekDay[5] = "Saturday";
    weekDay[6] = "Sunday";
    return weekDay[indeks];
}

unsigned int calendar::getWeekDayIterator(const boost::gregorian::date& d)
{
    int day = d.day_of_week() - 1;
    if (day == -1)
        day = 6;
    return day;
}

std::string calendar::currentDateToString()
{
    std::ostringstream out;
    out << getStartDate().month().as_long_string() << " "
        << getStartDate().year();
    return out.str();
}

unsigned int calendar::whatDayOfWeek(unsigned int dayOfMonth)
{
    unsigned int weekDayIterator = getWeekDayIterator(getStartDate());
    for (unsigned int day = 1; day < dayOfMonth; ++day) {
        ++weekDayIterator;
        if (weekDayIterator == 7) {
            weekDayIterator = 0;
        }
    }
    return weekDayIterator;
}

Day::Day()
    : index(0)
{
}

unsigned int Day::getIndex() const
{
    return index;
}

std::string Day::toString() const
{
    std::ostringstream out;
    unsigned int daysInMonth = calendar::getNumberOfDays();
    if (index + 1 > daysInMonth)
        out << index + 1 - daysInMonth;
    else
        out << index + 1;
    return out.str();
}

Day& Day::operator++()
{
    index++;
    return *this;
}

Day& Day::operator--()
{
    if (index == 0)
        return *this;
    index--;
    return *this;
}

Day Day::operator+(unsigned int numberOfDays) const
{
    Day temp;
    temp.index = this->index + numberOfDays;
    return temp;
}

Day Day::operator-(unsigned int numberOfDays) const
{
    Day temp;
    if (index <= numberOfDays)
        return temp;
    temp.index = this->index - numberOfDays;
    return temp;
}

Day& Day::operator+=(unsigned int numberOfDays)
{
    *this = *this + numberOfDays;
    return *this;
}
Day& Day::operator-=(unsigned int numberOfDays)
{
    *this = *this - numberOfDays;
    return *this;
}
