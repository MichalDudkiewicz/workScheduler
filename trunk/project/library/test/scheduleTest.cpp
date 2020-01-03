#include <boost/test/unit_test.hpp>
#include "schedule.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct MyGlobalFixture {
        MyGlobalFixture() {
        d = boost::gregorian::day_clock::local_day();
        startDate = boost::gregorian::date (d.year(),d.month()+1,1);
        day = startDate.day_of_week()-1;
        }
        ~MyGlobalFixture() {}

        static boost::gregorian::date d;
        static boost::gregorian::date startDate;
        static int day;
    };
    boost::gregorian::date MyGlobalFixture::d(boost::gregorian::day_clock::local_day());
    boost::gregorian::date MyGlobalFixture::startDate(MyGlobalFixture::d.year(),MyGlobalFixture::d.month()+1,1);
    int MyGlobalFixture::day = MyGlobalFixture::startDate.day_of_week()-1;

    BOOST_TEST_GLOBAL_FIXTURE( MyGlobalFixture );

    BOOST_AUTO_TEST_CASE(ScheduleCaseGetCurrentDate)
    {
        BOOST_CHECK_EQUAL(Schedule::getCurrentDate(),MyGlobalFixture::d);
    }

    BOOST_AUTO_TEST_CASE(ScheduleCaseGetNumberOfDays)
    {
        MyGlobalFixture::d += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(Schedule::getNumberOfDays(),boost::gregorian::gregorian_calendar::end_of_month_day(MyGlobalFixture::d.year(),MyGlobalFixture::d.month()));
    }

    BOOST_AUTO_TEST_CASE(ScheduleCaseStartDate)
    {
        BOOST_CHECK_EQUAL(Schedule::getStartDate(),MyGlobalFixture::startDate);
    }
    BOOST_AUTO_TEST_CASE(ScheduleCaseGetWeekDayIterator)
    {
        BOOST_CHECK_EQUAL(Schedule::getWeekDayIterator(MyGlobalFixture::startDate),MyGlobalFixture::day);
    }
BOOST_AUTO_TEST_SUITE_END()