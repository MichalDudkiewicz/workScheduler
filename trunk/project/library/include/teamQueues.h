#ifndef teamQueuesClass
#define teamQueuesClass

#include <memory>
#include <vector>
#include <string>

class Team;
class Employee;
class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::shared_ptr<Team> teamPtr;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::vector<employeePtr> employees;
typedef std::vector<employees> dayQueues;
typedef std::vector<dayQueues> queues;

class TeamQueues
{
private:
    teamPtr team;
    employees authorisedEmployees;
    queues teamQueues{};
public:
    TeamQueues(teamPtr,employees);
    const queues& getTeamQueues() const;
    const employees& getAuthorisedEmployees() const;
    const teamPtr& getTeam() const;
    void queueSort(unsigned int, unsigned int);
    std::string teamQueuesInfo() const;
};

#endif