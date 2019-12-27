#ifndef WORKSCHEDULER_EMPLOYEETYPE_H
#define WORKSCHEDULER_EMPLOYEETYPE_H

#include <string>

class EmployeeType
{
public:
    virtual ~EmployeeType()=default;
    virtual unsigned int getPriority() const=0;
    virtual std::string getType() const=0;
};

#endif //WORKSCHEDULER_EMPLOYEETYPE_H
