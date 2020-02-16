#ifndef WORKSCHEDULER_EMPLOYEESCHEDULES_H
#define WORKSCHEDULER_EMPLOYEESCHEDULES_H

#include "employeeSchedule.h"
#include "calendar.h"

class EmployeeSchedules {
private:
    EmployeeSchedule desiredSchedule;
    EmployeeSchedule currentSchedule;
public:
    EmployeeSchedules();
    unsigned int getWorkHours() const;
    unsigned int getShiftsQuantity() const;
    const Calendar<shifts>& getDesiredSchedule() const;
    const Calendar<shifts>& getCurrentSchedule() const;
    bool isAvailable(const shiftPtr& shift) const;
    void removeDesiredShift(unsigned int, unsigned int);
    void addCurrentShift(shiftPtr&);
    void addCurrentShift(unsigned int, unsigned int, unsigned int);
    void removeCurrentShift(unsigned int, unsigned int);
    bool isBusy(const shiftPtr&) const;
    std::string desiredScheduleInfo() const;
    std::string currentScheduleInfo() const;
    void addDesiredShift(shiftPtr&);
    void addDesiredShift(unsigned int, unsigned int, unsigned int);
};


#endif //WORKSCHEDULER_EMPLOYEESCHEDULES_H
