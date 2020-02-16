#include "authorisation.h"
#include "employee.h"
#include "position.h"
#include "team.h"
#include "shift.h"

namespace authorisation {
bool isAuthorised(const employeePtr &employee, const positionPtr& position, const teamPtr& team)
{
    return positionMatch(employee, position) and teamMatch(employee, team);
}

bool positionMatch(const employeePtr& employee, const positionPtr& position)
{
    for (const auto &p : employee->getPositions()) {
        if (p->positionID() == position->positionID()) {
            return true;
        }
    }
    return false;
}

bool teamMatch(const employeePtr& employee, const teamPtr& team)
{
    for (const auto &t : employee->getTeams()) {
        if (t->getName() == team->getName()) {
            return true;
        }
    }
    return false;
}
}