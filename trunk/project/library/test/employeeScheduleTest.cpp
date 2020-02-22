#include "employee/schedule/employeeSchedule.h"
#include "other/calendar.h"
#include "shift/shift.h"
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureEmployeeScheduleTest
{
  FixtureEmployeeScheduleTest()
    : s1()
    , s2()
    , s3()
    , s4()
    , s5()
    , s6()
    , shift1(new Shift(5, 10, 3))
    , shift2(new Shift(15, 20, 3))
    , shift3(new Shift(5, 10, 15))
    , shift4(new Shift(5, 15, 11))
    , shift5(new Shift(4, 15, 11))
    , shift6(new Shift(20, 24, 11))
    , schedule(){};

  ~FixtureEmployeeScheduleTest(){};
  std::ostringstream s1, s2, s3, s4, s5, s6;
  std::unique_ptr<Shift> shift1;
  std::unique_ptr<Shift> shift2;
  std::unique_ptr<Shift> shift3;
  std::unique_ptr<Shift> shift4;
  std::unique_ptr<Shift> shift5;
  std::unique_ptr<Shift> shift6;
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
  s1 << shift1->shiftInfo();
  s2 << shift2->shiftInfo();
  s3 << shift3->shiftInfo();
  s4 << shift4->shiftInfo();
  s6 << shift6->shiftInfo();
  schedule.addShift(shift2);
  schedule.addShift(shift1);
  schedule.addShift(shift3);
  schedule.addShift(shift4);
  schedule.addShift(shift6);
  BOOST_CHECK_EQUAL(schedule.getSchedule()[2][0]->shiftInfo(), s1.str());
  BOOST_CHECK_EQUAL(schedule.getSchedule()[2][1]->shiftInfo(), s2.str());
  BOOST_CHECK_EQUAL(schedule.getSchedule()[14][0]->shiftInfo(), s3.str());
  BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->shiftInfo(), s4.str());
  BOOST_CHECK_EQUAL(schedule.getSchedule()[10][1]->shiftInfo(), s6.str());
}

BOOST_FIXTURE_TEST_CASE(EmployeeScheduleCaseRemoveShift,
                        FixtureEmployeeScheduleTest)
{
  s1 << shift1->shiftInfo();
  s2 << shift2->shiftInfo();
  s3 << shift3->shiftInfo();
  s4 << shift4->shiftInfo();
  s6 << shift6->shiftInfo();
  schedule.addShift(shift2);
  schedule.addShift(shift1);
  schedule.addShift(shift3);
  schedule.addShift(shift4);
  schedule.addShift(shift6);
  schedule.removeShift(11, 1);
  BOOST_CHECK_EQUAL(schedule.getSchedule()[10][0]->shiftInfo(), s6.str());
  BOOST_TEST_MESSAGE(schedule.scheduleInfo());
}

BOOST_AUTO_TEST_SUITE_END()