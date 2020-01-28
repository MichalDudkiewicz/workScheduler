#ifndef finalScheduleClass
#define finalScheduleClass

#include <memory>
#include <string>
#include "teamQueues.h"

class Team;
typedef std::vector<TeamQueues> teamsQueues;
typedef std::vector<employeePtr> employees;
typedef std::vector<employees> employeesOnPosition;
typedef std::vector<employeesOnPosition> teamsOnDay;
typedef std::shared_ptr<Team> teamPtr;
typedef std::vector<teamPtr> teams;

class FinalSchedule{
private:
    teamsQueues allQueues{};
    Calendar<teamsOnDay> schedule{};
public:
    FinalSchedule(const teams&, const employees&);
    void makeSchedule();
    void clear();
    const Calendar<teamsOnDay>& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif