/// Test suite for the cli module.
///
/// Link all test files with the `gtest_main` library to create a command-line 
/// test runner.
///
#include <cstdlib>
#include <string>
#include <vector>
#include <gtest/gtest.h>

using std::string;
using std::vector;
using testing::Test;


extern int cli(int, char* []);  // cli.cpp


/// Test fixture for the cli module test suite.
///
/// This is used to group tests and provide common set-up and tear-down
/// code. A new test fixture is created for each test to prevent any side 
/// effects between tests. Member variables and methods are injected into
/// each test that uses this fixture.
///
class CliTest: public Test
{
protected:
    /// Set up test fixture.
    ///
    CliTest() {}   
    
    /// Tear down the test fixture.
    ///
    ~CliTest() 
    { 
        dealloc(); 
    }

    /// Set command-line arguments.
    ///
    void cmdl(const vector<string>& args)
    {
        dealloc();
        argc = static_cast<int>(args.size());
        argv = new char*[argc];
        auto iter(args.begin());
        for (int pos{0}; pos < argc; ++pos, ++iter) {
            const size_t len{iter->size() + 1};
            argv[pos] = new char[len];
            assert(strncpy(argv[pos], iter->c_str(), len) != nullptr);
        }
        return;
    }
    
    int argc{0};
    char** argv{nullptr};
    
private:
    /// Deallocate argv.
    ///
    void dealloc()
    {
        for (int pos{0}; pos < argc; ++pos) {
            delete[] argv[pos];
        }
        delete[] argv;
        argv = nullptr;
        argc = 0;
        return;        
    }
};


TEST_F(CliTest, help)
{
    cmdl({"{{ cookiecutter.app_name }}", "-h"});
    ASSERT_EQ(cli(argc, argv), EXIT_SUCCESS);
    return;
}


TEST_F(CliTest, version)
{
    cmdl({"{{ cookiecutter.app_name }}", "-v"});
    ASSERT_EQ(cli(argc, argv), EXIT_SUCCESS);
    return;
}
