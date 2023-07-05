/**
 * Implementation of the cmd1 sample command.
 */
#include "api.hpp"
#include "core/logging.hpp"
#include <cstdlib>

using Logging::logger;


int cmd1() {
    logger.debug("executing cmd1");    
    return EXIT_SUCCESS;
}
