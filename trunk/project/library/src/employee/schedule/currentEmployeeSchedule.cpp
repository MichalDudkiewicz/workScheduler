#include "employee/schedule/currentEmployeeSchedule.h"
#include "shift/shift.h"
#include "team/team.h"

void CurrentEmployeeSchedule::assign(teamPtr team, positionPtr position, shiftPtr shift){
    unsigned int day = shift->getDay();
    assignment assign;
    assign.team = std::move(team);
    assign.position = std::move(position);
    assign.shift = std::move(shift);
    schedule[day - 1].push_front(std::move(assign));
}
void CurrentEmployeeSchedule::removeAssignment(const teamPtr& team, unsigned int day){
    for(auto &assign : schedule[day-1])
    {
        if(assign.team->getName() == team -> getName())
        {
            schedule[day-1].remove(assign);
            return;
        }
    }
}

std::string CurrentEmployeeSchedule::scheduleInfo() const{
return "";
}
