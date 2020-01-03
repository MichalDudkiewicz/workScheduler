#include <boost/test/unit_test.hpp>
#include "employee.h"
#include <memory>
#include "doctor.h"
#include "medic.h"
#include "driverN.h"
#include "employeeType.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct MyGlobalFixture {
        MyGlobalFixture() {employee0 = std::make_shared<Employee>("Mateusz", 0);
            employee1 = std::make_shared<Employee>("Kamila",1);
            employee2 = std::make_shared<Employee>("Michal",2);
            employee3 = std::make_shared<Employee>("Janusz",3);

//            std::unique_ptr<Shift> shift11(new Shift(5,10,3));
//            std::unique_ptr<Shift> shift22(new Shift(15,20,3));
//            std::unique_ptr<Shift> shift33(new Shift(5,10,15));
//            std::unique_ptr<Shift> shift44(new Shift(15,19,11));
//            std::unique_ptr<Shift> shift66(new Shift(20,24,11));
        }
        ~MyGlobalFixture() {}
        static std::shared_ptr<Employee> employee0;
        static std::shared_ptr<Employee> employee1;
        static std::shared_ptr<Employee> employee2;
        static std::shared_ptr<Employee> employee3;
        static std::unique_ptr<Shift> shift11;
        static std::unique_ptr<Shift> shift22;
        static std::unique_ptr<Shift> shift33;
        static std::unique_ptr<Shift> shift44;
        static std::unique_ptr<Shift> shift66;
    };
    std::shared_ptr<Employee> MyGlobalFixture::employee0 = std::make_shared<Employee>("Mateusz", 0);
    std::shared_ptr<Employee> MyGlobalFixture::employee1 = std::make_shared<Employee>("Kamila",1);
    std::shared_ptr<Employee> MyGlobalFixture::employee2 = std::make_shared<Employee>("Michal",2);
    std::shared_ptr<Employee> MyGlobalFixture::employee3 = std::make_shared<Employee>("Janusz",3);

    std::unique_ptr<Shift> MyGlobalFixture::shift11(new Shift(5,10,3));
    std::unique_ptr<Shift> MyGlobalFixture::shift22(new Shift(15,20,3));
    std::unique_ptr<Shift> MyGlobalFixture::shift33(new Shift(5,10,15));
    std::unique_ptr<Shift> MyGlobalFixture::shift44(new Shift(15,19,11));
    std::unique_ptr<Shift> MyGlobalFixture::shift66(new Shift(20,24,11));

    BOOST_TEST_GLOBAL_FIXTURE( MyGlobalFixture );

    boost::gregorian::date date(boost::gregorian::day_clock::local_day());

    BOOST_AUTO_TEST_CASE(EmployeeConstructorCase)
    {
        Employee employee11("Paulina", 5);
        BOOST_CHECK_EQUAL(employee11.getPriority(),1);
        BOOST_CHECK_EQUAL(employee11.getName(), "Paulina");
        BOOST_CHECK_EQUAL(employee11.getPoints(), 0);
        BOOST_CHECK_EQUAL(employee11.getType()->getType(),"normal");
        BOOST_CHECK_EQUAL(employee11.getId(), 5);
        BOOST_CHECK_EQUAL(employee11.getHourlyWage(), 0);
        BOOST_CHECK_EQUAL(employee11.getMaxShifts(), 0);
        BOOST_CHECK_EQUAL(employee11.getMinShifts(), 0);
        BOOST_CHECK_EQUAL(employee11.isNonresident(), false);
        BOOST_CHECK_EQUAL(employee11.getWorkHours(), 0);
        BOOST_CHECK_EQUAL(employee11.getShiftsQuantity(), 0);
        BOOST_CHECK_EQUAL(employee11.getMyEnemies().size(), 0);
        BOOST_CHECK_EQUAL(employee11.getMyFriends().size(), 0);
        date += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(employee11.getDesiredSchedule().size(), boost::gregorian::gregorian_calendar::end_of_month_day(date.year(), date.month()) + 1);
        BOOST_CHECK_EQUAL(employee11.getCurrentSchedule().size(), boost::gregorian::gregorian_calendar::end_of_month_day(date.year(), date.month()) + 1);
        BOOST_CHECK_EQUAL(employee11.getPositions().size(), 0);
    }

    BOOST_AUTO_TEST_CASE(EmployeeFriendsEnemiesCase)
    {
        (*MyGlobalFixture::employee1).addFriend(MyGlobalFixture::employee0);
        (*MyGlobalFixture::employee1).addFriend(MyGlobalFixture::employee2);
        (*MyGlobalFixture::employee1).addEnemy(MyGlobalFixture::employee3);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee1).getMyFriends()[0]->getId(), 0);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isFriendWith(MyGlobalFixture::employee1), true);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee1).isFriendWith(MyGlobalFixture::employee0), true);
        (*MyGlobalFixture::employee1).addEnemy(MyGlobalFixture::employee0);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee1).isFriendWith(MyGlobalFixture::employee0), false);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isFriendWith(MyGlobalFixture::employee1), false);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee1).isEnemyWith(MyGlobalFixture::employee0), true);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isEnemyWith(MyGlobalFixture::employee1), true);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isEnemyWith(MyGlobalFixture::employee3), false);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isFriendWith(MyGlobalFixture::employee3), false);
    }

    BOOST_AUTO_TEST_CASE(EmployeeChangeResidencyCase)
    {
        (*MyGlobalFixture::employee0).setNonresident(true);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isNonresident(),true);
    }

    BOOST_AUTO_TEST_CASE(EmployeeSetShiftsLimitCase)
    {
        (*MyGlobalFixture::employee0).setMinShifts(5);
        (*MyGlobalFixture::employee0).setMaxShifts(10);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getMinShifts(),5);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getMaxShifts(),10);
    }

    BOOST_AUTO_TEST_CASE(EmployeeSetWageCase)
    {
        (*MyGlobalFixture::employee0).setHourlyWage(5);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getHourlyWage(),5);
    }

    BOOST_AUTO_TEST_CASE(EmployeeSetPointsCase)
    {
        (*MyGlobalFixture::employee0).setPoints(5);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPoints(),5);
        (*MyGlobalFixture::employee0).changePoints(5);
        (*MyGlobalFixture::employee0).changePoints(-1);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPoints(),9);
    }

    BOOST_AUTO_TEST_CASE(EmployeeChangeTypeCase)
    {
        (*MyGlobalFixture::employee0).changeType(1);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPriority(),0);
        (*MyGlobalFixture::employee0).changeType(2);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPriority(),2);
    }

    std::ostringstream d1,m;

    BOOST_AUTO_TEST_CASE(EmployeeAddRemovePositionCase)
    {
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        m << medic->positionInfo();
        d1 << doctor->positionInfo();
        (*MyGlobalFixture::employee0).addPosition(medic);
        (*MyGlobalFixture::employee0).addPosition(doctor);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPositions()[1]->positionInfo(),m.str());
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPositions()[0]->positionInfo(),d1.str());
        (*MyGlobalFixture::employee0).removePosition(medic);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPositions()[0]->positionInfo(),d1.str());
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getPositions().size(),1);
    }


    BOOST_AUTO_TEST_CASE(EmployeeDesiredScheduleCase)
    {

        (*MyGlobalFixture::employee0).addDesiredShift(MyGlobalFixture::shift11);
        (*MyGlobalFixture::employee0).addDesiredShift(MyGlobalFixture::shift22);
        (*MyGlobalFixture::employee0).addDesiredShift(MyGlobalFixture::shift33);
        (*MyGlobalFixture::employee0).addDesiredShift(MyGlobalFixture::shift66);
        (*MyGlobalFixture::employee0).addDesiredShift(MyGlobalFixture::shift44);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getDesiredSchedule()[10][0]->getStartHour(),15);
        (*MyGlobalFixture::employee0).removeDesiredShift(11,1);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getDesiredSchedule()[10][0]->getStartHour(),20);
        std::unique_ptr<Shift> shift7(new Shift(20,24,1));
        std::unique_ptr<Shift> shift8(new Shift(14,16,3));
        std::unique_ptr<Shift> shift9(new Shift(21,24,11));
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAvailable(shift7),false);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAvailable(shift8),false);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAvailable(shift9),true);
        std::unique_ptr<Shift> shift10(new Shift(20,24,20));
        std::unique_ptr<Shift> shift111(new Shift(0,8,21));
        (*MyGlobalFixture::employee0).addDesiredShift(shift10);
        (*MyGlobalFixture::employee0).addDesiredShift(shift111);
        std::unique_ptr<Shift> shift12(new Shift(21,6,20));
        std::unique_ptr<Shift> shift13(new Shift(21,10,20));
        std::unique_ptr<Shift> shift14(new Shift(20));
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAvailable(shift12),true);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAvailable(shift13),false);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAvailable(shift14),false);
    }

    BOOST_AUTO_TEST_CASE(EmployeeCurrentScheduleCase)
    {
        std::unique_ptr<Shift> shift1(new Shift(5,10,3));
        std::unique_ptr<Shift> shift2(new Shift(15,20,3));
        std::unique_ptr<Shift> shift3(new Shift(5,10,15));
        std::unique_ptr<Shift> shift4(new Shift(15,19,11));
        std::unique_ptr<Shift> shift6(new Shift(20,24,11));
//        (*MyGlobalFixture::employee0).addCurrentShift(MyGlobalFixture::shift11);
//        (*MyGlobalFixture::employee0).addCurrentShift(MyGlobalFixture::shift22);
//        (*MyGlobalFixture::employee0).addCurrentShift(MyGlobalFixture::shift33);
//        (*MyGlobalFixture::employee0).addCurrentShift(MyGlobalFixture::shift66);
//        (*MyGlobalFixture::employee0).addCurrentShift(MyGlobalFixture::shift44);
//        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getCurrentSchedule()[10][0]->getStartHour(),15);
//        (*MyGlobalFixture::employee0).removeCurrentShift(11,1);
//        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getCurrentSchedule()[10][0]->getStartHour(),20);
//        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getShiftsQuantity(),4);
//        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).getWorkHours(),19);
//        std::unique_ptr<Shift> shift7(new Shift(18,19,11));
//        std::unique_ptr<Shift> shift8(new Shift(9,20,3));
//        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isBusy(shift7),false);
//        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isBusy(shift8),true);
    }

    BOOST_AUTO_TEST_CASE(EmployeeIsAuthorisedCase)
    {
        std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
        std::shared_ptr<Position> medic=std::make_shared<Medic>();
        std::shared_ptr<Position> driver=std::make_shared<DriverN>();
        (*MyGlobalFixture::employee0).addPosition(doctor);
        (*MyGlobalFixture::employee0).addPosition(medic);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAuthorised(doctor),true);
        BOOST_CHECK_EQUAL((*MyGlobalFixture::employee0).isAuthorised(driver),false);
    }

BOOST_AUTO_TEST_SUITE_END()