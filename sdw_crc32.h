#ifndef LIBSUNDAOWEN_SDW_CRC32_H_
#define LIBSUNDAOWEN_SDW_CRC32_H_

#include "sdw_type.h"

u32 UpdateCRC32(const void* a_pData, u32 a_uSize, u32 a_uPreviousCRC32 = 0);

#endif	// LIBSUNDAOWEN_SDW_CRC32_H_
