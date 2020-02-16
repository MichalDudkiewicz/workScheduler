#include <boost/test/unit_test.hpp>
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include "teamQueues.h"
#include <memory>
#include "calendar.h"
#include "shift.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct FixtureTeamQueuesTest {
        typedef std::unique_ptr<std::vector<positionPtr>> positionsPtr;
        typedef std::unique_ptr<std::vector<shiftPtr>> shiftsPtr;
        FixtureTeamQueuesTest() : shift1(new Shift(0, 10, 2)), shift2(new Shift(15, 20, 3)), shift3(new Shift(0, 9, 8)),
                                  shift4(new Shift(1, 3, 20)), shift5(new Shift(21, 24, 7)),
                                  shift6(new Shift(20, 24, 7)), shift7(new Shift(0, 10, 8)),
                                  shift8(new Shift(0, 10, 20)), shift9(new Shift(10, 24, 12)),
                                  shift10(new Shift(0, 24, 12)), shift11(new Shift(0, 8, 30)),
                                  shift12(new Shift(0, 7, 30)), shift13(new Shift(20, 24, 29)),
                                  shift14(new Shift(21, 24, 29)),
                                  shifts(new std::vector<shiftPtr>), positions(new std::vector<positionPtr>),
                                  monday(new Shift(1, 2, 1)), tuesday(new Shift(22, 6, 2)), wednesday(new Shift(3)),
                                  thursday(new Shift(0, 7, 4)), friday(new Shift(21, 5, 5)),
                                  saturday(new Shift(3, 10, 6)), sunday(new Shift(20, 23, 7)), employees() {
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift1);
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift2);
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift3);
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift4);
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift5);
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift11);
            (*palinka).getAvailability().getDesiredSchedule().addShift(shift13);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift6);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift7);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift8);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift9);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift10);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift12);
            (*mateusz).getAvailability().getDesiredSchedule().addShift(shift14);

            (*mateusz).getAuthorisation().addPosition(doctor);
            (*mateusz).getAuthorisation().addPosition(medic);
            (*palinka).getAuthorisation().addPosition(medic);

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



        std::unique_ptr<Shift> shift1;
        std::unique_ptr<Shift> shift2;
        std::unique_ptr<Shift> shift3;
        std::unique_ptr<Shift> shift4;
        std::unique_ptr<Shift> shift5;
        std::unique_ptr<Shift> shift6;
        std::unique_ptr<Shift> shift7;
        std::unique_ptr<Shift> shift8;
        std::unique_ptr<Shift> shift9;
        std::unique_ptr<Shift> shift10;
        std::unique_ptr<Shift> shift11;
        std::unique_ptr<Shift> shift12;
        std::unique_ptr<Shift> shift13;
        std::unique_ptr<Shift> shift14;

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

    BOOST_FIXTURE_TEST_CASE(TeamQueuesCaseGetTeam, FixtureTeamQueuesTest) {
        TeamQueues queue(team, employees);
        BOOST_REQUIRE_EQUAL(queue.getTeam()->getName(), "S1");
    }

    BOOST_FIXTURE_TEST_CASE(TeamQueuesCaseGetTeamQueues, FixtureTeamQueuesTest) {
        palinka -> getAuthorisation().addTeam(team);
        mateusz -> getAuthorisation().addTeam(team);
        TeamQueues queue(team, employees);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[0].at(team -> getPositions().front()).empty(), true);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[0].at(team -> getPositions().back()).empty(), true);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[1].at(team -> getPositions().front()).empty(), true);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[11].at(team -> getPositions().back()).front()->getId(), 2);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[11].at(team -> getPositions().front()).size(), 1);
    }

    BOOST_AUTO_TEST_CASE(TemaQueueTestSort){
        positionPtr doctor = std::make_shared<Doctor>();
        std::shared_ptr<Employee> employee1 = std::make_shared<Employee>("Paulina", 1);
        std::shared_ptr<Employee> employee2 = std::make_shared<Employee>("Michal", 2);
        std::shared_ptr<Employee> employee3 = std::make_shared<Employee>("Pawel", 3);
        std::shared_ptr<Employee> employee4 = std::make_shared<Employee>("Justyna", 4);
        std::shared_ptr<Employee> employee5 = std::make_shared<Employee>("Jacek", 5);
        std::list<employeePtr> employees;
        (*employee1).getAuthorisation().addPosition(doctor);
        (*employee2).getAuthorisation().addPosition(doctor);
        (*employee3).getAuthorisation().addPosition(doctor);
        (*employee4).getAuthorisation().addPosition(doctor);
        (*employee5).getAuthorisation().addPosition(doctor);
        (*employee5).getAvailability().getCurrentSchedule().addShift(1, 5, 22);
        employees.push_back(employee1);
        employees.push_back(employee2);
        employees.push_back(employee3);
        employees.push_back(employee4);
        employees.push_back(employee5);
        (*employee1).getRules().setPoints(10);
        (*employee2).getRules().setPoints(5);
        (*employee3).getRules().setPoints(22);
        (*employee4).getRules().setPoints(5);
        (*employee5).getRules().setPoints(5);
        (*employee2).getRules().changeType(2);
        (*employee3).getRules().changeType(0);
        (*employee3).getRules().changeType(2);
        boost::gregorian::date d(calendar::getStartDate());
        while(d.day_of_week()!=1)
        {
            d += boost::gregorian::days(1);
        }
        (*employee1).getAvailability().getDesiredSchedule().addShift(0, 15, d.day());
        (*employee2).getAvailability().getDesiredSchedule().addShift(2, 12, d.day());
        (*employee3).getAvailability().getDesiredSchedule().addShift(5, 14, d.day());
        (*employee4).getAvailability().getDesiredSchedule().addShift(7, 14, d.day());
        (*employee5).getAvailability().getDesiredSchedule().addShift(7, 14, d.day());
        std::shared_ptr<Team> team = std::make_shared<Team>("S1");
        employee1->getAuthorisation().addTeam(team);
        employee2->getAuthorisation().addTeam(team);
        employee3->getAuthorisation().addTeam(team);
        employee4->getAuthorisation().addTeam(team);
        employee5->getAuthorisation().addTeam(team);
        team->addShift(8,12,1);
        team->addPosition(doctor);
        TeamQueues queues(team,employees);
        queues.queueSort(d.day()-1,team -> getPositions().front());
        BOOST_CHECK_EQUAL(queues.getTeamQueues()[d.day()-1].at(team -> getPositions().front()).front(), employee3);
        BOOST_CHECK_EQUAL(queues.getTeamQueues()[d.day()-1].at(team -> getPositions().front()).back(), employee5);
        BOOST_TEST_MESSAGE(queues.teamQueuesInfo());
    }

BOOST_AUTO_TEST_SUITE_END()