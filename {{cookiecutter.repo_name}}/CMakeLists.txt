cmake_minimum_required(VERSION 3.0)
project(CLionDemo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/${CMAKE_BUILD_TYPE})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES src/main.cpp src/greeting.cpp)
add_executable({{ cookiecutter.repo_name }} ${SOURCE_FILES})
