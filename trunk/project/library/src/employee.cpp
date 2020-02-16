#include "employee.h"
#include "shift.h"
#include "position.h"
#include <algorithm>
#include <sstream>
#include "employeeType.h"
#include "factor.h"


Employee::Employee(std::string name, unsigned int id) : name(std::move(name)), id(id),
                                                        hourlyWage(0), factor(new Factor(this)) {}

std::string Employee::employeeInfo() const {
    std::ostringstream out;
    out << "ID: " << id << std::endl;
    out << "name: " << name << std::endl;
    out << "type: " << factor->rules.getType()->getType() << std::endl;
    out << "points: " << factor->rules.getPoints() << std::endl;
    out << "hours worked: " << factor->availability.getWorkHours() << std::endl;
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

const factorPtr &Employee::getFactor() const {
    return factor;
}

bool compareID::operator()(const employeePtr &e1, const employeePtr &e2) const {
    return e1->getId() < e2->getId();
}

bool sortPointsTypeWorkHours::operator()(const employeePtr &e1, const employeePtr &e2) const {
    if (e1->getFactor()->getRules().getPoints() > e2->getFactor()->getRules().getPoints()) {
        return true;
    } else if (e1->getFactor()->getRules().getPoints() == e2->getFactor()->getRules().getPoints()) {
        if (e1->getFactor()->getRules().getType()->getPriority() > e2->getFactor()->getRules().getType()->getPriority())
            return true;
        else if (e1->getFactor()->getRules().getType()->getPriority() == e2->getFactor()->getRules().getType()->getPriority()) {
            return e1->getFactor()->getAvailability().getWorkHours() < e2->getFactor()->getAvailability().getWorkHours();
        } else {
            return false;
        }
    }
    return false;
}
