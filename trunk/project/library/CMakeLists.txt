cmake_minimum_required(VERSION 3.4)
project(Library)

set(SOURCE_FILES
        src/employee.cpp
        include/employee.h
        src/team.cpp
        include/team.h
        src/shift.cpp
        include/shift.h
        include/position.h
        include/ambulance.h
        include/doctor.h
        include/dispatcher.h
        include/sTeam.h
        include/driverN.h
        include/driverS.h
        include/medic.h
        include/nTeam.h
        include/rescuerN.h
        include/rescuerS.h
        include/medicalRecorder.h
        src/medic.cpp
        src/medicalRecorder.cpp
        src/doctor.cpp
        src/rescuerN.cpp
        src/rescuerS.cpp
        src/driverN.cpp
        src/driverS.cpp
        src/dispatcher.cpp
        src/teamQueues.cpp
        include/teamQueues.h
        include/schedule.h
        src/schedule.cpp
        src/employeeSchedule.cpp
        include/employeeSchedule.h
        include/employeeType.h
        include/jumperEmployee.h
        include/normalEmployee.h
        include/needyEmployee.h
        src/jumperEmployee.cpp
        src/needyEmployee.cpp
        src/normalEmployee.cpp
        src/employeeRepository.cpp
        include/employeeRepository.h
        src/teamRepository.cpp
        include/teamRepository.h
        )
#utwórz bibliotekę typu STATIC, SHARED albo MODULE ze wskazanych źródeł
add_library(Library ${SOURCE_FILES})

target_include_directories(Library PUBLIC include)
enable_testing()
find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

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
        test/employeeRepositoryTest.cpp
        test/teamRepositoryTest.cpp
        )

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
