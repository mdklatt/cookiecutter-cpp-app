/**
 * Implementation of the configure module.
 */
#include "configure.hpp"
#include <toml++/toml.h>
#include <cctype>
#include <fstream>
#include <iostream>
#include <istream>
#include <stdexcept>


using std::getline;
using std::ifstream;
using std::invalid_argument;
using std::isspace;
using std::istream;
using std::out_of_range;
using std::runtime_error;
using std::skipws;
using std::string;
using std::to_string;

using namespace configure;


Config::Config(istream& stream) {
    load(stream);
}


Config::Config(const std::string& path) {
    load(path);
}


void Config::load(const string& path) {
    ifstream stream(path);
    if (not stream) {
        throw runtime_error("could not open config file " + path);
    }
    load(stream);
    return;
}


void Config::load(istream& stream) {
    insert("", toml::parse(stream));
}


void Config::load(const std::filesystem::path& path) {
    insert("", toml::parse_file(path.string()));
}


string& Config::operator[](const string& key) {
    return data[key];
}
    

const string& Config::operator[](const string& key) const {
    try {
        return data.at(key);
    }
    catch (out_of_range&) {
        throw out_of_range("no value for '" + key + "'");
    }
}


void Config::insert(const std::string root, const toml::table& table) {
    for (auto&& [key, node] : table) {
        string path_key = string{key.str()};
        if (root != "") {
            path_key = root + "." + path_key;
        }
        if (node.is_value()) {
            data[path_key] = node.value_or("");
        }
        else if (node.is_table()) {
            insert(path_key, *node.as_table());
        }
        else {
            throw invalid_argument{"unexpected TOML node type"};
        }
    }
    return;
}

