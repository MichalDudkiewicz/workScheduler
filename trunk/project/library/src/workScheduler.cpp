#include "workScheduler.h"
#include "employeeRepository.h"
#include "teamRepository.h"

WorkScheduler::WorkScheduler() : employeeRepository(EmployeeRepository::getInstance()), teamRepository(TeamRepository::getInstance()), schedule(teamRepository, employeeRepository)
{}

void WorkScheduler::createSchedule()
{
    schedule.makeSchedule();
}

std::string WorkScheduler::scheduleInfo() const
{
    return schedule.scheduleInfo();
}

void WorkScheduler::updateSchedule()
{
    schedule.clear();
    createSchedule();
}