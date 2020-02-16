#include <boost/test/unit_test.hpp>
#include "medic.h"
#include "driverN.h"
#include <memory>
#include "teamRepository.h"
#include "employeeRepository.h"
#include "employee.h"
#include "team.h"
#include "shift.h"
#include "finalSchedule.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "calendar.h"
#include "factor.h"


BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)


    BOOST_AUTO_TEST_CASE(FinalScheduleCase) {
        TeamRepository::getInstance().remove("2");
        TeamRepository::getInstance().remove("B2");
        TeamRepository::getInstance().remove("C3");
        TeamRepository::getInstance().remove("D4");
        EmployeeRepository::getInstance().remove(4);
        EmployeeRepository::getInstance().remove(7);
        EmployeeRepository::getInstance().remove(8);
        EmployeeRepository::getInstance().remove(9);

        TeamRepository::getInstance().get("S2")->addShift(5, 10, 1);
        TeamRepository::getInstance().get("1")->addShift(10, 15, 2);

        boost::gregorian::date firstMonday(calendar::getStartDate());
        while (firstMonday.day_of_week() != 1) {
            firstMonday += boost::gregorian::days(1);
        }

        positionPtr medic = std::make_shared<Medic>();
        positionPtr driver = std::make_shared<DriverN>();

        EmployeeRepository::getInstance().get(2)->getFactor()->getAvailability().getDesiredSchedule().addShift(4, 11, firstMonday.day());
        EmployeeRepository::getInstance().get(2)->getFactor()->getAvailability().getDesiredSchedule().addShift(9, 16, firstMonday.day() + 1);
        EmployeeRepository::getInstance().get(3)->getFactor()->getAvailability().getDesiredSchedule().addShift(4, 11, firstMonday.day());
        EmployeeRepository::getInstance().get(3)->getFactor()->getAvailability().getDesiredSchedule().addShift(9, 16, firstMonday.day() + 1);

        EmployeeRepository::getInstance().get(2)->getFactor()->getAuthorisation().addPosition(medic);
        EmployeeRepository::getInstance().get(3)->getFactor()->getAuthorisation().addPosition(driver);

        EmployeeRepository::getInstance().get(2)->getFactor()->getAuthorisation().addTeam(TeamRepository::getInstance().get("S2"));
        EmployeeRepository::getInstance().get(2)->getFactor()->getAuthorisation().addTeam(TeamRepository::getInstance().get("1"));
        EmployeeRepository::getInstance().get(3)->getFactor()->getAuthorisation().addTeam(TeamRepository::getInstance().get("S2"));
        EmployeeRepository::getInstance().get(3)->getFactor()->getAuthorisation().addTeam(TeamRepository::getInstance().get("1"));

        FinalSchedule schedule(TeamRepository::getInstance().getAll(), EmployeeRepository::getInstance().getAll());
        schedule.makeSchedule();
        BOOST_TEST_MESSAGE(schedule.scheduleInfo());
        BOOST_CHECK_EQUAL(schedule.getSchedule()[0].at(TeamRepository::getInstance().getAll().front()).at(TeamRepository::getInstance().getAll().front()->getPositions().front()).empty(), true);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[firstMonday.day() - 1].at(TeamRepository::getInstance().get("S2")).at(TeamRepository::getInstance().get("S2")->getPositions().front()).front()->getId(), 3);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[firstMonday.day()].at(TeamRepository::getInstance().get("1")).at(TeamRepository::getInstance().get("1")->getPositions().front()).front()->getId(), 3);
        schedule.clear();
        BOOST_CHECK_EQUAL(schedule.getSchedule()[0].at(TeamRepository::getInstance().get("1")).at(TeamRepository::getInstance().get("1")->getPositions().front()).empty(), true);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[firstMonday.day() - 1].at(TeamRepository::getInstance().get("1")).at(TeamRepository::getInstance().get("1")->getPositions().front()).empty(), true);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[firstMonday.day()].at(TeamRepository::getInstance().get("S2")).at(TeamRepository::getInstance().get("S2")->getPositions().front()).empty(), true);
    }

BOOST_AUTO_TEST_SUITE_END()
