cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/employee.cpp
        src/team.cpp
        src/shift.cpp
        src/medic.cpp
        src/medicalRecorder.cpp
        src/doctor.cpp
        src/rescuerN.cpp
        src/rescuerS.cpp
        src/driverN.cpp
        src/driverS.cpp
        src/dispatcher.cpp
        src/teamQueues.cpp
        src/calendar.cpp
        src/employeeSchedule.cpp
        src/jumperEmployee.cpp
        src/needyEmployee.cpp
        src/normalEmployee.cpp
        src/employeeRepository.cpp
        src/teamRepository.cpp
        src/finalSchedule.cpp
        src/workScheduler.cpp
        src/teamManager.cpp
        src/employeeManager.cpp
        )
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
