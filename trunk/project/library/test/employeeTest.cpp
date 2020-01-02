#include <boost/test/unit_test.hpp>
#include "employee.h"
#include <memory>
#include "doctor.h"
#include "medic.h"
#include "driverN.h"
#include "employeeType.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeConstructorCase)
    {
        Employee palinka("Palinka",5);
        BOOST_CHECK_EQUAL(palinka.getPriority(),1);
        BOOST_CHECK_EQUAL(palinka.getName(),"Palinka");
        BOOST_CHECK_EQUAL(palinka.getPoints(),0);
        BOOST_CHECK_EQUAL(palinka.getType()->getType(),"normal");
        BOOST_CHECK_EQUAL(palinka.getId(),5);
        BOOST_CHECK_EQUAL(palinka.getHourlyWage(),0);
        BOOST_CHECK_EQUAL(palinka.getMaxShifts(),0);
        BOOST_CHECK_EQUAL(palinka.getMinShifts(),0);
        BOOST_CHECK_EQUAL(palinka.isNonresident(),false);
        BOOST_CHECK_EQUAL(palinka.getWorkHours(),0);
        BOOST_CHECK_EQUAL(palinka.getShiftsQuantity(),0);
        BOOST_CHECK_EQUAL(palinka.getMyEnemies().size(),0);
        BOOST_CHECK_EQUAL(palinka.getMyFriends().size(),0);
        boost::gregorian::date d(boost::gregorian::day_clock::local_day());
        d += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(palinka.getDesiredSchedule().size(),boost::gregorian::gregorian_calendar::end_of_month_day(d.year(),d.month())+1);
        BOOST_CHECK_EQUAL(palinka.getCurrentSchedule().size(),boost::gregorian::gregorian_calendar::end_of_month_day(d.year(),d.month())+1);
        BOOST_CHECK_EQUAL(palinka.getPositions().size(),0);
    }

    BOOST_AUTO_TEST_CASE(EmployeeFriendsEnemiesCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        std::shared_ptr<Employee> palinka = std::make_shared<Employee>("Palinka",1);
        std::shared_ptr<Employee> michal = std::make_shared<Employee>("Michal",2);
        std::shared_ptr<Employee> janusz = std::make_shared<Employee>("Janusz",3);
        (*palinka).addFriend(mateush);
        (*palinka).addFriend(michal);
        (*palinka).addEnemy(janusz);
        BOOST_CHECK_EQUAL((*palinka).getMyFriends()[0]->getId(),0);
        BOOST_CHECK_EQUAL((*mateush).isFriendWith(palinka),true);
        BOOST_CHECK_EQUAL((*palinka).isFriendWith(mateush),true);
        (*palinka).addEnemy(mateush);
        BOOST_CHECK_EQUAL((*palinka).isFriendWith(mateush),false);
        BOOST_CHECK_EQUAL((*mateush).isFriendWith(palinka),false);
        BOOST_CHECK_EQUAL((*palinka).isEnemyWith(mateush),true);
        BOOST_CHECK_EQUAL((*mateush).isEnemyWith(palinka),true);
        BOOST_CHECK_EQUAL((*mateush).isEnemyWith(janusz),false);
        BOOST_CHECK_EQUAL((*mateush).isFriendWith(janusz),false);
    }

    BOOST_AUTO_TEST_CASE(EmployeeChangeResidencyCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        (*mateush).setNonresident(true);
        BOOST_CHECK_EQUAL((*mateush).isNonresident(),true);
    }

    BOOST_AUTO_TEST_CASE(EmployeeSetShiftsLimitCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        (*mateush).setMinShifts(5);
        (*mateush).setMaxShifts(10);
        BOOST_CHECK_EQUAL((*mateush).getMinShifts(),5);
        BOOST_CHECK_EQUAL((*mateush).getMaxShifts(),10);
    }

    BOOST_AUTO_TEST_CASE(EmployeeSetWageCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        (*mateush).setHourlyWage(5);
        BOOST_CHECK_EQUAL((*mateush).getHourlyWage(),5);
    }

    BOOST_AUTO_TEST_CASE(EmployeeSetPointsCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        (*mateush).setPoints(5);
        (*mateush).changePoints(5);
        (*mateush).changePoints(-1);
        BOOST_CHECK_EQUAL((*mateush).getPoints(),9);
    }

    BOOST_AUTO_TEST_CASE(EmployeeChangeTypeCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        (*mateush).changeType(1);
        BOOST_CHECK_EQUAL((*mateush).getPriority(),0);
        (*mateush).changeType(2);
        BOOST_CHECK_EQUAL((*mateush).getPriority(),2);
    }

    BOOST_AUTO_TEST_CASE(EmployeeAddRemovePositionCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        std::ostringstream d,m;
        m << medic->positionInfo();
        d << doctor->positionInfo();
        (*mateush).addPosition(medic);
        (*mateush).addPosition(doctor);
        BOOST_CHECK_EQUAL((*mateush).getPositions()[1]->positionInfo(),m.str());
        BOOST_CHECK_EQUAL((*mateush).getPositions()[0]->positionInfo(),d.str());
        (*mateush).removePosition(medic);
        BOOST_CHECK_EQUAL((*mateush).getPositions()[0]->positionInfo(),d.str());
        BOOST_CHECK_EQUAL((*mateush).getPositions().size(),1);
    }

    BOOST_AUTO_TEST_CASE(EmployeeDesiredScheduleCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        std::unique_ptr<Shift> shift1(new Shift(5,10,3));
        std::unique_ptr<Shift> shift2(new Shift(15,20,3));
        std::unique_ptr<Shift> shift3(new Shift(5,10,15));
        std::unique_ptr<Shift> shift4(new Shift(15,19,11));
        std::unique_ptr<Shift> shift6(new Shift(20,24,11));
        (*mateush).addDesiredShift(shift1);
        (*mateush).addDesiredShift(shift2);
        (*mateush).addDesiredShift(shift3);
        (*mateush).addDesiredShift(shift6);
        (*mateush).addDesiredShift(shift4);
        BOOST_CHECK_EQUAL((*mateush).getDesiredSchedule()[10][0]->getStartHour(),15);
        (*mateush).removeDesiredShift(11,1);
        BOOST_CHECK_EQUAL((*mateush).getDesiredSchedule()[10][0]->getStartHour(),20);
        std::unique_ptr<Shift> shift7(new Shift(20,24,1));
        std::unique_ptr<Shift> shift8(new Shift(14,16,3));
        std::unique_ptr<Shift> shift9(new Shift(21,24,11));
        BOOST_CHECK_EQUAL((*mateush).isAvailable(shift7),false);
        BOOST_CHECK_EQUAL((*mateush).isAvailable(shift8),false);
        BOOST_CHECK_EQUAL((*mateush).isAvailable(shift9),true);
        std::unique_ptr<Shift> shift10(new Shift(20,24,20));
        std::unique_ptr<Shift> shift11(new Shift(0,8,21));
        (*mateush).addDesiredShift(shift10);
        (*mateush).addDesiredShift(shift11);
        std::unique_ptr<Shift> shift12(new Shift(21,6,20));
        std::unique_ptr<Shift> shift13(new Shift(21,10,20));
        std::unique_ptr<Shift> shift14(new Shift(20));
        BOOST_CHECK_EQUAL((*mateush).isAvailable(shift12),true);
        BOOST_CHECK_EQUAL((*mateush).isAvailable(shift13),false);
        BOOST_CHECK_EQUAL((*mateush).isAvailable(shift14),false);
    }

    BOOST_AUTO_TEST_CASE(EmployeeCurrentScheduleCase)
    {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",0);
        std::unique_ptr<Shift> shift1(new Shift(5,10,3));
        std::unique_ptr<Shift> shift2(new Shift(15,20,3));
        std::unique_ptr<Shift> shift3(new Shift(5,10,15));
        std::unique_ptr<Shift> shift4(new Shift(15,19,11));
        std::unique_ptr<Shift> shift6(new Shift(20,24,11));
        (*mateush).addCurrentShift(shift1);
        (*mateush).addCurrentShift(shift2);
        (*mateush).addCurrentShift(shift3);
        (*mateush).addCurrentShift(shift6);
        (*mateush).addCurrentShift(shift4);
        BOOST_CHECK_EQUAL((*mateush).getCurrentSchedule()[10][0]->getStartHour(),15);
        (*mateush).removeCurrentShift(11,1);
        BOOST_CHECK_EQUAL((*mateush).getCurrentSchedule()[10][0]->getStartHour(),20);
        BOOST_CHECK_EQUAL((*mateush).getShiftsQuantity(),4);
        BOOST_CHECK_EQUAL((*mateush).getWorkHours(),19);
        std::unique_ptr<Shift> shift7(new Shift(18,19,11));
        std::unique_ptr<Shift> shift8(new Shift(9,20,3));
        BOOST_CHECK_EQUAL((*mateush).isBusy(shift7),false);
        BOOST_CHECK_EQUAL((*mateush).isBusy(shift8),true);
    }

    BOOST_AUTO_TEST_CASE(EmployeeIsAuthorisedCase)
    {
        std::shared_ptr<Employee> mateusz = std::make_shared<Employee>("Mateusz",0);
        std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
        std::shared_ptr<Position> medic=std::make_shared<Medic>();
        std::shared_ptr<Position> driver=std::make_shared<DriverN>();
        (*mateusz).addPosition(doctor);
        (*mateusz).addPosition(medic);
        BOOST_CHECK_EQUAL((*mateusz).isAuthorised(doctor),true);
        BOOST_CHECK_EQUAL((*mateusz).isAuthorised(driver),false);
    }

BOOST_AUTO_TEST_SUITE_END()