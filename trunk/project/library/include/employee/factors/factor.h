#ifndef WORKSCHEDULER_FACTOR_H
#define WORKSCHEDULER_FACTOR_H

#include "employee/factors/authorisation/authorisation.h"
#include "employee/factors/availability/availability.h"
#include "employee/factors/relationship/relationship.h"
#include "employee/factors/rules/rules.h"

class Employee;

class Factor {
private:
    explicit Factor(Employee* employee);
    friend class Employee;
    Availability availability;
    Authorisation authorisation;
    Relationship relationship;
    Rules rules;

public:
    Authorisation& getAuthorisation();
    Availability& getAvailability();
    Relationship& getRelationship();
    Rules& getRules();
};

#endif // WORKSCHEDULER_FACTOR_H
