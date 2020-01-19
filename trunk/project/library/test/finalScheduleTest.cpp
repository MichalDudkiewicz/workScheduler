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
#include "schedule.h"


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

        TeamRepository::getInstance().get("S2")->addShift(5,10,1);
        TeamRepository::getInstance().get("1")->addShift(10,15,2);

        boost::gregorian::date firstMonday(Schedule::getStartDate());
        while(firstMonday.day_of_week()!=1)
        {
            firstMonday += boost::gregorian::days(1);
        }

        positionPtr medic = std::make_shared<Medic>();
        positionPtr driver = std::make_shared<DriverN>();

        EmployeeRepository::getInstance().get(2)->addDesiredShift(4,11,firstMonday.day());
        EmployeeRepository::getInstance().get(2)->addDesiredShift(9,16,firstMonday.day()+1);
        EmployeeRepository::getInstance().get(3)->addDesiredShift(4,11,firstMonday.day());
        EmployeeRepository::getInstance().get(3)->addDesiredShift(9,16,firstMonday.day()+1);

        EmployeeRepository::getInstance().get(2)->addPosition(medic);
        EmployeeRepository::getInstance().get(3)->addPosition(driver);

        FinalSchedule schedule(TeamRepository::getInstance().getAll(),EmployeeRepository::getInstance().getAll());
        schedule.makeSchedule();
        BOOST_TEST_MESSAGE(schedule.scheduleInfo());
        BOOST_CHECK_EQUAL(schedule.getSchedule()[0][0][0].empty(),true);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[2][0][0].front()->getId(),2);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[3][1][0].front()->getId(),3);
        schedule.clear();
        BOOST_CHECK_EQUAL(schedule.getSchedule()[0][0][0].empty(),true);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[2][0][0].empty(),true);
        BOOST_CHECK_EQUAL(schedule.getSchedule()[3][1][0].empty(),true);
    }

BOOST_AUTO_TEST_SUITE_END()
