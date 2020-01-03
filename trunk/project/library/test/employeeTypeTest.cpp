#include <boost/test/unit_test.hpp>
#include "employeeType.h"
#include "jumperEmployee.h"
#include "normalEmployee.h"
#include "needyEmployee.h"
#include <memory>

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    struct MyGlobalFixture {
        MyGlobalFixture() {
            normal = std::make_shared<NormalEmployee>();
            jumper = std::make_shared<JumperEmployee>();
            needy = std::make_shared<NeedyEmployee>();}
        ~MyGlobalFixture() {}
        static std::shared_ptr<EmployeeType> normal;
        static std::shared_ptr<EmployeeType> jumper;
        static std::shared_ptr<EmployeeType> needy;
    };
    std::shared_ptr<EmployeeType> MyGlobalFixture::normal = std::make_shared<NormalEmployee>();
    std::shared_ptr<EmployeeType> MyGlobalFixture::jumper = std::make_shared<JumperEmployee>();
    std::shared_ptr<EmployeeType> MyGlobalFixture::needy = std::make_shared<NeedyEmployee>();

    BOOST_TEST_GLOBAL_FIXTURE( MyGlobalFixture );

    BOOST_AUTO_TEST_CASE(EmployeeTypesCaseGetType)
    {
        BOOST_REQUIRE_EQUAL(MyGlobalFixture::normal->getType(),"normal");
        BOOST_REQUIRE_EQUAL(MyGlobalFixture::jumper->getType(),"jumper");
        BOOST_REQUIRE_EQUAL(MyGlobalFixture::needy->getType(),"needy");
    }
    BOOST_AUTO_TEST_CASE(EmployeeTypesCaseGetPriority)
    {
        BOOST_REQUIRE_EQUAL(MyGlobalFixture::needy->getPriority(),2);
        BOOST_REQUIRE_EQUAL(MyGlobalFixture::jumper->getPriority(),0);
        BOOST_REQUIRE_EQUAL(MyGlobalFixture::normal->getPriority(),1);
    }

BOOST_AUTO_TEST_SUITE_END()