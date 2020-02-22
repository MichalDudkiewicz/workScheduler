#ifndef normalEmployeeClass
#define normalEmployeeClass

#include "employeeType.h"

class NormalEmployee : public EmployeeType
{
public:
  unsigned int getPriority() const override;
  std::string getType() const override;
};

#endif