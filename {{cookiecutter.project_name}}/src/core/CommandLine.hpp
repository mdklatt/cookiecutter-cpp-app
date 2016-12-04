/// Header for the CommandLine class.
///
/// @file
#ifndef {{ cookiecutter.app_name|upper }}_COMMANDLINE_HPP
#define {{ cookiecutter.app_name|upper }}_COMMANDLINE_HPP

#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>


/// Parse POSIX-style command line arguments
///
/// A command line consists of the command name (e.g. argv[0]) followed by zero
/// or more named options and zero or more positional arguments. There is also
/// support for subcommand syntax, e.g. `git clone ...`.
///
/// An option is indicated with a single leading hyphen for a flag (e.g. '-f')
/// or two leading hyphens for a long name (e.g. '--long'). An option must have
/// a long name, and it may also have a short flag. These are all valid ways
/// of specifying an option with an argument: `-oarg`, `-o arg`, `--opt=arg`,
/// and `--opt arg`. An option without an argument is treated as a boolean
/// with a value equal to its long name. Although POSIX allows multiple flags
/// to be specified in a single argument, that is not supported here, e.g. use
/// `-a -b -c` instead of `-abc`.
///
/// Positional arguments follow the optional arguments. POSIX allows options
/// and positional arguments in any order, but here, any options must come
/// first. Positional arguments are grouped into named sets, where argument
/// order and count determines which name they are assigned to.
///
/// Arguments consisting exclusively of hyphens are treated as positional
/// arguments, not options. By convention, a single hyphen ('-') tells an
/// application to use STDIN and/or STDOUT for I/O (it is up to the application
/// to implement this functionality). A double hyphen ('--') is a signal to
/// halt option processing; any additional arguments are treated as positional
/// arguments, even if they look like options.
///
/// Subcommands break the command line into distinct groups of options and
/// positional arguments (the requirement that options precede arguments is
/// per subcommand). When a subcommand name is encountered, all further parsing
/// is delegated to it. This means that subcommands are hierarchical, and
/// subcommands may have their own subcommands. A subcommand name is treated
/// like a boolean option and stored in its parent with its name as its value.
/// All of a subcommand's arguments are visible to its parent (but the converse
/// is not true).
///
/// POSIX command-line syntax:
///   <http://www.gnu.org/software/libc/manual/html_node/Argument-Syntax.html>
///
class CommandLine
{
public:
    /// Indicate that an option only has a long name.
    ///
    static const char noflag{'\0'};

    /// Command name.
    ///
    /// For a subcommand, this is the subcommand name.
    ///
    const std::string name;

    /// Construct a new object.
    ///
    /// With strict argument checking, unexpected options or positional
    /// arguments will cause an exception to be thrown during parsing. The
    /// default help option will display a message and exit; this option
    /// will be applied to any subcommands as well.
    ///
    /// @param strict use strict argument checking
    /// @param help add `--help` option
    CommandLine(bool strict=false, bool help=true);

    ///
    ///
    /// @param name argument namehelp
    /// @return true if argument is present
    bool has_arg(const std::string& name) const;

    /// Parse command-line arguments.
    ///
    /// The arguments are as passed to main().
    ///
    /// @param argc argument count
    /// @param argv argument values
    void parse(int argc, char* argv[]);

    /// Add an option.
    ///
    /// @param name long name for this option
    /// @param flag flag character for this option (optional)
    /// @param has_val true if this option takes an argument
    /// @return
    void opt(const std::string& name, char flag=noflag, bool has_val=false);

    /// Add a set of positional arguments.
    ///
    /// @param name name for this set of arguments
    /// @param count number of arguments (all remaining arguments by default)
    void pos(const std::string& name, size_t count=0);
    
    /// Add a subcommand.
    ///
    /// @param name subcommand name
    /// @return reference to the subcommand object
    CommandLine& sub(const std::string& name);

    /// Retrieve parsed option or positional argument values.
    ///
    /// Use `cmdl["<name>"].empty()` to test for the presence of a boolean
    /// option.
    ///
    /// @param name named values to retrieve
    /// @return list of values; empty if there are none
    std::vector<std::string> operator[](const std::string& name) const;
 
    /// Generate a usage message for all defined arguments.
    /// 
    /// @return the formatted usage message
    std::string usage() const;

private:
    typedef std::vector<std::string>::iterator ArgvIter;
    struct OptArg {
        std::string name;
        char flag;
        bool has_val;
    };
    struct PosArg {
        std::string name;
        size_t count;
    };
    static const char optdel{'-'};
    const bool strict;
    const bool help;
    std::vector<OptArg> opt_args;
    std::vector<PosArg> pos_args;  // order must be preserved
    std::map<std::string, CommandLine> sub_args;
    std::multimap<std::string, std::string> arg_vals;

    /// Parse all arguments.
    ///
    /// This will be called recursively until all arguments have been parsed.
    ///
    /// @param iter current argv position
    /// @param end end of argv
    void parse_argv(ArgvIter& iter, const ArgvIter& end);

    /// Parse optional arguments.
    ///
    /// @param iter current argv position
    /// @param end end of argv
    void parse_opts(ArgvIter& iter, const ArgvIter& end);

    /// Parse positional arguments.
    ///
    /// @param iter current argv position
    /// @param end end of argv
    void parse_args(ArgvIter& iter, const ArgvIter& end);

    /// Parse subcommand arguments.
    /// 
    /// @param iter current argv position
    /// @param end end of argv
    void parse_subs(ArgvIter& iter, const ArgvIter& end);

    /// Determine if the next argument is an option.
    ///
    /// The input iterator may be incremented to advance to the next valid
    /// argument, e.g. if `--` is encountered.
    ///
    /// @param iter current argv position
    /// @return true if iterator points to an option.
    bool is_opt(ArgvIter& iter);

    /// Read the next optional argument.
    ///
    /// For arguments like `--opt=abc` or `-oabc`, the name/flag and its value
    /// will be split, otherwise the value will be an empty string. The
    /// iterator is advanced to the next argument.
    ///
    /// @param argv_iter argv iterator
    /// @return (opt, val, is_long) tuple
    std::tuple<std::string, std::string, bool> read_opt(ArgvIter& iter);
};

#endif  // {{ cookiecutter.app_name|upper }}_COMMANDLINE_HPP
