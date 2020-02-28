#include "employee/schedule/currentEmployeeSchedule.h"
#include "shift/shift.h"
#include <sstream>
#include "other/calendar.h"
#include "positions/position.h"
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
    std::ostringstream info;
    info << "My current schedule: " << std::endl;
    unsigned int dayNumber = 1;
    for (const auto &day : schedule)
    {
        info << dayNumber << ": " << std::endl;
        for (const auto & assignment : day)
        {
            info << "team: " << assignment.team->getName()<<std::endl;
            info << "position: "<<assignment.position->positionInfo()<<std::endl;
            info << "shift: " << assignment.shift->shiftInfo()<<std::endl;
        }
        info <<std::endl;
        dayNumber++;
        if(dayNumber==calendar::getNumberOfDays()+1)
            dayNumber=1;
    }
    return info.str();
}
