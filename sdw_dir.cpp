#include "sdw_dir.h"

bool UMakeDir(const UChar* a_pDirName)
{
	if (UMkdir(a_pDirName) != 0)
	{
		if (errno != EEXIST)
		{
			return false;
		}
	}
	return true;
}
