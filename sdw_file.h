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

#endif	// LIBSUNDAOWEN_SDW_FILE_H_
