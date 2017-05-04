/// Implemenation of the cmd1 sample command.
///
#include <cstdlib>
#include "api.hpp"
#include "../core/logging.hpp"

using Logging::logger;


int cmd1()
{
    logger.debug("executing cmd1");    
    return EXIT_SUCCESS;
}
