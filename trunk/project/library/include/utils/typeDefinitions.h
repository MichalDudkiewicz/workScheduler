#ifndef typeDefinitionsHeader
#define typeDefinitionsHeader

#include <list>
#include <memory>
#include <vector>

class Position;
class Employee;
class Shift;
class Team;
typedef std::shared_ptr<Employee> employeePtr;
typedef std::list<employeePtr> employees;
typedef std::shared_ptr<Position> positionPtr;
typedef std::list<positionPtr> positions;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::vector<shiftPtr> shifts;
typedef std::shared_ptr<Team> teamPtr;
typedef std::list<teamPtr> teams;

#endif
