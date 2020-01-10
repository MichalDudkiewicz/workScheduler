#ifndef workSchedulerClass
#define workSchedulerClass

#include <memory>
#include <string>
#include "finalSchedule.h"

class EmployeeRepository;
class TeamRepository;

class WorkScheduler
{
private:
    FinalSchedule schedule;
public:
    WorkScheduler();
    void createSchedule();
    void updateSchedule();
    std::string scheduleInfo() const;
};

#endif