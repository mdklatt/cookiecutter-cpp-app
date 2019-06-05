## Build the {{ cookiecutter.app_name }} application and its test suite.
##
cmake_minimum_required(VERSION 3.12)

project({{ cookiecutter.app_name }}
    VERSION {{ cookiecutter.project_version }}
    LANGUAGES CXX
)

set(EXECUTABLE {{ cookiecutter.app_name }})

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

add_executable(${EXECUTABLE})

target_sources(${EXECUTABLE}
PRIVATE
    ${API_SOURCE_FILES}
    ${CORE_SOURCE_FILES}
    ${CMAKE_SOURCE_DIR}/src/cli.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

target_include_directories(${EXECUTABLE}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(${EXECUTABLE}
PRIVATE
    cxx_std_11
)

target_compile_options(${EXECUTABLE}
PRIVATE
    -Wall
    -Wno-unknown-pragmas
    $<$<CXX_COMPILER_ID:GNU>:-pedantic>
)

add_subdirectory(test)
