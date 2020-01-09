#include "workScheduler.h"
#include "employeeRepository.h"
#include "teamRepository.h"

WorkScheduler::WorkScheduler() : schedule(TeamRepository::getInstance(), EmployeeRepository::getInstance())
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