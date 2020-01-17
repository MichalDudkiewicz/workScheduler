#include "employeeManager.h"
#include "employeeRepository.h"

EmployeeManager& EmployeeManager::getInstance()
{
    static EmployeeManager instance;
    return instance;
}

void EmployeeManager::addEmployee(unsigned int id, const std::string &name)
{
    EmployeeRepository::getInstance().addEmployee(id, name);
}

void EmployeeManager::removeEmployee(unsigned int id)
{
    EmployeeRepository::getInstance().removeEmployee(id);
}

const employeePtr& EmployeeManager::getEmployeeByID(unsigned int id) const
{
    return EmployeeRepository::getInstance().getEmployeeByID(id);
}

std::string EmployeeManager::repositoryInfo() const
{
    return  EmployeeRepository::getInstance().repositoryInfo();
}

std::string EmployeeManager::getStatisticsByID(unsigned int id) const
{
    return  EmployeeRepository::getInstance().getStatisticsByID(id);
}

const std::vector<employeePtr> &EmployeeManager::getAll() const
{
    return EmployeeRepository::getInstance().getAll();
}


