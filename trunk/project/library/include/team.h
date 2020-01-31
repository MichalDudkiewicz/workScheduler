#ifndef teamClass
#define teamClass

#include <string>
#include <memory>
#include <list>
#include <vector>

class Position;
class Shift;
typedef std::unique_ptr<Shift> shiftPtr;
typedef std::shared_ptr<Position> positionPtr;
typedef std::list<positionPtr> positions;

class Team{
private:
    std::string name;
    positions positionsRequired{};
    std::vector<shiftPtr> shifts{};
public:
    explicit Team(std::string);
    void removeShift(unsigned int);
    void addPosition(const positionPtr&);
    void removePosition(const positionPtr&);
    std::string positionsInfo() const;
    std::string shiftsInfo() const;
    std::string teamInfo() const;
    const std::string& getName() const;
    const positions& getPositions() const;
    const std::vector<shiftPtr>& getShifts() const;
    void setName(std::string);
    void addShift(shiftPtr&);
    void addShift(unsigned int, unsigned int, unsigned int);
};

#endif