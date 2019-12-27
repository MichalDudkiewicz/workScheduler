#include <boost/test/unit_test.hpp>
#include "schedule.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(ScheduleCase)
    {
        Schedule schedule;
        boost::gregorian::date d(boost::gregorian::day_clock::local_day());
        BOOST_CHECK_EQUAL(schedule.getCurrentDate(),d);
        d += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(schedule.getNumberOfDays(),boost::gregorian::gregorian_calendar::end_of_month_day(d.year(),d.month()));
        boost::gregorian::date startDate(d.year(),d.month(),1);
        BOOST_CHECK_EQUAL(schedule.getStartDate(),startDate);
        std::ostringstream out;
        out << startDate.day_of_week();
        BOOST_CHECK_EQUAL(schedule.getWeekDay(schedule.getWeekDayIterator(startDate)),out.str());
    }

BOOST_AUTO_TEST_SUITE_END()