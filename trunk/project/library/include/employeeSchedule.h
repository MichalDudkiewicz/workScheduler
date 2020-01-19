#ifndef employeeScheduleClass
#define employeeScheduleClass

#include <vector>
#include <memory>
#include <string>

class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::vector<shiftPtr> shifts;
typedef std::vector<shifts> schedule;

class EmployeeSchedule{
private:
    schedule shiftsInSchedule{};
public:
    EmployeeSchedule();
    void addShift(shiftPtr&);
    void removeShift(unsigned int,unsigned int);
    const schedule& getSchedule() const;
    std::string scheduleInfo() const;
};

#endif
