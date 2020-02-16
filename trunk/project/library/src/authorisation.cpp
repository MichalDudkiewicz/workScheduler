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
    for (const auto &p : getPositions()) {
        if (p->positionID() == position->positionID()) {
            return true;
        }
    }
    return false;
}

bool Authorisation::teamMatch(const teamPtr& team) const
{
    for (const auto &t : getTeams()) {
        if (t->getName() == team->getName()) {
            return true;
        }
    }
    return false;
}

const positions &Authorisation::getPositions() const {
    return myPositions;
}

const teams &Authorisation::getTeams() const {
    return myTeams;
}


void Authorisation::addTeam(const teamPtr &team) {
    myTeams.push_front(team);
}

void Authorisation::removeTeam(const teamPtr &team) {
    myTeams.remove(team);
}

void Authorisation::addPosition(const positionPtr &position) {
    myPositions.push_front(position);
    myPositions.sort(comparePositionID());
}

void Authorisation::removePosition(const positionPtr &position) {
    myPositions.remove(position);
}