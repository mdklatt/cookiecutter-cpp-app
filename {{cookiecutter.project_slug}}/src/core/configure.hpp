/**
 * Global application configuration.
 *
 * This module defines a global configuration object that other modules can 
 * use to store application-wide configuration values.
 *
 * @file
 */
#ifndef {{ cookiecutter.app_name|upper }}_CONFIGURE_HPP
#define {{ cookiecutter.app_name|upper }}_CONFIGURE_HPP

#include <toml++/toml.h>
#include <filesystem>
#include <istream>
#include <map>
#include <string>


namespace configure {
    /**
     * Store application config data.
     */
    class Config {
    public:
        /**
         * Default constructor.
         */
        Config() = default;

        /**
         * Construct a Config object from an input stream.
         *
         * @param stream configuration file
         */
        explicit Config(std::istream& stream);

        /**
         * Construct a Config object from a file path.
         *
         * @param path configuration file path
         */
        explicit Config(const std::filesystem::path& path);

        /** @overload */
        explicit Config(const std::string& path);

        /**
         * Load config data from an input stream.
         *
         * @param stream configuration data stream
         */
        void load(std::istream& stream);

        /**
         * Load config data from a file path.
         *
         * @param path configuration file path
         */
        void load(const std::filesystem::path& path);

        /** @overload */
        void load(const std::string& path);

        /**
         * Set a config value.
         *
         * @param key key
         * @param value value
         * @param section section name; defaults to the root section
         */
        void set(const std::string& key, const std::string& value="", const std::string& section="");

        /**
         * Get a config value.
         *
         * @param key key
         * @param section section name; defaults to the root section
         */
        std::string get(const std::string& key, const std::string& section="") const;        
        
    private:
        typedef std::map<std::string, std::map<std::string, std::string>> ValueMap;
        const static char comment = ';';
        ValueMap data;

        /**
         *
         */
        void insert(const std::string key, const toml::table& table);
    };
}


#endif  // {{ cookiecutter.app_name|upper }}_CONFIGURE_HPP
