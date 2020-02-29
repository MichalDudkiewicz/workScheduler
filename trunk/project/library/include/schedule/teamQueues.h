#ifndef teamQueuesClass
#define teamQueuesClass

#include "positions/position.h"
#include "utils/calendar.h"
#include "utils/schedule.h"
#include "utils/typeDefinitions.h"
#include <map>

typedef std::map<positionPtr, employees, comparePositionID> employeesToPosition;

class TeamQueues : public Schedule<employeesToPosition> {
private:
    teamPtr team;
    employees authorisedEmployees;

public:
    TeamQueues(teamPtr, employees);
    void createQueues();
    const teamPtr& getTeam() const;
    void queueSort(unsigned int, const positionPtr& position);
    std::string scheduleInfo() const override;
};

#endif