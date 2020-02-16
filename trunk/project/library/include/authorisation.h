#ifndef WORKSCHEDULER_AUTHORISATION_H
#define WORKSCHEDULER_AUTHORISATION_H

#include "typeDefinitions.h"

class Authorisation {
private:
    positions myPositions{};
    teams myTeams{};
    friend Employee;
    explicit Authorisation()= default;
    Authorisation(const Authorisation&)= default;
    Authorisation& operator=(const Authorisation&)= default;
public:
    bool isAuthorised(const positionPtr &position, const teamPtr &team);
    bool positionMatch(const positionPtr &position) const;
    const positions &getPositions() const;
    bool teamMatch(const teamPtr &team) const;
    const teams &getTeams() const;
    void addPosition(const positionPtr&);
    void removePosition(const positionPtr&);
    void addTeam(const teamPtr&);
    void removeTeam(const teamPtr&);
};
#endif //WORKSCHEDULER_AUTHORISATION_H
