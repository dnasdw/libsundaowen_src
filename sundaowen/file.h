#ifndef LIBSUNDAOWEN_SUNDAOWEN_FILE_H_
#define LIBSUNDAOWEN_SUNDAOWEN_FILE_H_

#include "platform.h"
#include "type.h"

#if SDW_COMPILER == SDW_COMPILER_MSC
#define Chsize _chsize_s
#define Fileno _fileno
#else
#define Chsize ftruncate
#define Fileno fileno
#endif

#endif	// LIBSUNDAOWEN_SUNDAOWEN_FILE_H_
