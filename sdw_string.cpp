#include "sdw_string.h"

static const n32 s_nFormatBufferSize = 4096;

string FormatV(const char* a_szFormat, va_list a_vaList)
{
	static char c_szBuffer[s_nFormatBufferSize] = {};
	vsnprintf(c_szBuffer, s_nFormatBufferSize, a_szFormat, a_vaList);
	return c_szBuffer;
}

wstring FormatV(const wchar_t* a_szFormat, va_list a_vaList)
{
	static wchar_t c_szBuffer[s_nFormatBufferSize] = {};
	vswprintf(c_szBuffer, s_nFormatBufferSize, a_szFormat, a_vaList);
	return c_szBuffer;
}

string Format(const char* a_szFormat, ...)
{
	va_list vaList;
	va_start(vaList, a_szFormat);
	string sFormatted = FormatV(a_szFormat, vaList);
	va_end(vaList);
	return sFormatted;
}

wstring Format(const wchar_t* a_szFormat, ...)
{
	va_list vaList;
	va_start(vaList, a_szFormat);
	wstring sFormatted = FormatV(a_szFormat, vaList);
	va_end(vaList);
	return sFormatted;
}
