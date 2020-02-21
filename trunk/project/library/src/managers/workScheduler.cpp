#include "managers/workScheduler.h"
#include "repositories/employeeRepository.h"
#include "repositories/teamRepository.h"
#include "team/team.h"
#include "employee/employee.h"
#include "positions/position.h"
#include "shift/shift.h"
#include "other/calendar.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

WorkScheduler &WorkScheduler::getInstance() {
    static WorkScheduler instance;
    return instance;
}

WorkScheduler::WorkScheduler() : schedule(TeamRepository::getInstance().getAll(),
                                          EmployeeRepository::getInstance().getAll()) {}

void WorkScheduler::createSchedule() {
    schedule.makeSchedule();
}

std::string WorkScheduler::scheduleInfo() const {
    return schedule.scheduleInfo();
}

void WorkScheduler::updateSchedule() {
    schedule.clear();
    createSchedule();
}

const Calendar<employeesToTeam> &WorkScheduler::getSchedule() const {
    return schedule.getSchedule();
}

std::ofstream &operator<<(std::ofstream &output, const WorkScheduler &scheduler) {
    unsigned int numberOfColumns = 1;
    for (const auto &team : TeamRepository::getInstance().getAll()) {
        numberOfColumns += team->getPositions().size();
    }
    for (unsigned int i = 0; i < numberOfColumns / 2 - 3; ++i) {
        output << ",";
    }
    output << calendar::currentDateToString() << " work schedule";
    for (unsigned int i = numberOfColumns / 2 - 3; i < numberOfColumns; ++i) {
        output << ",";
    }
    output << std::endl << ",";
    for (const auto &team : TeamRepository::getInstance().getAll()) {
        for (unsigned long i = 0; i < team->getPositions().size() / 2; ++i) {
            output << ",";
        }
        output << team->getName();
        for (unsigned long i = team->getPositions().size() / 2; i < team->getPositions().size(); ++i) {
            output << ",";
        }
    }
    output << std::endl << ",";
    for (const auto &team : TeamRepository::getInstance().getAll()) {
        for (const auto &position : team->getPositions()) {
            output << position->shortcut() << ",";
        }
    }
    output << std::endl;
    unsigned int d = 1;
    for (const auto &day : scheduler.getSchedule()) {
        if (d > calendar::getNumberOfDays())
            d = 1;
        output << d << ",";
        for (const auto &team : day) {
            for (const auto &employeesOnPosition : team.second) {
                if (employeesOnPosition.second.empty())
                    output << ",";
                else {
                    output << employeesOnPosition.second.front()->getId() << ",";
                }
            }
        }
        output << std::endl;
        ++d;
    }
    return output;
}

std::string WorkScheduler::toJson() const
{
    json scheduleJson;
    json calendarJson;
    json teamJson;
    json positionJson;
    for(const auto &day : getSchedule())
    {
        for(const auto &team : day)
        {
            for(const auto &position : team.second)
            {
                if(!position.second.empty())
                    positionJson[std::to_string(position.first->positionID())]=position.second.front()->getId();
                else
                    positionJson[std::to_string(position.first->positionID())]=NULL;
            }
            teamJson[team.first->getName()]=positionJson;
            positionJson.clear();
        }
        calendarJson.push_back(teamJson);
        teamJson.clear();
    }
    scheduleJson[calendar::currentDateToString()] = calendarJson;
    return scheduleJson.dump(2);
}


