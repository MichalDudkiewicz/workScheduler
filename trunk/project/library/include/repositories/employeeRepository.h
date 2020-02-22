#ifndef employeeRepositoryClass
#define employeeRepositoryClass

#include "other/typeDefinitions.h"
#include "repositories/repository.h"
#include <string>
#include <unordered_map>

class EmployeeNotFound : public std::logic_error
{
public:
  explicit EmployeeNotFound(const std::string& message = "Employee not found.");
};
class EmployeeWithThisIdExist : public std::logic_error
{
public:
  explicit EmployeeWithThisIdExist(
    const std::string& message = "Employee with this id exists. ");
};

class EmployeeRepository : public Repository<Employee, unsigned int>
{
private:
  std::unordered_map<unsigned int, employeePtr> employeesRepository{};
  EmployeeRepository() = default;
  void checkIfIdExist(const unsigned int& id);

public:
  static EmployeeRepository& getInstance();
  EmployeeRepository(const EmployeeRepository&) = delete;
  void operator=(const EmployeeRepository&) = delete;
  void add(const employeePtr&) override;
  void add(unsigned int, const std::string&);
  void remove(const unsigned int&) override;
  std::string info() const override;
  employees getAll() const override;
  const employeePtr& get(const unsigned int&) const override;
  employees getByPosition(const positionPtr&) const;
  std::vector<employees> getByTeam(const teamPtr&) const;
  employees getByType(unsigned int) const;
  std::string getStatisticsByID(unsigned int) const;
  employees getAllUnsatisfied() const;
};

#endif