#ifndef finalScheduleClass
#define finalScheduleClass

#include <memory>
#include <vector>
#include <string>
#include "teamQueues.h"

class EmployeeRepository;
class TeamRepository;
typedef std::unique_ptr<EmployeeRepository> empRepositoryPtr;
typedef std::unique_ptr<TeamRepository> teamRepositoryPtr;
typedef std::vector<TeamQueues> teamsQueues;
typedef std::vector<employeePtr> employees;
typedef std::vector<employees> employeesOnPosition;
typedef std::vector<employeesOnPosition> teamsOnDay;
typedef std::vector<teamsOnDay> calendar;

class FinalSchedule
{
private:
    teamsQueues allQueues{};
    calendar schedule{};
public:
    FinalSchedule(const teamRepositoryPtr&, const empRepositoryPtr&);
    void makeSchedule();
    const calendar& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif