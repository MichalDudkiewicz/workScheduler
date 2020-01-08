#ifndef jumperEmployeeClass
#define jumperEmployeeClass

#include "employeeType.h"

class JumperEmployee : public EmployeeType
{
public:
    unsigned int getPriority() const override;
    std::string getType() const override;
};

#endif