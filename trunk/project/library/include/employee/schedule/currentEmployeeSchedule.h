#ifndef WORKSCHEDULER_CURRENTEMPLOYEESCHEDULE_H
#define WORKSCHEDULER_CURRENTEMPLOYEESCHEDULE_H

#include "employee/schedule/employeeSchedule.h"
#include "other/typeDefinitions.h"
#include <string>
#include <list>

struct assignment
{
    teamPtr team{};
    positionPtr position{};
    shiftPtr shift{};
    bool operator==(const assignment &other)
    {
        return this->team == other.team and this-> position == other.position and this->shift==other.shift;
    }
};

typedef std::list<assignment> assignments;

class CurrentEmployeeSchedule : public EmployeeSchedule<assignments>{
    public:
    void assign(teamPtr team, positionPtr position, shiftPtr shift);
    void removeAssignment(const teamPtr& team, unsigned int day);
    std::string scheduleInfo() const override;
};


#endif //WORKSCHEDULER_CURRENTEMPLOYEESCHEDULE_H
