#ifndef WORKSCHEDULER_RULES_H
#define WORKSCHEDULER_RULES_H

#include <memory>

class ValueException : public std::logic_error {
public:
    explicit ValueException(const std::string& message);
};

class NotTypeException : public ValueException {
public:
    explicit NotTypeException(
        const std::string& message = "It's not a type of employee. ");
};

class EmployeeType;
typedef std::shared_ptr<EmployeeType> employeeTypePtr;

class Rules {
private:
    unsigned int maxShifts;
    unsigned int minShifts;
    int points;
    bool nonresident;
    employeeTypePtr employeeType;
    friend class Factor;
    Rules();

public:
    void setPoints(int);
    int getPoints() const;
    void changePoints(int);
    void setMaxShifts(unsigned int);
    void setMinShifts(unsigned int);
    unsigned int getMinShifts() const;
    unsigned int getMaxShifts() const;
    const employeeTypePtr& getType() const;
    bool isNonresident() const;
    void setNonresident(bool);
    void changeType(unsigned int);
};

#endif // WORKSCHEDULER_RULES_H
