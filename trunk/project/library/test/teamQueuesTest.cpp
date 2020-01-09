#include <boost/test/unit_test.hpp>
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include "teamQueues.h"
#include <memory>
#include "schedule.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

struct FixtureTeamQueuesTest{
    FixtureTeamQueuesTest() : shift1(new Shift(0,10,2)), shift2(new Shift(15,20,3)), shift3(new Shift(0,9,8)), shift4(new Shift(1,3,20)), shift5(new Shift(21,24,7)), shift6(new Shift(20,24,7)), shift7(new Shift(0,10,8)),
    shift8(new Shift(0,10,20)), shift9(new Shift(10,24,12)), shift10(new Shift(0,24,12)), shift11(new Shift(0,8,30)), shift12(new Shift(0,7,30)), shift13(new Shift(20,24,29)), shift14(new Shift(21,24,29)),
    shifts(new std::vector<shiftPtr>), positions(new std::vector<positionPtr>), monday(new Shift(1,2,1)), tuesday(new Shift(22,6,2)), wednesday(new Shift(3)), thursday(new Shift(0, 7,4)), friday(new Shift(21,5,5)),
    saturday(new Shift(3,10,6)), sunday(new Shift(20,23,7)), employees(){
        (*palinka).addDesiredShift(shift1);
        (*palinka).addDesiredShift(shift2);
        (*palinka).addDesiredShift(shift3);
        (*palinka).addDesiredShift(shift4);
        (*palinka).addDesiredShift(shift5);
        (*palinka).addDesiredShift(shift11);
        (*palinka).addDesiredShift(shift13);
        (*mateusz).addDesiredShift(shift6);
        (*mateusz).addDesiredShift(shift7);
        (*mateusz).addDesiredShift(shift8);
        (*mateusz).addDesiredShift(shift9);
        (*mateusz).addDesiredShift(shift10);
        (*mateusz).addDesiredShift(shift12);
        (*mateusz).addDesiredShift(shift14);

        (*mateusz).addPosition(doctor);
        (*mateusz).addPosition(medic);
        (*palinka).addPosition(medic);

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

    std::shared_ptr<Employee> palinka=std::make_shared<Employee>("Palinka",1);
    std::shared_ptr<Employee> mateusz=std::make_shared<Employee>("Mateusz",2);

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

    std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
    std::shared_ptr<Position> medic=std::make_shared<Medic>();

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

    std::vector<employeePtr> employees;


};

    BOOST_FIXTURE_TEST_CASE(TeamQueuesCaseGetTeam, FixtureTeamQueuesTest)
    {
        TeamQueues queue(team,employees);
        BOOST_REQUIRE_EQUAL(queue.getTeam()->getName(), "S1");
    }

    BOOST_FIXTURE_TEST_CASE(TeamQueuesCaseGetId, FixtureTeamQueuesTest)
    {
        TeamQueues queue(team,employees);
        BOOST_REQUIRE_EQUAL(queue.getAuthorisedEmployees()[0]->getId(), 2);
        BOOST_REQUIRE_EQUAL(queue.getAuthorisedEmployees()[1]->getId(), 1);
    }

    BOOST_FIXTURE_TEST_CASE(TeamQueuesCaseGetTeamQueues, FixtureTeamQueuesTest)
    {
        TeamQueues queue(team,employees);
        unsigned int day=1;
        unsigned int p;
        for(const auto &dayQueue : queue.getTeamQueues())
        {
            std::cout<<"Day "<<day<<" shifts queue: "<<std::endl;
            p=0;
            for(const auto &positionQueue : dayQueue)
            {
                std::cout<<queue.getTeam()->getPositions()[p]->positionInfo()<<": ";
                for(const auto &shift : positionQueue)
                {
                    std::cout << shift->getId() << ", ";
                }
                std::cout<<std::endl;
                p+=1;
            }
            day+=1;
        }
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[0][0].empty(), true);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[0][1].empty(), true);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[1][0].empty(), true);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[7][1][0]->getId(), 2);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[6][0][0]->getId(), 2);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[6][1][0]->getId(), 2);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[6][1][1]->getId(), 1);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[11][0][0]->getId(), 2);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[11][1][0]->getId(), 2);
        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[19][0].size(), 1);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[19][1].size(), 2);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[30][0].size(), 1);
//        BOOST_REQUIRE_EQUAL(queue.getTeamQueues()[30][1].size(), 2);
    }

BOOST_AUTO_TEST_SUITE_END()