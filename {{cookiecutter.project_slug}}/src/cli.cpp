/// Implementation of the {{ cookiecutter.app_name }} CLI.
///
/// @file
#include <getopt.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "core/logging.hpp"
#include "api/api.hpp"
#include "version.hpp"

using Logging::logger;
using Logging::level;
using std::cout;
using std::endl;
using std::string;


namespace {  // internal linkage
    
    /// Display a help message.
    ///
    void help()
    {
        cout << "{{ cookiecutter.app_name }} [-h]" << endl;
        return;
    }
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
                cout << "{{ cookiecutter.app_name }} [-h]" << endl;
                return EXIT_SUCCESS;
            case 'v':
                cout << "{{ cookiecutter.app_name }} v" << version() << endl;
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
    int status{EXIT_FAILURE};
    if (optind == argc) {
        help();
    }
    else if (argv[optind] == string("cmd1")) {
        status = cmd1();
    }
    else if (argv[optind] == string("cmd2")) {
        status = cmd2();
    }
    else {
        help();
    }
    logger.info("application complete");
    return status;
}
