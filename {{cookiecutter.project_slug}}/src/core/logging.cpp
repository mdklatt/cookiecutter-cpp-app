/**
 * Implementation of the logging module.
 */
#include <cctype>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <stdexcept>
#include <iomanip>
#include <iterator>
#include <list>
#include <sstream>
#include "logging.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::microseconds;
using std::chrono::seconds;
using std::copy;
using std::list;
using std::ostream;
using std::ostream_iterator;
using std::ostringstream;
using std::prev;
using std::runtime_error;
using std::string;
using std::strftime;
using std::unique_ptr;

using namespace Logging;


Logger Logging::logger{"{{ cookiecutter.app_name }}"};


string Logging::level(Level val) {
    // This does not handle NOTSET because it is a private implementation 
    // detail of this module.
    static const std::map<Level, string> levels{
        {DEBUG, "DEBUG"},
        {INFO, "INFO"},
        {WARN, "WARN"},
        {ERROR, "ERROR"},
        {FATAL, "FATAL"}
    };
    return levels.at(val);  // why won't operator[] compile here?
}


Level Logging::level(string str) {
    // This does not handle NOTSET because it is a private implementation 
    // detail of this module.
    static const std::map<string, Level> levels{
        {"DEBUG", DEBUG},
        {"INFO", INFO},
        {"WARN", WARN},
        {"ERROR", ERROR},
        {"FATAL", FATAL}
    };
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    try {
        return levels.at(str);  // why won't operator[] compile here?        
    }
    catch (const std::out_of_range&) {
        throw std::runtime_error("unknown warning level: " + str);
    }
}


void StreamHandler::emit(const Record& record) const {
    // TODO: Allow user-specified formatting.
    const list<string> fields{time(record), Logging::level(record.level), record.name, record.message};
    const auto last(prev(fields.end()));
    copy(fields.begin(), last, ostream_iterator<string>{stream, ";"});
    stream << *last << std::endl;  // don't want delimiter after last element
    return;
}


string StreamHandler::time(const Record& record) const {
    const auto elapsed(record.time.time_since_epoch());
    const std::time_t time{duration_cast<seconds>(elapsed).count()};
    const auto time_info(std::localtime(&time));
    const long msecs(duration_cast<milliseconds>(elapsed).count() % 1000);
    char buffer[23+1];
    if (strftime(&buffer[0], 19+1, "%F %T", time_info) != 19) {
        throw runtime_error("error converting time to string");
    }
    if (snprintf(&buffer[19], 4+1, ",%03ld", msecs) != 4) {
        throw runtime_error("error converting time to string");
    }
    return string(buffer);
}


StreamHandler* StreamHandler::clone() const {
    return new StreamHandler(*this);
}


void Logger::start(Level level, ostream& stream) {
    this->level = level;
    handler(StreamHandler(level, stream));
    return;
}


void Logger::stop() {
    handlers.clear();
    return;
}


void Logger::handler(const Handler& handler) {
    handlers.push_back(unique_ptr<const Handler>{handler.clone()});
    return;
}


void Logger::debug(const string& message) const {
    log(DEBUG, message);
    return;
}


void Logger::info(const string& message) const {
    log(INFO, message);
    return;
}


void Logger::warn(const string& message) const {
    log(WARN, message);
    return;
}


void Logger::error(const string& message) const {
    log(ERROR, message);
    return;
}


void Logger::fatal(const string& message) const {
    log(FATAL, message);
    return;
}


void Logger::log(Level level, const string& message) const {
    if (level >= this->level) {
        const Record record{level, name, message};
        for (auto& handler: handlers) {
            handler->handle(record);
        }
    }
    return;
}


void Handler::handle(const Record& record) const {
    if (record.level >= level) {
         emit(record);
    }
    return;
}
