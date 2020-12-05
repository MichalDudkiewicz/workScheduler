cmake_minimum_required(VERSION 3.4)
set(CMAKE_CXX_FLAGS "-Wall -Wpedantic -Wextra -Weffc++ -Werror")
project(workScheduler)
enable_language(CXX)
IF (WIN32)
    # set boost for windows
ELSE()
    set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/thirdparty/linux/boost/boost_1_60_0/include)
ENDIF()
add_subdirectory(library)
add_subdirectory(program)
enable_testing()

