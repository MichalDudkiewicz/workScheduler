#include <boost/test/unit_test.hpp>
#include "employee.h"
#include "team.h"
#include "doctor.h"
#include "medic.h"
#include "teamQueues.h"
#include <memory>
#include <iostream>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(TeamQueuesCase)
    {
        std::shared_ptr<Employee> palinka=std::make_shared<Employee>("Palinka",1);
        std::shared_ptr<Employee> mateusz=std::make_shared<Employee>("Mateusz",2);
        std::unique_ptr<Shift> shift1(new Shift(0,10,2));
        std::unique_ptr<Shift> shift2(new Shift(15,20,3));
        std::unique_ptr<Shift> shift3(new Shift(0,9,8));
        std::unique_ptr<Shift> shift4(new Shift(1,3,20));
        std::unique_ptr<Shift> shift5(new Shift(21,24,7));
        std::unique_ptr<Shift> shift6(new Shift(20,24,7));
        std::unique_ptr<Shift> shift7(new Shift(0,10,8));
        std::unique_ptr<Shift> shift8(new Shift(0,10,20));
        std::unique_ptr<Shift> shift9(new Shift(10,24,12));
        std::unique_ptr<Shift> shift10(new Shift(0,24,12));
        std::shared_ptr<Position> doctor=std::make_shared<Doctor>();
        std::shared_ptr<Position> medic=std::make_shared<Medic>();
        (*palinka).addDesiredShift(shift1);
        (*palinka).addDesiredShift(shift2);
        (*palinka).addDesiredShift(shift3);
        (*palinka).addDesiredShift(shift4);
        (*palinka).addDesiredShift(shift5);
        (*mateusz).addDesiredShift(shift6);
        (*mateusz).addDesiredShift(shift7);
        (*mateusz).addDesiredShift(shift8);
        (*mateusz).addDesiredShift(shift9);
        (*mateusz).addDesiredShift(shift10);
        (*mateusz).addPosition(doctor);
        (*mateusz).addPosition(medic);
        (*palinka).addPosition(medic);
        shiftsPtr shifts(new std::vector<shiftPtr>);
        positionsPtr positions(new std::vector<positionPtr>);

        std::unique_ptr<Shift> monday(new Shift(1,2,1));
        std::unique_ptr<Shift> tuesday(new Shift(22,6,2));
        std::unique_ptr<Shift> wednesday(new Shift(3));
        std::unique_ptr<Shift> thursday(new Shift(0, 7,4));
        std::unique_ptr<Shift> friday(new Shift(4,9,5));
        std::unique_ptr<Shift> saturday(new Shift(8, 16,6));
        std::unique_ptr<Shift> sunday(new Shift(20,23,7));


        std::shared_ptr<Team> team = std::make_shared<Team>("S1");
        (*team).addShift(monday);
        (*team).addShift(tuesday);
        (*team).addShift(wednesday);
        (*team).addShift(thursday);
        (*team).addShift(friday);
        (*team).addShift(saturday);
        (*team).addShift(sunday);
        (*team).addPosition(medic);
        (*team).addPosition(doctor);
        std::vector<employeePtr> employees;
        employees.push_back(mateusz);
        employees.push_back(palinka);
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
                p+=1;
                for(const auto &shift : positionQueue)
                {
                    std::cout << shift->getId() << ", ";
                }
                std::cout<<std::endl;
            }
            day+=1;
        }
    }

BOOST_AUTO_TEST_SUITE_END()