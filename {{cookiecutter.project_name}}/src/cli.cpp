/// Implementation of the {{ cookiecutter.project_name}} CLI.
///
/// @file
#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "core/CommandLine.hpp"
#include "core/logging.hpp"
#include "api/api.hpp"
#include "version.h"

using Logging::logger;
using Logging::level;
using std::cout;
using std::endl;
using std::string;
using std::vector;


/// Display a help message.
///
void help()
{
    cout << "{{ cookiecutter.app_name }} [-h]" << endl;
    return;
}


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
    // The leading '+' for short_opts enables POSIXLY_CORRECT behavior, which
    // halts option processing as soon as a non-option is encountered. This is
    // necessary for implementing subcommands.
    const char* short_opts{"+:hvw:"};
    const option long_opts[]{
        {"help", no_argument, nullptr, 'h'},
        {"version", no_argument, nullptr, 'v'},
        {"warn", required_argument, nullptr, 'w'},
        {nullptr, 0, nullptr, 0}  // sentinel
    };
    string warn("warn");
    optind = 0;  // reset getopt parser (POSIXLY_CORRECT mode); not thread-safe
    while (true) {
        // Process options.
        const int opt{getopt_long(argc, argv, short_opts, long_opts, nullptr)};
        if (opt == -1) {
            break;
        }
        switch (opt) {        
            case 'h': 
                help();
                return EXIT_SUCCESS;
            case 'v': 
                cout << "{{ cookiecutter.app_name }} v" <<  {{ cookiecutter.app_name|upper }}_VERSION << endl;
                return EXIT_SUCCESS;
            case 'w':
                warn = optarg;
                break;
            case '?':  // unknown option
            case ':':  // missing option value
            default:
                help();
                return EXIT_FAILURE;
        }
    }
    logger.start(level(warn));
    logger.info("starting application");
    return EXIT_SUCCESS;
}
