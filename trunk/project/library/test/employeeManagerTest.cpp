#include "boost/test/unit_test.hpp"
#include "employeeManager.h"
#include "employee.h"
#include "employeeType.h"
#include "medic.h"
#include "shift.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeManagerTestCase) {
        EmployeeManager::getInstance().addEmployee(7, "Monika");
        EmployeeManager::getInstance().addEmployee(8, "Krzysztof");
        EmployeeManager::getInstance().addEmployee(6, "Adam");
        EmployeeManager::getInstance().addEmployee(4, "Katarzyna");
        BOOST_CHECK_EQUAL(EmployeeManager::getInstance().getEmployeeByID(7)->getName(), "Monika");
        BOOST_CHECK_EQUAL(EmployeeManager::getInstance().repositoryInfo(), "2. Michal\n"
                                                                           "3. Mateusz\n"
                                                                           "4. Katarzyna\n"
                                                                           "6. Adam\n"
                                                                           "7. Monika\n"
                                                                           "8. Krzysztof\n"
                                                                           "9. Paulina\n");
        BOOST_CHECK_EQUAL(EmployeeManager::getInstance().getStatisticsByID(4), "ID: 4\n"
                                                                               "name: Katarzyna\n"
                                                                               "type: normal\n"
                                                                               "points: 0\n"
                                                                               "hours worked: 0\n"
                                                                               "wage/hour: 0\n"
                                                                               "\n");
        EmployeeManager::getInstance().removeEmployee(6);
        BOOST_CHECK_EQUAL(EmployeeManager::getInstance().repositoryInfo(), "2. Michal\n"
                                                                           "3. Mateusz\n"
                                                                           "4. Katarzyna\n"
                                                                           "7. Monika\n"
                                                                           "8. Krzysztof\n"
                                                                           "9. Paulina\n");
    }


BOOST_AUTO_TEST_SUITE_END()