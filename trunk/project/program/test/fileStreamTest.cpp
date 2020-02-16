#include <boost/test/unit_test.hpp>
#include "fileStream.h"
#include "teamRepository.h"
#include "employeeRepository.h"
#include "employee.h"
#include "team.h"
#include "shift.h"
#include "workScheduler.h"

BOOST_AUTO_TEST_SUITE(TestSuiteCorrect)


    BOOST_AUTO_TEST_CASE(InputIncorrectPathCase) {
        input::loadPositions();
        BOOST_REQUIRE_THROW(input::employeeRepository("../../../dataset/some_directory/employeeRepository.csv"), std::logic_error);
        BOOST_REQUIRE_THROW(input::teamRepository("../../../dataset/some_directory/teamRepository.csv"), std::logic_error);
        input::employeeRepository("../../../dataset/.test/employeeRepository.csv");
        input::teamRepository("../../../dataset/.test/teamRepository.csv");
        BOOST_REQUIRE_THROW(input::teamSchedule("../../../dataset/some_directory/teamSchedule.csv"), std::logic_error);
        BOOST_REQUIRE_THROW(input::desiredSchedule("../../../dataset/some_directory/desiredSchedule.csv"), std::logic_error);

    }

    BOOST_AUTO_TEST_CASE(InputIncorrectEmployeeTeamCase) {
        TeamRepository::getInstance().remove("S1");
        BOOST_REQUIRE_THROW(input::teamSchedule("../../../dataset/.test/teamSchedule.csv"), std::logic_error);
        EmployeeRepository::getInstance().remove(1);
        BOOST_REQUIRE_THROW(input::desiredSchedule("../../../dataset/.test/desiredSchedule.csv"), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(RepositoryCreationCase) {
        BOOST_REQUIRE_EQUAL(TeamRepository::getInstance().getAll().size(),15);
        BOOST_REQUIRE_EQUAL(EmployeeRepository::getInstance().getAll().size(),70);
    }

    BOOST_AUTO_TEST_CASE(SchedulesCreationCase) {
        EmployeeRepository::getInstance().add(1,"Michal");
        TeamRepository::getInstance().add("S1");
        input::teamSchedule("../../../dataset/.test/teamSchedule.csv");
        input::desiredSchedule("../../../dataset/.test/desiredSchedules.csv");
        BOOST_REQUIRE_EQUAL(EmployeeRepository::getInstance().get(2)->getEmployeeSchedules().desiredScheduleInfo(),"day: 1, 0 - 24\n"
                "day: 3, 0 - 24\n"
                                                                                            "day: 8, 0 - 24\n"
                                                                                            "day: 9, 0 - 24\n"
                                                                                            "day: 10, 0 - 24\n"
                                                                                            "day: 13, 0 - 24\n"
                                                                                            "day: 14, 0 - 24\n"
                                                                                            "day: 18, 0 - 24\n"
                                                                                            "day: 19, 0 - 24\n"
                                                                                            "day: 22, 0 - 24\n"
                                                                                            "day: 24, 0 - 24\n"
                                                                                            "day: 25, 0 - 24\n"
                                                                                            "day: 26, 0 - 24\n"
                                                                                            "day: 28, 0 - 24\n"
                                                                                            "day: 29, 0 - 24\n");
        BOOST_REQUIRE_EQUAL(TeamRepository::getInstance().get("S2")->teamInfo(),"Team S2\nPositions required: doctor, driver (special), rescuer (special), \n"
                                                                                "Team shifts: \n"
                                                                                "Monday: day: 1, 7 - 19\n"
                                                                                "Tuesday: day: 2, 7 - 19\n"
                                                                                "Wednesday: day: 3, 7 - 19\n"
                                                                                "Thursday: day: 4, 7 - 19\n"
                                                                                "Friday: day: 5, 7 - 19\n"
                                                                                "Saturday: day: 6, 9 - 21\n"
                                                                                "Sunday: day: 7, 9 - 21\n\n");
    }

    BOOST_AUTO_TEST_CASE(OutputIncorrectPathCase) {
        WorkScheduler::getInstance().createSchedule();
        BOOST_REQUIRE_THROW(output::employeeRepository("../../../dataset/some_directory/employeeRepository.csv"), std::logic_error);
        BOOST_REQUIRE_THROW(output::teamRepository("../../../dataset/some_directory/teamRepository.csv"), std::logic_error);
        BOOST_REQUIRE_THROW(output::teamSchedule("../../../dataset/some_directory/teamSchedule.csv"), std::logic_error);
        BOOST_REQUIRE_THROW(output::desiredSchedule("../../../dataset/some_directory/desiredSchedule.csv"), std::logic_error);
        BOOST_REQUIRE_THROW(output::schedule("../../../dataset/some_directory/schedule.csv"), std::logic_error);
    }

BOOST_AUTO_TEST_SUITE_END()