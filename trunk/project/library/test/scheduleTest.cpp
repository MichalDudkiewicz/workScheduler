#include <boost/test/unit_test.hpp>
#include "schedule.h"
#include <memory>


BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(ScheduleCase)
    {
        boost::gregorian::date d(boost::gregorian::day_clock::local_day());
        BOOST_CHECK_EQUAL(Schedule::getCurrentDate(),d);
        d += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(Schedule::getNumberOfDays(),boost::gregorian::gregorian_calendar::end_of_month_day(d.year(),d.month()));
        boost::gregorian::date startDate(d.year(),d.month(),1);
        BOOST_CHECK_EQUAL(Schedule::getStartDate(),startDate);
        int day = startDate.day_of_week()-1;
        //BOOST_CHECK_EQUAL(Schedule::getWeekDay(Schedule::getWeekDayIterator(startDate)),out.str());
        BOOST_CHECK_EQUAL(Schedule::getWeekDayIterator(startDate),day);
    }

BOOST_AUTO_TEST_SUITE_END()