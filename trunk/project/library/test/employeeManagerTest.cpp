#include "boost/test/unit_test.hpp"
#include "employeeManager.h"
#include "employee.h"
#include "employeeType.h"
#include "medic.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeManagerTestCase) {
        EmployeeManager::getInstance().add(7, "Monika");
        EmployeeManager::getInstance().add(8, "Krzysztof");
        EmployeeManager::getInstance().add(6, "Adam");
        EmployeeManager::getInstance().add(4, "Katarzyna");
        BOOST_CHECK_EQUAL(EmployeeManager::getInstance().get(7)->getName(), "Monika");
        BOOST_TEST_MESSAGE(EmployeeManager::getInstance().info());
        BOOST_CHECK_EQUAL(EmployeeManager::getInstance().getStatisticsByID(4), "ID: 4\n"
                                                                               "name: Katarzyna\n"
                                                                               "type: normal\n"
                                                                               "points: 0\n"
                                                                               "hours worked: 0\n"
                                                                               "wage/hour: 0\n"
                                                                               "\n");
        EmployeeManager::getInstance().remove(6);
        BOOST_TEST_MESSAGE(EmployeeManager::getInstance().info());
    }


BOOST_AUTO_TEST_SUITE_END()