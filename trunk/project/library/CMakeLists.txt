cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/employee/employee.cpp
        src/team/team.cpp
        src/shift/shift.cpp
        src/positions/medic.cpp
        src/positions/medicalRecorder.cpp
        src/positions/doctor.cpp
        src/positions/rescuerN.cpp
        src/positions/rescuerS.cpp
        src/positions/driverN.cpp
        src/positions/driverS.cpp
        src/positions/dispatcher.cpp
        src/schedule/teamQueues.cpp
        src/other/calendar.cpp
        src/employee/factors/rules/employeeTypes/jumperEmployee.cpp
        src/employee/factors/rules/employeeTypes/needyEmployee.cpp
        src/employee/factors/rules/employeeTypes/normalEmployee.cpp
        src/repositories/employeeRepository.cpp
        src/repositories/teamRepository.cpp
        src/schedule/finalSchedule.cpp
        src/managers/workScheduler.cpp
        src/managers/teamManager.cpp
        src/managers/employeeManager.cpp
        include/managers/manager.h src/repositories/positionRepository.cpp include/repositories/positionRepository.h src/managers/positionManager.cpp include/managers/positionManager.h include/other/typeDefinitions.h src/employee/factors/authorisation/authorisation.cpp include/employee/factors/authorisation/authorisation.h src/employee/factors/relationship/relationship.cpp include/employee/factors/relationship/relationship.h src/employee/factors/availability/availability.cpp include/employee/factors/availability/availability.h src/employee/factors/rules/rules.cpp include/employee/factors/rules/rules.h src/employee/factors/factor.cpp include/employee/factors/factor.h src/employee/schedule/currentEmployeeSchedule.cpp include/employee/schedule/currentEmployeeSchedule.h src/employee/schedule/desiredEmployeeSchedule.cpp include/employee/schedule/desiredEmployeeSchedule.h)
#utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

#linkowanie z boost::date_time
find_package (Boost 1.60.0 COMPONENTS "date_time" REQUIRED)
target_link_libraries(Library PUBLIC Boost::date_time)

include_directories(
 ${CMAKE_CURRENT_SOURCE_DIR}/include
 ${Boost_INCLUDE_DIRS}
)

set(SOURCE_TEST_FILES
    test/master.cpp
        test/positionTest.cpp
        test/shiftTest.cpp
        test/teamTest.cpp
        test/employeeTypeTest.cpp
        test/employeeScheduleTest.cpp
        test/scheduleTest.cpp
        test/employeeTest.cpp
        test/teamQueuesTest.cpp
        test/teamRepositoryTest.cpp
        test/employeeRepositoryTest.cpp
        test/employeeManagerTest.cpp test/teamManagerTest.cpp test/finalScheduleTest.cpp test/workSchedulerTest.cpp)

add_executable (TestLibr ${SOURCE_TEST_FILES})

#dołącz bibliotekę z testowanymi klasami do programu testów
target_link_libraries (TestLibr
 Library
 ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )

#dodaj test TestBiblioteki1. Instrukcji cmake add_test może być wiele. 
#Dodatkowe parametry wpływają na szczegółowość generowanego raportu. Standardowo znajduje się on w Testing/Temporary.
add_test(TestLibrary1 TestLibr
 --report_level=detailed
 --log_level=all
 --color_output=yes
 )
add_custom_target(check ${CMAKE_COMMAND} -E env CTEST_OUTPUT_ON_FAILURE=1 BOOST_TEST_LOG_LEVEL=all
        ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> --verbose
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
