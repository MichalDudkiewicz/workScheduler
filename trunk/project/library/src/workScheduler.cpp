#include "workScheduler.h"
#include "employeeRepository.h"
#include "teamRepository.h"
#include "schedule.h"
#include "team.h"
#include "employee.h"
#include "position.h"
#include "shift.h"

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

const calendar &WorkScheduler::getSchedule() const {
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
    output << Schedule::scheduleDate() << " work schedule";
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
        if (d > Schedule::getNumberOfDays())
            d = 1;
        output << d << ",";
        for (const auto &team : day) {
            for (const auto &position : team) {
                if (position.empty())
                    output << ",";
                else {
                    output << position.front()->getId() << ",";
                }
            }
        }
        output << std::endl;
        ++d;
    }
    return output;
}
