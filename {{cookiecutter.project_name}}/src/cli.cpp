/// Implementation of the {{ cookiecutter.project_name}} CLI.
///
#include <cstdlib>
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
    CommandLine cmdl;
    cmdl.parse(argc, argv);
    return EXIT_SUCCESS;
}
