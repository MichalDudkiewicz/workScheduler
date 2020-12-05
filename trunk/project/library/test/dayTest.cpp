#include "boost/test/unit_test.hpp"
#include "utils/calendar.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

BOOST_AUTO_TEST_CASE(DayConctructionCase)
{
    Day day;
    std::ostringstream out;
    out << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(out.str(), "1 day:");
}

BOOST_AUTO_TEST_CASE(DayPreIncrementationCase)
{
    Day day;
    ++day;
    std::ostringstream out;
    out << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 1);
    BOOST_CHECK_EQUAL(out.str(), "2 day:");
}

BOOST_AUTO_TEST_CASE(DayPreDecrementationCase)
{
    Day day;
    ++day;
    std::ostringstream out1;
    out1 << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 1);
    BOOST_CHECK_EQUAL(out1.str(), "2 day:");
    --day;
    std::ostringstream out2;
    out2 << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(out2.str(), "1 day:");
}

BOOST_AUTO_TEST_CASE(DayAddingCase)
{
    Day day;
    day = day + 5;
    std::ostringstream out1;
    out1 << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 5);
    BOOST_CHECK_EQUAL(out1.str(), "6 day:");
}

BOOST_AUTO_TEST_CASE(DaySubstractingCase)
{
    Day day;
    day = day + 5;
    day = day - 1;
    std::ostringstream out1;
    out1 << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 4);
    BOOST_CHECK_EQUAL(out1.str(), "5 day:");
}

BOOST_AUTO_TEST_CASE(DayAddAndAssignCase)
{
    Day day;
    day += 5;
    std::ostringstream out1;
    out1 << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 5);
    BOOST_CHECK_EQUAL(out1.str(), "6 day:");
}

BOOST_AUTO_TEST_CASE(DaySubstractAndAssignCase)
{
    Day day;
    day += 5;
    day -= 1;
    std::ostringstream out1;
    out1 << day;
    BOOST_CHECK_EQUAL(day.getIndex(), 4);
    BOOST_CHECK_EQUAL(out1.str(), "5 day:");
}

BOOST_AUTO_TEST_CASE(DayNegativeCase)
{
    Day day;
    BOOST_REQUIRE_THROW(--day, DayException);
    BOOST_REQUIRE_THROW(day -= 10, DayException);
}

BOOST_AUTO_TEST_CASE(DayExceededRangeCase)
{
    Day day;
    BOOST_REQUIRE_THROW(day += 35, DayException);
    day += calendar::getNumberOfDays();
    BOOST_REQUIRE_THROW(++day, DayException);
}

BOOST_AUTO_TEST_CASE(DayDayOfWeekCase)
{
    Day day(boost::gregorian::day_clock::local_day().day());
    BOOST_CHECK_EQUAL(day.dayOfWeek(), calendar::whatDayOfWeek(boost::gregorian::day_clock::local_day().day()));
}

BOOST_AUTO_TEST_SUITE_END()