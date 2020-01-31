#include "team.h"
#include "position.h"
#include "calendar.h"
#include "shift.h"

Team::Team(std::string teamName) : name(std::move(teamName)) {
    shifts.reserve(7);
    for (unsigned int i = 0; i < 7; ++i) {
        shifts.emplace_back(new Shift(i + 1));
    }
}

void Team::addShift(shiftPtr &shift) {
    shifts[shift->getDay() - 1] = std::move(shift);
}

void Team::addShift(unsigned int startHour, unsigned int endHour, unsigned int day) {
    shiftPtr shift(new Shift(startHour, endHour, day));
    addShift(shift);
}

void Team::removeShift(unsigned int day) {
    shiftPtr shift(new Shift(day));
    addShift(shift);
}

void Team::addPosition(const positionPtr &position) {
    positionsRequired.push_front(position);
    positionsRequired.sort(comparePositionID());
}

void Team::removePosition(const positionPtr &position) {
    positionsRequired.remove(position);
}

std::string Team::positionsInfo() const {
    std::ostringstream out;
    out << "Positions required: ";
    for (const auto &position : positionsRequired) {
        out << position->positionInfo() << ", ";
    }
    return out.str();
}

std::string Team::shiftsInfo() const {
    std::ostringstream out;
    out << "Team shifts: " << std::endl;
    unsigned int weekDay = 0;
    for (const auto &shift : shifts) {
        out << calendar::getWeekDay(weekDay) << ": " << shift->shiftInfo() << std::endl;
        weekDay++;
    }
    return out.str();
}

std::string Team::teamInfo() const {
    std::ostringstream out;
    out << "Team " << name << std::endl << positionsInfo() << std::endl << shiftsInfo() << std::endl;
    return out.str();
}

const std::string &Team::getName() const {
    return name;
}

const positions &Team::getPositions() const {
    return positionsRequired;
}

const std::vector<shiftPtr> &Team::getShifts() const {
    return shifts;
}

void Team::setName(std::string n) {
    name = std::move(n);
}
