#ifndef employeeManagerClass
#define employeeManagerClass

#include <memory>
#include <string>

class Employee;
typedef std::shared_ptr<Employee> employeePtr;

class EmployeeManager
{
public:
    static void addEmployee(unsigned int, const std::string&);
    static void removeEmployee(unsigned int);
    std::string repositoryInfo() const;
    const employeePtr& getEmployeeByID(unsigned int) const;
    std::string getStatisticsByID(unsigned int) const;
};

#endif