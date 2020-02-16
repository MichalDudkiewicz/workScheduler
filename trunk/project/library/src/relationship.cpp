#include "relationship.h"
#include "employee.h"
#include "shift.h"

void Relationship::addFriend(Employee *employee) {
    friends.push_front(employee);
    if(!employee->relationship.isFriendWith(relationshipOwner))
        employee->relationship.addFriend(relationshipOwner);
    removeEnemy(employee);
}

void Relationship::removeFriend(Employee *employee) {
    friends.remove(employee);
    if (employee->relationship.isFriendWith(relationshipOwner)) {
        employee->relationship.removeFriend(relationshipOwner);
    }
}

void Relationship::addEnemy(Employee *employee) {
    enemies.push_front(employee);
    if(!employee->relationship.isEnemyWith(relationshipOwner))
        employee->relationship.enemies.push_front(relationshipOwner);
    removeFriend(employee);
}

void Relationship::removeEnemy(Employee *employee) {
    enemies.remove(employee);
    if (employee->relationship.isEnemyWith(relationshipOwner)) {
        employee->relationship.removeEnemy(relationshipOwner);
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
