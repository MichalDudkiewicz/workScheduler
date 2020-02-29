#ifndef finalScheduleClass
#define finalScheduleClass

#include "teamQueues.h"
#include "utils/schedule.h"
#include "utils/typeDefinitions.h"
#include <map>

typedef std::vector<TeamQueues> allTeamsQueues;
typedef std::map<teamPtr, employeesToPosition> employeesToTeam;

class FinalSchedule : public Schedule<employeesToTeam> {
private:
    allTeamsQueues allQueues{};

public:
    FinalSchedule(const teams&, const employees&);
    void createSchedule();
    void clear();
    std::string scheduleInfo() const override;
};

#endif