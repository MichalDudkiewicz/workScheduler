#include <boost/test/unit_test.hpp>
#include "repositories/teamRepository.h"
#include "employee/employee.h"
#include "team/team.h"
#include "employee/factors/rules/employeeTypes/employeeType.h"
#include <memory>
#include "positions/medic.h"
#include "positions/doctor.h"
#include "positions/driverN.h"
#include "shift/shift.h"
#include "employee/factors/factor.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(TeamRepositoryCase) {
        std::shared_ptr<Employee> mateush = std::make_shared<Employee>("Mateusz", 3);
        std::shared_ptr<Employee> palinka = std::make_shared<Employee>("Palinka", 9);
        std::shared_ptr<Employee> michal = std::make_shared<Employee>("Michal", 2);
        std::shared_ptr<Employee> janusz = std::make_shared<Employee>("Janusz", 5);
        std::shared_ptr<Position> doctor = std::make_shared<Doctor>();
        std::shared_ptr<Position> medic = std::make_shared<Medic>();
        std::shared_ptr<Position> driver = std::make_shared<DriverN>();
        (*mateush).getFactor()->getAuthorisation().addPosition(medic);
        (*mateush).getFactor()->getAuthorisation().addPosition(doctor);
        (*palinka).getFactor()->getAuthorisation().addPosition(medic);
        (*michal).getFactor()->getAuthorisation().addPosition(doctor);
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
        TeamRepository::getInstance().add(teamS1);
        TeamRepository::getInstance().add(teamS2);
        TeamRepository::getInstance().add(team1);
        TeamRepository::getInstance().add(team2);
        BOOST_TEST_MESSAGE(TeamRepository::getInstance().info());
        BOOST_CHECK_EQUAL(TeamRepository::getInstance().get("S2")->getName(), "S2");
        BOOST_CHECK_EQUAL(TeamRepository::getInstance().getAll().size(), 4);
        TeamRepository::getInstance().remove("S1");
        BOOST_CHECK_EQUAL(TeamRepository::getInstance().getAll().size(), 3);
    }

    BOOST_AUTO_TEST_CASE(ExceptionTest) {
        std::shared_ptr<Team> teamR3 = std::make_shared<Team>("R3");
        std::shared_ptr<Team> teamR4 = std::make_shared<Team>("R3");
        TeamRepository::getInstance().add(teamR3);
        BOOST_REQUIRE_THROW(TeamRepository::getInstance().add(teamR4), std::logic_error);
        TeamRepository::getInstance().remove("R3");
        BOOST_REQUIRE_THROW(TeamRepository::getInstance().get("R3"), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()