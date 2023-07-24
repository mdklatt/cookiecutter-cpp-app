# Get dependencies.

include(FetchContent)

FetchContent_Declare(
    tomlplusplus
    GIT_REPOSITORY https://github.com/marzer/tomlplusplus
    GIT_TAG v3.3.0
)
FetchContent_MakeAvailable(tomlplusplus)


# Generate version header from the project version in CMakeLists.txt.

configure_file(version.hpp.in ${CMAKE_CURRENT_BINARY_DIR}/version.hpp)


# Define targets. The application is split into two components, an object
# library containing all the core functionality and the executable itself that
# includes main(). The object library can then be used for unit testing.

add_library(${name}_obj OBJECT
    cli.cpp
    api/cmd1.cpp
    api/cmd2.cpp
    core/CommandLine.cpp
    core/configure.cpp
    core/logging.cpp
)
target_link_libraries(${name}_obj
PUBLIC
    tomlplusplus::tomlplusplus
)


target_include_directories(${name}_obj
PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>  # CMake-generated files
)
target_compile_options(${name}_obj
PRIVATE
    -Wall
    $<$<CXX_COMPILER_ID:GNU>:-pedantic>
)

add_executable(${name} main.cpp)
target_link_libraries(${name} ${name}_obj)


# Install rules.

install(TARGETS ${name} DESTINATION bin)
