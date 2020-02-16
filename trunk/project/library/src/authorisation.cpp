#include "authorisation.h"
#include "employee.h"
#include "position.h"
#include "team.h"
#include "shift.h"

bool Authorisation::isAuthorised(const positionPtr& position, const teamPtr& team)
{
    return positionMatch(position) and teamMatch(team);
}

bool Authorisation::positionMatch(const positionPtr& position) const
{
    for (const auto &p : authorisationOwner->getPositions()) {
        if (p->positionID() == position->positionID()) {
            return true;
        }
    }
    return false;
}

bool Authorisation::teamMatch(const teamPtr& team) const
{
    for (const auto &t : authorisationOwner->getTeams()) {
        if (t->getName() == team->getName()) {
            return true;
        }
    }
    return false;
}

Authorisation::Authorisation(Employee *employee) : authorisationOwner(employee)
{}

const positions &Authorisation::getPositions() const {
    return myPositions;
}

const teams &Authorisation::getTeams() const {
    return myTeams;
}
