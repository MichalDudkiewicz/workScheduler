#include "teamQueues.h"
#include "employee.h"
#include "team.h"
#include "shift.h"
#include "position.h"

TeamQueues::TeamQueues(teamPtr t, const employees &authorisedEmployees) : team(std::move(t)) {
    for(auto &day : calendarOfQueues)
    {
        for (const auto &position : team->getPositions()) {
            day.emplace(position, employees{});
        }
    }
    unsigned int day = 1;
    unsigned int dayOfWeek;
    for (auto &queuesOnDay : calendarOfQueues) {
        dayOfWeek = calendar::whatDayOfWeek(day);
        if (!team->getShifts()[dayOfWeek]->isDayOff()) {
            team->getShifts()[dayOfWeek]->setDay(day);
            for (auto &queueToPosition : queuesOnDay) {
                for (const auto &employee : authorisedEmployees) {
                    if (employee->getAuthorisation().isAuthorised(queueToPosition.first, team) and
                            employee->getAvailability().isAvailable(team->getShifts()[dayOfWeek])) {
                        queueToPosition.second.push_front(employee);
                    }
                }
            }
        }
        day += 1;
    }
}

const Calendar<employeesToPosition> &TeamQueues::getTeamQueues() const{
    return calendarOfQueues;
}

const teamPtr &TeamQueues::getTeam() const {
    return team;
}

void TeamQueues::queueSort(unsigned int day, const positionPtr &position) {
    calendarOfQueues[day].at(position).sort(sortPointsTypeWorkHours());
}

std::string TeamQueues::teamQueuesInfo() const {
    std::ostringstream out;
    unsigned int day = 1;
    for (const auto &queueOnDay : getTeamQueues()) {
        out << "day " << day << " shifts queue: " << std::endl;
        for (const auto &queueToPosition : queueOnDay) {
            out << queueToPosition.first -> positionInfo() << ": ";
            for (const auto &employee : queueToPosition.second) {
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
