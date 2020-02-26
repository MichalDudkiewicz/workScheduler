#ifndef WORKSCHEDULER_AVAILABILITY_H
#define WORKSCHEDULER_AVAILABILITY_H

#include "employee/schedule/employeeSchedule.h"
#include "other/calendar.h"

class Availability {
private:
    EmployeeSchedule desiredSchedule;
    EmployeeSchedule currentSchedule;
    friend class Factor;
    Availability();

public:
    unsigned int getWorkHours() const;
    unsigned int getShiftsQuantity() const;
    bool isAvailable(const shiftPtr& shift) const;
    bool isBusy(const shiftPtr&) const;
    bool isBusy(unsigned int startHour,
        unsigned int endHour,
        unsigned int day) const;
    EmployeeSchedule& getCurrentSchedule();
    EmployeeSchedule& getDesiredSchedule();
};

#endif // WORKSCHEDULER_AVAILABILITY_H
