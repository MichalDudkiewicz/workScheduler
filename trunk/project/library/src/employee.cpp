#include "employee.h"
#include "shift.h"
#include "position.h"
#include <algorithm>
#include <sstream>
#include "employeeType.h"


Employee::Employee(std::string name, unsigned int id) : name(std::move(name)), id(id),
                                                        hourlyWage(0), availability(), authorisation(), relationship(this), rules() {}

std::string Employee::employeeInfo() const {
    std::ostringstream out;
    out << "ID: " << id << std::endl;
    out << "name: " << name << std::endl;
    out << "type: " << rules.employeeType->getType() << std::endl;
    out << "points: " << rules.points << std::endl;
    out << "hours worked: " << availability.getWorkHours() << std::endl;
    out << "wage/hour: " << hourlyWage << std::endl;
    return out.str();
}

unsigned int Employee::getHourlyWage() const {
    return hourlyWage;
}

void Employee::setHourlyWage(unsigned int w) {
    hourlyWage = w;
}

const std::string &Employee::getName() const {
    return name;
}

unsigned int Employee::getId() const {
    return id;
}

bool compareID::operator()(const employeePtr &e1, const employeePtr &e2) const {
    return e1->getId() < e2->getId();
}

bool sortPointsTypeWorkHours::operator()(const employeePtr &e1, const employeePtr &e2) const {
    if (e1->getRules().getPoints() > e2->getRules().getPoints()) {
        return true;
    } else if (e1->getRules().getPoints() == e2->getRules().getPoints()) {
        if (e1->getRules().getType()->getPriority() > e2->getRules().getType()->getPriority())
            return true;
        else if (e1->getRules().getType()->getPriority() == e2->getRules().getType()->getPriority()) {
            return e1->getAvailability().getWorkHours() < e2->getAvailability().getWorkHours();
        } else {
            return false;
        }
    }
    return false;
}

Authorisation &Employee::getAuthorisation() {
    return authorisation;
}

Availability &Employee::getAvailability() {
    return availability;
}

Relationship &Employee::getRelationship() {
    return relationship;
}

Rules &Employee::getRules() {
    return rules;
}
