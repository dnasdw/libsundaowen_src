#include "sdw_module.h"
#include "sdw_platform.h"
#include "sdw_string.h"

const UString& UGetModuleFileName()
{
	const u32 uMaxPath = 4096;
	static UString c_sFileName;
	if (!c_sFileName.empty())
	{
		return c_sFileName;
	}
	UString sFileName(uMaxPath, USTR('\0'));
	u32 uSize = 0;
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	uSize = GetModuleFileNameW(nullptr, &*sFileName.begin(), uMaxPath);
#elif SDW_PLATFORM == SDW_PLATFORM_MACOS
	char szPath[uMaxPath] = {};
	u32 uPathSize = uMaxPath;
	if (_NSGetExecutablePath(szPath, &uPathSize) != 0)
	{
		sFileName.clear();
		printf("ERROR: _NSGetExecutablePath error\n\n");
	}
	else if (realpath(szPath, &*sFileName.begin()) == nullptr)
	{
		sFileName.clear();
		printf("ERROR: realpath error\n\n");
	}
	uSize = strlen(sFileName.c_str());
#elif SDW_PLATFORM == SDW_PLATFORM_LINUX || SDW_PLATFORM == SDW_PLATFORM_CYGWIN
	ssize_t nCount = readlink("/proc/self/exe", &*sFileName.begin(), uMaxPath);
	if (nCount == -1)
	{
		sFileName.clear();
		printf("ERROR: readlink /proc/self/exe error\n\n");
	}
	else
	{
		sFileName[nCount] = '\0';
	}
	uSize = strlen(sFileName.c_str());
#endif
	sFileName.erase(uSize);
	sFileName = Replace(sFileName, USTR('\\'), USTR('/'));
	c_sFileName = sFileName;
	return c_sFileName;
}

const UString& UGetModuleDirName()
{
	static UString c_sDirName;
	if (!c_sDirName.empty())
	{
		return c_sDirName;
	}
	UString sDirName = UGetModuleFileName();
	UString::size_type uPos = sDirName.rfind(USTR('/'));
	if (uPos != UString::npos)
	{
		sDirName.erase(uPos);
	}
	else
	{
		sDirName.clear();
	}
	c_sDirName = sDirName;
	return c_sDirName;
}
