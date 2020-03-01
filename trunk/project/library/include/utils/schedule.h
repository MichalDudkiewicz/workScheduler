#ifndef employeeScheduleClass
#define employeeScheduleClass

#include "utils/calendar.h"
#include "utils/typeDefinitions.h"
#include <string>

template <typename T>
class Schedule {
protected:
    Calendar<T> schedule;

public:
    explicit Schedule()
        : schedule(calendar::getNumberOfDays() + 1)
    {
    }
    virtual ~Schedule() = default;
    const Calendar<T>& getSchedule() const
    {
        return schedule;
    }
    bool isLastDay(const Day& day) const;
    virtual std::string scheduleInfo() const = 0;
    unsigned int size() const
    {
        return schedule.size();
    }
};

template <typename T>
bool Schedule<T>::isLastDay(const Day& day) const
{
    return day.getIndex() == schedule.size() - 1;
}

#endif
