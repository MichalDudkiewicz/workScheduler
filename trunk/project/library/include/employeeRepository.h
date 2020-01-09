#ifndef employeeRepositoryClass
#define employeeRepositoryClass

#include <vector>
#include <memory>
#include <string>

class Employee;
class Position;
class Team;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::vector<employeePtr> employees;
typedef std::shared_ptr<Position> positionPtr;
typedef std::shared_ptr<Team> teamPtr;

class EmployeeRepository
{
private:
    employees employeesRepository{};
    EmployeeRepository()=default;
public:
    static EmployeeRepository& getInstance();
    EmployeeRepository(const EmployeeRepository&)=delete;
    void operator=(const EmployeeRepository&)=delete;
    void addEmployee(const employeePtr&);
    void addEmployee(unsigned int, const std::string&);
    void removeEmployee(unsigned int);
    std::string repositoryInfo() const;
    const employees& getAll() const;
    const employeePtr& getEmployeeByID(unsigned int) const;
    employees getByPosition(const positionPtr&) const;
    std::vector<employees> getByTeam(const teamPtr&) const;
    employees getByType(unsigned int) const;
    std::string getStatisticsByID(unsigned int) const;
    employees getAllUnsatisfied() const;
};

#endif