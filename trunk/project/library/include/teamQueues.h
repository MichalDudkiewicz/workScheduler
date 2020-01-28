#ifndef teamQueuesClass
#define teamQueuesClass

#include <memory>
#include <string>
#include "calendar.h"

class Team;
class Employee;
class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::shared_ptr<Team> teamPtr;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::vector<employeePtr> employees;
typedef std::vector<employees> dayQueues;

class TeamQueues{
private:
    teamPtr team;
    Calendar<dayQueues> teamQueues{};
public:
    TeamQueues(teamPtr,const employees&);
    const Calendar<dayQueues>& getTeamQueues() const;
    const teamPtr& getTeam() const;
    void queueSort(unsigned int, unsigned int);
    std::string teamQueuesInfo() const;
};

#endif