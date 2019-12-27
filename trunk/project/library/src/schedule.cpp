#include "schedule.h"
#include <sstream>

Schedule::Schedule() : currentDate(boost::gregorian::day_clock::local_day())
{
    weekDay[0] = "Mon";
    weekDay[1] = "Tue";
    weekDay[2] = "Wed";
    weekDay[3] = "Thu";
    weekDay[4] = "Fri";
    weekDay[5] = "Sat";
    weekDay[6] = "Sun";
}

unsigned int Schedule::getNumberOfDays() const
{
    boost::gregorian::date nextMonthDate(currentDate);
    nextMonthDate+=boost::gregorian::months(1);
    return boost::gregorian::gregorian_calendar::end_of_month_day(nextMonthDate.year(),nextMonthDate.month());
}

const boost::gregorian::date& Schedule::getCurrentDate() const
{
    return currentDate;
}

boost::gregorian::date Schedule::getStartDate() const
{
    boost::gregorian::date nextMonthDate(currentDate);
    nextMonthDate+=boost::gregorian::months(1);
    boost::gregorian::date startDate(nextMonthDate.year(),nextMonthDate.month(),1);
    return startDate;
}

const std::string& Schedule::getWeekDay(unsigned int indeks) const
{
    return weekDay[indeks];
}

unsigned int Schedule::getWeekDayIterator(const boost::gregorian::date &d) const
{
    std::ostringstream startWeekDay;
    startWeekDay << d.day_of_week();
    unsigned int weekDayIterator = 0;
    while(startWeekDay.str() != getWeekDay(weekDayIterator))
    {
        ++weekDayIterator;
    }
    return weekDayIterator;
}

//std::string Schedule::scheduleDate() const
//{
//    std::ostringstream out;
//    boost::gregorian::date nextMonthDate(currentDate);
//    nextMonthDate+=boost::gregorian::months(1);
//    out<<nextMonthDate.month().as_long_string()<< " " <<nextMonthDate.year();
//    return out.str();
//}
