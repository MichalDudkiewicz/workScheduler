#ifndef needyEmployeeClass
#define needyEmployeeClass

#include "employeeType.h"

class NeedyEmployee : public EmployeeType
{
public:
  unsigned int getPriority() const override;
  std::string getType() const override;
};

#endif