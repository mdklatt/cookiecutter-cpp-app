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
         * @param stream TOML data stream
         */
        explicit Config(std::istream& stream);

        /**
         * Construct a Config object from a file.
         *
         * @param path TOML file path
         */
        explicit Config(const std::filesystem::path& path);

        /** @overload */
        explicit Config(const std::string& path);

        /**
         * Load config data from an input stream.
         *
         * @param stream TOML data stream
         */
        void load(std::istream& stream);

        /**
         * Load config data from a file path.
         *
         * @param path TOML file path
         */
        void load(const std::filesystem::path& path);

        /**
         * Access a writable config value.
         *
         * If `key` does not exist it will be crated. Use dotted components to
         * refer to nested values, *e.g.* "table.nested.value". Keys without
         # dotted components refer to root-level scalar values.
         *
         * @param key key
         * @return value reference mapped to 'key'
         */
        std::string& operator[](const std::string& key);

        /**
         * Access a read-only config value.
         *
         * A `std::out_of_range` exception will be thrown if the key does not
         * exist. Use dotted components to refer to nested values, *e.g.*
         * "table.nested.value". Keys without  dotted components refer to
         * root-level scalar values.
         *
         * @param key hierarchical element key
         * @param section section name; defaults to the root section
         */
        const std::string& operator[](const std::string& key) const;
        
    private:
        typedef std::map<std::string, std::string> ValueMap;
        ValueMap data;

        /**
         * Insert a table element into the data structure.
         *
         * Nested tables are inserted recursively using dotted components for
         * the key name, *e.g.* "root.nested.value".
         *
         * @param root key that designates the root of this table
         * @param table TOML table element
         */
        void insert(const std::string root, const toml::table& table);
    };

    extern Config config;

}  // namespace


#endif  // {{ cookiecutter.app_name|upper }}_CONFIGURE_HPP
