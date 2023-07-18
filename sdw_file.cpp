#include "sdw_file.h"
#include "sdw_string.h"

void fu16printf(FILE* a_pFile, const wchar_t* a_szFormat, ...)
{
	va_list vaList;
	va_start(vaList, a_szFormat);
	int nBufferSize = vswprintf(nullptr, 0, a_szFormat, vaList);
	va_end(vaList);
	if (nBufferSize < 0)
	{
		return;
	}
	wstring sBuffer;
	sBuffer.resize(nBufferSize + 1);
	va_start(vaList, a_szFormat);
	vswprintf(&*sBuffer.begin(), nBufferSize + 1, a_szFormat, vaList);
	va_end(vaList);
	sBuffer.erase(nBufferSize);
	U16String sString = WToU16(sBuffer);
	fwrite(sString.c_str(), 2, sString.size(), a_pFile);
}

bool UGetFileSize(const UString& a_sFileName, n64& a_nFileSize)
{
	Stat st;
	if (UStat(a_sFileName.c_str(), &st) != 0)
	{
		a_nFileSize = 0;
		return false;
	}
	a_nFileSize = st.st_size;
	return true;
}

FILE* Fopen(const string& a_sFileName, const string& a_sMode, bool a_bVerbose /* = true */)
{
	string sFileName = a_sFileName;
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
	static const size_t kMaxPath = 32768;
	char nFilePath[kMaxPath] = {};
	if (_fullpath(nFilePath, sFileName.c_str(), kMaxPath) == nullptr)
	{
		return nullptr;
	}
	sFileName = nFilePath;
	if (!StartWith(sFileName, "\\\\"))
	{
		sFileName = "\\\\?\\" + sFileName;
	}
#endif
	FILE* fp = fopen(sFileName.c_str(), a_sMode.c_str());
	if (fp == nullptr && a_bVerbose)
	{
		printf("ERROR: open file %s failed\n\n", a_sFileName.c_str());
	}
	return fp;
}

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
FILE* FopenW(const wstring& a_sFileName, const wstring& a_sMode, bool a_bVerbose /* = true */)
{
	wstring sFileName = a_sFileName;
	static const size_t kMaxPath = 32768;
	wchar_t uFilePath[kMaxPath] = {};
	if (_wfullpath(uFilePath, sFileName.c_str(), kMaxPath) == nullptr)
	{
		return nullptr;
	}
	sFileName = uFilePath;
	if (!StartWith(sFileName, L"\\\\"))
	{
		sFileName = L"\\\\?\\" + sFileName;
	}
	FILE* fp = _wfopen(sFileName.c_str(), a_sMode.c_str());
	if (fp == nullptr && a_bVerbose)
	{
		wprintf(L"ERROR: open file %ls failed\n\n", a_sFileName.c_str());
	}
	return fp;
}
#endif

bool Seek(FILE* a_fpFile, n64 a_nOffset)
{
	if (fflush(a_fpFile) != 0)
	{
		return false;
	}
	int nFd = Fileno(a_fpFile);
	if (nFd == -1)
	{
		return false;
	}
	Fseek(a_fpFile, 0, SEEK_END);
	n64 nFileSize = Ftell(a_fpFile);
	if (nFileSize < a_nOffset)
	{
		n64 nOffset = Lseek(nFd, a_nOffset - 1, SEEK_SET);
		if (nOffset == -1)
		{
			return false;
		}
		fputc(0, a_fpFile);
		fflush(a_fpFile);
	}
	else
	{
		Fseek(a_fpFile, a_nOffset, SEEK_SET);
	}
	return true;
}

void CopyFile(FILE* a_fpDest, FILE* a_fpSrc, n64 a_nSrcOffset, n64 a_nSize)
{
	const n64 nBufferSize = 0x100000;
	u8* pBuffer = new u8[nBufferSize];
	Fseek(a_fpSrc, a_nSrcOffset, SEEK_SET);
	while (a_nSize > 0)
	{
		n64 nSize = a_nSize > nBufferSize ? nBufferSize : a_nSize;
		fread(pBuffer, 1, static_cast<size_t>(nSize), a_fpSrc);
		fwrite(pBuffer, 1, static_cast<size_t>(nSize), a_fpDest);
		a_nSize -= nSize;
	}
	delete[] pBuffer;
}

void PadFile(FILE* a_fpFile, n64 a_nPadSize, u8 a_uPadData)
{
	const n64 nBufferSize = 0x100000;
	u8* pBuffer = new u8[nBufferSize];
	memset(pBuffer, a_uPadData, nBufferSize);
	while (a_nPadSize > 0)
	{
		n64 nSize = a_nPadSize > nBufferSize ? nBufferSize : a_nPadSize;
		fwrite(pBuffer, 1, static_cast<size_t>(nSize), a_fpFile);
		a_nPadSize -= nSize;
	}
	delete[] pBuffer;
}
