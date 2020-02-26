#ifndef finalScheduleClass
#define finalScheduleClass

#include "other/typeDefinitions.h"
#include "teamQueues.h"
#include <map>

typedef std::vector<TeamQueues> allTeamsQueues;
typedef std::map<teamPtr, employeesToPosition> employeesToTeam;

class FinalSchedule {
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