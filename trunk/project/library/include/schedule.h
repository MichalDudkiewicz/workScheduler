#ifndef scheduleClass
#define scheduleClass

#include <memory>
#include <vector>
#include "boost/date_time/gregorian/gregorian.hpp"


namespace Schedule
{
    boost::gregorian::date getCurrentDate();
    boost::gregorian::date getStartDate();
    std::string getWeekDay(unsigned int);
    unsigned int getWeekDayIterator(const boost::gregorian::date&);
    unsigned int getNumberOfDays();
//    virtual std::string scheduleDate();
}

#endif