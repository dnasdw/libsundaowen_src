#ifndef LIBSUNDAOWEN_SDW_DIR_H_
#define LIBSUNDAOWEN_SDW_DIR_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#define Mkdir _mkdir
#define UMkdir _wmkdir
#else
#define Mkdir(x) mkdir((x), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#define UMkdir Mkdir
#endif

bool UMakeDir(const UString::value_type* a_pDirName);

#endif	// LIBSUNDAOWEN_SDW_DIR_H_
