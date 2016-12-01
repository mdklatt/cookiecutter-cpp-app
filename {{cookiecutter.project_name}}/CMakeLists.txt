## CMake build file for the {{ cookiecutter.app_name }} application.
##
## This will build the application itself and its test suite. Compiled binaries
## will be written to build/${CMAKE_BUILD_TYPE}.
##
cmake_minimum_required(VERSION 2.8.12)

project({{ cookiecutter.app_name }})

set(CORE_SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/core/CommandLine.cpp
)
set(APP_SOURCE_FILES
    ${CORE_SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

include_directories(
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
add_executable(${PROJECT_NAME} ${APP_SOURCE_FILES})
add_subdirectory(test)
