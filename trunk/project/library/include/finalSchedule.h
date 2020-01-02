#ifndef finalScheduleClass
#define finalScheduleClass

#include <memory>
#include <vector>
#include "teamQueues.h"

class EmployeeRepository;
class TeamRepository;
typedef std::unique_ptr<EmployeeRepository> empRepositoryPtr;
typedef std::unique_ptr<TeamRepository> teamRepositoryPtr;
typedef std::vector<TeamQueues> teamsQueues;

class FinalSchedule
{
private:
    teamsQueues allQueues{};
public:
    FinalSchedule(const teamRepositoryPtr&, const empRepositoryPtr&);
    std::string makeSchedule() const;
};

#endif