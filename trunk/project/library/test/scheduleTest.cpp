#include "utils/calendar.h"
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureScheduleTest {
    FixtureScheduleTest()
        : d(boost::gregorian::day_clock::local_day())
        , startDate((d + boost::gregorian::months(1)).year(), (d + boost::gregorian::months(1)).month(), 1)
        , day(startDate.day_of_week() - 1)
    {
        if (day == -1)
            day = 6;
    }

    ~FixtureScheduleTest() {}

    boost::gregorian::date d;
    boost::gregorian::date startDate;
    int day;
};

BOOST_FIXTURE_TEST_CASE(ScheduleCaseGetCurrentDate, FixtureScheduleTest)
{
    BOOST_CHECK_EQUAL(calendar::getCurrentDate(), d);
}

BOOST_FIXTURE_TEST_CASE(ScheduleCaseGetNumberOfDays, FixtureScheduleTest)
{
    d += boost::gregorian::months(1);
    BOOST_CHECK_EQUAL(calendar::getNumberOfDays(),
        boost::gregorian::gregorian_calendar::end_of_month_day(
            d.year(), d.month()));
}

BOOST_FIXTURE_TEST_CASE(ScheduleCaseStartDate, FixtureScheduleTest)
{
    BOOST_CHECK_EQUAL(calendar::getStartDate(), startDate);
}

BOOST_FIXTURE_TEST_CASE(ScheduleCaseGetWeekDayIterator, FixtureScheduleTest)
{
    BOOST_CHECK_EQUAL(calendar::getWeekDayIterator(startDate), day);
}

BOOST_AUTO_TEST_SUITE_END()