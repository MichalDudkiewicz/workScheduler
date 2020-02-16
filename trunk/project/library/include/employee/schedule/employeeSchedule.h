#ifndef employeeScheduleClass
#define employeeScheduleClass

#include "other/calendar.h"
#include "other/typeDefinitions.h"

class EmployeeSchedule{
private:
    Calendar<shifts> shiftsInSchedule{};
public:
    void addShift(shiftPtr&);
    void addShift(unsigned int, unsigned int, unsigned int);
    void removeShift(unsigned int,unsigned int);
    const Calendar<shifts>& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif
