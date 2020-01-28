#ifndef calendarNamespace
#define calendarNamespace

#include "boost/date_time/gregorian/gregorian.hpp"
#include <vector>

namespace calendar{
    boost::gregorian::date getCurrentDate();
    boost::gregorian::date getStartDate();
    std::string getWeekDay(unsigned int);
    unsigned int getWeekDayIterator(const boost::gregorian::date&);
    unsigned int getNumberOfDays();
    std::string currentDateToString();
    unsigned int whatDayOfWeek(unsigned int dayOfMonth);
}

template <class T>
class Calendar
{
private:
    std::vector<T> calendar{};
public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    Calendar()
    {
        calendar.reserve(calendar::getNumberOfDays() + 1);
        for(unsigned int day = 1; day <= calendar::getNumberOfDays() + 1; ++day)
        {
            calendar.emplace_back();
        }
    }
    iterator begin()
    {
        return calendar.begin();
    }
    const_iterator begin() const
    {
        return calendar.begin();
    }
    iterator end()
    {
        return calendar.end();
    }
    const_iterator end() const
    {
        return calendar.end();
    }
    T & operator[](unsigned int index)
    {
        return calendar[index];
    }
    unsigned int size() const
    {
        return calendar.size();
    }
    const T & operator[](unsigned int index) const
    {
        return calendar[index];
    }
};

#endif