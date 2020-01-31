#ifndef finalScheduleClass
#define finalScheduleClass

#include "teamQueues.h"
#include <map>

class Team;
typedef std::vector<TeamQueues> allTeamsQueues;
typedef std::shared_ptr<Team> teamPtr;
typedef std::map<teamPtr, employeesToPosition> employeesToTeam;
typedef std::list<teamPtr> teams;

class FinalSchedule{
private:
    allTeamsQueues allQueues{};
    Calendar<employeesToTeam> schedule{};
public:
    FinalSchedule(const teams&, const employees&);
    void makeSchedule();
    void clear();
    const Calendar<employeesToTeam>& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif