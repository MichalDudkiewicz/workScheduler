#include "employee/employee.h"
#include "boost/date_time/gregorian/gregorian.hpp"
#include "employee/factors/authorisation/authorisation.h"
#include "employee/factors/factor.h"
#include "employee/factors/rules/employeeTypes/employeeType.h"
#include "positions/doctor.h"
#include "positions/driverN.h"
#include "positions/medic.h"
#include "shift/shift.h"
#include "team/team.h"
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureEmployeeTest {
    FixtureEmployeeTest()
        : date((boost::gregorian::day_clock::local_day()))
        , d1()
        , m()
    {
    }

    ~FixtureEmployeeTest() {}

    std::shared_ptr<Employee> employee0 = std::make_shared<Employee>("Mateusz", 0);
    std::shared_ptr<Employee> employee1 = std::make_shared<Employee>("Kamila", 1);
    std::shared_ptr<Employee> employee2 = std::make_shared<Employee>("Michal", 2);
    std::shared_ptr<Employee> employee3 = std::make_shared<Employee>("Janusz", 3);

    boost::gregorian::date date;

    std::ostringstream d1, m;
};

BOOST_FIXTURE_TEST_CASE(EmployeeConstructorCase, FixtureEmployeeTest)
{
    Employee employee11("Paulina", 5);
    BOOST_CHECK_EQUAL(employee11.getFactor()->getRules().getType()->getPriority(),
        1);
    BOOST_CHECK_EQUAL(employee11.getName(), "Paulina");
    BOOST_CHECK_EQUAL(employee11.getFactor()->getRules().getPoints(), 0);
    BOOST_CHECK_EQUAL(employee11.getFactor()->getRules().getType()->getType(),
        "normal");
    BOOST_CHECK_EQUAL(employee11.getId(), 5);
    BOOST_CHECK_EQUAL(employee11.getHourlyWage(), 0);
    BOOST_CHECK_EQUAL(employee11.getFactor()->getRules().getMaxShifts(), 100);
    BOOST_CHECK_EQUAL(employee11.getFactor()->getRules().getMinShifts(), 0);
    BOOST_CHECK_EQUAL(employee11.getFactor()->getRules().isNonresident(), false);
    BOOST_CHECK_EQUAL(employee11.getFactor()->getAvailability().getWorkHours(),
        0);
    BOOST_CHECK_EQUAL(
        employee11.getFactor()->getAvailability().getShiftsQuantity(), 0);
    BOOST_CHECK_EQUAL(
        employee11.getFactor()->getRelationship().getMyEnemies().size(), 0);
    BOOST_CHECK_EQUAL(
        employee11.getFactor()->getRelationship().getMyFriends().size(), 0);
    date += boost::gregorian::months(1);
    BOOST_CHECK_EQUAL(employee11.getFactor()
                          ->getAvailability()
                          .getDesiredSchedule()
                          .getSchedule()
                          .size(),
        boost::gregorian::gregorian_calendar::end_of_month_day(
            date.year(), date.month())
            + 1);
    BOOST_CHECK_EQUAL(employee11.getFactor()
                          ->getAvailability()
                          .getCurrentSchedule()
                          .getSchedule()
                          .size(),
        boost::gregorian::gregorian_calendar::end_of_month_day(
            date.year(), date.month())
            + 1);
    BOOST_CHECK_EQUAL(
        employee11.getFactor()->getAuthorisation().getPositions().size(), 0);
}

BOOST_FIXTURE_TEST_CASE(EmployeeFriendsEnemiesCase, FixtureEmployeeTest)
{
    (*employee1).getFactor()->getRelationship().addFriend(employee0);
    (*employee1).getFactor()->getRelationship().addFriend(employee2);
    (*employee1).getFactor()->getRelationship().addEnemy(employee3);
    BOOST_CHECK_EQUAL((*employee1)
                          .getFactor()
                          ->getRelationship()
                          .getMyFriends()
                          .front()
                          ->getId(),
        2);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRelationship().isFriendWith(employee1),
        true);
    BOOST_CHECK_EQUAL(
        (*employee1).getFactor()->getRelationship().isFriendWith(employee0),
        true);
    (*employee1).getFactor()->getRelationship().addEnemy(employee0);
    BOOST_CHECK_EQUAL(
        (*employee1).getFactor()->getRelationship().isFriendWith(employee0),
        false);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRelationship().isFriendWith(employee1),
        false);
    BOOST_CHECK_EQUAL(
        (*employee1).getFactor()->getRelationship().isEnemyWith(employee0), true);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRelationship().isEnemyWith(employee1), true);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRelationship().isEnemyWith(employee3),
        false);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRelationship().isFriendWith(employee3),
        false);
}

BOOST_FIXTURE_TEST_CASE(EmployeeChangeResidencyCase, FixtureEmployeeTest)
{
    (*employee0).getFactor()->getRules().setNonresident(true);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getRules().isNonresident(), true);
}

BOOST_FIXTURE_TEST_CASE(EmployeeSetShiftsLimitCase, FixtureEmployeeTest)
{
    (*employee0).getFactor()->getRules().setMinShifts(5);
    (*employee0).getFactor()->getRules().setMaxShifts(10);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getRules().getMinShifts(), 5);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getRules().getMaxShifts(), 10);
}

BOOST_FIXTURE_TEST_CASE(EmployeeSetWageCase, FixtureEmployeeTest)
{
    (*employee0).setHourlyWage(5);
    BOOST_CHECK_EQUAL((*employee0).getHourlyWage(), 5);
}

BOOST_FIXTURE_TEST_CASE(EmployeeSetPointsCase, FixtureEmployeeTest)
{
    (*employee0).getFactor()->getRules().setPoints(5);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getRules().getPoints(), 5);
    (*employee0).getFactor()->getRules().changePoints(5);
    (*employee0).getFactor()->getRules().changePoints(-1);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getRules().getPoints(), 9);
}

BOOST_FIXTURE_TEST_CASE(EmployeeChangeTypeCase, FixtureEmployeeTest)
{
    (*employee0).getFactor()->getRules().changeType(0);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRules().getType()->getPriority(), 0);
    (*employee0).getFactor()->getRules().changeType(2);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getRules().getType()->getPriority(), 2);
}

BOOST_FIXTURE_TEST_CASE(EmployeeAddRemovePositionCase, FixtureEmployeeTest)
{
    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> medic = std::make_shared<Medic>();
    d1 << doctor->positionInfo();
    (*employee0).getFactor()->getAuthorisation().addPosition(medic);
    (*employee0).getFactor()->getAuthorisation().addPosition(doctor);
    BOOST_CHECK_EQUAL((*employee0)
                          .getFactor()
                          ->getAuthorisation()
                          .getPositions()
                          .front()
                          ->positionInfo(),
        d1.str());
    (*employee0).getFactor()->getAuthorisation().removePosition(medic);
    BOOST_CHECK_EQUAL((*employee0)
                          .getFactor()
                          ->getAuthorisation()
                          .getPositions()
                          .front()
                          ->positionInfo(),
        d1.str());
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAuthorisation().getPositions().size(), 1);
}

BOOST_FIXTURE_TEST_CASE(EmployeeDesiredScheduleCase, FixtureEmployeeTest)
{
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(5, 10, 3);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(15, 20, 3);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(5, 10, 15);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(20, 24, 11);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(15, 19, 11);
    BOOST_CHECK_EQUAL((*employee0)
                          .getFactor()
                          ->getAvailability()
                          .getDesiredSchedule()
                          .getSchedule()[10][0]
                          ->getStartHour(),
        15);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .removeShift(11, 1);
    BOOST_CHECK_EQUAL((*employee0)
                          .getFactor()
                          ->getAvailability()
                          .getDesiredSchedule()
                          .getSchedule()[10][0]
                          ->getStartHour(),
        20);
    std::unique_ptr<Shift> shift7(new Shift(20, 24, 1));
    std::unique_ptr<Shift> shift8(new Shift(14, 16, 3));
    std::unique_ptr<Shift> shift9(new Shift(21, 24, 11));
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().isAvailable(shift7), false);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().isAvailable(shift8), false);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().isAvailable(shift9), true);
    std::unique_ptr<Shift> shift10(new Shift(20, 24, 20));
    std::unique_ptr<Shift> shift111(new Shift(0, 8, 21));
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(20, 24, 20);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(0, 8, 21);
    std::unique_ptr<Shift> shift12(new Shift(21, 6, 20));
    std::unique_ptr<Shift> shift13(new Shift(21, 10, 20));
    std::unique_ptr<Shift> shift14(new Shift(20));
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().isAvailable(shift12), true);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().isAvailable(shift13), false);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().isAvailable(shift14), false);
}

BOOST_FIXTURE_TEST_CASE(EmployeeCurrentScheduleCase, FixtureEmployeeTest)
{
    std::unique_ptr<Shift> shift11(new Shift(5, 10, 3));
    std::unique_ptr<Shift> shift22(new Shift(15, 20, 3));
    std::unique_ptr<Shift> shift33(new Shift(5, 10, 15));
    std::unique_ptr<Shift> shift44(new Shift(15, 19, 11));
    std::unique_ptr<Shift> shift66(new Shift(20, 24, 11));

    std::unique_ptr<Shift> shift1(new Shift(5, 10, 3));
    std::unique_ptr<Shift> shift2(new Shift(15, 20, 3));
    std::unique_ptr<Shift> shift3(new Shift(5, 10, 15));
    std::unique_ptr<Shift> shift4(new Shift(15, 19, 11));

    positionPtr doctor = std::make_shared<Doctor>();
    teamPtr team = std::make_shared<Team>("S1");

    (*employee0)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .assign(team, doctor, std::move(shift11));
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .assign(team, doctor, std::move(shift22));
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .assign(team, doctor, std::move(shift33));
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .assign(team, doctor, std::move(shift66));
    BOOST_CHECK_EQUAL((*employee0)
                              .getFactor()
                              ->getAvailability()
                              .getCurrentSchedule()
                              .getSchedule()[10].front().position
                              ->positionInfo(),
                      "doctor");
    BOOST_CHECK_EQUAL((*employee0)
                              .getFactor()
                              ->getAvailability()
                              .getCurrentSchedule()
                              .getSchedule()[10].front().team
                              ->getName(),
                      "S1");

    teamPtr team2 = std::make_shared<Team>("S2");
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .assign(team2, doctor, std::move(shift4));

    BOOST_CHECK_EQUAL((*employee0)
                              .getFactor()
                              ->getAvailability()
                              .getCurrentSchedule()
                              .getSchedule()[10].front().team
                              ->getName(),
                      "S2");

    BOOST_CHECK_EQUAL((*employee0)
                          .getFactor()
                          ->getAvailability()
                          .getCurrentSchedule()
                          .getSchedule()[10].front().shift
                          ->getStartHour(),
        15);
    BOOST_CHECK_EQUAL((*employee0)
                              .getFactor()
                              ->getAvailability()
                              .getCurrentSchedule()
                              .getSchedule()[10].size(),
                      2);
    (*employee0)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .removeAssignment(team2, 11);

    BOOST_CHECK_EQUAL((*employee0)
                              .getFactor()
                              ->getAvailability()
                              .getCurrentSchedule()
                              .getSchedule()[10].front().team
                              ->getName(),
                      "S1");
    BOOST_CHECK_EQUAL((*employee0)
                          .getFactor()
                          ->getAvailability()
                          .getCurrentSchedule()
                          .getSchedule()[10].front().shift
                          ->getStartHour(),
        20);
    BOOST_CHECK_EQUAL((*employee0)
                              .getFactor()
                              ->getAvailability()
                              .getCurrentSchedule()
                              .getSchedule()[10].size(),
                      1);
    BOOST_CHECK_EQUAL(
        (*employee0).getFactor()->getAvailability().getShiftsQuantity(), 4);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getAvailability().getWorkHours(),
        19);
    std::unique_ptr<Shift> shift7(new Shift(18, 19, 11));
    std::unique_ptr<Shift> shift8(new Shift(9, 20, 3));
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getAvailability().isBusy(shift7),
        false);
    BOOST_CHECK_EQUAL((*employee0).getFactor()->getAvailability().isBusy(shift8),
        true);
}

BOOST_FIXTURE_TEST_CASE(EmployeeIsAuthorisedCase, FixtureEmployeeTest)
{
    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> medic = std::make_shared<Medic>();
    std::shared_ptr<Position> driver = std::make_shared<DriverN>();
    (*employee0).getFactor()->getAuthorisation().addPosition(doctor);
    (*employee0).getFactor()->getAuthorisation().addPosition(medic);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().positionMatch(doctor), true);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().positionMatch(driver), false);
}

BOOST_FIXTURE_TEST_CASE(EmployeeAddTeamCase, FixtureEmployeeTest)
{
    std::shared_ptr<Team> team = std::make_shared<Team>("S1");
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().getTeams().size(), 0);
    BOOST_CHECK_EQUAL(employee0->getFactor()->getAuthorisation().teamMatch(team),
        false);
    employee0->getFactor()->getAuthorisation().addTeam(team);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().getTeams().size(), 1);
    BOOST_CHECK_EQUAL(employee0->getFactor()->getAuthorisation().teamMatch(team),
        true);
}

BOOST_FIXTURE_TEST_CASE(EmployeeAuthorisationCase, FixtureEmployeeTest)
{
    std::shared_ptr<Team> team1 = std::make_shared<Team>("S1");
    std::shared_ptr<Team> team2 = std::make_shared<Team>("S2");
    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> medic = std::make_shared<Medic>();
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(doctor, team1),
        false);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(medic, team2),
        false);
    employee0->getFactor()->getAuthorisation().addTeam(team1);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(doctor, team1),
        false);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(medic, team2),
        false);
    employee0->getFactor()->getAuthorisation().addTeam(team2);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(doctor, team1),
        false);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(medic, team2),
        false);
    employee0->getFactor()->getAuthorisation().addPosition(doctor);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(doctor, team1),
        true);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(medic, team2),
        false);
    employee0->getFactor()->getAuthorisation().addPosition(medic);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(doctor, team1),
        true);
    BOOST_CHECK_EQUAL(
        employee0->getFactor()->getAuthorisation().isAuthorised(medic, team2),
        true);
}

BOOST_AUTO_TEST_SUITE_END()