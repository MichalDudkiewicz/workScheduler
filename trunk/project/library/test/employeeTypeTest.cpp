#include <boost/test/unit_test.hpp>
#include "employee/factors/rules/employeeTypes/employeeType.h"
#include "employee/factors/rules/employeeTypes/jumperEmployee.h"
#include "employee/factors/rules/employeeTypes/normalEmployee.h"
#include "employee/factors/rules/employeeTypes/needyEmployee.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct FixtureEmployeeTypeTest {
        FixtureEmployeeTypeTest() {}

        ~FixtureEmployeeTypeTest() {}

        std::shared_ptr<EmployeeType> normal = std::make_shared<NormalEmployee>();
        std::shared_ptr<EmployeeType> jumper = std::make_shared<JumperEmployee>();
        std::shared_ptr<EmployeeType> needy = std::make_shared<NeedyEmployee>();
    };

    BOOST_FIXTURE_TEST_CASE(EmployeeTypesCaseGetType, FixtureEmployeeTypeTest) {
        BOOST_REQUIRE_EQUAL(normal->getType(), "normal");
        BOOST_REQUIRE_EQUAL(jumper->getType(), "jumper");
        BOOST_REQUIRE_EQUAL(needy->getType(), "needy");
    }

    BOOST_FIXTURE_TEST_CASE(EmployeeTypesCaseGetPriority, FixtureEmployeeTypeTest) {
        BOOST_REQUIRE_EQUAL(needy->getPriority(), 2);
        BOOST_REQUIRE_EQUAL(jumper->getPriority(), 0);
        BOOST_REQUIRE_EQUAL(normal->getPriority(), 1);
    }

BOOST_AUTO_TEST_SUITE_END()