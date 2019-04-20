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
	c_sFileName.resize(uMaxPath, USTR('\0'));
	u32 uSize = 0;
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	uSize = GetModuleFileNameW(nullptr, &*c_sFileName.begin(), uMaxPath);
#elif SDW_PLATFORM == SDW_PLATFORM_MACOS
	char szPath[uMaxPath] = {};
	u32 uPathSize = uMaxPath;
	if (_NSGetExecutablePath(szPath, &uPathSize) != 0)
	{
		c_sFileName.clear();
		printf("ERROR: _NSGetExecutablePath error\n\n");
	}
	else if (realpath(szPath, &*c_sFileName.begin()) == nullptr)
	{
		c_sFileName.clear();
		printf("ERROR: realpath error\n\n");
	}
	uSize = strlen(c_sFileName.c_str());
#elif SDW_PLATFORM == SDW_PLATFORM_LINUX || SDW_PLATFORM == SDW_PLATFORM_CYGWIN
	ssize_t nCount = readlink("/proc/self/exe", &*c_sFileName.begin(), uMaxPath);
	if (nCount == -1)
	{
		c_sFileName.clear();
		printf("ERROR: readlink /proc/self/exe error\n\n");
	}
	else
	{
		c_sFileName[nCount] = '\0';
	}
	uSize = strlen(c_sFileName.c_str());
#endif
	c_sFileName.erase(uSize);
	c_sFileName = Replace(c_sFileName, USTR('\\'), USTR('/'));
	return c_sFileName;
}

const UString& UGetModuleDirName()
{
	static UString c_sDirName;
	if (!c_sDirName.empty())
	{
		return c_sDirName;
	}
	c_sDirName = UGetModuleFileName();
	UString::size_type uPos = c_sDirName.rfind(USTR('/'));
	if (uPos != UString::npos)
	{
		c_sDirName.erase(uPos);
	}
	else
	{
		c_sDirName.clear();
	}
	return c_sDirName;
}
