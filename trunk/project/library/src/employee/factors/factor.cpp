#include "employee/factors/factor.h"
#include "shift/shift.h"

Authorisation&
Factor::getAuthorisation()
{
  return authorisation;
}

Availability&
Factor::getAvailability()
{
  return availability;
}

Relationship&
Factor::getRelationship()
{
  return relationship;
}

Rules&
Factor::getRules()
{
  return rules;
}

Factor::Factor(Employee* employee)
  : availability()
  , authorisation()
  , relationship(employee)
  , rules()
{}
