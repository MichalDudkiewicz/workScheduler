#include "employee/factors/relationship/relationship.h"
#include "employee/employee.h"
#include "shift/shift.h"
#include "employee/factors/factor.h"

void Relationship::addFriend(Employee *employee) {
    friends.push_front(employee);
    if(!employee->getFactor()->getRelationship().isFriendWith(relationshipOwner))
        employee->getFactor()->getRelationship().addFriend(relationshipOwner);
    removeEnemy(employee);
}

void Relationship::removeFriend(Employee *employee) {
    friends.remove(employee);
    if (employee->getFactor()->getRelationship().isFriendWith(relationshipOwner)) {
        employee->getFactor()->getRelationship().removeFriend(relationshipOwner);
    }
}

void Relationship::addEnemy(Employee *employee) {
    enemies.push_front(employee);
    if(!employee->getFactor()->getRelationship().isEnemyWith(relationshipOwner))
        employee->getFactor()->getRelationship().enemies.push_front(relationshipOwner);
    removeFriend(employee);
}

void Relationship::removeEnemy(Employee *employee) {
    enemies.remove(employee);
    if (employee->getFactor()->getRelationship().isEnemyWith(relationshipOwner)) {
        employee->getFactor()->getRelationship().removeEnemy(relationshipOwner);
    }
}

bool Relationship::isFriendWith(Employee *employee) const {
    for (const auto &e : friends) {
        if (e -> getId() == employee -> getId()) {
            return true;
        }
    }
    return false;
}

bool Relationship::isEnemyWith(Employee *employee) const {
    for (const auto &e : enemies) {
        if (e -> getId() == employee -> getId()) {
            return true;
        }
    }
    return false;
}

const std::list<Employee*>& Relationship::getMyFriends() const {
    return friends;
}

const std::list<Employee*>& Relationship::getMyEnemies() const {
    return enemies;
}

Relationship::Relationship(Employee *employee) : relationshipOwner(employee)
{}

void Relationship::addFriend(const employeePtr &employee) {
    addFriend(employee.get());
}

void Relationship::removeFriend(const employeePtr &employee) {
    removeFriend(employee.get());
}

void Relationship::addEnemy(const employeePtr &employee) {
    addEnemy(employee.get());
}

void Relationship::removeEnemy(const employeePtr &employee) {
    removeEnemy(employee.get());
}

bool Relationship::isFriendWith(const employeePtr &employee) const {
    return isFriendWith(employee.get());
}

bool Relationship::isEnemyWith(const employeePtr &employee) const {
    return isEnemyWith(employee.get());
}