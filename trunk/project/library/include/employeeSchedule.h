#ifndef employeeScheduleClass
#define employeeScheduleClass

#include "calendar.h"
#include "typeDefinitions.h"

class EmployeeSchedule{
private:
    Calendar<shifts> shiftsInSchedule{};
public:
    void addShift(shiftPtr&);
    void removeShift(unsigned int,unsigned int);
    const Calendar<shifts>& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif
