#ifndef LIBSUNDAOWEN_SDW_MAIN_H_
#define LIBSUNDAOWEN_SDW_MAIN_H_

#include "sdw_platform.h"

#if !defined(SDW_MAIN)
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#define UMain wmain
#else
#define UMain main
#endif
#endif

#endif	// LIBSUNDAOWEN_SDW_MAIN_H_
