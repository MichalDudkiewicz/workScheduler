#ifndef shiftClass
#define shiftClass

#include <string>
#include <memory>

class ValueValidException: public std::logic_error
{
public:
    explicit ValueValidException(const std::string &message);
    virtual std::string message() const;
};

class DayOffException: public ValueValidException
{
public:
    explicit DayOffException(const std::string &message = "Day off exception.");
};

class InvalidHoursException: public ValueValidException
{
public:
    explicit InvalidHoursException(const std::string &message = "Valid hours.");
};

class Shift
{
private:
    unsigned int startHour;
    unsigned int endHour;
    unsigned int day;
    bool nightShift;
public:
    Shift(unsigned int, unsigned int, unsigned int);
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