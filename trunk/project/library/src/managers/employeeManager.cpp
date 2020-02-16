#include "managers/employeeManager.h"
#include "repositories/employeeRepository.h"
#include "employee/employee.h"
#include "positions/position.h"
#include "employee/factors/rules/employeeTypes/employeeType.h"
#include "other/calendar.h"
#include "shift/shift.h"
#include "employee/factors/factor.h"

EmployeeManager &EmployeeManager::getInstance() {
    static EmployeeManager instance;
    return instance;
}

void EmployeeManager::add(unsigned int id, const std::string &name) {
    EmployeeRepository::getInstance().add(id, name);
}

void EmployeeManager::remove(const unsigned int &id) {
    EmployeeRepository::getInstance().remove(id);
}

const employeePtr &EmployeeManager::get(const unsigned int &id) const {
    return EmployeeRepository::getInstance().get(id);
}

std::string EmployeeManager::info() const {
    return EmployeeRepository::getInstance().info();
}

std::string EmployeeManager::getStatisticsByID(unsigned int id) const {
    return EmployeeRepository::getInstance().getStatisticsByID(id);
}

std::list<employeePtr> EmployeeManager::getAll() const {
    return EmployeeRepository::getInstance().getAll();
}

std::ofstream &operator<<(std::ofstream &output, const EmployeeManager &manager) {
    output << "ID,name,wage,points,priority,nonresident,positions,enemies," << std::endl;
    for (const auto &employee : manager.getAll()) {
        output << employee->getId() << "," << employee->getName() << "," << employee->getHourlyWage() << ","
                 << employee->getFactor()->getRules().getPoints() << "," << employee->getFactor()->getRules().getType()->getPriority() << ","
                 << employee->getFactor()->getRules().isNonresident() << ",";
        for (const auto &position : employee->getFactor()->getAuthorisation().getPositions()) {
            output << position->positionID() << ";";
        }
        output << ",";
        for (const auto &enemy : employee->getFactor()->getRelationship().getMyEnemies()) {
            output << enemy->getId() << ";";
        }
        output << ",";
        output << std::endl;
    }
    return output;
}

std::ofstream &operator<(std::ofstream &output, const EmployeeManager &manager) {
    output << "ID\\day" << ",";
    for (unsigned int day = 1; day <= calendar::getNumberOfDays(); ++day) {
        output << day << ",";
    }
    output << "1" << "," << std::endl;
    for (const auto &employee : manager.getAll()) {
        output << employee->getId() << ",";
        for (const auto &shifts : employee->getFactor()->getAvailability().getDesiredSchedule().getSchedule()) {
            for (const auto &shift : shifts) {
                output << shift->getStartHour() << "-" << shift->getEndHour() << ";";
            }
            output << ",";
        }
        output << std::endl;
    }
    return output;
}


