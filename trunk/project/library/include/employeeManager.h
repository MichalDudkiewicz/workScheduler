#ifndef employeeManagerClass
#define employeeManagerClass

#include <memory>
#include <string>
#include <vector>

class Employee;
typedef std::shared_ptr<Employee> employeePtr;

class EmployeeManager{
private:
    EmployeeManager()=default;
public:
    static EmployeeManager& getInstance();
    EmployeeManager(const EmployeeManager&)=delete;
    void operator=(const EmployeeManager&)=delete;
    static void addEmployee(unsigned int, const std::string&);
    static void removeEmployee(unsigned int);
    std::string repositoryInfo() const;
    const employeePtr& getEmployeeByID(unsigned int) const;
    std::string getStatisticsByID(unsigned int) const;
    const std::vector<employeePtr>& getAll() const;
};

#endif