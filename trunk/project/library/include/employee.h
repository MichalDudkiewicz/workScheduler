#ifndef employeeClass
#define employeeClass

#include <memory>
#include <string>
#include <vector>
#include "employeeSchedule.h"

class ValueException: public std::logic_error{
public:
    explicit ValueException(const std::string &message);
};

class NotTypeException: public ValueException{
public:
    explicit NotTypeException(const std::string &message = "It's not a type of employee. ");
};

class EmployeeType;
class Position;
class Employee;
class  Shift;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::vector<employeePtr> employees;
typedef std::shared_ptr<EmployeeType> employeeTypePtr;
typedef std::shared_ptr<Position> positionPtr;
typedef std::vector<positionPtr> positions;
typedef std::unique_ptr<Shift> shiftPtr;

class Employee : public std::enable_shared_from_this<Employee>{
private:
    std::string name;
    bool nonresident;
    int points;
    unsigned int id;
    unsigned int maxShifts;
    unsigned int minShifts;
    unsigned int hourlyWage;
    employeeTypePtr employeeType;
    positions myPositions{};
    employees friends{};
    employees enemies{};
    EmployeeSchedule desiredSchedule;
    EmployeeSchedule currentSchedule;
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
    const schedule& getDesiredSchedule() const;
    const schedule& getCurrentSchedule() const;
    void addPosition(const positionPtr&);
    void removePosition(const positionPtr&);
    void addFriend(const employeePtr&);
    void removeFriend(const employeePtr&);
    void addEnemy(const employeePtr&);
    void removeEnemy(const employeePtr&);
    bool isFriendWith(const employeePtr&) const;
    bool isEnemyWith(const employeePtr&) const;
    const employees& getMyEnemies() const;
    const employees& getMyFriends() const;
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
    bool isAuthorised(const positionPtr&) const;
    std::string desiredScheduleInfo() const;
    std::string currentScheduleInfo() const;
};

struct sortPointsTypeWorkHours{
    bool operator()(const employeePtr&, const employeePtr&) const;
};

struct compareID{
    bool operator()(const employeePtr&, const employeePtr&) const;
};


#endif