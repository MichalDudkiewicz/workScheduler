#ifndef calendarNamespace
#define calendarNamespace

#include <boost/date_time/gregorian/gregorian.hpp>
#include <exception>
#include <vector>

namespace calendar {
boost::gregorian::date getCurrentDate();
boost::gregorian::date getStartDate();
std::string getWeekDay(unsigned int);
unsigned int getWeekDayIterator(const boost::gregorian::date&);
unsigned int getNumberOfDays();
std::string currentDateToString();
unsigned int whatDayOfWeek(unsigned int dayOfMonth);
} // namespace calendar

template <class T>
class Calendar {
private:
    std::vector<T> calendar{};

public:
    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;
    explicit Calendar(unsigned int sizeOfSchedule)
    {
        calendar.reserve(sizeOfSchedule);
        for (unsigned int day = 1; day <= sizeOfSchedule; ++day) {
            calendar.emplace_back();
        }
    }
    iterator begin() { return calendar.begin(); }
    const_iterator begin() const { return calendar.begin(); }
    iterator end() { return calendar.end(); }
    const_iterator end() const { return calendar.end(); }
    T& operator[](unsigned int index) { return calendar[index]; }
    unsigned int size() const { return calendar.size(); }
    const T& operator[](unsigned int index) const { return calendar[index]; }
    const std::vector<T>& getCalendar() const { return calendar; }
};

class DayException : public std::logic_error {
public:
    explicit DayException(const std::string& message);
    std::string message() const;
};

class Day {
private:
    unsigned int index;

public:
    Day();
    explicit Day(int dayNumber);
    Day& operator=(const Day& rhs) = default;
    Day& operator++() noexcept(false);
    Day& operator--() noexcept(false);
    Day& operator+=(unsigned int numberOfDays);
    Day& operator-=(unsigned int numberOfDays);
    Day operator+(unsigned int numberOfDays) const noexcept(false);
    Day operator-(unsigned int numberOfDays) const noexcept(false);
    unsigned int dayOfWeek() const;
    unsigned int getIndex() const;
};

std::ostream& operator<<(std::ostream& os, const Day& day);

#endif