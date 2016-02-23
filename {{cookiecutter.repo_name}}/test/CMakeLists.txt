project(test_{{ cookiecutter.app_name }})

add_subdirectory(lib/gtest)

include_directories(${gtest_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} test_greeting.cpp ../src/greeting.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)
