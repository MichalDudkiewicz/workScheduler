#include "schedule/finalSchedule.h"
#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "positions/position.h"
#include "shift/shift.h"
#include "team/team.h"

FinalSchedule::FinalSchedule(const teams& allTeams,
    const employees& allEmployees)
{
    allQueues.reserve(allTeams.size());
    for (const auto& team : allTeams) {
        allQueues.emplace_back(TeamQueues(team, allEmployees));
    }
    for (auto& teamQueues : allQueues) {
        teamQueues.createQueues();
    }
    for (auto& day : schedule) {
        for (const auto& team : allTeams) {
            day.emplace(team, employeesToPosition{});
            for (const auto& position : team->getPositions()) {
                day.at(team).emplace(position, employees{});
            }
        }
    }
}

void FinalSchedule::createSchedule()
{
    bool enemiesInTeam;
    unsigned int startHour;
    unsigned int endHour;
    for (unsigned int day = 1; day <= calendar::getNumberOfDays() + 1; ++day) {
        for (auto& teamQueue : allQueues) {
            for (const auto& position : teamQueue.getTeam()->getPositions()) {
                teamQueue.queueSort(day - 1, position);
                startHour = teamQueue.getTeam()
                                ->getShifts()[calendar::whatDayOfWeek(day)]
                                ->getStartHour();
                endHour = teamQueue.getTeam()
                              ->getShifts()[calendar::whatDayOfWeek(day)]
                              ->getEndHour();
                for (const auto& e : teamQueue.getSchedule()[day - 1].at(position)) {
                    enemiesInTeam = false;
                    for (const auto& employeesInTeam :
                        schedule[day - 1].at(teamQueue.getTeam())) {
                        if (!employeesInTeam.second.empty()) {
                            if (employeesInTeam.second.front()
                                    ->getFactor()
                                    ->getRelationship()
                                    .isEnemyWith(e)) {
                                enemiesInTeam = true;
                                break;
                            }
                        }
                    }
                    if (!e->getFactor()->getAvailability().isBusy(startHour, endHour,
                            day)
                        and !enemiesInTeam and e->getFactor()->getAvailability().getShiftsQuantity() < e->getFactor()->getRules().getMaxShifts()) {
                        schedule[day - 1]
                            .at(teamQueue.getTeam())
                            .at(position)
                            .push_front(e);
                        e->getFactor()->getAvailability().getCurrentSchedule().assign(
                            teamQueue.getTeam(), position, shiftPtr(new Shift(startHour, endHour, day)));
                        break;
                    }
                }
            }
        }
    }
}

std::string FinalSchedule::scheduleInfo() const
{
    std::ostringstream out;
    out << std::endl
        << std::setw(90) << calendar::currentDateToString()
        << " work schedule: " << std::endl;
    out << std::setw(3) << " ";
    for (const auto& team : schedule[0]) {
        out << std::setw(team.first->getPositions().size() * 5)
            << team.first->getName();
    }
    out << std::endl;
    out << std::setw(3) << " ";
    for (const auto& team : schedule[0]) {
        for (const auto& position : team.first->getPositions()) {
            out << std::setw(4) << position->shortcut() << "|";
        }
    }
    out << std::endl;
    unsigned int day = 1;
    for (const auto& queuesOnDay : schedule) {
        out << std::setw(2) << day << "|";
        for (const auto& team : queuesOnDay) {
            for (const auto& employeesInTeam : team.second) {
                if (!employeesInTeam.second.empty()) {
                    out << std::setw(4) << employeesInTeam.second.front()->getId() << "|";
                } else {
                    out << std::setw(4) << " "
                        << "|";
                }
            }
        }
        ++day;
        if (day > calendar::getNumberOfDays()) {
            day = 1;
        }
        out << std::endl;
    }
    out << std::endl;
    return out.str();
}

void FinalSchedule::clear()
{
    for (auto& day : schedule) {
        for (auto& team : day) {
            for (auto& queueToPosition : team.second) {
                queueToPosition.second.clear();
            }
        }
    }
}