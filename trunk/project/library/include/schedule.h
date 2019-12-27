#ifndef scheduleClass
#define scheduleClass

#include <memory>
#include <vector>
#include "boost/date_time/gregorian/gregorian.hpp"


class Schedule
{
private:
    boost::gregorian::date currentDate;
    std::vector<std::string> weekDay{7};
public:
    Schedule();
    virtual ~Schedule() = default;
    const boost::gregorian::date& getCurrentDate() const;
    boost::gregorian::date getStartDate() const;
    const std::string& getWeekDay(unsigned int) const;
    unsigned int getWeekDayIterator(const boost::gregorian::date&) const;
    unsigned int getNumberOfDays() const;
//    virtual std::string scheduleDate() const;
};

#endif