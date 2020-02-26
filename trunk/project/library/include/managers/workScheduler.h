#ifndef workSchedulerClass
#define workSchedulerClass

#include "schedule/finalSchedule.h"
#include <fstream>

class EmployeeRepository;
class TeamRepository;

class WorkScheduler {
private:
    FinalSchedule schedule;
    WorkScheduler();

public:
    static WorkScheduler& getInstance();
    WorkScheduler(const WorkScheduler&) = delete;
    void operator=(const WorkScheduler&) = delete;
    void createSchedule();
    void updateSchedule();
    std::string scheduleInfo() const;
    const Calendar<employeesToTeam>& getSchedule() const;
    friend std::ofstream& operator<<(std::ofstream& output,
        const WorkScheduler& scheduler);
    std::string toJson() const;
};

#endif