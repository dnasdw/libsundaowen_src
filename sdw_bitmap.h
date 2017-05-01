#ifndef LIBSUNDAOWEN_SDW_BITMAP_H_
#define LIBSUNDAOWEN_SDW_BITMAP_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#include SDW_MSC_PUSH_PACKED
#if SDW_PLATFORM != SDW_PLATFORM_WINDOWS
struct BITMAPFILEHEADER
{
	u16 bfType;
	u32 bfSize;
	u16 bfReserved1;
	u16 bfReserved2;
	u32 bfOffBits;
} SDW_GNUC_PACKED;

struct BITMAPINFOHEADER
{
	u32 biSize;
	n32 biWidth;
	n32 biHeight;
	u16 biPlanes;
	u16 biBitCount;
	u32 biCompression;
	u32 biSizeImage;
	n32 biXPelsPerMeter;
	n32 biYPelsPerMeter;
	u32 biClrUsed;
	u32 biClrImportant;
} SDW_GNUC_PACKED;
#endif
#include SDW_MSC_POP_PACKED

#ifndef BI_RGB
#define BI_RGB 0
#endif

#endif	// LIBSUNDAOWEN_SDW_BITMAP_H_
