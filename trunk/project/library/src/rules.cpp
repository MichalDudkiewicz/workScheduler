#include "rules.h"
#include "employeeType.h"
#include "jumperEmployee.h"
#include "normalEmployee.h"
#include "needyEmployee.h"

static const employeeTypePtr normalEmployee = std::make_shared<NormalEmployee>();
static const employeeTypePtr jumperEmployee = std::make_shared<JumperEmployee>();
static const employeeTypePtr needyEmployee = std::make_shared<NeedyEmployee>();


ValueException::ValueException(const std::string &message)
        : logic_error(message) {}

NotTypeException::NotTypeException(const std::string &message)
        : ValueException(message) {}


Rules::Rules() : maxShifts(100), minShifts(0), points(0), nonresident(false), employeeType(normalEmployee)
{}

const employeeTypePtr &Rules::getType() const {
    return employeeType;
}

bool Rules::isNonresident() const {
    return nonresident;
}

void Rules::setNonresident(bool r) {
    nonresident = r;
}

void Rules::changeType(unsigned int typeNumber) {
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

void Rules::setPoints(int p) {
    points = p;
}

void Rules::changePoints(int p) {
    points += p;
}

void Rules::setMaxShifts(unsigned int s) {
    maxShifts = s;
}

void Rules::setMinShifts(unsigned int s) {
    minShifts = s;
}

unsigned int Rules::getMaxShifts() const {
    return maxShifts;
}

unsigned int Rules::getMinShifts() const {
    return minShifts;
}

int Rules::getPoints() const {
    return points;
}