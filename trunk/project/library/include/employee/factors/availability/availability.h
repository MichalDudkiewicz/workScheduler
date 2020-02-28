#ifndef WORKSCHEDULER_AVAILABILITY_H
#define WORKSCHEDULER_AVAILABILITY_H

#include "employee/schedule/currentEmployeeSchedule.h"
#include "employee/schedule/desiredEmployeeSchedule.h"
#include "other/calendar.h"

class Availability {
private:
    DesiredEmployeeSchedule desiredSchedule;
    CurrentEmployeeSchedule currentSchedule;
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
    CurrentEmployeeSchedule& getCurrentSchedule();
    DesiredEmployeeSchedule& getDesiredSchedule();
};

#endif // WORKSCHEDULER_AVAILABILITY_H
