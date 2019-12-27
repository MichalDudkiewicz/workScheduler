#ifndef WORKSCHEDULER_EMPLOYEESCHEDULE_H
#define WORKSCHEDULER_EMPLOYEESCHEDULE_H

#include <vector>
#include <memory>
#include "schedule.h"
#include "shift.h" //forward declaration (?)

typedef std::unique_ptr<Shift> shiftPtr;
typedef std::vector<shiftPtr> shifts;
typedef std::vector<shifts> schedule;

class EmployeeSchedule : public Schedule
{
private:
    schedule shiftsInSchedule{};
public:
    EmployeeSchedule();
    void addShift(shiftPtr&);
    void removeShift(unsigned int,unsigned int);
    const schedule& getSchedule() const;
};

#endif //WORKSCHEDULER_EMPLOYEESCHEDULE_H
