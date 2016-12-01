/// Implementation of the {{ cookiecutter.project_name}} CLI.
///
#include <cstdlib>
#include <iostream>
#include "core/CommandLine.hpp"


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
    CommandLine cmdl{true};  // strict argument parsing
    cmdl.opt("version", 'v');
    cmdl.parse(argc, argv);
    if (cmdl.has_arg("version")) {
        // TODO: Implement project versioning.
        std::cout << "{{ cookiecutter.project_name }} x.x.x" << std::endl;
        return EXIT_SUCCESS;
    }
    // TODO: Implment subcommand(s).
    return EXIT_SUCCESS;
}
