## CMake build file for the {{ cookiecutter.app_name }} application test suite.
##
## This will build a Google Test test runner for all contained tests.
##
project(test_{{ cookiecutter.app_name }})

set(TEST_SOURCE_FILES
    ${CORE_SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/test/CommandLineTest.cpp
)

add_subdirectory(lib/gtest)
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)
add_executable(${PROJECT_NAME} ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
