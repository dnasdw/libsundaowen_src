#include "sdw_file.h"
#include "sdw_string.h"

void FU16Printf(FILE* a_pFile, const wchar_t* a_szFormat, ...)
{
	va_list vaList;
	va_start(vaList, a_szFormat);
	wstring sFormatted = FormatV(a_szFormat, vaList);
	va_end(vaList);
	U16String sString = WToU16(sFormatted);
	fwrite(sString.c_str(), 2, sString.size(), a_pFile);
}
