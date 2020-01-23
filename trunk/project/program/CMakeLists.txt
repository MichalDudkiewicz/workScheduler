cmake_minimum_required(VERSION 3.4)

project(Program)

#ustaw we własnej zmiennej SOURCE_FILES zbiór plików źródłowych projektu
set(SOURCE_FILES
        src/main.cpp
        src/fileStream.cpp
        )
#włącz powyższy zbiór plików do zbudowania programu wykonywalnego Program
add_executable(Program ${SOURCE_FILES})
#Określenie zależności pomiędzy projektami Program i Biblioteka
target_link_libraries(Program Library)
#dołącz katalog include podprojektu Program do globalnej listy. Dzięki temu każdy inny podprojekt będzie ten katalog "widział"
target_include_directories(Program PUBLIC include)

################################################
#TESTS PROGRAM:

enable_testing()

find_package (Boost 1.60.0 COMPONENTS "unit_test_framework" REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

set(SOURCE_TEST_FILES
        test/fileStreamTest.cpp
        test/master.cpp
        src/fileStream.cpp include/fileStream.h
        )

add_executable (TestProgram ${SOURCE_TEST_FILES})

target_include_directories(TestProgram PUBLIC include)

target_link_libraries (TestProgram
        Library
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        )


add_test(TestProgram1 TestProgram
        --report_level=detailed
        --log_level=all
        --color_output=yes
        )