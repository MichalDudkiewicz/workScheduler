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
    bool checkEnemiesInTeam(const employeePtr& employee, unsigned int day, const teamPtr& team) const;
    bool isBreakNeeded(const employeePtr& employee, const positionPtr& position, unsigned int day, const shiftPtr& shift) const;

public:
    FinalSchedule(const teams&, const employees&);
    void createSchedule();
    void clear();
    std::string scheduleInfo() const override;
};

#endif