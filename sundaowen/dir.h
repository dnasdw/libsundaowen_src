#ifndef LIBSUNDAOWEN_SUNDAOWEN_DIR_H_
#define LIBSUNDAOWEN_SUNDAOWEN_DIR_H_

#include "platform.h"
#include "type.h"

#if SDW_COMPILER == SDW_COMPILER_MSC
#define MkdirA _mkdir
#define Mkdir _wmkdir
#else
#define MkdirA(x) mkdir((x), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH)
#define Mkdir MkdirA
#endif

#endif	// LIBSUNDAOWEN_SUNDAOWEN_DIR_H_
