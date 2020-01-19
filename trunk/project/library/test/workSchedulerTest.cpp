#include <boost/test/unit_test.hpp>
#include "workScheduler.h"
#include "employeeRepository.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(WorkSchedulerConstructionCase) {
        WorkScheduler::getInstance().createSchedule();
        BOOST_TEST_MESSAGE(WorkScheduler::getInstance().scheduleInfo());
        WorkScheduler::getInstance().updateSchedule();
        BOOST_TEST_MESSAGE(WorkScheduler::getInstance().scheduleInfo());
    }

BOOST_AUTO_TEST_SUITE_END()