## CMake build file for the {{ cookiecutter.app_name }} application.
##
## This will build the application itself and its test suite. Compiled binaries
## will be written to build/${CMAKE_BUILD_TYPE}.
##
cmake_minimum_required(VERSION 3.0)
project({{ cookiecutter.app_name }})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

set(SOURCE_FILES src/main.cpp src/greeting.cpp)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -Wall")
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
add_subdirectory(test)
