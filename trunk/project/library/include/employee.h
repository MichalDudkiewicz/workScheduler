#ifndef employeeClass
#define employeeClass

#include "employeeSchedule.h"
#include "typeDefinitions.h"
#include "relationship.h"
#include "authorisation.h"

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
    EmployeeSchedule desiredSchedule;
    EmployeeSchedule currentSchedule;
    Authorisation authorisation;
    Relationship relationship;
    friend Relationship;
public:
    Employee(std::string, unsigned int);
    std::string employeeInfo() const;
    unsigned int getWorkHours() const;
    unsigned int getShiftsQuantity() const;
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
    const positions& getPositions() const;
    bool isAvailable(const shiftPtr& shift) const;
    const Calendar<shifts>& getDesiredSchedule() const;
    const Calendar<shifts>& getCurrentSchedule() const;
    void addPosition(const positionPtr&);
    void removePosition(const positionPtr&);
    void addFriend(const employeePtr&);
    void removeFriend(const employeePtr&);
    void addEnemy(const employeePtr&);
    void removeEnemy(const employeePtr&);
    bool isFriendWith(const employeePtr&) const;
    bool isEnemyWith(const employeePtr&) const;
    const std::list<Employee*>& getMyEnemies() const;
    const std::list<Employee*>& getMyFriends() const;
    bool isNonresident() const;
    void setNonresident(bool);
    void changeType(unsigned int);
    unsigned int getPriority() const;
    void addDesiredShift(shiftPtr&);
    void addDesiredShift(unsigned int, unsigned int, unsigned int);
    void removeDesiredShift(unsigned int, unsigned int);
    void addCurrentShift(shiftPtr&);
    void addCurrentShift(unsigned int, unsigned int, unsigned int);
    void removeCurrentShift(unsigned int, unsigned int);
    bool isBusy(const shiftPtr&) const;
    bool isAuthorised(const positionPtr&, const teamPtr&);
    std::string desiredScheduleInfo() const;
    std::string currentScheduleInfo() const;
    const teams& getTeams() const;
    void addTeam(const teamPtr&);
    void removeTeam(const teamPtr&);
    const Authorisation& getAuthorisation() const;
};

struct sortPointsTypeWorkHours{
    bool operator()(const employeePtr&, const employeePtr&) const;
};

struct compareID{
    bool operator()(const employeePtr&, const employeePtr&) const;
};


#endif