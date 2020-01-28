#include "employeeManager.h"
#include "employeeRepository.h"
#include "employee.h"
#include "position.h"
#include "employeeType.h"
#include "calendar.h"
#include "shift.h"

EmployeeManager &EmployeeManager::getInstance() {
    static EmployeeManager instance;
    return instance;
}

void EmployeeManager::addEmployee(unsigned int id, const std::string &name) {
    EmployeeRepository::getInstance().add(id, name);
}

void EmployeeManager::removeEmployee(unsigned int id) {
    EmployeeRepository::getInstance().remove(id);
}

const employeePtr &EmployeeManager::getEmployeeByID(unsigned int id) const {
    return EmployeeRepository::getInstance().get(id);
}

std::string EmployeeManager::repositoryInfo() const {
    return EmployeeRepository::getInstance().info();
}

std::string EmployeeManager::getStatisticsByID(unsigned int id) const {
    return EmployeeRepository::getInstance().getStatisticsByID(id);
}

const std::vector<employeePtr> &EmployeeManager::getAll() const {
    return EmployeeRepository::getInstance().getAll();
}

std::ofstream &operator<<(std::ofstream &output, const EmployeeManager &manager) {
    output << "ID,name,wage,points,priority,nonresident,positions,enemies," << std::endl;
    for (const auto &employee : manager.getAll()) {
        output << employee->getId() << "," << employee->getName() << "," << employee->getHourlyWage() << ","
                 << employee->getPoints() << "," << employee->getType()->getPriority() << ","
                 << employee->isNonresident() << ",";
        for (const auto &position : employee->getPositions()) {
            output << position->positionID() << ";";
        }
        output << ",";
        for (const auto &enemy : employee->getMyEnemies()) {
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
        for (const auto &shifts : employee->getDesiredSchedule()) {
            for (const auto &shift : shifts) {
                output << shift->getStartHour() << "-" << shift->getEndHour() << ";";
            }
            output << ",";
        }
        output << std::endl;
    }
    return output;
}


