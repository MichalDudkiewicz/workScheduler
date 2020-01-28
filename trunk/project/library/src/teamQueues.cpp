#include "teamQueues.h"
#include "employee.h"
#include "team.h"
#include "shift.h"
#include "position.h"

TeamQueues::TeamQueues(teamPtr t, const employees &authorisedEmployees) : team(std::move(t)) {
    for(auto &day : teamQueues)
    {
        for (unsigned long j = 0; j < team->getPositions().size(); ++j) {
            day.emplace_back();
        }
    }
    unsigned int p;
    unsigned int day = 1;
    for (auto &dayQueue : teamQueues) {
        if (!team->getShifts()[calendar::whatDayOfWeek(day)]->isDayOff()) {
            team->getShifts()[calendar::whatDayOfWeek(day)]->setDay(day);
            p = 0;
            for (auto &positionQueue : dayQueue) {
                for (const auto &employee : authorisedEmployees) {
                    if (employee->isAuthorised(team->getPositions()[p]) and
                        employee->isAvailable(team->getShifts()[calendar::whatDayOfWeek(day)])) {
                        positionQueue.push_back(employee);
                    }
                }
                p += 1;
            }
        }
        day += 1;
    }
}

const Calendar<dayQueues> &TeamQueues::getTeamQueues() const{
    return teamQueues;
}

const teamPtr &TeamQueues::getTeam() const {
    return team;
}

void TeamQueues::queueSort(unsigned int d, unsigned int i) {
    std::sort(teamQueues[d][i].begin(), teamQueues[d][i].end(), sortPointsTypeWorkHours());
}

std::string TeamQueues::teamQueuesInfo() const {
    std::ostringstream out;
    unsigned int day = 1;
    unsigned int p;
    for (const auto &dayQueue : getTeamQueues()) {
        out << "day " << day << " shifts queue: " << std::endl;
        p = 0;
        for (const auto &positionQueue : dayQueue) {
            out << getTeam()->getPositions()[p]->positionInfo() << ": ";
            for (const auto &shift : positionQueue) {
                out << shift->getId() << ", ";
            }
            out << std::endl;
            p += 1;
        }
        day += 1;
        if (day > calendar::getNumberOfDays())
            day = 1;
    }
    return out.str();
}