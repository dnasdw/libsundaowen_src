#include "sdw_module.h"
#include "sdw_platform.h"
#include "sdw_string.h"

const UString& UGetModuleFileName()
{
	const u32 uMaxPath = 4096;
	static UString sFileName;
	if (!sFileName.empty())
	{
		return sFileName;
	}
	sFileName.resize(uMaxPath, USTR('\0'));
	u32 uSize = 0;
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	uSize = GetModuleFileNameW(nullptr, &*sFileName.begin(), uMaxPath);
#elif SDW_PLATFORM == SDW_PLATFORM_MACOS
	char szPath[uMaxPath] = {};
	u32 uPathSize = uMaxPath;
	if (_NSGetExecutablePath(szPath, &uPathSize) != 0)
	{
		printf("ERROR: _NSGetExecutablePath error\n\n");
		sFileName.clear();
	}
	else if (realpath(szPath, &*sFileName.begin()) == nullptr)
	{
		printf("ERROR: realpath error\n\n");
		sFileName.clear();
	}
	uSize = strlen(sFileName.c_str());
#elif SDW_PLATFORM == SDW_PLATFORM_LINUX
	ssize_t nCount = readlink("/proc/self/exe", &*sFileName.begin(), uMaxPath);
	if (nCount == -1)
	{
		printf("ERROR: readlink /proc/self/exe error\n\n");
		sFileName.clear();
	}
	else
	{
		sFileName[nCount] = '\0';
	}
	uSize = strlen(sFileName.c_str());
#endif
	sFileName.erase(uSize);
	sFileName = Replace(sFileName, USTR('\\'), USTR('/'));
	return sFileName;
}

const UString& UGetModuleDirName()
{
	static UString sDirName;
	if (!sDirName.empty())
	{
		return sDirName;
	}
	sDirName = UGetModuleFileName();
	UString::size_type uPos = sDirName.rfind(USTR('/'));
	if (uPos != UString::npos)
	{
		sDirName.erase(uPos);
	}
	else
	{
		sDirName.clear();
	}
	return sDirName;
}
