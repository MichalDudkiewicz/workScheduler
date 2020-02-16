#ifndef WORKSCHEDULER_AVAILABILITY_H
#define WORKSCHEDULER_AVAILABILITY_H

#include "employeeSchedule.h"
#include "calendar.h"

class Availability {
private:
    EmployeeSchedule desiredSchedule;
    EmployeeSchedule currentSchedule;
    friend Employee;
    Availability();
public:
    unsigned int getWorkHours() const;
    unsigned int getShiftsQuantity() const;
    bool isAvailable(const shiftPtr& shift) const;
    bool isBusy(const shiftPtr&) const;
    EmployeeSchedule& getCurrentSchedule();
    EmployeeSchedule& getDesiredSchedule();
};


#endif //WORKSCHEDULER_AVAILABILITY_H
