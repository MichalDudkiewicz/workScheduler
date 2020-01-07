#include "team.h"
#include <sstream>
#include "position.h"
#include "shift.h"
#include <algorithm>
#include "schedule.h"

Team::Team(std::string teamName) : name(std::move(teamName))
{
    for(unsigned int i=0; i<7; ++i)
    {
        shifts.emplace_back(new Shift(i+1));
    }
}

void Team::addShift(shiftPtr &shift)
{
    shifts.erase(shifts.begin()+shift->getDay()-1);
    shifts.insert(shifts.begin()+shift->getDay()-1,std::move(shift));
}

void Team::addShift(unsigned int startHour, unsigned int endHour, unsigned int day)
{
    shiftPtr shift(new Shift(startHour, endHour, day));
    shifts.erase(shifts.begin()+shift->getDay()-1);
    shifts.insert(shifts.begin()+shift->getDay()-1,std::move(shift));
}

void Team::removeShift(unsigned int day)
{
    shifts.erase(shifts.begin()+day-1);
    shifts.emplace(shifts.begin()+day-1,new Shift(day));
}

void Team::addPosition(const positionPtr &position)
{
    positionsRequired.push_back(position);
    std::sort(positionsRequired.begin(),positionsRequired.end(),comparePositionID());
}

void Team::removePosition(const positionPtr &position)
{
    unsigned int i= 0;
    for(auto &p : positionsRequired)
    {
        if(p==position)
        {
            positionsRequired.erase(positionsRequired.begin()+i);
        }
        ++i;
    }
}

std::string Team::positionsInfo() const
{
    std::ostringstream out;
    out << "Positions required: ";
    for(const auto &position : positionsRequired)
    {
        out << position->positionInfo() << ", ";
    }
    return out.str();
}

std::string Team::shiftsInfo() const
{
    std::ostringstream out;
    out << "Team shifts: " << std::endl;
    unsigned  int it = 0;
    for(const auto &shift : shifts)
    {
        out << Schedule::getWeekDay(it) << ": " << shift -> shiftInfo() << std::endl;
        it++;
    }
    return out.str();
}

std::string Team::teamInfo() const
{
    std::ostringstream out;
    out << "Team " << name << std::endl << positionsInfo() << std::endl << shiftsInfo() << std::endl;
    return out.str();
}

const std::string& Team::getName() const
{
    return name;
}

const std::vector<positionPtr>& Team::getPositions() const
{
    return positionsRequired;
}

const std::vector<shiftPtr>& Team::getShifts() const
{
    return shifts;
}

void Team::setName(std::string n)
{
    name = std::move(n);
}
