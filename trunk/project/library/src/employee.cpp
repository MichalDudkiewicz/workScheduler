#include "employee.h"
#include "shift.h"
#include "employeeSchedule.h"
#include "jumperEmployee.h"
#include "normalEmployee.h"
#include "needyEmployee.h"
#include "position.h"
#include <algorithm>
#include <sstream>
#include "authorisation.h"

ValueException::ValueException(const std::string &message)
        : logic_error(message) {}

NotTypeException::NotTypeException(const std::string &message)
        : ValueException(message) {}

static const employeeTypePtr normalEmployee = std::make_shared<NormalEmployee>();
static const employeeTypePtr jumperEmployee = std::make_shared<JumperEmployee>();
static const employeeTypePtr needyEmployee = std::make_shared<NeedyEmployee>();

Employee::Employee(std::string name, unsigned int id) : name(std::move(name)), nonresident(false), points(0), id(id),
                                                        maxShifts(100), minShifts(0), hourlyWage(0),
                                                        employeeType(normalEmployee), desiredSchedule(),
                                                        currentSchedule() {}

std::string Employee::employeeInfo() const {
    std::ostringstream out;
    out << "ID: " << id << std::endl;
    out << "name: " << name << std::endl;
    out << "type: " << employeeType->getType() << std::endl;
    out << "points: " << points << std::endl;
    out << "hours worked: " << getWorkHours() << std::endl;
    out << "wage/hour: " << hourlyWage << std::endl;
    return out.str();
}

unsigned int Employee::getWorkHours() const {
    unsigned int workHours = 0;
    for (const auto &shifts : currentSchedule.getSchedule()) {
        for (const auto &shift : shifts) {
            workHours += shift->getLength();
        }
    }
    return workHours;
}

unsigned int Employee::getShiftsQuantity() const {
    unsigned int shiftsQuantity = 0;
    for (const auto &shifts : currentSchedule.getSchedule()) {
        shiftsQuantity += shifts.size();
    }
    return shiftsQuantity;
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

const Calendar<shifts> &Employee::getDesiredSchedule() const {
    return desiredSchedule.getSchedule();
}

const Calendar<shifts> &Employee::getCurrentSchedule() const {
    return currentSchedule.getSchedule();
}

unsigned int Employee::getId() const {
    return id;
}

const employeeTypePtr &Employee::getType() const {
    return employeeType;
}

const positions &Employee::getPositions() const {
    return myPositions;
}


bool Employee::isAvailable(const shiftPtr &shift) const {
    if (shift->isDayOff()) {
        return false;
    }
    if (!shift->isNightShift()) {
        for (const auto &s : desiredSchedule.getSchedule()[shift->getDay() - 1]) {
            if ((*s) >= (*shift)) {
                return true;
            }
        }
        return false;
    }
    if (shift->getDay() != desiredSchedule.getSchedule().size()) {
        if (!desiredSchedule.getSchedule()[shift->getDay() - 1].empty() and
            !desiredSchedule.getSchedule()[shift->getDay()].empty()) {
            return ((*desiredSchedule.getSchedule()[shift->getDay() - 1].back()) +
                    (*desiredSchedule.getSchedule()[shift->getDay()][0])) >= (*shift);
        }
    }
    return false;
}

void Employee::addPosition(const positionPtr &position) {
    myPositions.push_front(position);
    myPositions.sort(comparePositionID());
}

void Employee::removePosition(const positionPtr &position) {
    myPositions.remove(position);
}

void Employee::addFriend(const employeePtr &employee) {
    friends.push_front(employee);
    employee->friends.push_front(shared_from_this());
    removeEnemy(employee);
}

void Employee::removeFriend(const employeePtr &employee) {
    friends.remove(employee);
    if (employee->isFriendWith(shared_from_this())) {
        employee->removeFriend(shared_from_this());
    }
}

void Employee::addEnemy(const employeePtr &employee) {
    enemies.push_front(employee);
    employee->enemies.push_front(shared_from_this());
    removeFriend(employee);
}

void Employee::removeEnemy(const employeePtr &employee) {
    enemies.remove(employee);
    if (employee->isEnemyWith(shared_from_this())) {
        employee->removeEnemy(shared_from_this());
    }
}

bool Employee::isFriendWith(const employeePtr &employee) const {
    for (const auto &e : friends) {
        if (e -> getId() == employee -> getId()) {
            return true;
        }
    }
    return false;
}

bool Employee::isEnemyWith(const employeePtr &employee) const {
    for (const auto &e : enemies) {
        if (e -> getId() == employee -> getId()) {
            return true;
        }
    }
    return false;
}

const employees &Employee::getMyFriends() const {
    return friends;
}

const employees &Employee::getMyEnemies() const {
    return enemies;
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

void Employee::addDesiredShift(shiftPtr &shift) {
    desiredSchedule.addShift(shift);
}

void Employee::addDesiredShift(unsigned int startHour, unsigned int endHour, unsigned int day) {
    shiftPtr shift(new Shift(startHour, endHour, day));
    desiredSchedule.addShift(shift);
}

void Employee::removeDesiredShift(unsigned int day, unsigned int shiftNumber) {
    desiredSchedule.removeShift(day, shiftNumber);
}

void Employee::addCurrentShift(shiftPtr &shift) {
    currentSchedule.addShift(shift);
}

void Employee::addCurrentShift(unsigned int startHour, unsigned int endHour, unsigned int day) {
    shiftPtr shift(new Shift(startHour, endHour, day));
    currentSchedule.addShift(shift);
}

void Employee::removeCurrentShift(unsigned int day, unsigned int shiftNumber) {
    currentSchedule.removeShift(day, shiftNumber);
}

bool Employee::isBusy(const shiftPtr &shift) const {
    for (const auto &s : currentSchedule.getSchedule()[shift->getDay() - 1]) {
        if ((*s) == (*shift)) {
            return true;
        }
    }
    return false;
}

bool Employee::isAuthorised(const positionPtr &position, const teamPtr &team) {
    return authorisation::isAuthorised(shared_from_this(), position, team);
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
            return e1->getWorkHours() < e2->getWorkHours();
        } else {
            return false;
        }
    }
    return false;
}

std::string Employee::desiredScheduleInfo() const {
    return desiredSchedule.scheduleInfo();
}

std::string Employee::currentScheduleInfo() const {
    return currentSchedule.scheduleInfo();
}

const teams &Employee::getTeams() const{
    return myTeams;
}

void Employee::addTeam(const teamPtr &team) {
    myTeams.push_front(team);
}

void Employee::removeTeam(const teamPtr &team) {
    myTeams.remove(team);
}
