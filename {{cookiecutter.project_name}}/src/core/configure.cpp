/// Implementation of the configure module.
///
#include <cctype>
#include <fstream>
#include <iostream>
#include <istream>
#include <stdexcept>
#include "configure.hpp"


using std::getline;
using std::ifstream;
using std::isspace;
using std::istream;
using std::out_of_range;
using std::runtime_error;
using std::skipws;
using std::string;
using std::to_string;

using namespace configure;


Config::Config(istream& stream)
{
    load(stream);
}


Config::Config(const std::string& path)
{
    load(path);
}


void Config::load(const string& path)
{
    ifstream stream(path);
    if (not stream) {
        throw runtime_error("could not open config file " + path);
    }
    load(stream);
    return;
}


void Config::load(istream& stream)
{
    // This is intended as a proof-of-concept for application configuration,
    // not a complete INI parser.
    const string whitespace(" \t\n\r\f\v");  // FIXME: not locale aware
    string line;
    string section("");  // root section
    while (getline(stream, line)) {
        line.erase(0, line.find_first_not_of(whitespace));
        if (line.empty() or line[0] == comment) {
            // Ignore blank lines and comment lines.
            continue;
        }
        else if (line[0] == '[') {
            // Insert a section heading.
            const auto pos(line.find_last_of(']'));
            if (pos == string::npos) {
                throw runtime_error("invalid section heading: " + line);
            }
            section = line.substr(1, pos-1);
            data.emplace(section, ValueMap::mapped_type());
        }
        else {
            // Insert a key/value pair. Should space around '=' be allowed?
            const auto pos(line.find('='));
            if (pos == 0 or pos == string::npos) {
                throw runtime_error("expected key=value: " + line);                
            }
            const string key(line.substr(0, pos));
            const string value(line.substr(pos+1));  // empty value is okay
            const ValueMap::mapped_type::value_type entry({key, value});
            data[section][key] = value;
        }       
    }
    return;
}


void Config::set(const string& key, const string& value, const string& section)
{
    data.emplace(section, ValueMap::mapped_type());
    data[section][key] = value;    
    return;
}
    

string Config::get(const string& key, const string& section) const
{
    string value;
    try {
        value = data.at(section).at(key);
    }
    catch (out_of_range&) {
        throw out_of_range("no '" + key + "' in '" + section + "'");
    }
    return value;
}
