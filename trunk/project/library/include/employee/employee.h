#ifndef employeeClass
#define employeeClass

#include "other/typeDefinitions.h"
class Factor;
typedef std::unique_ptr<Factor> factorPtr;

class Employee {
private:
    std::string name;
    unsigned int id;
    unsigned int hourlyWage;
    factorPtr factor;
public:
    Employee(std::string, unsigned int);
    std::string employeeInfo() const;
    unsigned int getHourlyWage() const;
    void setHourlyWage(unsigned int);
    const std::string& getName() const;
    unsigned int getId() const;
    const factorPtr& getFactor() const;
};

struct sortPointsTypeWorkHours{
    bool operator()(const employeePtr&, const employeePtr&) const;
};

struct compareID{
    bool operator()(const employeePtr&, const employeePtr&) const;
};


#endif