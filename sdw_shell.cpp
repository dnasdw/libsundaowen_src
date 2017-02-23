#include "sdw_shell.h"
#include "sdw_platform.h"
#include "sdw_type.h"

void Pause()
{
#if SDW_COMPILER == SDW_COMPILER_MSC
	system("PAUSE");
#else
	execlp("bash", "bash", "-c", "read -rsp \"Press any key to continue . . . \" -n 1 && echo", nullptr);
#endif
}
