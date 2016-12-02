/// Implementation of the {{ cookiecutter.project_name}} CLI.
///
#include <cstdlib>
#include <iostream>
#include <string>
#include "core/CommandLine.hpp"
#include "api/api.hpp"


/// Entry point for the command line interface.
///
/// The arguments are as passed to main(). The first value of `argv` will be
/// the command name used to execute the application.
///
/// @param argc size of argv
/// @param argv array of arguments from the command line
/// @return application exit code
int cli(int argc, char* argv[])
{
    CommandLine cmdl{true};  // enable strict argument parsing
    cmdl.opt("version", 'v');
    auto sub1(cmdl.sub("cmd1"));
    sub1.pos("arg");
    auto sub2(cmdl.sub("cmd2"));
    sub2.pos("arg");
    
    cmdl.parse(argc, argv);
    if (cmdl.has_arg("version")) {
        // TODO: Implement project versioning.
        std::cout << "{{ cookiecutter.project_name }} x.x.x" << std::endl;
        return EXIT_SUCCESS;
    }
    if (cmdl.has_arg("cmd1")) {
        const auto arg(cmdl["arg"].front());
        cmd1(arg);
    }
    else if (cmdl.has_arg("cmd2")) {
        const auto arg(cmdl["arg"].front());
        cmd2(arg);    
    }
    else {
        // Missing subcommand.
        std::cout << cmdl.usage() << std::endl;
    }
    
    return EXIT_SUCCESS;
}
