## CMake build file for the {{ cookiecutter.app_name }} application test suite.
##
## This will build a Google Test test runner for all contained tests.
##
project(test_{{ cookiecutter.app_name }})

add_subdirectory(lib/gtest)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${gtest_SOURCE_DIR} 
    ${gtest_SOURCE_DIR}/include
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

add_executable(${PROJECT_NAME} 
    test_greeting.cpp 
    CommandLineTest.cpp
    ${CMAKE_SOURCE_DIR}/src/greeting.cpp 
    ${CMAKE_SOURCE_DIR}/src/core/CommandLine.cpp
)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
