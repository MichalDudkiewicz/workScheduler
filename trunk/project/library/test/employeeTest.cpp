#include <boost/test/unit_test.hpp>
#include "employee.h"
#include <memory>
#include "doctor.h"
#include "medic.h"
#include "driverN.h"
#include "employeeType.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct FixtureEmployeeTest {
        FixtureEmployeeTest() : shift1(new Shift(5, 10, 3)), shift2(new Shift(15, 20, 3)), shift3(new Shift(5, 10, 15)),
                                shift4(new Shift(15, 19, 11)), shift6(new Shift(20, 24, 11)),
                                date((boost::gregorian::day_clock::local_day())), d1(), m() {}

        ~FixtureEmployeeTest() {}

        std::shared_ptr<Employee> employee0 = std::make_shared<Employee>("Mateusz", 0);
        std::shared_ptr<Employee> employee1 = std::make_shared<Employee>("Kamila", 1);
        std::shared_ptr<Employee> employee2 = std::make_shared<Employee>("Michal", 2);
        std::shared_ptr<Employee> employee3 = std::make_shared<Employee>("Janusz", 3);

        std::unique_ptr<Shift> shift1;
        std::unique_ptr<Shift> shift2;
        std::unique_ptr<Shift> shift3;
        std::unique_ptr<Shift> shift4;
        std::unique_ptr<Shift> shift6;

        boost::gregorian::date date;

        std::ostringstream d1, m;

    };

    BOOST_FIXTURE_TEST_CASE(EmployeeConstructorCase, FixtureEmployeeTest) {
        Employee employee11("Paulina", 5);
        BOOST_CHECK_EQUAL(employee11.getPriority(), 1);
        BOOST_CHECK_EQUAL(employee11.getName(), "Paulina");
        BOOST_CHECK_EQUAL(employee11.getPoints(), 0);
        BOOST_CHECK_EQUAL(employee11.getType()->getType(), "normal");
        BOOST_CHECK_EQUAL(employee11.getId(), 5);
        BOOST_CHECK_EQUAL(employee11.getHourlyWage(), 0);
        BOOST_CHECK_EQUAL(employee11.getMaxShifts(), 100);
        BOOST_CHECK_EQUAL(employee11.getMinShifts(), 0);
        BOOST_CHECK_EQUAL(employee11.isNonresident(), false);
        BOOST_CHECK_EQUAL(employee11.getWorkHours(), 0);
        BOOST_CHECK_EQUAL(employee11.getShiftsQuantity(), 0);
        BOOST_CHECK_EQUAL(employee11.getMyEnemies().size(), 0);
        BOOST_CHECK_EQUAL(employee11.getMyFriends().size(), 0);
        date += boost::gregorian::months(1);
        BOOST_CHECK_EQUAL(employee11.getDesiredSchedule().size(),
                          boost::gregorian::gregorian_calendar::end_of_month_day(date.year(), date.month()) + 1);
        BOOST_CHECK_EQUAL(employee11.getCurrentSchedule().size(),
                          boost::gregorian::gregorian_calendar::end_of_month_day(date.year(), date.month()) + 1);
        BOOST_CHECK_EQUAL(employee11.getPositions().size(), 0);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeFriendsEnemiesCase, FixtureEmployeeTest) {
        (*employee1).addFriend(employee0);
        (*employee1).addFriend(employee2);
        (*employee1).addEnemy(employee3);
        BOOST_CHECK_EQUAL((*employee1).getMyFriends().front()->getId(), 2);
        BOOST_CHECK_EQUAL((*employee0).isFriendWith(employee1), true);
        BOOST_CHECK_EQUAL((*employee1).isFriendWith(employee0), true);
        (*employee1).addEnemy(employee0);
        BOOST_CHECK_EQUAL((*employee1).isFriendWith(employee0), false);
        BOOST_CHECK_EQUAL((*employee0).isFriendWith(employee1), false);
        BOOST_CHECK_EQUAL((*employee1).isEnemyWith(employee0), true);
        BOOST_CHECK_EQUAL((*employee0).isEnemyWith(employee1), true);
        BOOST_CHECK_EQUAL((*employee0).isEnemyWith(employee3), false);
        BOOST_CHECK_EQUAL((*employee0).isFriendWith(employee3), false);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeChangeResidencyCase, FixtureEmployeeTest) {
        (*employee0).setNonresident(true);
        BOOST_CHECK_EQUAL((*employee0).isNonresident(), true);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeSetShiftsLimitCase, FixtureEmployeeTest) {
        (*employee0).setMinShifts(5);
        (*employee0).setMaxShifts(10);
        BOOST_CHECK_EQUAL((*employee0).getMinShifts(), 5);
        BOOST_CHECK_EQUAL((*employee0).getMaxShifts(), 10);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeSetWageCase, FixtureEmployeeTest) {
        (*employee0).setHourlyWage(5);
        BOOST_CHECK_EQUAL((*employee0).getHourlyWage(), 5);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeSetPointsCase, FixtureEmployeeTest) {
        (*employee0).setPoints(5);
        BOOST_CHECK_EQUAL((*employee0).getPoints(), 5);
        (*employee0).changePoints(5);
        (*employee0).changePoints(-1);
        BOOST_CHECK_EQUAL((*employee0).getPoints(), 9);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeChangeTypeCase, FixtureEmployeeTest) {
        (*employee0).changeType(0);
        BOOST_CHECK_EQUAL((*employee0).getPriority(), 0);
        (*employee0).changeType(2);
        BOOST_CHECK_EQUAL((*employee0).getPriority(), 2);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeAddRemovePositionCase, FixtureEmployeeTest) {
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        d1 << doctor->positionInfo();
        (*employee0).addPosition(medic);
        (*employee0).addPosition(doctor);
        BOOST_CHECK_EQUAL((*employee0).getPositions().front()->positionInfo(), d1.str());
        (*employee0).removePosition(medic);
        BOOST_CHECK_EQUAL((*employee0).getPositions().front()->positionInfo(), d1.str());
        BOOST_CHECK_EQUAL((*employee0).getPositions().size(), 1);
    }


    BOOST_FIXTURE_TEST_CASE(EmployeeDesiredScheduleCase, FixtureEmployeeTest) {
        (*employee0).addDesiredShift(shift1);
        (*employee0).addDesiredShift(shift2);
        (*employee0).addDesiredShift(shift3);
        (*employee0).addDesiredShift(shift6);
        (*employee0).addDesiredShift(shift4);
        BOOST_CHECK_EQUAL((*employee0).getDesiredSchedule()[10][0]->getStartHour(), 15);
        (*employee0).removeDesiredShift(11, 1);
        BOOST_CHECK_EQUAL((*employee0).getDesiredSchedule()[10][0]->getStartHour(), 20);
        std::unique_ptr<Shift> shift7(new Shift(20, 24, 1));
        std::unique_ptr<Shift> shift8(new Shift(14, 16, 3));
        std::unique_ptr<Shift> shift9(new Shift(21, 24, 11));
        BOOST_CHECK_EQUAL((*employee0).isAvailable(shift7), false);
        BOOST_CHECK_EQUAL((*employee0).isAvailable(shift8), false);
        BOOST_CHECK_EQUAL((*employee0).isAvailable(shift9), true);
        std::unique_ptr<Shift> shift10(new Shift(20, 24, 20));
        std::unique_ptr<Shift> shift111(new Shift(0, 8, 21));
        (*employee0).addDesiredShift(shift10);
        (*employee0).addDesiredShift(shift111);
        std::unique_ptr<Shift> shift12(new Shift(21, 6, 20));
        std::unique_ptr<Shift> shift13(new Shift(21, 10, 20));
        std::unique_ptr<Shift> shift14(new Shift(20));
        BOOST_CHECK_EQUAL((*employee0).isAvailable(shift12), true);
        BOOST_CHECK_EQUAL((*employee0).isAvailable(shift13), false);
        BOOST_CHECK_EQUAL((*employee0).isAvailable(shift14), false);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeCurrentScheduleCase, FixtureEmployeeTest) {
        std::unique_ptr<Shift> shift11(new Shift(5, 10, 3));
        std::unique_ptr<Shift> shift22(new Shift(15, 20, 3));
        std::unique_ptr<Shift> shift33(new Shift(5, 10, 15));
        std::unique_ptr<Shift> shift44(new Shift(15, 19, 11));
        std::unique_ptr<Shift> shift66(new Shift(20, 24, 11));

        std::unique_ptr<Shift> shift1(new Shift(5, 10, 3));
        std::unique_ptr<Shift> shift2(new Shift(15, 20, 3));
        std::unique_ptr<Shift> shift3(new Shift(5, 10, 15));
        std::unique_ptr<Shift> shift4(new Shift(15, 19, 11));
        (*employee0).addCurrentShift(shift11);
        (*employee0).addCurrentShift(shift22);
        (*employee0).addCurrentShift(shift33);
        (*employee0).addCurrentShift(shift66);
        (*employee0).addCurrentShift(shift44);
        BOOST_CHECK_EQUAL((*employee0).getCurrentSchedule()[10][0]->getStartHour(), 15);
        (*employee0).removeCurrentShift(11, 1);
        BOOST_CHECK_EQUAL((*employee0).getCurrentSchedule()[10][0]->getStartHour(), 20);
        BOOST_CHECK_EQUAL((*employee0).getShiftsQuantity(), 4);
        BOOST_CHECK_EQUAL((*employee0).getWorkHours(), 19);
        std::unique_ptr<Shift> shift7(new Shift(18, 19, 11));
        std::unique_ptr<Shift> shift8(new Shift(9, 20, 3));
        BOOST_CHECK_EQUAL((*employee0).isBusy(shift7), false);
        BOOST_CHECK_EQUAL((*employee0).isBusy(shift8), true);
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeIsAuthorisedCase, FixtureEmployeeTest) {
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        std::shared_ptr<Position> driver = std::make_shared<DriverN>();
        (*employee0).addPosition(doctor);
        (*employee0).addPosition(medic);
        BOOST_CHECK_EQUAL((*employee0).isAuthorised(doctor), true);
        BOOST_CHECK_EQUAL((*employee0).isAuthorised(driver), false);
    }

BOOST_AUTO_TEST_SUITE_END()