#ifndef LIBSUNDAOWEN_SDW_DIR_H_
#define LIBSUNDAOWEN_SDW_DIR_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#if SDW_COMPILER == SDW_COMPILER_MSC
#define MkdirA _mkdir
#define Mkdir _wmkdir
#else
#define MkdirA(x) mkdir((x), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#define Mkdir MkdirA
#endif

#endif	// LIBSUNDAOWEN_SDW_DIR_H_
