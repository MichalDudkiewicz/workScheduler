#include "employee/schedule/employeeSchedule.h"
#include "other/calendar.h"
#include "shift/shift.h"
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureEmployeeScheduleTest {
    FixtureEmployeeScheduleTest()
        : schedule(){};

    ~FixtureEmployeeScheduleTest(){};
    EmployeeSchedule schedule;
};

BOOST_FIXTURE_TEST_CASE(EmployeeScheduleCaseCreateSchedule,
    FixtureEmployeeScheduleTest)
{
    BOOST_CHECK_EQUAL(schedule.getSchedule().size(),
        calendar::getNumberOfDays() + 1);
}

BOOST_FIXTURE_TEST_CASE(EmployeeScheduleCaseAddShift,
    FixtureEmployeeScheduleTest)
{
    schedule.addShift(15, 20, 3);
    schedule.addShift(5, 10, 3);
    schedule.addShift(5, 10, 15);
    schedule.addShift(5, 15, 11);
    schedule.addShift(20, 24, 11);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[2][0]->getStartHour(), 5);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[2][1]->getEndHour(), 20);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[14][0]->getEndHour(), 10);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->getStartHour(), 5);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[10][1]->getEndHour(), 24);
}

BOOST_FIXTURE_TEST_CASE(EmployeeScheduleCaseRemoveShift,
    FixtureEmployeeScheduleTest)
{
    schedule.addShift(15, 20, 3);
    schedule.addShift(5, 10, 3);
    schedule.addShift(5, 10, 15);
    schedule.addShift(5, 15, 11);
    schedule.addShift(20, 24, 11);
    schedule.removeShift(11, 1);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->getEndHour(), 24);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->getStartHour(), 20);
    BOOST_TEST_MESSAGE(schedule.scheduleInfo());
}

BOOST_FIXTURE_TEST_CASE(EmployeeScheduleAddNightShiftCase,
    FixtureEmployeeScheduleTest)
{
    schedule.addShift(18, 10, 5);
    schedule.addShift(0, 0, 22);
    schedule.addShift(24, 24, 26);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[4].front()->shiftInfo(),
        "day: 5, 18 - 24");
    BOOST_CHECK_EQUAL(schedule.getSchedule()[5].front()->shiftInfo(),
        "day: 6, 0 - 10");
    BOOST_CHECK_EQUAL(schedule.getSchedule()[20].empty(), true);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[21].front()->shiftInfo(),
        "day: 22, 0 - 24");
    BOOST_CHECK_EQUAL(schedule.getSchedule()[22].empty(), true);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[24].empty(), true);
    BOOST_CHECK_EQUAL(schedule.getSchedule()[25].front()->shiftInfo(),
        "day: 26, 0 - 24");
    BOOST_CHECK_EQUAL(schedule.getSchedule()[26].empty(), true);
}

BOOST_AUTO_TEST_SUITE_END()