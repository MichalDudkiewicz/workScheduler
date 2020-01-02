#ifndef teamClass
#define teamClass

#include <string>
#include <memory>
#include <vector>

class Position;
class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::shared_ptr<Position> positionPtr;
typedef std::unique_ptr<std::vector<positionPtr>> positionsPtr;
typedef std::unique_ptr<std::vector<shiftPtr>> shiftsPtr;

class Team
{
private:
    std::string name;
    std::vector<positionPtr> positionsRequired{};
    std::vector<shiftPtr> shifts{};
    std::vector<std::string> weekDay{7};
public:
    explicit Team(std::string);
    void removeShift(unsigned int);
    void addPosition(const positionPtr&);
    void removePosition(const positionPtr&);
    std::string positionsInfo() const;
    std::string shiftsInfo() const;
    std::string teamInfo() const;
    const std::string& getName() const;
    const std::vector<positionPtr>& getPositions() const;
    const std::vector<shiftPtr>& getShifts() const;
    void setName(std::string);
    void addShift(shiftPtr&);
    const std::vector<shiftPtr>& getShiftOnDay(unsigned int) const;
};

#endif