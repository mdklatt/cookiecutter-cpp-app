/// Implemenation of the cmd2 sample command.
///
#include <cstdlib>
#include "api.hpp"
#include "../core/logging.hpp"

using Logging::logger;


int cmd2()
{
    logger.debug("executing cmd2");
    return EXIT_SUCCESS;
}
