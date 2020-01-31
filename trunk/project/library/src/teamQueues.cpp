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
    for (auto &queuesOnDay : calendarOfQueues) {
        if (!team->getShifts()[calendar::whatDayOfWeek(day)]->isDayOff()) {
            team->getShifts()[calendar::whatDayOfWeek(day)]->setDay(day);
            for (auto &queueToPosition : queuesOnDay) {
                for (const auto &employee : authorisedEmployees) {
                    if (employee->isAuthorised(queueToPosition.first) and
                        employee->isAvailable(team->getShifts()[calendar::whatDayOfWeek(day)])) {
                        queueToPosition.second.push_front(employee);
                    }
                }
            }
        }
        day += 1;
    }
}

const Calendar<queuesToPosition> &TeamQueues::getTeamQueues() const{
    return calendarOfQueues;
}

const teamPtr &TeamQueues::getTeam() const {
    return team;
}

void TeamQueues::queueSort(unsigned int d, const positionPtr &position) {
    calendarOfQueues[d].at(position).sort(sortPointsTypeWorkHours());
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
