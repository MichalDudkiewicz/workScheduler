#include <iostream>
#include "schedule.h"
#include "employee.h"
#include "team.h"
#include "medic.h"
#include "teamQueues.h"
#include <memory>
using namespace std;

int main()
{
    cout << Schedule::getCurrentDate();
    std::shared_ptr<Team> team = std::make_shared<Team>("S1");
    std::vector<employeePtr> employees;
    TeamQueues queue(team,employees);
    return 0;
}
