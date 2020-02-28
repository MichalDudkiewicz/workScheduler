#ifndef employeeScheduleClass
#define employeeScheduleClass

#include "other/calendar.h"
#include "other/typeDefinitions.h"
#include <string>

template <typename T>
class EmployeeSchedule {
protected:
    Calendar<T> schedule{};

public:
    virtual ~EmployeeSchedule() = default;
    const Calendar<T>& getSchedule() const
    {
        return schedule;
    }
    virtual std::string scheduleInfo() const = 0;
};

#endif
