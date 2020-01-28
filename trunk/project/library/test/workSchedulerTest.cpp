#include <boost/test/unit_test.hpp>
#include "workScheduler.h"
#include "employeeRepository.h"
#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"
#include "calendar.h"
#include "employee.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(WorkSchedulerConstructionCase) {
        boost::gregorian::date firstMonday(calendar::getStartDate());
        while(firstMonday.day_of_week()!=1)
        {
            firstMonday += boost::gregorian::days(1);
        }
        WorkScheduler::getInstance().createSchedule();
        BOOST_TEST_MESSAGE(WorkScheduler::getInstance().scheduleInfo());
        BOOST_CHECK_EQUAL(WorkScheduler::getInstance().getSchedule()[0][0][0].empty(),true);
        BOOST_CHECK_EQUAL(WorkScheduler::getInstance().getSchedule()[firstMonday.day()-1][0][0].front()->getId(),3);
        WorkScheduler::getInstance().updateSchedule();
        BOOST_CHECK_EQUAL(WorkScheduler::getInstance().getSchedule()[firstMonday.day()-1][0][0].empty(),true);
    }

BOOST_AUTO_TEST_SUITE_END()