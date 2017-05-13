#include <BELogger.h>

int main()
{
	BlackEngine::Logger logger;

	logger.StartLogger("test");

	logger.SendMessage(logger.BE_FATALERROR, "error fatal.", 37);

	return 0;
}