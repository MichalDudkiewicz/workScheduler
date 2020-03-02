#include "schedule/finalSchedule.h"
#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "positions/position.h"
#include "shift/shift.h"
#include "team/team.h"
#include <set>

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
    for (unsigned int day = 1; day <= calendar::getNumberOfDays() + 1; ++day) {
        for (auto& teamQueue : allQueues) {
            for (const auto& position : teamQueue.getTeam()->getPositions()) {
                teamQueue.queueSort(day - 1, position);
                shiftPtr shift(new Shift(teamQueue.getTeam()
                                             ->getShifts()[calendar::whatDayOfWeek(day)]
                                             ->getStartHour(),
                    teamQueue.getTeam()
                        ->getShifts()[calendar::whatDayOfWeek(day)]
                        ->getEndHour(),
                    day));
                for (const auto& e : teamQueue.getSchedule()[day - 1].at(position)) {

                    bool enemiesInTeam = checkEnemiesInTeam(e, day, teamQueue.getTeam());
                    bool isBusy = e->getFactor()->getAvailability().isBusy(shift);
                    bool shiftsLimitExceeded = e->getFactor()->getAvailability().getShiftsQuantity() >= e->getFactor()->getRules().getMaxShifts();
                    bool needBreak = isBreakNeeded(e, position, day, shift);

                    if (!isBusy and !enemiesInTeam and !shiftsLimitExceeded and !needBreak) {
                        schedule[day - 1]
                            .at(teamQueue.getTeam())
                            .at(position)
                            .push_front(e);
                        e->getFactor()->getAvailability().getCurrentSchedule().assign(
                            teamQueue.getTeam(), position, std::move(shift));
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

bool FinalSchedule::checkEnemiesInTeam(const employeePtr& employee, unsigned int day, const teamPtr& team) const
{
    for (const auto& employeesInTeam :
        schedule[day - 1].at(team)) {
        if (!employeesInTeam.second.empty()) {
            if (employeesInTeam.second.front()
                    ->getFactor()
                    ->getRelationship()
                    .isEnemyWith(employee)) {
                return true;
            }
        }
    }
    return false;
}

bool FinalSchedule::isBreakNeeded(const employeePtr& employee, const positionPtr& position, unsigned int day, const shiftPtr& shift) const
{
    std::list<Shift> shiftsToCheck;
    std::list<Shift> allDriverShifts;
    if (position->positionID() == 2 or position->positionID() == 3) {
        unsigned int dayAfter = day;
        if (day < calendar::getNumberOfDays() + 1)
            ++dayAfter;
        unsigned int dayBefore = day;
        if (day > 1)
            --dayBefore;
        std::set<unsigned int> daysToCheck{ dayBefore, day, dayAfter };
        for (const auto& dayToCheck : daysToCheck) {
            for (const auto& assignment : employee->getFactor()->getAvailability().getCurrentSchedule().getSchedule()[dayToCheck - 1]) {
                if (assignment.position->positionID() == 2 or assignment.position->positionID() == 3) {
                    allDriverShifts.push_front(*assignment.shift);
                    if ((*assignment.shift) + 3 == (*shift) + 3) {
                        if ((*assignment.shift).getLength() + (*shift).getLength() > 14)
                            return true;
                        shiftsToCheck.push_front(*assignment.shift);
                    }
                }
            }
        }
        unsigned int collidingShiftsLength = 0;
        for (const auto& shiftToCheck : shiftsToCheck) {
            collidingShiftsLength += shiftToCheck.getLength();
        }
        if (collidingShiftsLength + (*shift).getLength() > 14)
            return true;
        for (auto& shiftColliding : shiftsToCheck) {
            for (auto& shiftPotentiallyColliding : allDriverShifts) {
                if (((shiftColliding + 3) == (shiftPotentiallyColliding + 3)) and ((shiftColliding.getLength() + shiftPotentiallyColliding.getLength() + (*shift).getLength()) > 14)) {
                    return true;
                }
            }
        }
    }
    return false;
}
