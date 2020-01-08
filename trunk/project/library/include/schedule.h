#ifndef scheduleClass
#define scheduleClass

#include "boost/date_time/gregorian/gregorian.hpp"

namespace Schedule
{
    boost::gregorian::date getCurrentDate();
    boost::gregorian::date getStartDate();
    std::string getWeekDay(unsigned int);
    unsigned int getWeekDayIterator(const boost::gregorian::date&);
    unsigned int getNumberOfDays();
    std::string scheduleDate();
}

#endif