/**
 * Header for the logging module.
 *
 * @file
 */
#ifndef {{ cookiecutter.app_name|upper }}_LOGGING_HPP
#define {{ cookiecutter.app_name|upper }}_LOGGING_HPP

#include <chrono>
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <memory>
#include <ostream>
#include <string>


namespace Logging {
    /**
     * Message priority levels.
     *
     * Messages are filtered at the Logger and Handler level by priority.
     * Messages that do not meet the minimum priority will be ignored at that
     * point.
     *
     * Suggested usages of priority levels:
     *
     *   DEBUG - output useful for developers
     *   INFO - trace normal program flow, especially external interactions
     *   WARN - an abnormal condition was detected that might need attention
     *   ERROR - an error was detected but execution continued
     *   FATAL - an error was detected and execution could not continue
     *
     * The NOTSET level is an implementation detail and should not be used by
     * clients of this module.
     */
    enum Level { NOTSET, DEBUG, INFO, WARN, ERROR, FATAL };

    Level level(std::string str);

    /**
     * Convert the record level to a string.
     *
     * @param val level value
     * @return record level
     */
    std::string level(Level val);
    
    /**
     * Fields for a Logger record.
     *
     * This is used by the implementation. There is no need for module clients
     * to construct a Record directly.
     */
    struct Record {
        typedef std::chrono::system_clock Clock;
        Record(Level level, const std::string& name, const std::string& message):
            level{level},
            name{name},
            message{message},
            time{Clock::now()} {}
        const Level level;
        const std::string name;
        const std::string message;
        const Clock::time_point time;
    };

    /**
     * Logger handler abstract base class.
     *
     * A Handler is what actually sends logger records to a destination. A
     * logger may have zero or more associated handlers, each with their own
     * priority levels (but in all cases, the logger's priority level takes
     * precedence).
     */
    class Handler {
    public:
        /**
         * Process a logger record.
         *
         * @param record
         */
        void handle(const Record& record) const;

        /**
         * Destructor.
         */
        virtual ~Handler() = default;

        /**
         * Create a clone of this object.
         *
         * This must be defined by each derived class to return an object of
         * the correct type allocated using new. The caller is responsible for
         * calling delete. This is intended for use by polymorphic containers.
         *
         * @return pointer to the new clone
         */
        virtual Handler* clone() const = 0;

    protected:
        /**
         * Construct a new Handler.
         *
         * Records with a lower priority level will not be emitted by this
         * handler.
         *
         * @param level priority level
         */
        Handler(Level level=WARN) :
            level{level} {}

        /**
         * Emit a logger record.
         *
         * This is the final step in processing a record, and must be defined
         * by derived classes to e.g. write to a stream or file. At this point
         * the record has already by filtered by priority level.
         *
         * @param record logger record
         */
        virtual void emit(const Record& record) const = 0;

    private:
        const Level level;
    };


    /**
     * Logger handler for outputting to a stream.
     */
    class StreamHandler: public Handler {
    public:
        /**
         * Construct a new StreamHandler.
         *
         * @param level priority level
         * @param stream destination stream
         */
        StreamHandler(Level level=WARN, std::ostream& stream=std::clog):
            Handler(level),
            stream(stream) {}

        /**
         * Create a clone of this object.
         *
         * The caller is responsible for deleting the new pointer. This is
         * intended for use by polymorphic containers.
         *
         * @return pointer to the new clone
         */
        virtual StreamHandler* clone() const;  // covariant return

    protected:
        /**
         * Write a formatted record to the destination stream.
         *
         * @param record logger record
         */
        virtual void emit(const Record& record) const;

    private:
        /**
         * Convert the record time to a string.
         *
         * The format matches the ISO8601 format (YYYY-mm-dd HH:MM:SS,sss)
         * commonly used by other logging frameworks like Log4x and the Python
         * logging module.
         *
         * @param record logger record
         * @return record time
         */
        std::string time(const Record& record) const;

        std::ostream& stream;
    };

    /**
     * Log messages.
     *
     * A logger sends messages to one or more handlers.
     */
    class Logger {
    public:
        /**
         * Construct a new Logger.
         *
         * @param name logger name
         */
        Logger(const std::string& name):
            name{name}, 
            level{NOTSET} {}

        /**
         * Start logging with this logger.
         *
         * Messages below the given priority level will be ignored by this
         * logger.
         *
         * @param level priority level
         * @param stream output stream
         */
        void start(Level level=WARN, std::ostream& stream=std::clog);

        /**
         * Stop logging with this logger.
         *
         * All handlers will be removed from the logger, and it will no longer
         * emit any messages.
         */
        void stop();

        /**
         * Add a handler to this logger.
         *
         * Handlers are responsible for actually emitting the records sent to
         * this logger. At least one handler is required for records to be
         * logged. Multiple handlers may be used to log records to multiple
         * destinations, e.g. STDERR, a file, syslog, email, etc. Handlers
         * have their own priority levels, but the logger will filter records
         * according to its priority level before passing them to handlers.
         *
         * @param handler
         */
        void handler(const Handler& handler);

        /**
         * Log a message with the given priority level.
         *
         * The message is annotated with the priority level, the time, and
         * the logger name. If the level is lower than the logger's priority
         * level it will be ignored.
         *
         * @param level priority level
         * @param message message
         */
        void log(Level level, const std::string& message) const;

        /**
         * Log an INFO message.
         *
         * This is an alias for `log(INFO, message)`.
         *
         * @param message message to log
         */
        void debug(const std::string& message) const;

        /**
         * Log a DEBUG message.
         *
         * This is an alias for `log(DEBUG, message)`.
         *
         * @param message message to log
         */
        void info(const std::string& message) const;

        /**
         * Log a WARN message.
         *
         * This is an alias for `log(WARN, message)`.
         *
         * @param message message to log
         */
        void warn(const std::string& message) const;

        /**
         * Log an ERROR message.
         *
         * This is an alias for `log(ERROR, message)`.
         *
         * @param message message to log
         */
        void error(const std::string& message) const;

        /**
         * Log a FATAL message.
         *
         * This is an alias for `log(FATAL, message)`.
         *
         * @param message message to log
         */
        void fatal(const std::string& message) const;

    private:
        const std::string name;
        Level level;
        std::list<std::unique_ptr<const Handler>> handlers;
    };
    
    extern Logger logger;
}

#endif  // {{ cookiecutter.app_name|upper }}_LOGGING_HPP
