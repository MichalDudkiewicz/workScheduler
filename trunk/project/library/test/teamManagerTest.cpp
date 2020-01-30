#include <boost/test/unit_test.hpp>
#include "teamManager.h"
#include "team.h"
#include "employeeType.h"
#include "medic.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(TeamManagerCase) {
        TeamManager::getInstance().addTeam("A1");
        TeamManager::getInstance().addTeam("B2");
        TeamManager::getInstance().addTeam("C3");
        TeamManager::getInstance().addTeam("D4");
        BOOST_TEST_MESSAGE(TeamManager::getInstance().info());
        TeamManager::getInstance().remove("A1");
        BOOST_TEST_MESSAGE(TeamManager::getInstance().info());
    }

BOOST_AUTO_TEST_SUITE_END()