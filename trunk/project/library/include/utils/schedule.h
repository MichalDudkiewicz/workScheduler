#ifndef employeeScheduleClass
#define employeeScheduleClass

#include "utils/calendar.h"
#include "utils/typeDefinitions.h"
#include <string>

template <typename T>
class Schedule {
protected:
    Calendar<T> schedule{};

public:
    virtual ~Schedule() = default;
    const Calendar<T>& getSchedule() const
    {
        return schedule;
    }
    virtual std::string scheduleInfo() const = 0;
};

#endif
