#include <boost/test/unit_test.hpp>
#include "employeeType.h"
#include "jumperEmployee.h"
#include "normalEmployee.h"
#include "needyEmployee.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(EmployeeTypesCase)
    {
        std::shared_ptr<EmployeeType> normal = std::make_shared<NormalEmployee>();
        std::shared_ptr<EmployeeType> jumper = std::make_shared<JumperEmployee>();
        std::shared_ptr<EmployeeType> needy = std::make_shared<NeedyEmployee>();
        BOOST_REQUIRE_EQUAL(normal->getType(),"normal");
        BOOST_REQUIRE_EQUAL(jumper->getType(),"jumper");
        BOOST_REQUIRE_EQUAL(needy->getType(),"needy");
        BOOST_REQUIRE_EQUAL(needy->getPriority(),2);
        BOOST_REQUIRE_EQUAL(jumper->getPriority(),0);
        BOOST_REQUIRE_EQUAL(normal->getPriority(),1);
    }

BOOST_AUTO_TEST_SUITE_END()