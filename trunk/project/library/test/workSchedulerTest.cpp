#include "managers/workScheduler.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "employee/employee.h"
#include "other/calendar.h"
#include "repositories/employeeRepository.h"
#include "repositories/teamRepository.h"
#include "shift/shift.h"
#include "team/team.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

BOOST_AUTO_TEST_CASE(WorkSchedulerConstructionCase)
{
  boost::gregorian::date firstMonday(calendar::getStartDate());
  while (firstMonday.day_of_week() != 1) {
    firstMonday += boost::gregorian::days(1);
  }
  WorkScheduler::getInstance().createSchedule();
  BOOST_TEST_MESSAGE(WorkScheduler::getInstance().scheduleInfo());
  BOOST_CHECK_EQUAL(
    WorkScheduler::getInstance()
      .getSchedule()[0]
      .at(TeamRepository::getInstance().get("1"))
      .at(TeamRepository::getInstance().get("1")->getPositions().front())
      .empty(),
    true);
  BOOST_CHECK_EQUAL(
    WorkScheduler::getInstance()
      .getSchedule()[firstMonday.day() - 1]
      .at(TeamRepository::getInstance().get("S2"))
      .at(TeamRepository::getInstance().get("S2")->getPositions().front())
      .front()
      ->getId(),
    2);
  WorkScheduler::getInstance().updateSchedule();
  BOOST_CHECK_EQUAL(
    WorkScheduler::getInstance()
      .getSchedule()[firstMonday.day() - 1]
      .at(TeamRepository::getInstance().get("S2"))
      .at(TeamRepository::getInstance().get("S2")->getPositions().front())
      .empty(),
    true);
}

BOOST_AUTO_TEST_SUITE_END()