#include "boost/test/unit_test.hpp"
#include "employeeManager.h"
#include "employee.h"
#include "employeeType.h"
#include "medic.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

        BOOST_AUTO_TEST_CASE(EmployeeManagerTestCase) {
            EmployeeManager::getInstance().addEmployee(3, "Mateusz");
            EmployeeManager::getInstance().addEmployee(9, "Palinka");
            EmployeeManager::getInstance().addEmployee(2, "Michal");
            EmployeeManager::getInstance().addEmployee(5, "Janusz");
            BOOST_CHECK_EQUAL(EmployeeManager::getInstance().getEmployeeByID(9)->getName(), "Palinka");
            BOOST_CHECK_EQUAL(EmployeeManager::getInstance().repositoryInfo(), "2. Michal\n"
                                                                                  "3. Mateusz\n"
                                                                                  "5. Janusz\n"
                                                                                  "9. Palinka\n");
            BOOST_CHECK_EQUAL(EmployeeManager::getInstance().getStatisticsByID(5), "ID: 5\n"
                                                                                      "name: Janusz\n"
                                                                                      "type: normal\n"
                                                                                      "points: 0\n"
                                                                                      "hours worked: 0\n"
                                                                                      "wage/hour: 0\n"
                                                                                      "\n");
            EmployeeManager::getInstance().removeEmployee(5);
            BOOST_CHECK_EQUAL(EmployeeManager::getInstance().repositoryInfo(), "2. Michal\n"
                                                                                  "3. Mateusz\n"
                                                                                  "9. Palinka\n");
        }


BOOST_AUTO_TEST_SUITE_END()