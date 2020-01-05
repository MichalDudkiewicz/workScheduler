#include <boost/test/unit_test.hpp>
#include "teamRepository.h"
#include <employee.h>
#include <team.h>
#include <employeeType.h>
#include <memory>
#include "medic.h"
#include "doctor.h"
#include "driverN.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(TeamRepositoryCase)
    {
        TeamRepository *repository;
        repository = TeamRepository::getInstance();
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz",3);
        std::shared_ptr<Employee> palinka = std::make_shared<Employee>("Palinka",9);
        std::shared_ptr<Employee> michal = std::make_shared<Employee>("Michal",2);
        std::shared_ptr<Employee> janusz = std::make_shared<Employee>("Janusz",5);
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        std::shared_ptr<Position> driver = std::make_shared<DriverN>();
        (*mateush).addPosition(medic);
        (*mateush).addPosition(doctor);
        (*palinka).addPosition(medic);
        (*michal).addPosition(doctor);
        std::shared_ptr<Team> teamS1 = std::make_shared<Team>("S1");
        std::shared_ptr<Team> teamS2 = std::make_shared<Team>("S2");
        std::shared_ptr<Team> team1 = std::make_shared<Team>("1");
        std::shared_ptr<Team> team2 = std::make_shared<Team>("2");
        (*teamS1).addPosition(doctor);
        (*teamS1).addPosition(medic);
        (*teamS1).addPosition(driver);
        (*teamS2).addPosition(medic);
        (*team1).addPosition(driver);
        (*team2).addPosition(medic);
        (*repository).addTeam(teamS1);
        (*repository).addTeam(teamS2);
        (*repository).addTeam(team1);
        (*repository).addTeam(team2);
        BOOST_CHECK_EQUAL((*repository).repositoryInfo(),"Team S1\n"
                                                      "Positions required: doctor, driver (normal), medic, \n"
                                                      "Team shifts: \n"
                                                      "Monday: day: 1, 0 - 0\n"
                                                      "Tuesday: day: 2, 0 - 0\n"
                                                      "Wednesday: day: 3, 0 - 0\n"
                                                      "Thursday: day: 4, 0 - 0\n"
                                                      "Friday: day: 5, 0 - 0\n"
                                                      "Saturday: day: 6, 0 - 0\n"
                                                      "Sunday: day: 7, 0 - 0\n"
                                                      "\n"
                                                      "\n"
                                                      "Team S2\n"
                                                      "Positions required: medic, \n"
                                                      "Team shifts: \n"
                                                      "Monday: day: 1, 0 - 0\n"
                                                      "Tuesday: day: 2, 0 - 0\n"
                                                      "Wednesday: day: 3, 0 - 0\n"
                                                      "Thursday: day: 4, 0 - 0\n"
                                                      "Friday: day: 5, 0 - 0\n"
                                                      "Saturday: day: 6, 0 - 0\n"
                                                      "Sunday: day: 7, 0 - 0\n"
                                                      "\n"
                                                      "\n"
                                                      "Team 1\n"
                                                      "Positions required: driver (normal), \n"
                                                      "Team shifts: \n"
                                                      "Monday: day: 1, 0 - 0\n"
                                                      "Tuesday: day: 2, 0 - 0\n"
                                                      "Wednesday: day: 3, 0 - 0\n"
                                                      "Thursday: day: 4, 0 - 0\n"
                                                      "Friday: day: 5, 0 - 0\n"
                                                      "Saturday: day: 6, 0 - 0\n"
                                                      "Sunday: day: 7, 0 - 0\n"
                                                      "\n"
                                                      "\n"
                                                      "Team 2\n"
                                                      "Positions required: medic, \n"
                                                      "Team shifts: \n"
                                                      "Monday: day: 1, 0 - 0\n"
                                                      "Tuesday: day: 2, 0 - 0\n"
                                                      "Wednesday: day: 3, 0 - 0\n"
                                                      "Thursday: day: 4, 0 - 0\n"
                                                      "Friday: day: 5, 0 - 0\n"
                                                      "Saturday: day: 6, 0 - 0\n"
                                                      "Sunday: day: 7, 0 - 0\n"
                                                      "\n"
                                                      "\n");
        BOOST_CHECK_EQUAL((*repository).getTeamByName("S2")->getName(),"S2");
        BOOST_CHECK_EQUAL((*repository).getAll()[0]->getName(),"S1");
        BOOST_CHECK_EQUAL((*repository).getAll().size(),4);
        (*repository).removeTeam("S1");
        BOOST_CHECK_EQUAL((*repository).getAll()[0]->getName(),"S2");
        BOOST_CHECK_EQUAL((*repository).getAll().size(),3);
    }

BOOST_AUTO_TEST_SUITE_END()