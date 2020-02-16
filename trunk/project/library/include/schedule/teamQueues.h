#ifndef teamQueuesClass
#define teamQueuesClass

#include "other/calendar.h"
#include "positions/position.h"
#include <map>
#include "other/typeDefinitions.h"

typedef std::map<positionPtr, employees, comparePositionID> employeesToPosition;

class TeamQueues{
private:
    teamPtr team;
    Calendar<employeesToPosition> calendarOfQueues{};
public:
    TeamQueues(teamPtr,const employees&);
    const Calendar<employeesToPosition>& getTeamQueues() const;
    const teamPtr& getTeam() const;
    void queueSort(unsigned int, const positionPtr &position);
    std::string teamQueuesInfo() const;
};

#endif