#ifndef employeeScheduleClass
#define employeeScheduleClass

#include <memory>
#include <string>
#include "calendar.h"

class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::vector<shiftPtr> shifts;

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
