#include "schedule/teamQueues.h"
#include "employee/employee.h"
#include "employee/factors/factor.h"
#include "positions/doctor.h"
#include "positions/medic.h"
#include "shift/shift.h"
#include "team/team.h"
#include "utils/calendar.h"
#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureTeamQueuesTest {
    typedef std::unique_ptr<std::vector<positionPtr>> positionsPtr;
    typedef std::unique_ptr<std::vector<shiftPtr>> shiftsPtr;
    FixtureTeamQueuesTest()
        : shifts(new std::vector<shiftPtr>)
        , positions(new std::vector<positionPtr>)
        , monday(new Shift(1, 2, 1))
        , tuesday(new Shift(22, 6, 2))
        , wednesday(new Shift(3))
        , thursday(new Shift(0, 7, 4))
        , friday(new Shift(21, 5, 5))
        , saturday(new Shift(3, 10, 6))
        , sunday(new Shift(20, 23, 7))
        , employees()
    {
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 10, 2);
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            15, 20, 3);
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 9, 8);
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            1, 3, 20);
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            21, 24, 7);
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 8, 30);
        (*palinka).getFactor()->getAvailability().getDesiredSchedule().addShift(
            20, 24, 29);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            20, 24, 7);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 10, 8);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 10, 20);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            10, 24, 12);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 24, 12);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            0, 7, 30);
        (*mateusz).getFactor()->getAvailability().getDesiredSchedule().addShift(
            21, 24, 29);
        (*mateusz).getFactor()->getAuthorisation().addPosition(doctor);
        (*mateusz).getFactor()->getAuthorisation().addPosition(medic);
        (*palinka).getFactor()->getAuthorisation().addPosition(medic);

        (*team).addShift(monday);
        (*team).addShift(tuesday);
        (*team).addShift(wednesday);
        (*team).addShift(thursday);
        (*team).addShift(friday);
        (*team).addShift(saturday);
        (*team).addShift(sunday);
        (*team).addPosition(medic);
        (*team).addPosition(doctor);

        employees.push_back(mateusz);
        employees.push_back(palinka);
    }

    ~FixtureTeamQueuesTest() {}

    std::shared_ptr<Employee> palinka = std::make_shared<Employee>("Palinka", 1);
    std::shared_ptr<Employee> mateusz = std::make_shared<Employee>("Mateusz", 2);

    std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
    std::shared_ptr<Position> medic = std::make_shared<Medic>();

    shiftsPtr shifts;
    positionsPtr positions;

    std::unique_ptr<Shift> monday;
    std::unique_ptr<Shift> tuesday;
    std::unique_ptr<Shift> wednesday;
    std::unique_ptr<Shift> thursday;
    std::unique_ptr<Shift> friday;
    std::unique_ptr<Shift> saturday;
    std::unique_ptr<Shift> sunday;

    std::shared_ptr<Team> team = std::make_shared<Team>("S1");

    std::list<employeePtr> employees;
};

BOOST_FIXTURE_TEST_CASE(TeamQueuesCaseGetTeam, FixtureTeamQueuesTest)
{
    TeamQueues queue(team, employees);
    BOOST_REQUIRE_EQUAL(queue.getTeam()->getName(), "S1");
}

BOOST_FIXTURE_TEST_CASE(TeamQueuesCasegetSchedule, FixtureTeamQueuesTest)
{
    palinka->getFactor()->getAuthorisation().addTeam(team);
    mateusz->getFactor()->getAuthorisation().addTeam(team);
    TeamQueues queue(team, employees);
    BOOST_REQUIRE_EQUAL(
        queue.getSchedule()[0].at(team->getPositions().front()).empty(), true);
    BOOST_REQUIRE_EQUAL(
        queue.getSchedule()[0].at(team->getPositions().back()).empty(), true);
    BOOST_REQUIRE_EQUAL(
        queue.getSchedule()[1].at(team->getPositions().front()).empty(), true);
    BOOST_REQUIRE_EQUAL(queue.getSchedule()[11]
                            .at(team->getPositions().back())
                            .front()
                            ->getId(),
        2);
    BOOST_REQUIRE_EQUAL(
        queue.getSchedule()[11].at(team->getPositions().front()).size(), 1);
}

BOOST_AUTO_TEST_CASE(TemaQueueTestSort)
{
    positionPtr doctor = std::make_shared<Doctor>();
    std::shared_ptr<Team> team = std::make_shared<Team>("S1");
    std::shared_ptr<Employee> employee1 = std::make_shared<Employee>("Paulina", 1);
    std::shared_ptr<Employee> employee2 = std::make_shared<Employee>("Michal", 2);
    std::shared_ptr<Employee> employee3 = std::make_shared<Employee>("Pawel", 3);
    std::shared_ptr<Employee> employee4 = std::make_shared<Employee>("Justyna", 4);
    std::shared_ptr<Employee> employee5 = std::make_shared<Employee>("Jacek", 5);
    std::list<employeePtr> employees;
    (*employee1).getFactor()->getAuthorisation().addPosition(doctor);
    (*employee2).getFactor()->getAuthorisation().addPosition(doctor);
    (*employee3).getFactor()->getAuthorisation().addPosition(doctor);
    (*employee4).getFactor()->getAuthorisation().addPosition(doctor);
    (*employee5).getFactor()->getAuthorisation().addPosition(doctor);
    (*employee5)
        .getFactor()
        ->getAvailability()
        .getCurrentSchedule()
        .assign(team, doctor, std::unique_ptr<Shift>(new Shift(1, 5, 22)));
    employees.push_back(employee1);
    employees.push_back(employee2);
    employees.push_back(employee3);
    employees.push_back(employee4);
    employees.push_back(employee5);
    (*employee1).getFactor()->getRules().setPoints(10);
    (*employee2).getFactor()->getRules().setPoints(5);
    (*employee3).getFactor()->getRules().setPoints(22);
    (*employee4).getFactor()->getRules().setPoints(5);
    (*employee5).getFactor()->getRules().setPoints(5);
    (*employee2).getFactor()->getRules().changeType(2);
    (*employee3).getFactor()->getRules().changeType(0);
    (*employee3).getFactor()->getRules().changeType(2);
    boost::gregorian::date d(calendar::getStartDate());
    while (d.day_of_week() != 1) {
        d += boost::gregorian::days(1);
    }
    (*employee1)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(0, 15, d.day());
    (*employee2)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(2, 12, d.day());
    (*employee3)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(5, 14, d.day());
    (*employee4)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(7, 14, d.day());
    (*employee5)
        .getFactor()
        ->getAvailability()
        .getDesiredSchedule()
        .addShift(7, 14, d.day());
    employee1->getFactor()->getAuthorisation().addTeam(team);
    employee2->getFactor()->getAuthorisation().addTeam(team);
    employee3->getFactor()->getAuthorisation().addTeam(team);
    employee4->getFactor()->getAuthorisation().addTeam(team);
    employee5->getFactor()->getAuthorisation().addTeam(team);
    team->addShift(8, 12, 1);
    team->addPosition(doctor);
    TeamQueues queues(team, employees);
    queues.queueSort(d.day() - 1, team->getPositions().front());
    BOOST_CHECK_EQUAL(queues.getSchedule()[d.day() - 1]
                          .at(team->getPositions().front())
                          .front(),
        employee3);
    BOOST_CHECK_EQUAL(queues.getSchedule()[d.day() - 1]
                          .at(team->getPositions().front())
                          .back(),
        employee5);
    BOOST_TEST_MESSAGE(queues.scheduleInfo());
}

BOOST_AUTO_TEST_SUITE_END()