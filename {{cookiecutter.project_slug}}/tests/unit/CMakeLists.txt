# Get dependencies.

include(FetchContent)
include(GoogleTest)

FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG {{ cookiecutter.googletest_version }}
)
FetchContent_MakeAvailable(googletest)


# Define targets.

add_executable(test_${name}
    test_cli.cpp
    test_configure.cpp
    test_logging.cpp
)
target_link_libraries(test_${name}
PRIVATE
    ${name}_obj
    gtest
    gtest_main
)
