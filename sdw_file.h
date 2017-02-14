#ifndef LIBSUNDAOWEN_SDW_FILE_H_
#define LIBSUNDAOWEN_SDW_FILE_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#if SDW_COMPILER == SDW_COMPILER_MSC
#define Chsize _chsize_s
#define Fileno _fileno
#else
#define Chsize ftruncate
#define Fileno fileno
#endif

void FU16Printf(FILE* a_pFile, const wchar_t* a_szFormat, ...);

#endif	// LIBSUNDAOWEN_SDW_FILE_H_
