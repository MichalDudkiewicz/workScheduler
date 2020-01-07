#include "employeeManager.h"
#include "employeeRepository.h"

EmployeeManager::EmployeeManager() : employeeRepository(EmployeeRepository::getInstance())
{}

void EmployeeManager::addEmployee(unsigned int id, const std::string &name)
{
    employeeRepository->addEmployee(id, name);
}

void EmployeeManager::removeEmployee(unsigned int id)
{
    employeeRepository->removeEmployee(id);
}

const employeePtr& EmployeeManager::getEmployeeByID(unsigned int id) const
{
    return employeeRepository->getEmployeeByID(id);
}

std::string EmployeeManager::repositoryInfo() const
{
    return employeeRepository->repositoryInfo();
}

std::string EmployeeManager::getStatisticsByID(unsigned int id) const
{
    return employeeRepository->getStatisticsByID(id);
}


