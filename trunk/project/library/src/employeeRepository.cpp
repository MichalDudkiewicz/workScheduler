#include "employeeRepository.h"
#include "employee.h"
#include "team.h"
#include "employeeType.h"
#include "shift.h"

EmployeeNotFound::EmployeeNotFound(const std::string &message)
        : logic_error(message) {}

EmployeeWithThisIdExist::EmployeeWithThisIdExist(const std::string &message)
        : logic_error(message) {}

EmployeeRepository &EmployeeRepository::getInstance() {
    static EmployeeRepository instance;
    return instance;
}

void EmployeeRepository::checkIfIdExist(const unsigned int &id) {
    auto search = employeesRepository.find(id);
    if (search != employeesRepository.end()) {
        throw EmployeeWithThisIdExist();
    } else {
        return;
    }
}

void EmployeeRepository::add(const employeePtr &employee) {
    checkIfIdExist(employee->getId());
    employeesRepository.insert(std::make_pair(employee->getId(), employee));
}

void EmployeeRepository::add(unsigned int id, const std::string &name) {
    employeePtr employee = std::make_shared<Employee>(name, id);
    employeesRepository.emplace(std::make_pair(id, std::make_shared<Employee>(name,id)));
}

void EmployeeRepository::remove(const unsigned int &id) {
    employeesRepository.erase(id);
}

std::string EmployeeRepository::info() const {
    std::ostringstream out;
    for (const auto &employee : employeesRepository) {
        out << employee.second->getId() << ". " << employee.second->getName() << std::endl;
    }
    return out.str();
}

employees EmployeeRepository::getAll() const {
    employees allEmployees;
    for(const auto &employee : employeesRepository)
    {
        allEmployees.push_front(employee.second);
    }
    allEmployees.sort(compareID());
    return allEmployees;
}

const employeePtr &EmployeeRepository::get(const unsigned int &id) const {
    try
    {
        return employeesRepository.at(id);
    } catch(std::out_of_range &error)
    {
        throw EmployeeNotFound();
    }
}

employees EmployeeRepository::getByPosition(const positionPtr &position) const {
    employees employeesByPosition;
    for (const auto &employee : employeesRepository) {
        if (employee.second->isAuthorised(position)) {
            employeesByPosition.push_front(employee.second);
        }
    }
    return employeesByPosition;
}

std::vector<employees> EmployeeRepository::getByTeam(const teamPtr &team) const {
    std::vector<employees> employeesByTeam;
    for (const auto &position : team->getPositions()) {
        employeesByTeam.emplace_back(getByPosition(position));
    }
    return employeesByTeam;
}

employees EmployeeRepository::getByType(unsigned int typeID) const {
    employees employeesByType;
    for (const auto &employee : employeesRepository) {
        if (employee.second->getType()->getPriority() == typeID) {
            employeesByType.push_front(employee.second);
        }
    }
    return employeesByType;
}

std::string EmployeeRepository::getStatisticsByID(unsigned int id) const {
    std::ostringstream out;
    out << get(id)->employeeInfo() << std::endl;
    return out.str();
}

employees EmployeeRepository::getAllUnsatisfied() const {
    employees unsatisfied;
    for (const auto &employee : employeesRepository) {
        if (employee.second->getMinShifts() > employee.second->getShiftsQuantity()) {
            unsatisfied.push_front(employee.second);
        }
    }
    return unsatisfied;
}