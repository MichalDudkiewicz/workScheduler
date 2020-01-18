#include "workScheduler.h"
#include "employeeRepository.h"
#include "teamRepository.h"

WorkScheduler& WorkScheduler::getInstance()
{
    static WorkScheduler instance;
    return instance;
}

WorkScheduler::WorkScheduler() : schedule(TeamRepository::getInstance().getAll(), EmployeeRepository::getInstance().getAll())
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

const calendar& WorkScheduler::getSchedule() const
{
    return schedule.getSchedule();
}