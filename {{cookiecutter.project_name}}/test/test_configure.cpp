/// Test suite for the configure module.
///
/// Link all test files with the `gtest_main` library to create a command-line 
/// test runner.
///
#include <cstdio>  // remove()
#include <cstdlib>  // tmpnam()
#include <fstream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>
#include "core/configure.hpp"

using std::ofstream;
using std::istringstream;
using std::string;
using std::tmpnam;
using std::vector;
using testing::Test;

using namespace configure;


/// Test fixture for the configure test suite.
///
/// This is used to group tests and provide common set-up and tear-down
/// code. A new test fixture is created for each test to prevent any side 
/// effects between tests. Member variables and methods are injected into
/// each test that uses this fixture.
///
/// This will be parametrized over all logging levels.
///
class ConfigTest: public Test
{
protected:
    /// Set up test fixture.
    ///
    /// Set up the test fixture.
    ///
    ConfigTest():
        path{tmpnam(nullptr)}
    {
        stream.str(ini);  // segfault when using member initialization (why?)
        ofstream file{path};  // possible race condition with path creation
        file << ini;
        file.close();
    }

    /// Tear down the test fixture.
    ///
    ~ConfigTest() {
        remove(path.c_str());
    }

    /// Path to INI file for testing.
    ///
    const std::string path;
    
    /// Keys for testing.
    ///
    const vector<string> keys = {"key1", "key2"};
    
    /// Values for testing.
    ///
    const vector<string> values = {"value1", "value2"};

    /// INI stream for testing.
    ///
    istringstream stream;
    
private:
    const string ini = R"(
        ; root section         
        key1=value1
        key2=value2

        [section1]            
        key1=value1
        key2=value2
    )";    
};


/// Test the stream constructor.
///
TEST_F(ConfigTest, ctor_stream)
{
    Config config(stream);
    for (size_t pos(0); pos != keys.size(); ++ pos) {
        ASSERT_EQ(config.get(keys[pos]), values[pos]);
        ASSERT_EQ(config.get(keys[pos], "section1"), values[pos]);
    }
}


/// Test the file constructor.
///
TEST_F(ConfigTest, ctor_file)
{
    Config config(path);
    for (size_t pos(0); pos != keys.size(); ++ pos) {
        ASSERT_EQ(config.get(keys[pos]), values[pos]);
        ASSERT_EQ(config.get(keys[pos], "section1"), values[pos]);
    }
}


/// Test the load method for a stream.
///
TEST_F(ConfigTest, load_stream)
{
    Config config;
    config.load(stream);
    for (size_t pos(0); pos != keys.size(); ++ pos) {
        ASSERT_EQ(config.get(keys[pos]), values[pos]);
        ASSERT_EQ(config.get(keys[pos], "section1"), values[pos]);
    }
}


/// Test the load method for a file.
///
TEST_F(ConfigTest, load_file)
{
    Config config;
    config.load(path);
    for (size_t pos(0); pos != keys.size(); ++ pos) {
        ASSERT_EQ(config.get(keys[pos]), values[pos]);
        ASSERT_EQ(config.get(keys[pos], "section1"), values[pos]);
    }
}


/// Test the set() and get() methods.
///
TEST_F(ConfigTest, set_get)
{
    Config config;
    for (size_t pos(0); pos != keys.size(); ++ pos) {
        config.set(keys[pos], values[pos]);
        config.set(keys[pos], values[pos], "section1");
    }
    for (size_t pos(0); pos != keys.size(); ++ pos) {
        ASSERT_EQ(config.get(keys[pos]), values[pos]);
        ASSERT_EQ(config.get(keys[pos], "section1"), values[pos]);
    }
}
