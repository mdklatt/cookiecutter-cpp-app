/// Implementation of the CommandLine class.
///
#include <cstdlib>
#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <utility>
#include "CommandLine.hpp"

using std::find_if;
using std::function;
using std::multimap;
using std::make_tuple;
using std::runtime_error;
using std::string;
using std::tuple;
using std::vector;


CommandLine::CommandLine(bool strict, bool help) :
    strict(strict),
    help(help)
{
    if (help) {
        opt("help", 'h');
    }
    return;
}


bool CommandLine::has_arg(const std::string& name) const
{
    return arg_vals.find(name) != arg_vals.end();
}


void CommandLine::parse(int argc, char* argv[])
{
    vector<string> vargv{argv, argv + argc};
    auto iter(vargv.begin());
    parse_argv(iter, vargv.end());
    return;
}


void CommandLine::opt(const std::string& name, char flag, bool has_val)
{
    opt_args.push_back(CommandLine::OptArg{name, flag, has_val});
    return;
}


void CommandLine::pos(const std::string& name, size_t count)
{
    pos_args.push_back(CommandLine::PosArg{name, count});
    return;
}


CommandLine& CommandLine::sub(const string& name)
{
    CommandLine cmdl{strict, help};
    sub_args.emplace(make_pair(name, std::move(cmdl)));  // invalidates cmdl
    return sub_args[name];
}


vector<string> CommandLine::operator[](const std::string& name) const
{
    const auto range(arg_vals.equal_range(name));
    vector<string> values;
    for (auto iter(range.first); iter != range.second; ++iter) {
        values.push_back(iter->second);
    }
    return values;
}


string CommandLine::usage() const
{
    // TODO
    std::ostringstream buffer;
    buffer << "usage: " << name;
    for (auto opt: opt_args) {
        buffer << " [--" << opt.name << "]";
    }
    for (auto pos: pos_args) {
        buffer << " " << pos.name;
    }
    return buffer.str();
}


void CommandLine::parse_argv(ArgvIter& iter, const ArgvIter& end)
{
    // If this is a subcommand, first argument will be the subcommand name.
    const_cast<string&>(name) = *iter++;
    parse_opts(iter, end);
    if (help and has_arg("help")) {
        std::cout << usage() << std::endl;
        std::exit(EXIT_SUCCESS);
    }
    parse_subs(iter, end);  // subcommand will process remaining args
    parse_args(iter, end);
    return;
}



void CommandLine::parse_opts(ArgvIter& iter, const ArgvIter& end)
{
    while (iter != end && is_opt(iter)) {
        // Process each option. At the end of the loop, 'argv_iter' will point
        // to the first positional argument.
        string arg;
        string val;
        bool is_long;
        std::tie(arg, val, is_long) = read_opt(iter);
        function<bool(const OptArg&)> found;
        if (is_long) {
            found = [arg](const OptArg& opt) { return opt.name == arg; };
        }
        else {
            found = [arg](const OptArg& opt) { return opt.flag == arg[0]; };
        }
        auto opts_iter(find_if(opt_args.begin(), opt_args.end(), found));
        if (opts_iter == opt_args.end()) {
            if (strict) {
                throw runtime_error("unknown option: " + arg);
            }
            continue;  // ignore unknown option
        }
        const auto name(opts_iter->name);
        if (opts_iter->has_val) {
            if (val.empty()) {
                // Next argument should be the option value, e.g. `--opt val`.
                if (iter == end) {
                    throw runtime_error("missing value for option " + name);
                }
                val = *iter++;
            }
        }
        else {
            // For boolean options, the value is set to the option name.
            if (!val.empty()) {
                throw runtime_error("unexpected value for option " + name);
            }
            val = opts_iter->name;
        }
        if (not opts_iter->has_val and has_arg(name)) {
            // There should only be one instance of a boolean option.
            continue;
        }
        arg_vals.emplace(make_pair(name, val));
    }
    return;
}


void CommandLine::parse_subs(ArgvIter& iter, const ArgvIter& end)
{
    // Subcommands are parsed recursively. If this is a subcommand, it is
    // responsible for all further argument processing unless one of its own
    // subcommands is encountered, and so on.
    const auto subs_iter(iter != end ? sub_args.find(*iter) : sub_args.end());
    if (subs_iter == sub_args.end()) {
        // Not a subcommand name.
        return;
    }
    const auto& name(subs_iter->first);
    if (not has_arg(name)) {
        // Treat like a boolean option.
        arg_vals.insert(make_pair(name, name));
    }
    auto& cmdl(subs_iter->second);
    cmdl.parse_argv(iter, end);
    for (auto vals_iter: cmdl.arg_vals) {
        // Merge subcommand options with its parent.
        arg_vals.insert(vals_iter);
    }
    return;
}


void CommandLine::parse_args(ArgvIter& iter, const ArgvIter& end)
{
    auto last(iter);
    for (auto const& arg: pos_args) {
        if (arg.count == 0) {
            // Consume all remaining arguments.
            last = end;
        }
        else {
            last += arg.count;
            if (last >= end) {
                throw std::runtime_error("missing argument(s): " + arg.name);
            }
        }
        for (; iter != last; ++iter)  {
            arg_vals.insert(multimap<string, string>::value_type(arg.name, *iter));
        }
    }
    if (strict and iter != end) {
        throw runtime_error("unexpected positional arguments");
    }
    return;
}


bool CommandLine::is_opt(ArgvIter& iter)
{
    // Return true if this is an optional argument.
    auto arg(*iter);
    if (arg[0] != CommandLine::optdel) {
        // This is a regular positional argument or subcommand name.
        return false;
    }
    else if (arg.find_first_not_of(CommandLine::optdel) == string::npos) {
        // This argument is all hyphens.
        if (arg.size() > 1) {
            // A double hyphen signals the end of option processing. Here,
            // two or more hyphens are accepted, which deviates slightly
            // from the POSIX standard. This argument itself is ignored.
            ++iter;
        }
        return false;
    }
    return true;
};


tuple<string, string, bool> CommandLine::read_opt(ArgvIter& iter)
{
    auto opt(*iter++);
    auto pos(opt.find_first_not_of(CommandLine::optdel));
    auto is_long(pos > 1);
    opt = opt.substr(pos);
    string val;
    if (is_long) {
        if ((pos = opt.find('=')) != string::npos) {
            // Long option contains a value, e.g. `--opt=abc`
            val = opt.substr(pos+1);
            opt = opt.substr(0, pos);
        }
    }
    else {
        if (opt.size() > 1) {
            // Short option contains a value, e.g. `-oabc`.
            val = opt.substr(1);
            opt = opt.substr(0, 1);
        }
    }
    return make_tuple(opt, val, is_long);
};
