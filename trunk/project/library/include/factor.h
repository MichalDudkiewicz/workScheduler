#ifndef WORKSCHEDULER_FACTOR_H
#define WORKSCHEDULER_FACTOR_H

#include "relationship.h"
#include "authorisation.h"
#include "availability.h"
#include "rules.h"

class Employee;

class Factor {
private:
    explicit Factor(Employee *employee);
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


#endif //WORKSCHEDULER_FACTOR_H
