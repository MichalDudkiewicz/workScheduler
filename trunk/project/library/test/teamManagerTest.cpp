#include "managers/teamManager.h"
#include "employee/factors/rules/employeeTypes/employeeType.h"
#include "positions/medic.h"
#include "shift/shift.h"
#include "team/team.h"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

BOOST_AUTO_TEST_CASE(TeamManagerCase)
{
    TeamManager::getInstance().addTeam("A1");
    TeamManager::getInstance().addTeam("B2");
    TeamManager::getInstance().addTeam("C3");
    TeamManager::getInstance().addTeam("D4");
    BOOST_TEST_MESSAGE(TeamManager::getInstance().info());
    TeamManager::getInstance().remove("A1");
    BOOST_TEST_MESSAGE(TeamManager::getInstance().info());
}

BOOST_AUTO_TEST_SUITE_END()