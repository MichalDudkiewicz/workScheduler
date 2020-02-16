#ifndef employeeClass
#define employeeClass

#include "typeDefinitions.h"
#include "relationship.h"
#include "authorisation.h"
#include "availability.h"

class ValueException: public std::logic_error{
public:
    explicit ValueException(const std::string &message);
};

class NotTypeException: public ValueException{
public:
    explicit NotTypeException(const std::string &message = "It's not a type of employee. ");
};

class EmployeeType;
typedef std::shared_ptr<EmployeeType> employeeTypePtr;

class Employee {
private:
    std::string name;
    bool nonresident;
    int points;
    unsigned int id;
    unsigned int maxShifts;
    unsigned int minShifts;
    unsigned int hourlyWage;
    employeeTypePtr employeeType;
    Availability availability;
    Authorisation authorisation;
    Relationship relationship;
    friend Relationship;
public:
    Employee(std::string, unsigned int);
    std::string employeeInfo() const;
    unsigned int getMaxShifts() const;
    unsigned int getMinShifts() const;
    int getPoints() const;
    unsigned int getHourlyWage() const;
    void setPoints(int);
    void changePoints(int);
    void setMaxShifts(unsigned int);
    void setMinShifts(unsigned int);
    void setHourlyWage(unsigned int);
    const std::string& getName() const;
    unsigned int getId() const;
    const employeeTypePtr& getType() const;
    bool isNonresident() const;
    void setNonresident(bool);
    void changeType(unsigned int);
    unsigned int getPriority() const;
    Authorisation& getAuthorisation();
    Availability& getAvailability();
    Relationship& getRelationship();
};

struct sortPointsTypeWorkHours{
    bool operator()(const employeePtr&, const employeePtr&) const;
};

struct compareID{
    bool operator()(const employeePtr&, const employeePtr&) const;
};


#endif