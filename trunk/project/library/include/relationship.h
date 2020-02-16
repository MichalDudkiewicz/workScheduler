#ifndef WORKSCHEDULER_RELATIONSHIP_H
#define WORKSCHEDULER_RELATIONSHIP_H

#include "typeDefinitions.h"

class Relationship {
private:
    std::list<Employee*> friends{};
    std::list<Employee*> enemies{};
    Employee* relationshipOwner;
    friend Employee;
    explicit Relationship(Employee *employee);
    Relationship(const Relationship&)= default;
    Relationship& operator=(const Relationship&)= default;
public:
    void addFriend(Employee *employee);
    void removeFriend(Employee *employee);
    void addEnemy(Employee *employee);
    void removeEnemy(Employee *employee);
    bool isFriendWith(Employee *employee) const;
    bool isEnemyWith(Employee *employee) const;
    const std::list<Employee*>& getMyEnemies() const;
    const std::list<Employee*>& getMyFriends() const;
};


#endif //WORKSCHEDULER_RELATIONSHIP_H
