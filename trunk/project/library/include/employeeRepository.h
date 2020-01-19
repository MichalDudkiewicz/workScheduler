#ifndef employeeRepositoryClass
#define employeeRepositoryClass

#include <vector>
#include <memory>
#include <string>
#include "repository.h"

class EmployeeNotFound: public std::logic_error{
public:
    explicit EmployeeNotFound(const std::string &message = "Employee not found.");
};
class EmployeeWithThisIdExist: public std::logic_error{
public:
    explicit EmployeeWithThisIdExist(const std::string &message = "Employee with this id exists. ");
};

class Employee;
class Position;
class Team;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::vector<employeePtr> employees;
typedef std::shared_ptr<Position> positionPtr;
typedef std::shared_ptr<Team> teamPtr;

class EmployeeRepository : public Repository<Employee,unsigned int>{
private:
    employees employeesRepository{};
    EmployeeRepository()=default;
    void checkIfIdExist(const employeePtr &employee);
public:
    static EmployeeRepository& getInstance();
    EmployeeRepository(const EmployeeRepository&)=delete;
    void operator=(const EmployeeRepository&)=delete;
    void add(const employeePtr&) override;
    void add(unsigned int, const std::string&);
    void remove(const unsigned int&) override;
    std::string info() const override;
    const employees& getAll() const override;
    const employeePtr& get(const unsigned int&) const override;
    employees getByPosition(const positionPtr&) const;
    std::vector<employees> getByTeam(const teamPtr&) const;
    employees getByType(unsigned int) const;
    std::string getStatisticsByID(unsigned int) const;
    employees getAllUnsatisfied() const;
};

#endif