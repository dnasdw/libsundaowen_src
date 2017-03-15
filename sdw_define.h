#ifndef LIBSUNDAOWEN_SDW_DEFINE_H_
#define LIBSUNDAOWEN_SDW_DEFINE_H_

#define SDW_ARRAY_COUNT(a) (sizeof(a) / sizeof(a[0]))

#define SDW_BIT32(x) (1u << (x))

#define SDW_BIT64(x) (1uLL << (x))

#define SDW_CONVERT_ENDIAN16(n) (((n) >> 8 & 0xFF) | ((n) << 8 & 0xFF00))

#define SDW_CONVERT_ENDIAN32(n) (((n) >> 24 & 0xFF) | ((n) >> 8 & 0xFF00) | ((n) << 8 & 0xFF0000) | ((n) << 24 & 0xFF000000))

#endif	// LIBSUNDAOWEN_SDW_DEFINE_H_
