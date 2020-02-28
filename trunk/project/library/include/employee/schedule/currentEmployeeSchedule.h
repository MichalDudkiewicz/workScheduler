#ifndef WORKSCHEDULER_CURRENTEMPLOYEESCHEDULE_H
#define WORKSCHEDULER_CURRENTEMPLOYEESCHEDULE_H

#include "utils/schedule.h"
#include "utils/typeDefinitions.h"
#include <list>
#include <string>

struct assignment {
    teamPtr team{};
    positionPtr position{};
    shiftPtr shift{};
    bool operator==(const assignment& other)
    {
        return this->team == other.team and this->position == other.position and this->shift == other.shift;
    }
};

typedef std::list<assignment> assignments;

class CurrentEmployeeSchedule : public Schedule<assignments> {
public:
    void assign(teamPtr team, positionPtr position, shiftPtr shift);
    void removeAssignment(const teamPtr& team, unsigned int day);
    std::string scheduleInfo() const override;
};

#endif //WORKSCHEDULER_CURRENTEMPLOYEESCHEDULE_H
