#ifndef finalScheduleClass
#define finalScheduleClass

#include "teamQueues.h"

class Team;
typedef std::vector<TeamQueues> allTeamsQueues;
typedef std::list<employeePtr> employees;
typedef std::vector<employees> employeesOnPositionQueues;
typedef std::vector<employeesOnPositionQueues> teamOnDayQueues;
typedef std::shared_ptr<Team> teamPtr;
typedef std::list<teamPtr> teams;

class FinalSchedule{
private:
    allTeamsQueues allQueues{};
    Calendar<teamOnDayQueues> schedule{};
public:
    FinalSchedule(const teams&, const employees&);
    void makeSchedule();
    void clear();
    const Calendar<teamOnDayQueues>& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif