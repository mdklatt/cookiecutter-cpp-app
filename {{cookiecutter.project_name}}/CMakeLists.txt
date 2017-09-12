## CMake build file for the {{ cookiecutter.app_name }} application.
##
## This will build the application itself and its test suite. Compiled binaries
## will be written to build/${CMAKE_BUILD_TYPE}.
##
cmake_minimum_required(VERSION 2.8.12)

project({{ cookiecutter.app_name }})

set(API_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/api/cmd1.cpp
    ${CMAKE_SOURCE_DIR}/src/api/cmd2.cpp
)
set(CORE_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/core/CommandLine.cpp
    ${CMAKE_SOURCE_DIR}/src/core/configure.cpp    
    ${CMAKE_SOURCE_DIR}/src/core/logging.cpp
)
set(APP_SOURCE_FILES
    ${API_SOURCE_FILES}
    ${CORE_SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/src/cli.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
include_directories(
    ${CMAKE_SOURCE_DIR}/src
)
add_executable(${PROJECT_NAME} ${APP_SOURCE_FILES})
add_subdirectory(test)
