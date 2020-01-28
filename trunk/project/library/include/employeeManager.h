#ifndef employeeManagerClass
#define employeeManagerClass

#include <fstream>
#include "manager.h"

class Employee;
typedef std::shared_ptr<Employee> employeePtr;

class EmployeeManager : public Manager<Employee, unsigned int>{
private:
    EmployeeManager()=default;
public:
    static EmployeeManager& getInstance();
    EmployeeManager(const EmployeeManager&)=delete;
    void operator=(const EmployeeManager&)=delete;
    static void add(unsigned int, const std::string&);
    void remove(const unsigned int&) override;
    std::string info() const override;
    const employeePtr& get(const unsigned int &) const override;
    std::string getStatisticsByID(unsigned int) const;
    const std::vector<employeePtr>& getAll() const override;
    friend std::ofstream& operator<<(std::ofstream& output, const EmployeeManager& manager);
    friend std::ofstream& operator<(std::ofstream& output, const EmployeeManager& manager);
};

#endif