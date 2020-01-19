#include "employeeRepository.h"
#include "employee.h"
#include "team.h"
#include "employeeType.h"
#include <sstream>
#include <algorithm>
#include <iostream>
#include "shift.h"

EmployeeNotFound::EmployeeNotFound(const std::string &message)
        : logic_error(message)
{}

EmployeeWithThisIdExist::EmployeeWithThisIdExist(const std::string &message)
        : logic_error(message)
{}

EmployeeRepository& EmployeeRepository::getInstance()
{
    static EmployeeRepository instance;
    return instance;
}

void EmployeeRepository::checkIfIdExist(const employeePtr &employee){
    int i = 0;
    bool flag = false;
    while(i<(int)employeesRepository.size() && !flag){
        if(employeesRepository[i]->getId()==employee->getId()){
            flag = true;
            throw EmployeeWithThisIdExist();
        }
        i++;
    }
}

void EmployeeRepository::add(const employeePtr &employee)
{
    checkIfIdExist(employee);
    employeesRepository.push_back(employee);
    std::sort(employeesRepository.begin(),employeesRepository.end(),compareID());
}

void EmployeeRepository::add(unsigned int id, const std::string &name)
{
    employeePtr employee = std::make_shared<Employee>(name, id);
    employeesRepository.push_back(employee);
    std::sort(employeesRepository.begin(),employeesRepository.end(),compareID());
}

void EmployeeRepository::remove(const unsigned int &id)
{
    unsigned int it = 0;
    for(const auto &e : employeesRepository)
    {
        if(e->getId()==id)
        {
            employeesRepository.erase(employeesRepository.begin()+it);
            return;
        }
        it += 1;
    }
}

std::string EmployeeRepository::info() const
{
    std::ostringstream out;
    for(const auto &e : employeesRepository)
    {
        out<<e->getId()<<". "<<e->getName()<<std::endl;
    }
    return out.str();
}

const employees& EmployeeRepository::getAll() const
{
    return employeesRepository;
}

const employeePtr& EmployeeRepository::get(const unsigned int &id) const
{
    for(const auto &e : employeesRepository)
    {
        if(e->getId()==id)
        {
            return e;
        }
    }
    throw EmployeeNotFound();
}

employees EmployeeRepository::getByPosition(const positionPtr &position) const
{
    employees employeesByPosition;
    for(const auto &e : employeesRepository)
    {
        if(e->isAuthorised(position))
        {
            employeesByPosition.push_back(e);
        }
    }
    return employeesByPosition;
}

std::vector<employees> EmployeeRepository::getByTeam(const teamPtr &team) const
{
    std::vector<employees> employeesByTeam;
    unsigned int i = 0;
    for(const auto &position : team->getPositions())
    {
        employeesByTeam.emplace_back(getByPosition(position));
        ++i;
    }
    return employeesByTeam;
}

employees EmployeeRepository::getByType(unsigned int typeID) const
{
    employees employeesByType;
    for(const auto &e : employeesRepository)
    {
        if(e->getType()->getPriority()==typeID)
        {
            employeesByType.push_back(e);
        }
    }
    return employeesByType;
}

std::string EmployeeRepository::getStatisticsByID(unsigned int id) const
{
    std::ostringstream out;
    out << get(id)->employeeInfo() << std::endl;
    return out.str();
}

employees EmployeeRepository::getAllUnsatisfied() const
{
    employees unsatisfied;
    for(const auto &e : employeesRepository)
    {
        if(e->getMinShifts()>e->getShiftsQuantity())
        {
            unsatisfied.push_back(e);
        }
    }
    return unsatisfied;
}