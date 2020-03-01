#ifndef shiftClass
#define shiftClass

#include "utils/typeDefinitions.h"
#include <string>

class Shift {
private:
    unsigned int startHour;
    unsigned int endHour;
    unsigned int day;
    bool nightShift;

public:
    Shift(unsigned int, unsigned int, unsigned int);
    Shift(const Shift& shift) = default;
    explicit Shift(unsigned int);
    unsigned int getLength() const;
    std::string shiftInfo() const;
    unsigned int getStartHour() const;
    unsigned int getEndHour() const;
    void setStartHour(unsigned int);
    void setEndHour(unsigned int);
    bool operator>=(const Shift&) const;
    bool isNightShift() const;
    Shift operator+(const Shift&) const;
    Shift operator+(unsigned int hours);
    unsigned int getDay() const;
    bool operator==(const Shift& shift) const;
    void setDay(unsigned int);
    bool isDayOff() const;
};

struct compareShiftStartHour {
    bool operator()(const shiftPtr&, const shiftPtr&) const;
};

#endif