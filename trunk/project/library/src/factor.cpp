#include "factor.h"
#include "shift.h"

Authorisation &Factor::getAuthorisation() {
    return authorisation;
}

Availability &Factor::getAvailability() {
    return availability;
}

Relationship &Factor::getRelationship() {
    return relationship;
}

Rules &Factor::getRules() {
    return rules;
}

Factor::Factor(Employee *employee) : availability(), authorisation(), relationship(employee), rules(){}
