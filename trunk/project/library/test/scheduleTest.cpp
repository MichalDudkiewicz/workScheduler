#include <boost/test/unit_test.hpp>
#include "schedule.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)
    boost::gregorian::date d(boost::gregorian::day_clock::local_day());
    boost::gregorian::date startDate(d.year(),d.month()+1,1);
    int day = startDate.day_of_week()-1;

    BOOST_AUTO_TEST_CASE(ScheduleCaseGetCurrentDate)
    {
        BOOST_CHECK_EQUAL(Schedule::getCurrentDate(),d);
    }

    BOOST_AUTO_TEST_CASE(ScheduleCaseGetNumberOfDays)
    {
        d += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(Schedule::getNumberOfDays(),boost::gregorian::gregorian_calendar::end_of_month_day(d.year(),d.month()));
    }

    BOOST_AUTO_TEST_CASE(ScheduleCaseStartDate)
    {
        BOOST_CHECK_EQUAL(Schedule::getStartDate(),startDate);
    }
    BOOST_AUTO_TEST_CASE(ScheduleCaseGetWeekDayIterator)
    {
        BOOST_CHECK_EQUAL(Schedule::getWeekDayIterator(startDate),day);
    }
BOOST_AUTO_TEST_SUITE_END()