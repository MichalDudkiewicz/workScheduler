#ifndef teamQueuesClass
#define teamQueuesClass

#include "calendar.h"
#include "position.h"
#include <list>
#include <map>

class Team;
class Employee;
typedef std::shared_ptr<Team> teamPtr;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::list<employeePtr> employees;
typedef std::shared_ptr<Position> positionPtr;
typedef std::map<positionPtr, employees, comparePositionID> queuesToPosition;

class TeamQueues{
private:
    teamPtr team;
    Calendar<queuesToPosition> calendarOfQueues{};
public:
    TeamQueues(teamPtr,const employees&);
    const Calendar<queuesToPosition>& getTeamQueues() const;
    const teamPtr& getTeam() const;
    void queueSort(unsigned int, const positionPtr &position);
    std::string teamQueuesInfo() const;
};

#endif