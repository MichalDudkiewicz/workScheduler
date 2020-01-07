#ifndef workSchedulerClass
#define workSchedulerClass

#include <memory>
#include <string>
#include "finalSchedule.h"

class EmployeeRepository;
class TeamRepository;
class Team;
class Employee;

class WorkScheduler
{
private:
    EmployeeRepository* employeeRepository;
    TeamRepository* teamRepository;
    FinalSchedule schedule;
public:
    WorkScheduler();
    WorkScheduler(const WorkScheduler&)= default;
    WorkScheduler& operator=(const WorkScheduler&)= default;
    void createSchedule();
    void updateSchedule();
    std::string scheduleInfo() const;
};

#endif