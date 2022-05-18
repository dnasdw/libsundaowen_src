#ifndef LIBSUNDAOWEN_SDW_FILE_H_
#define LIBSUNDAOWEN_SDW_FILE_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#define Chsize _chsize_s
#define Fileno _fileno
#define UFopen FopenW
#define Fseek _fseeki64
#define Ftell _ftelli64
#define Lseek _lseeki64
#define URename _wrename
#else
#define Chsize ftruncate
#define Fileno fileno
#define UFopen Fopen
#define Fseek fseeko
#define Ftell ftello
#define Lseek lseek
#define URename rename
#endif

void fu16printf(FILE* a_pFile, const wchar_t* a_szFormat, ...);

bool UGetFileSize(const UString& a_sFileName, n64& a_nFileSize);

FILE* Fopen(const string& a_sFileName, const string& a_sMode, bool a_bVerbose = true);

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
FILE* FopenW(const wstring& a_sFileName, const wstring& a_sMode, bool a_bVerbose = true);
#endif

bool Seek(FILE* a_fpFile, n64 a_nOffset);

void CopyFile(FILE* a_fpDest, FILE* a_fpSrc, n64 a_nSrcOffset, n64 a_nSize);

void PadFile(FILE* a_fpFile, n64 a_nPadSize, u8 a_uPadData);

#endif	// LIBSUNDAOWEN_SDW_FILE_H_
