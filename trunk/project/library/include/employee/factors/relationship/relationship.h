#ifndef WORKSCHEDULER_RELATIONSHIP_H
#define WORKSCHEDULER_RELATIONSHIP_H

#include "other/typeDefinitions.h"

class Relationship {
private:
    std::list<Employee*> friends{};
    std::list<Employee*> enemies{};
    Employee* relationshipOwner;
    friend class Factor;
    explicit Relationship(Employee *employee);
    Relationship(const Relationship&)= default;
    Relationship& operator=(const Relationship&)= default;
public:
    void addFriend(Employee *employee);
    void removeFriend(Employee *employee);
    void addEnemy(Employee *employee);
    void removeEnemy(Employee *employee);
    void addFriend(const employeePtr&);
    void removeFriend(const employeePtr&);
    void addEnemy(const employeePtr&);
    void removeEnemy(const employeePtr&);
    bool isFriendWith(Employee *employee) const;
    bool isEnemyWith(Employee *employee) const;
    bool isFriendWith(const employeePtr&) const;
    bool isEnemyWith(const employeePtr&) const;
    const std::list<Employee*>& getMyEnemies() const;
    const std::list<Employee*>& getMyFriends() const;
};


#endif //WORKSCHEDULER_RELATIONSHIP_H
