#include "shell.h"
#include "platform.h"
#include "type.h"

void Pause()
{
#if SDW_COMPILER == SDW_COMPILER_MSC
	system("PAUSE");
#else
	system("read -rsp \"Press any key to continue . . . \" -n 1");
#endif
}
