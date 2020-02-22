#ifndef employeeManagerClass
#define employeeManagerClass

#include "manager.h"
#include "other/typeDefinitions.h"
#include <fstream>

class EmployeeManager : public Manager<Employee, unsigned int>
{
private:
  EmployeeManager() = default;

public:
  static EmployeeManager& getInstance();
  EmployeeManager(const EmployeeManager&) = delete;
  void operator=(const EmployeeManager&) = delete;
  static void add(unsigned int, const std::string&);
  void remove(const unsigned int&) override;
  std::string info() const override;
  const employeePtr& get(const unsigned int&) const override;
  std::string getStatisticsByID(unsigned int) const;
  std::list<employeePtr> getAll() const override;
  friend std::ofstream& operator<<(std::ofstream& output,
                                   const EmployeeManager& manager);
  friend std::ofstream& operator<(std::ofstream& output,
                                  const EmployeeManager& manager);
};

#endif