#include "include/vamplogger/logger.h"


static void SetLevel(VampLogger *tthis, unsigned int level)
{
    tthis->__level__ = level;
}


VampLogger *VampNewLogger(const char *name)
{
    VampLogger *new_logger = new VampLogger();

    new_logger->__level__   = VAMP_LOGGER_LEVEL_ERROR;
    new_logger->__name__    = std::string(name);
    new_logger->SetLevel    = SetLevel;

    return new_logger;
}

void VampDestroyLogger(VampLogger *logger)
{
    delete logger;
}