#ifndef WORKSCHEDULER_AUTHORISATION_H
#define WORKSCHEDULER_AUTHORISATION_H

#include "typeDefinitions.h"

class Authorisation {
private:
    positions myPositions{};
    teams myTeams{};
    Employee *authorisationOwner;
    friend Employee;
    explicit Authorisation(Employee *employee);
    Authorisation(const Authorisation&)= default;
    Authorisation& operator=(const Authorisation&)= default;
public:
    bool isAuthorised(const positionPtr &position, const teamPtr &team);
    bool positionMatch(const positionPtr &position) const;
    const positions &getPositions() const;
    bool teamMatch(const teamPtr &team) const;
    const teams &getTeams() const;
};
#endif //WORKSCHEDULER_AUTHORISATION_H
