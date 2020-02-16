#include "employee.h"
#include "shift.h"
#include "jumperEmployee.h"
#include "normalEmployee.h"
#include "needyEmployee.h"
#include "position.h"
#include <algorithm>
#include <sstream>

ValueException::ValueException(const std::string &message)
        : logic_error(message) {}

NotTypeException::NotTypeException(const std::string &message)
        : ValueException(message) {}

static const employeeTypePtr normalEmployee = std::make_shared<NormalEmployee>();
static const employeeTypePtr jumperEmployee = std::make_shared<JumperEmployee>();
static const employeeTypePtr needyEmployee = std::make_shared<NeedyEmployee>();

Employee::Employee(std::string name, unsigned int id) : name(std::move(name)), nonresident(false), points(0), id(id),
                                                        maxShifts(100), minShifts(0), hourlyWage(0),
                                                        employeeType(normalEmployee), employeeSchedules(), authorisation(), relationship(this) {}

std::string Employee::employeeInfo() const {
    std::ostringstream out;
    out << "ID: " << id << std::endl;
    out << "name: " << name << std::endl;
    out << "type: " << employeeType->getType() << std::endl;
    out << "points: " << points << std::endl;
    out << "hours worked: " << employeeSchedules.getWorkHours() << std::endl;
    out << "wage/hour: " << hourlyWage << std::endl;
    return out.str();
}


unsigned int Employee::getMaxShifts() const {
    return maxShifts;
}

unsigned int Employee::getMinShifts() const {
    return minShifts;
}

int Employee::getPoints() const {
    return points;
}

unsigned int Employee::getHourlyWage() const {
    return hourlyWage;
}

void Employee::setPoints(int p) {
    points = p;
}

void Employee::changePoints(int p) {
    points += p;
}

void Employee::setMaxShifts(unsigned int s) {
    maxShifts = s;
}

void Employee::setMinShifts(unsigned int s) {
    minShifts = s;
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

const employeeTypePtr &Employee::getType() const {
    return employeeType;
}

void Employee::addFriend(const employeePtr &employee) {
    relationship.addFriend(employee.get());
}

void Employee::removeFriend(const employeePtr &employee) {
    relationship.removeFriend(employee.get());
}

void Employee::addEnemy(const employeePtr &employee) {
    relationship.addEnemy(employee.get());
}

void Employee::removeEnemy(const employeePtr &employee) {
    relationship.removeEnemy(employee.get());
}

bool Employee::isFriendWith(const employeePtr &employee) const {
    return relationship.isFriendWith(employee.get());
}

bool Employee::isEnemyWith(const employeePtr &employee) const {
    return relationship.isEnemyWith(employee.get());
}

bool Employee::isNonresident() const {
    return nonresident;
}

void Employee::setNonresident(bool r) {
    nonresident = r;
}

void Employee::changeType(unsigned int typeNumber) {
    if (typeNumber == 1) {
        employeeType = normalEmployee;
    } else if (typeNumber == 0) {
        employeeType = jumperEmployee;
    } else if (typeNumber == 2) {
        employeeType = needyEmployee;
    } else {
        throw NotTypeException();
    }
}

unsigned int Employee::getPriority() const {
    return employeeType->getPriority();
}

bool compareID::operator()(const employeePtr &e1, const employeePtr &e2) const {
    return e1->getId() < e2->getId();
}

bool sortPointsTypeWorkHours::operator()(const employeePtr &e1, const employeePtr &e2) const {
    if (e1->getPoints() > e2->getPoints()) {
        return true;
    } else if (e1->getPoints() == e2->getPoints()) {
        if (e1->getPriority() > e2->getPriority())
            return true;
        else if (e1->getPriority() == e2->getPriority()) {
            return e1->getEmployeeSchedules().getWorkHours() < e2->getEmployeeSchedules().getWorkHours();
        } else {
            return false;
        }
    }
    return false;
}

const std::list<Employee*> &Employee::getMyEnemies() const {
    return relationship.getMyEnemies();
}

const std::list<Employee*> &Employee::getMyFriends() const {
    return relationship.getMyFriends();
}

Authorisation &Employee::getAuthorisation() {
    return authorisation;
}

EmployeeSchedules &Employee::getEmployeeSchedules() {
    return employeeSchedules;
}
