#include "sdw_main.h"
#include "sdw_type.h"
#include "sdw_string.h"

#if defined(SDW_MAIN)
extern int UMain(int argc, UChar* argv[]);

int main(int argc, char* argv[])
{
	SetLocale();
	int nArgc = 0;
	UChar** pArgv = nullptr;
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	pArgv = CommandLineToArgvW(GetCommandLineW(), &nArgc);
	if (pArgv == nullptr)
	{
		return 1;
	}
#else
	nArgc = argc;
	pArgv = argv;
#endif
	int nResult = UMain(nArgc, pArgv);
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	LocalFree(pArgv);
#endif
	return nResult;
}
#endif
