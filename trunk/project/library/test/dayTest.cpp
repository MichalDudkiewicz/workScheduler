#include "boost/test/unit_test.hpp"
#include "utils/calendar.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

BOOST_AUTO_TEST_CASE(DayConctructionCase)
{
    Day day;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(day.toString(), "1");
}

BOOST_AUTO_TEST_CASE(DayPreIncrementationCase)
{
    Day day;
    ++day;
    BOOST_CHECK_EQUAL(day.getIndex(), 1);
    BOOST_CHECK_EQUAL(day.toString(), "2");
}

BOOST_AUTO_TEST_CASE(DayPreDecrementationCase)
{
    Day day;
    ++day;
    BOOST_CHECK_EQUAL(day.getIndex(), 1);
    BOOST_CHECK_EQUAL(day.toString(), "2");
    --day;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(day.toString(), "1");
    --day;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(day.toString(), "1");
}

BOOST_AUTO_TEST_CASE(DayAddingCase)
{
    Day day;
    day = day + 5;
    BOOST_CHECK_EQUAL(day.getIndex(), 5);
    BOOST_CHECK_EQUAL(day.toString(), "6");
    day = day + 30;
    BOOST_CHECK_EQUAL(day.getIndex(), 35);
    BOOST_CHECK_EQUAL(day.toString().length(), 1);
}

BOOST_AUTO_TEST_CASE(DaySubstractingCase)
{
    Day day;
    day = day + 5;
    day = day - 1;
    BOOST_CHECK_EQUAL(day.getIndex(), 4);
    BOOST_CHECK_EQUAL(day.toString(), "5");
    day = day - 10;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(day.toString(), "1");
}

BOOST_AUTO_TEST_CASE(DayAddAndAssignCase)
{
    Day day;
    day += 5;
    BOOST_CHECK_EQUAL(day.getIndex(), 5);
    BOOST_CHECK_EQUAL(day.toString(), "6");
    day += 30;
    BOOST_CHECK_EQUAL(day.getIndex(), 35);
    BOOST_CHECK_EQUAL(day.toString().length(), 1);
}

BOOST_AUTO_TEST_CASE(DaySubstractAndAssignCase)
{
    Day day;
    day += 5;
    day -= 1;
    BOOST_CHECK_EQUAL(day.getIndex(), 4);
    BOOST_CHECK_EQUAL(day.toString(), "5");
    day -= 10;
    BOOST_CHECK_EQUAL(day.getIndex(), 0);
    BOOST_CHECK_EQUAL(day.toString(), "1");
}

BOOST_AUTO_TEST_SUITE_END()