#include "employeeRepository.h"
#include <sstream>
#include <employee.h>
#include <algorithm>
#include <team.h>
#include <employeeType.h>

void EmployeeRepository::addEmployee(const employeePtr &employee)
{
    employeesRepository.push_back(employee);
    std::sort(employeesRepository.begin(),employeesRepository.end(),compareID());
}

void EmployeeRepository::removeEmployee(unsigned int id)
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

std::string EmployeeRepository::repositoryInfo() const
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

const employeePtr& EmployeeRepository::getEmployeeByID(unsigned int id) const
{
    for(const auto &e : employeesRepository)
    {
        if(e->getId()==id)
        {
            return e;
        }
    }
    // throw exception employee not found
    return employeesRepository[0];
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
    out << getEmployeeByID(id)->employeeInfo()<<std::endl;
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