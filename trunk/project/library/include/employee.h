#ifndef employeeClass
#define employeeClass

#include "typeDefinitions.h"
#include "relationship.h"
#include "authorisation.h"
#include "availability.h"
#include "rules.h"


class Employee {
private:
    std::string name;
    unsigned int id;
    unsigned int hourlyWage;
    Availability availability;
    Authorisation authorisation;
    Relationship relationship;
    friend Relationship;
    Rules rules;
public:
    Employee(std::string, unsigned int);
    std::string employeeInfo() const;
    unsigned int getHourlyWage() const;
    void setHourlyWage(unsigned int);
    const std::string& getName() const;
    unsigned int getId() const;
    Authorisation& getAuthorisation();
    Availability& getAvailability();
    Relationship& getRelationship();
    Rules& getRules();
};

struct sortPointsTypeWorkHours{
    bool operator()(const employeePtr&, const employeePtr&) const;
};

struct compareID{
    bool operator()(const employeePtr&, const employeePtr&) const;
};


#endif