#ifndef employeeTypeClass
#define employeeTypeClass

#include <string>

class EmployeeType{
public:
    virtual ~EmployeeType()=default;
    virtual unsigned int getPriority() const=0;
    virtual std::string getType() const=0;
};

#endif
