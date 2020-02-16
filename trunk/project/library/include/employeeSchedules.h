#ifndef WORKSCHEDULER_EMPLOYEESCHEDULES_H
#define WORKSCHEDULER_EMPLOYEESCHEDULES_H

#include "employeeSchedule.h"
#include "calendar.h"

class EmployeeSchedules {
private:
    EmployeeSchedule desiredSchedule;
    EmployeeSchedule currentSchedule;
    friend Employee;
    EmployeeSchedules();
public:
    unsigned int getWorkHours() const;
    unsigned int getShiftsQuantity() const;
    bool isAvailable(const shiftPtr& shift) const;
    bool isBusy(const shiftPtr&) const;
    EmployeeSchedule& getCurrentSchedule();
    EmployeeSchedule& getDesiredSchedule();
};


#endif //WORKSCHEDULER_EMPLOYEESCHEDULES_H
