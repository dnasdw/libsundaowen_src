#include "sdw_dir.h"
#include "sdw_string.h"

bool UMakeDir(const UString& a_sDirName)
{
	UString sDirPrefix;
	UString sDirName = a_sDirName;
	UString sSeperator = USTR("/");
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	static const size_t kMaxPath = 32768;
	wchar_t uDirPath[kMaxPath] = {};
	if (_wfullpath(uDirPath, UToW(sDirName).c_str(), kMaxPath) == nullptr)
	{
		return false;
	}
	sDirName = WToU(uDirPath);
	if (!StartWith(sDirName, USTR("\\\\")))
	{
		sDirName = USTR("\\\\?\\") + sDirName;
	}
	if (StartWith(sDirName, USTR("\\\\?\\")))
	{
		sDirPrefix = USTR("\\\\?\\");
		sSeperator = USTR("\\");
	}
	else if (StartWith(sDirName, USTR("\\\\")))
	{
		sDirPrefix = USTR("\\\\");
		sSeperator = USTR("\\");
	}
	sDirName = sDirName.substr(sDirPrefix.size());
#endif
	vector<UString> vDir = SplitOf(sDirName, USTR("/\\"));
	sDirName = sDirPrefix;
	for (int i = 0; i < static_cast<int>(vDir.size()); i++)
	{
		if (i != 0)
		{
			sDirName += sSeperator;
		}
		sDirName += vDir[i];
		if ((!sDirPrefix.empty() && i < 1) || sDirName.empty())
		{
			// do nothing
		}
		else
		{
			UMkdir(sDirName.c_str());
		}
	}
	if (UMkdir(sDirName.c_str()) != 0)
	{
		if (errno != EEXIST)
		{
			return false;
		}
	}
	return true;
}
