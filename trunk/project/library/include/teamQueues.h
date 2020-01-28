#ifndef teamQueuesClass
#define teamQueuesClass

#include "calendar.h"

class Team;
class Employee;
typedef std::shared_ptr<Team> teamPtr;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::vector<employeePtr> employees;
typedef std::vector<employees> queuesToPosition;

class TeamQueues{
private:
    teamPtr team;
    Calendar<queuesToPosition> calendarOfQueues{};
public:
    TeamQueues(teamPtr,const employees&);
    const Calendar<queuesToPosition>& getTeamQueues() const;
    const teamPtr& getTeam() const;
    void queueSort(unsigned int, unsigned int);
    std::string teamQueuesInfo() const;
};

#endif