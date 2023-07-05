/**
 * Implementation of the cmd2 sample command.
 */
#include "api.hpp"
#include "core/logging.hpp"
#include <cstdlib>

using Logging::logger;


int cmd2() {
    logger.debug("executing cmd2");
    return EXIT_SUCCESS;
}
