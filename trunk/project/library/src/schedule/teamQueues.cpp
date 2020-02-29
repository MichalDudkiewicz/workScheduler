#include "schedule/teamQueues.h"

#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "positions/position.h"
#include "shift/shift.h"
#include "team/team.h"
#include <utility>

TeamQueues::TeamQueues(teamPtr t, employees authorisedEmployees)
    : team(std::move(t))
    , authorisedEmployees(std::move(authorisedEmployees))
{
    for (auto& day : schedule) {
        for (const auto& position : team->getPositions()) {
            day.emplace(position, employees{});
        }
    }
}

const teamPtr& TeamQueues::getTeam() const
{
    return team;
}

void TeamQueues::queueSort(unsigned int day, const positionPtr& position)
{
    schedule[day].at(position).sort(sortPointsTypeWorkHours());
}

std::string TeamQueues::scheduleInfo() const
{
    std::ostringstream out;
    unsigned int day = 1;
    for (const auto& queueOnDay : getSchedule()) {
        out << "day " << day << " shifts queue: " << std::endl;
        for (const auto& queueToPosition : queueOnDay) {
            out << queueToPosition.first->positionInfo() << ": ";
            for (const auto& employee : queueToPosition.second) {
                out << employee->getId() << ", ";
            }
            out << std::endl;
        }
        day += 1;
        if (day > calendar::getNumberOfDays())
            day = 1;
    }
    return out.str();
}
void TeamQueues::createQueues()
{
    unsigned int day = 1;
    unsigned int dayOfWeek;
    for (auto& queuesOnDay : schedule) {
        dayOfWeek = calendar::whatDayOfWeek(day);
        if (!team->getShifts()[dayOfWeek]->isDayOff()) {
            team->getShifts()[dayOfWeek]->setDay(day);
            for (auto& queueToPosition : queuesOnDay) {
                for (const auto& employee : authorisedEmployees) {
                    if (employee->getFactor()->getAuthorisation().isAuthorised(
                            queueToPosition.first, team)
                        and employee->getFactor()->getAvailability().isAvailable(
                                team->getShifts()[dayOfWeek])) {
                        queueToPosition.second.push_front(employee);
                    }
                }
            }
        }
        day += 1;
    }
}
