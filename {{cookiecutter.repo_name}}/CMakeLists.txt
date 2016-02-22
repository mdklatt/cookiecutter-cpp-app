## CMake build file for the {{ cookiecutter.repo_name }} application.
##
## This will build the application itself and its test suite. Compiled binaries
## will be written to build/${CMAKE_BUILD_TYPE}.
##
cmake_minimum_required(VERSION 3.0)
project({{ cookiecutter.repo_name }} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})

set(SOURCE_FILES src/main.cpp src/greeting.cpp)
add_executable({{ cookiecutter.repo_name }} ${SOURCE_FILES})
add_subdirectory(test)
