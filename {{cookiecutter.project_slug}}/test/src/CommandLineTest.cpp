/// Test suite for the CommandLine class.
///
/// Link all test files with the `gtest_main` library to create a command-line 
/// test runner.
///
#include <cstring>  // strncpy
#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "core/CommandLine.hpp"


using std::string;
using std::strncpy;
using std::vector;
using testing::Test;
using testing::ExitedWithCode;


/// CommandLine test fixture.
///
/// This is used to group tests and provide common set-up and tear-down
/// code. A new test fixture is created for each test to prevent any side 
/// effects between tests. Member variables and methods are injected into
/// each test that uses this fixture.
///
class CommandLineTest: public Test
{
protected:
    /// Set up test fixture.
    ///
    CommandLineTest() {}   
    
    /// Tear down the test fixture.
    ///
    ~CommandLineTest() { dealloc(); }

    /// Set command-line arguments.
    ///
    void args(const vector<string>& args)
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


/// Test the name attribute.
///
TEST_F(CommandLineTest, name)
{
    CommandLine cmdl;
    args({"cmd"});
    cmdl.parse(argc, argv);
    ASSERT_EQ("cmd", cmdl.name);
    return;
}


/// Test the parse() method for one positional argument.
///
TEST_F(CommandLineTest, parse_pos_one)
{
    CommandLine cmdl;
    cmdl.pos("pos", 1);
    args({"cmd", "abc", "123"});  // not strict, extra argument ignored
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"abc"}), cmdl["pos"]);
    return;
}


/// Test the parse() method for all positional arguments.
///
TEST_F(CommandLineTest, parse_pos_all)
{
    CommandLine cmdl;
    cmdl.pos("pos");
    args({"cmd", "abc", "123"});
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"abc", "123"}), cmdl["pos"]);
    return;
}


/// Test the parse() method with positional argument error handling.
///
TEST_F(CommandLineTest, parse_pos_err)
{
    CommandLine cmdl{true};
    cmdl.pos("pos", 1);
    args({"cmd"});  // not enough arguments
    ASSERT_THROW(cmdl.parse(argc, argv), std::runtime_error);
    args({"cmd", "abc", "def"});  // too many arguments
    ASSERT_THROW(cmdl.parse(argc, argv), std::runtime_error);
    return;
}


/// Test the parse() method for a short option.
///
TEST_F(CommandLineTest, parse_opt_short)
{
    // Not strict, extra option should be ignored.
    args({"cmd", "-f", "-x"});
    CommandLine cmdl;
    cmdl.opt("flag", 'f');
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"flag"}), cmdl["flag"]);
    return;
}


/// Test the parse() method for a long option.
///
TEST_F(CommandLineTest, parse_opt_long)
{
    // Not strict, extra option should be ignored.
    args({"cmd", "--long", "--extra"});
    CommandLine cmdl;
    cmdl.opt("long");
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"long"}), cmdl["long"]);
    return;
}


/// Test the parse() method for options that take values.
///
TEST_F(CommandLineTest, parse_opt_vals)
{
    // Verify that '--' ends option processing.
    args({"cmd", "-s", "abc", "-sabc", "--num", "123", "--str=def"});
    CommandLine cmdl;
    cmdl.opt("num", CommandLine::noflag, true);
    cmdl.opt("str", 's', true);
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"abc", "abc", "def"}), cmdl["str"]);
    ASSERT_EQ((vector<string>{"123"}), cmdl["num"]);
    return;
}


/// Test the parse() method for a boolean option.
///
TEST_F(CommandLineTest, parse_opt_bool)
{
    args({"cmd", "-b", "--bool"});  // verify that option is a singleton
    CommandLine cmdl;
    cmdl.opt("bool", 'b');
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"bool"}), cmdl["bool"]);
    return;
}


/// Test the parse() method with '--' to end option processing.
///
TEST_F(CommandLineTest, parse_opt_end)
{
    args({"cmd", "-s", "abc", "--", "-sabc"});
    CommandLine cmdl;
    cmdl.opt("str", 's', true);
    cmdl.pos("pos");
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"abc"}), cmdl["str"]);
    ASSERT_EQ((vector<string>{"-sabc"}), cmdl["pos"]);
    return;
}


/// Test the parse() method with option error handling
///
TEST_F(CommandLineTest, parse_opt_err)
{
    CommandLine cmdl{true};
    cmdl.opt("bool", CommandLine::noflag, false);
    cmdl.opt("val", CommandLine::noflag, true);
    args({"cmd", "--none"});  // unknown option
    ASSERT_THROW(cmdl.parse(argc, argv), std::runtime_error);
    args({"cmd", "--bool=true"});  // unexpected value
    ASSERT_THROW(cmdl.parse(argc, argv), std::runtime_error);
    args({"cmd", "--val"});  // missing value
    ASSERT_THROW(cmdl.parse(argc, argv), std::runtime_error);
    return;
}



/// Test the parse() method with subcommands.
///
TEST_F(CommandLineTest, parse_subs)
{
    args({"cmd", "--bool", "sub1", "--str=abc", "sub2", "123"});
    CommandLine cmdl;
    cmdl.opt("bool", 'b');
    auto& sub1(cmdl.sub("sub1"));
    sub1.opt("str", CommandLine::noflag, true);
    auto& sub2(sub1.sub("sub2"));
    sub2.pos("num");
    cmdl.parse(argc, argv);
    ASSERT_EQ((vector<string>{"bool"}), cmdl["bool"]);
    ASSERT_EQ((vector<string>{"sub1"}), cmdl["sub1"]);
    ASSERT_EQ((vector<string>{"abc"}), cmdl["str"]);
    ASSERT_EQ((vector<string>{"123"}), cmdl["num"]);
    ASSERT_EQ((vector<string>{"sub2"}), cmdl["sub2"]);
    ASSERT_EQ((vector<string>{"abc"}), sub1["str"]);
    ASSERT_EQ((vector<string>{"sub2"}), sub1["sub2"]);
    ASSERT_EQ((vector<string>{"123"}), sub1["num"]);
    return;
}


/// Test the parse() method with the help option.
///
TEST_F(CommandLineTest, parse_help)
{
    CommandLine cmdl;
    args({"cmd", "--help"});
    ASSERT_EXIT(cmdl.parse(argc, argv), ExitedWithCode(0), "");
    return;
}


/// Test the has_arg() method.
///
TEST_F(CommandLineTest, has_arg)
{
    CommandLine cmdl;
    cmdl.opt("bool");
    args({"cmd"});
    cmdl.parse(argc, argv);
    ASSERT_FALSE(cmdl.has_arg("bool"));
    args({"cmd", "--bool"});
    cmdl.parse(argc, argv);
    ASSERT_TRUE(cmdl.has_arg("bool"));
    return;
}
