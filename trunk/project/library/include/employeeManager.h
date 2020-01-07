#ifndef employeeManagerClass
#define employeeManagerClass

#include <vector>
#include <memory>
#include <string>

class EmployeeRepository;
class Employee;
typedef std::shared_ptr<Employee> employeePtr;

class EmployeeManager
{
private:
    EmployeeRepository* employeeRepository;
public:
    EmployeeManager();
    void addEmployee(unsigned int, const std::string&);
    void removeEmployee(unsigned int);
    std::string repositoryInfo() const;
    const employeePtr& getEmployeeByID(unsigned int) const;
    std::string getStatisticsByID(unsigned int) const;
};

#endif