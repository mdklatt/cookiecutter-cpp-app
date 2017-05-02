/// Test suite for the cli module.
///
/// Link all test files with the `gtest_main` library to create a command-line 
/// test runner.
///
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <gtest/gtest.h>

using std::clog;
using std::cout;
using std::ostringstream;
using std::streambuf;
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
    /// Output to std::cout and std::clog will be captured for the lifetime of
    /// the fixture.
    ///
    CliTest() :
        outbuf{cout.rdbuf(stdout.rdbuf())},
        errbuf{clog.rdbuf(stderr.rdbuf())} 
    {}  
    
    /// Tear down the test fixture.
    ///
    ~CliTest() 
    { 
        dealloc(); 
        cout.rdbuf(outbuf);
        clog.rdbuf(errbuf);
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
    ostringstream stdout;
    ostringstream stderr;
    streambuf* const outbuf;
    streambuf* const errbuf;
    
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

/// Test the --help option.
///
TEST_F(CliTest, help)
{
    for (auto flag: vector<string>{"-h", "--help"}) {
        cmdl({"{{ cookiecutter.app_name }}", flag});
        ASSERT_EQ(cli(argc, argv), EXIT_SUCCESS);
        ASSERT_NE(stdout.str().find("{{ cookiecutter.app_name }}"), string::npos);
    }
    return;
}


/// Test the --version option.
///
TEST_F(CliTest, version)
{
    // TODO: Test correct output to cout.
    for (auto flag: vector<string>{"-v", "--version"}) {
        cmdl({"{{ cookiecutter.app_name }}", flag});
        ASSERT_EQ(cli(argc, argv), EXIT_SUCCESS);        
        ASSERT_NE(stdout.str().find("v{{ cookiecutter.project_version }}"), string::npos);
    }
    return;
}


/// Test the --warn option.
///
TEST_F(CliTest, warn)
{
    for (auto flag: vector<string>{"-w", "--warn"}) {
        cmdl({"{{ cookiecutter.app_name }}", flag, "info"});
        ASSERT_EQ(cli(argc, argv), EXIT_SUCCESS);
        ASSERT_NE(stderr.str().find("starting application"), string::npos);    
    }
    return;
}


/// Test invalid options.
///
TEST_F(CliTest, invalid)
{
    for (auto flag: vector<string>{"-x", "--help=badarg"}) {
        cmdl({"{{ cookiecutter.app_name }}", flag});
        ASSERT_EQ(cli(argc, argv), EXIT_FAILURE);        
        ASSERT_NE(stdout.str().find("{{ cookiecutter.app_name }}"), string::npos);
    }
    return;
}
