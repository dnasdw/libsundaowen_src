#ifndef LIBSUNDAOWEN_SDW_DEFINE_H_
#define LIBSUNDAOWEN_SDW_DEFINE_H_

#include "sdw_type.h"

#define SDW_PURE = 0

#define SDW_ARRAY_COUNT(a) (sizeof(a) / sizeof(a[0]))

#define SDW_BIT32(n) (UINT32_C(1) << (n))

#define SDW_BIT64(n) (UINT64_C(1) << (n))

#define SDW_CONVERT_ENDIAN16(n) (((n) >> 8 & 0xFF) | ((n) << 8 & 0xFF00))

#define SDW_CONVERT_ENDIAN32(n) (((n) >> 24 & 0xFF) | ((n) >> 8 & 0xFF00) | ((n) << 8 & 0xFF0000) | ((n) << 24 & 0xFF000000))

#define SDW_CONVERT_ENDIAN64(n) (((n) >> 56 & UINT64_C(0xFF)) | ((n) >> 40 & UINT64_C(0xFF00)) | ((n) >> 24 & UINT64_C(0xFF0000)) | ((n) >> 8 & UINT64_C(0xFF000000)) | ((n) << 8 & UINT64_C(0xFF00000000)) | ((n) << 24 & UINT64_C(0xFF0000000000)) | ((n) << 40 & UINT64_C(0xFF000000000000)) | ((n) << 56 & UINT64_C(0xFF00000000000000)))

#endif	// LIBSUNDAOWEN_SDW_DEFINE_H_
