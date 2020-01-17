#include <boost/test/unit_test.hpp>
#include "workScheduler.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)

    BOOST_AUTO_TEST_CASE(WorkSchedulerConstructionCase) {
        WorkScheduler::getInstance().createSchedule();
//        BOOST_CHECK_EQUAL(WorkScheduler::getInstance().scheduleInfo(), "                                                                             February 2020 work schedule:\n"
//                                                                       "      S2    1    2B2C3D4\n"
//                                                                       "      S|   K|   S|\n"
//                                                                       " 1|    |    |    |\n"
//                                                                       " 2|    |    |    |\n"
//                                                                       " 3|    |    |    |\n"
//                                                                       " 4|    |    |    |\n"
//                                                                       " 5|    |    |    |\n"
//                                                                       " 6|    |    |    |\n"
//                                                                       " 7|    |    |    |\n"
//                                                                       " 8|    |    |    |\n"
//                                                                       " 9|    |    |    |\n"
//                                                                       "10|    |    |    |\n"
//                                                                       "11|    |    |    |\n"
//                                                                       "12|    |    |    |\n"
//                                                                       "13|    |    |    |\n"
//                                                                       "14|    |    |    |\n"
//                                                                       "15|    |    |    |\n"
//                                                                       "16|    |    |    |\n"
//                                                                       "17|    |    |    |\n"
//                                                                       "18|    |    |    |\n"
//                                                                       "19|    |    |    |\n"
//                                                                       "20|    |    |    |\n"
//                                                                       "21|    |    |    |\n"
//                                                                       "22|    |    |    |\n"
//                                                                       "23|    |    |    |\n"
//                                                                       "24|    |    |    |\n"
//                                                                       "25|    |    |    |\n"
//                                                                       "26|    |    |    |\n"
//                                                                       "27|    |    |    |\n"
//                                                                       "28|    |    |    |\n"
//                                                                       "29|    |    |    |\n"
//                                                                       " 1|    |    |    |\n\n");
        BOOST_TEST_MESSAGE(WorkScheduler::getInstance().scheduleInfo());
        WorkScheduler::getInstance().updateSchedule();
        BOOST_TEST_MESSAGE(WorkScheduler::getInstance().scheduleInfo());
    }

BOOST_AUTO_TEST_SUITE_END()