#ifndef employeeScheduleClass
#define employeeScheduleClass

#include <vector>
#include <memory>

class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::vector<shiftPtr> shifts;
typedef std::vector<shifts> schedule;

class EmployeeSchedule
{
private:
    schedule shiftsInSchedule{};
public:
    EmployeeSchedule();
    void addShift(shiftPtr&);
    void removeShift(unsigned int,unsigned int);
    const schedule& getSchedule() const;
};

#endif
