#include "sdw_string.h"

void SetLocale()
{
#if defined(__APPLE__)
	setlocale(LC_ALL, "en_US.UTF-8");
#else
	setlocale(LC_ALL, "");
#endif
}

n8 SToN8(const string& a_sString, n32 a_nRadix)
{
	return static_cast<n8>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

n8 SToN8(const wstring& a_sString, n32 a_nRadix)
{
	return static_cast<n8>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

n16 SToN16(const string& a_sString, n32 a_nRadix)
{
	return static_cast<n16>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

n16 SToN16(const wstring& a_sString, n32 a_nRadix)
{
	return static_cast<n16>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

n32 SToN32(const string& a_sString, n32 a_nRadix)
{
	return static_cast<n32>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

n32 SToN32(const wstring& a_sString, n32 a_nRadix)
{
	return static_cast<n32>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

n64 SToN64(const string& a_sString, n32 a_nRadix)
{
	return strtoll(a_sString.c_str(), nullptr, a_nRadix);
}

n64 SToN64(const wstring& a_sString, n32 a_nRadix)
{
	return wcstoll(a_sString.c_str(), nullptr, a_nRadix);
}

u8 SToU8(const string& a_sString, n32 a_nRadix)
{
	return static_cast<u8>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

u8 SToU8(const wstring& a_sString, n32 a_nRadix)
{
	return static_cast<u8>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

u16 SToU16(const string& a_sString, n32 a_nRadix)
{
	return static_cast<u16>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

u16 SToU16(const wstring& a_sString, n32 a_nRadix)
{
	return static_cast<u16>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

u32 SToU32(const string& a_sString, n32 a_nRadix)
{
	return static_cast<u32>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

u32 SToU32(const wstring& a_sString, n32 a_nRadix)
{
	return static_cast<u32>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

u64 SToU64(const string& a_sString, n32 a_nRadix)
{
	return strtoull(a_sString.c_str(), nullptr, a_nRadix);
}

u64 SToU64(const wstring& a_sString, n32 a_nRadix)
{
	return wcstoull(a_sString.c_str(), nullptr, a_nRadix);
}

#if SDW_COMPILER == SDW_COMPILER_MSC && SDW_COMPILER_VERSION < 1600
string WToU8(const wstring& a_sString)
{
	n32 nLength = WideCharToMultiByte(CP_UTF8, 0, a_sString.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* pTemp = new char[nLength];
	WideCharToMultiByte(CP_UTF8, 0, a_sString.c_str(), -1, pTemp, nLength, nullptr, nullptr);
	string sString = pTemp;
	delete[] pTemp;
	return sString;
}

string U16ToU8(const U16String& a_sString)
{
	return WToU8(a_sString);
}

wstring U8ToW(const string& a_sString)
{
	n32 nLength = MultiByteToWideChar(CP_UTF8, 0, a_sString.c_str(), -1, nullptr, 0);
	wchar_t* pTemp = new wchar_t[nLength];
	MultiByteToWideChar(CP_UTF8, 0, a_sString.c_str(), -1, pTemp, nLength);
	wstring sString = pTemp;
	delete[] pTemp;
	return sString;
}

wstring U16ToW(const U16String& a_sString)
{
	return a_sString;
}

U16String U8ToU16(const string& a_sString)
{
	return U8ToW(a_sString);
}

U16String WToU16(const wstring& a_sString)
{
	return a_sString;
}
#else
string WToU8(const wstring& a_sString)
{
	static wstring_convert<codecvt_utf8<wchar_t>> c_cvt_u8;
	return c_cvt_u8.to_bytes(a_sString);
}

string U16ToU8(const U16String& a_sString)
{
	static wstring_convert<codecvt_utf8_utf16<Char16_t>, Char16_t> c_cvt_u8_u16;
	return c_cvt_u8_u16.to_bytes(a_sString);
}

wstring U8ToW(const string& a_sString)
{
	static wstring_convert<codecvt_utf8<wchar_t>> c_cvt_u8;
	return c_cvt_u8.from_bytes(a_sString);
}

wstring U16ToW(const U16String& a_sString)
{
	return U8ToW(U16ToU8(a_sString));
}

U16String U8ToU16(const string& a_sString)
{
	static wstring_convert<codecvt_utf8_utf16<Char16_t>, Char16_t> c_cvt_u8_u16;
	return c_cvt_u8_u16.from_bytes(a_sString);
}

U16String WToU16(const wstring& a_sString)
{
	return U8ToU16(WToU8(a_sString));
}
#endif

#if SDW_COMPILER == SDW_COMPILER_MSC
wstring AToW(const string& a_sString)
{
	n32 nLength = MultiByteToWideChar(CP_ACP, 0, a_sString.c_str(), -1, nullptr, 0);
	wchar_t* pTemp = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, a_sString.c_str(), -1, pTemp, nLength);
	wstring sString = pTemp;
	delete[] pTemp;
	return sString;
}
#else
wstring AToW(const string& a_sString)
{
	return U8ToW(a_sString);
}
#endif

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
