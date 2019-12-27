#ifndef shiftClass
#define shiftClass

#include <string>
#include <memory>

class Shift
{
private:
    unsigned int startHour;
    unsigned int endHour;
    unsigned int day;
public:
    Shift(unsigned int, unsigned int, unsigned int);
    Shift(unsigned int);
    unsigned int getLength() const;
    std::string shiftInfo() const;
    unsigned int getStartHour() const;
    unsigned int getEndHour() const;
    void setStartHour(unsigned int);
    void setEndHour(unsigned int);
    bool operator>=(const Shift&) const;
    bool isNightShift() const;
    Shift operator+(const Shift&) const;
    unsigned int getDay() const;
    bool operator==(const Shift &shift) const;
    void setDay(unsigned int);
    bool isDayOff() const;
};

typedef std::unique_ptr<Shift> shiftPtr;

struct compareShiftStartHour
{
    bool operator()(const shiftPtr&, const shiftPtr&) const;
};

#endif