#include "sdw_shell.h"
#include "sdw_platform.h"
#include "sdw_type.h"

void Pause()
{
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	system("PAUSE");
#else
	system("bash -c \'read -rsp \"Press any key to continue . . . \" -n 1 && echo\'");
#endif
}
