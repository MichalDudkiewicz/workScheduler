#ifndef teamClass
#define teamClass

#include <string>
#include "other/typeDefinitions.h"

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