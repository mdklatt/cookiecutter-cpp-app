/// Test suite for the logging module.
///
/// Link all test files with the `gtest_main` library to create a command-line 
/// test runner.
///
#include <list>
#include <sstream>
#include <gtest/gtest.h>
#include "core/logging.hpp"

#include <iostream>

using std::list;
using std::ostringstream;
using std::string;
using testing::TestWithParam;
using testing::Values;

using namespace Logging;


/// Test fixture for the Logger test suite.
///
/// This is used to group tests and provide common set-up and tear-down
/// code. A new test fixture is created for each test to prevent any side 
/// effects between tests. Member variables and methods are injected into
/// each test that uses this fixture.
///
/// This will be parametrized over all logging levels.
///
class LoggerTest: public TestWithParam<Level>
{
protected:
    /// Set up test fixture.
    ///
    /// The default logger and its handler have the same severity level and
    /// will emit the same messages.
    ///
    LoggerTest() :
        logger{"LoggerTest"}
    {
        logger.start(level, stream);
        return;
    }
    const Level level{GetParam()};
    const string message{"test message"};
    Logger logger;
    std::ostringstream stream;
};

INSTANTIATE_TEST_CASE_P(Levels, LoggerTest, Values(INFO, INFO, WARN, ERROR, FATAL));


/// Test the stop() method.
///
TEST_P(LoggerTest, stop)
{
    logger.stop();
    logger.log(level, message);
    ASSERT_EQ(stream.str().find(message), string::npos); 
    return;  
}


/// Test the log() method.
///
TEST_P(LoggerTest, log)
{
    logger.log(level, message);
    ASSERT_NE(stream.str().find(message), string::npos);
    if (level < FATAL) {
        // Test the case where the logger has a higher severity level than the
        // handler; messages that would normally be emitted are ignored at the
        // logger level.
        Logger silent{"LoggerTest"};
        ostringstream stream;
        silent.start(FATAL, stream);
        silent.log(level, message);
        ASSERT_TRUE(stream.str().empty());
    }
    return;
}


/// Test the debug() method.
///
TEST_P(LoggerTest, debug)
{
    logger.debug(message);
    if (level <= DEBUG) {
        // Message should be logged.
        ASSERT_NE(stream.str().find(message), string::npos);
    }
    else {
        // Message should be ignored.
        ASSERT_TRUE(stream.str().empty());
    }
    return;
}


/// Test the info() method.
///
TEST_P(LoggerTest, info)
{
    logger.info(message);
    if (level <= INFO) {
        // Message should be logged.
        ASSERT_NE(stream.str().find(message), string::npos);
    }
    else {
        // Message should be ignored.
        ASSERT_TRUE(stream.str().empty());
    }
    return;
}


/// Test the warn() method.
///
TEST_P(LoggerTest, warn)
{
    logger.warn(message);
    if (level <= WARN) {
        // Message should be logged.
        ASSERT_NE(stream.str().find(message), string::npos);
    }
    else {
        // Message should be ignored.
        ASSERT_TRUE(stream.str().empty());
    }
    return;
}


/// Test the error() method.
///
TEST_P(LoggerTest, error)
{
    logger.error(message);
    if (level <= ERROR) {
        // Message should be logged.
        ASSERT_NE(stream.str().find(message), string::npos);
    }
    else {
        // Message should be ignored.
        ASSERT_TRUE(stream.str().empty());
    }
    return;
}


/// Test the fatal() method.
///
TEST_P(LoggerTest, fatal)
{
    logger.fatal(message);
    if (level <= FATAL) {
        // Message should be logged.
        ASSERT_NE(stream.str().find(message), string::npos);
    }
    else {
        // Message should be ignored.
        ASSERT_TRUE(stream.str().empty());
    }
    return;
}
