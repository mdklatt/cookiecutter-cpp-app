## Build the application test suite.
##
## This will build a Google Test test runner for all contained tests.
##
project(test_{{ cookiecutter.app_name }})

set(EXECUTABLE test_{{ cookiecutter.app_name }})

add_subdirectory(vendor/googletest EXCLUDE_FROM_ALL)

target_compile_features(gtest
PUBLIC
    cxx_std_11
)

add_executable(${EXECUTABLE})

target_sources(${EXECUTABLE}
PRIVATE
    ${CMAKE_SOURCE_DIR}/src/cli.cpp
    ${CORE_SOURCE_FILES}
    ${API_SOURCE_FILES}
    ${CMAKE_CURRENT_LIST_DIR}/src/CommandLineTest.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/test_cli.cpp    
    ${CMAKE_CURRENT_LIST_DIR}/src/test_configure.cpp    
    ${CMAKE_CURRENT_LIST_DIR}/src/test_logging.cpp    
)

target_include_directories(${EXECUTABLE}
PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${EXECUTABLE} ${libname} gtest gtest_main)
