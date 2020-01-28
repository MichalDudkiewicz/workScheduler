#include <boost/test/unit_test.hpp>
#include "calendar.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct FixtureScheduleTest {
        FixtureScheduleTest() : d(boost::gregorian::day_clock::local_day()), startDate(d.year(), d.month() + 1, 1),
                                day(startDate.day_of_week() - 1) {}

        ~FixtureScheduleTest() {}

        boost::gregorian::date d;
        boost::gregorian::date startDate;
        int day;
    };

    BOOST_FIXTURE_TEST_CASE(ScheduleCaseGetCurrentDate, FixtureScheduleTest) {
        BOOST_CHECK_EQUAL(calendar::getCurrentDate(), d);
    }

    BOOST_FIXTURE_TEST_CASE(ScheduleCaseGetNumberOfDays, FixtureScheduleTest) {
        d += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(calendar::getNumberOfDays(),
                          boost::gregorian::gregorian_calendar::end_of_month_day(d.year(), d.month()));
    }

    BOOST_FIXTURE_TEST_CASE(ScheduleCaseStartDate, FixtureScheduleTest) {
        BOOST_CHECK_EQUAL(calendar::getStartDate(), startDate);
    }

    BOOST_FIXTURE_TEST_CASE(ScheduleCaseGetWeekDayIterator, FixtureScheduleTest) {
        BOOST_CHECK_EQUAL(calendar::getWeekDayIterator(startDate), day);
    }

BOOST_AUTO_TEST_SUITE_END()