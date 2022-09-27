#include "sdw_string.h"

void SetLocale()
{
#if SDW_PLATFORM == SDW_PLATFORM_MACOS
	setlocale(LC_ALL, "en_US.UTF-8");
#else
	setlocale(LC_ALL, "");
#endif
}

n8 SToN8(const string& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<n8>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

n8 SToN8(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<n8>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

n16 SToN16(const string& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<n16>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

n16 SToN16(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<n16>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

n32 SToN32(const string& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<n32>(strtol(a_sString.c_str(), nullptr, a_nRadix));
}

n32 SToN32(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<n32>(wcstol(a_sString.c_str(), nullptr, a_nRadix));
}

n64 SToN64(const string& a_sString, int a_nRadix /* = 10 */)
{
	return strtoll(a_sString.c_str(), nullptr, a_nRadix);
}

n64 SToN64(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return wcstoll(a_sString.c_str(), nullptr, a_nRadix);
}

u8 SToU8(const string& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<u8>(strtoul(a_sString.c_str(), nullptr, a_nRadix));
}

u8 SToU8(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<u8>(wcstoul(a_sString.c_str(), nullptr, a_nRadix));
}

u16 SToU16(const string& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<u16>(strtoul(a_sString.c_str(), nullptr, a_nRadix));
}

u16 SToU16(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<u16>(wcstoul(a_sString.c_str(), nullptr, a_nRadix));
}

u32 SToU32(const string& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<u32>(strtoul(a_sString.c_str(), nullptr, a_nRadix));
}

u32 SToU32(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return static_cast<u32>(wcstoul(a_sString.c_str(), nullptr, a_nRadix));
}

u64 SToU64(const string& a_sString, int a_nRadix /* = 10 */)
{
	return strtoull(a_sString.c_str(), nullptr, a_nRadix);
}

u64 SToU64(const wstring& a_sString, int a_nRadix /* = 10 */)
{
	return wcstoull(a_sString.c_str(), nullptr, a_nRadix);
}

f32 SToF32(const string& a_sString)
{
	return static_cast<f32>(strtod(a_sString.c_str(), nullptr));
}

f32 SToF32(const wstring& a_sString)
{
	return static_cast<f32>(wcstod(a_sString.c_str(), nullptr));
}

f64 SToF64(const string& a_sString)
{
	return strtod(a_sString.c_str(), nullptr);
}

f64 SToF64(const wstring& a_sString)
{
	return wcstod(a_sString.c_str(), nullptr);
}

#if (SDW_COMPILER == SDW_COMPILER_MSC && SDW_COMPILER_VERSION < 1600) || (SDW_PLATFORM == SDW_PLATFORM_WINDOWS && SDW_COMPILER != SDW_COMPILER_MSC)
string WToU8(const wstring& a_sString)
{
	int nLength = WideCharToMultiByte(CP_UTF8, 0, a_sString.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* pTemp = new char[nLength];
	WideCharToMultiByte(CP_UTF8, 0, a_sString.c_str(), -1, pTemp, nLength, nullptr, nullptr);
	string sString = pTemp;
	delete[] pTemp;
	return sString;
}

string WToU8_TS(const wstring& a_sString)
{
	return WToU8(a_sString);
}

string U16ToU8(const U16String& a_sString)
{
	return WToU8(a_sString);
}

string U16ToU8_TS(const U16String& a_sString)
{
	return WToU8_TS(a_sString);
}

wstring U8ToW(const string& a_sString)
{
	int nLength = MultiByteToWideChar(CP_UTF8, 0, a_sString.c_str(), -1, nullptr, 0);
	wchar_t* pTemp = new wchar_t[nLength];
	MultiByteToWideChar(CP_UTF8, 0, a_sString.c_str(), -1, pTemp, nLength);
	wstring sString = pTemp;
	delete[] pTemp;
	return sString;
}

wstring U8ToW_TS(const string& a_sString)
{
	return U8ToW(a_sString);
}

wstring U16ToW(const U16String& a_sString)
{
	return a_sString;
}

wstring U16ToW_TS(const U16String& a_sString)
{
	return a_sString;
}

U16String U8ToU16(const string& a_sString)
{
	return U8ToW(a_sString);
}

U16String U8ToU16_TS(const string& a_sString)
{
	return U8ToW_TS(a_sString);
}

U16String WToU16(const wstring& a_sString)
{
	return a_sString;
}

U16String WToU16_TS(const wstring& a_sString)
{
	return a_sString;
}
#elif (SDW_COMPILER == SDW_COMPILER_GNUC && SDW_COMPILER_VERSION < 50400) || SDW_PLATFORM == SDW_PLATFORM_CYGWIN
string WToU8(const wstring& a_sString)
{
	return TSToS<wstring, string>(a_sString, "WCHAR_T", "UTF-8");
}

string WToU8_TS(const wstring& a_sString)
{
	return WToU8(a_sString);
}

string U16ToU8(const U16String& a_sString)
{
	return TSToS<U16String, string>(a_sString, "UTF-16LE", "UTF-8");
}

string U16ToU8_TS(const U16String& a_sString)
{
	return U16ToU8(a_sString);
}

wstring U8ToW(const string& a_sString)
{
	return TSToS<string, wstring>(a_sString, "UTF-8", "WCHAR_T");
}

wstring U8ToW_TS(const string& a_sString)
{
	return U8ToW(a_sString);
}

wstring U16ToW(const U16String& a_sString)
{
	return TSToS<U16String, wstring>(a_sString, "UTF-16LE", "WCHAR_T");
}

wstring U16ToW_TS(const U16String& a_sString)
{
	return U16ToW(a_sString);
}

U16String U8ToU16(const string& a_sString)
{
	return TSToS<string, U16String>(a_sString, "UTF-8", "UTF-16LE");
}

U16String U8ToU16_TS(const string& a_sString)
{
	return U8ToU16(a_sString);
}

U16String WToU16(const wstring& a_sString)
{
	return TSToS<wstring, U16String>(a_sString, "WCHAR_T", "UTF-16LE");
}

U16String WToU16_TS(const wstring& a_sString)
{
	return WToU16(a_sString);
}
#else
string WToU8(const wstring& a_sString)
{
	static wstring_convert<codecvt_utf8<wchar_t>> c_cvt_u8;
	return c_cvt_u8.to_bytes(a_sString);
}

string WToU8_TS(const wstring& a_sString)
{
	wstring_convert<codecvt_utf8<wchar_t>> c_cvt_u8;
	return c_cvt_u8.to_bytes(a_sString);
}

string U16ToU8(const U16String& a_sString)
{
	static wstring_convert<codecvt_utf8_utf16<Char16_t>, Char16_t> c_cvt_u8_u16;
	return c_cvt_u8_u16.to_bytes(a_sString);
}

string U16ToU8_TS(const U16String& a_sString)
{
	wstring_convert<codecvt_utf8_utf16<Char16_t>, Char16_t> c_cvt_u8_u16;
	return c_cvt_u8_u16.to_bytes(a_sString);
}

wstring U8ToW(const string& a_sString)
{
	static wstring_convert<codecvt_utf8<wchar_t>> c_cvt_u8;
	return c_cvt_u8.from_bytes(a_sString);
}

wstring U8ToW_TS(const string& a_sString)
{
	wstring_convert<codecvt_utf8<wchar_t>> c_cvt_u8;
	return c_cvt_u8.from_bytes(a_sString);
}

wstring U16ToW(const U16String& a_sString)
{
	return U8ToW(U16ToU8(a_sString));
}

wstring U16ToW_TS(const U16String& a_sString)
{
	return U8ToW_TS(U16ToU8_TS(a_sString));
}

U16String U8ToU16(const string& a_sString)
{
	static wstring_convert<codecvt_utf8_utf16<Char16_t>, Char16_t> c_cvt_u8_u16;
	return c_cvt_u8_u16.from_bytes(a_sString);
}

U16String U8ToU16_TS(const string& a_sString)
{
	wstring_convert<codecvt_utf8_utf16<Char16_t>, Char16_t> c_cvt_u8_u16;
	return c_cvt_u8_u16.from_bytes(a_sString);
}

U16String WToU16(const wstring& a_sString)
{
	return U8ToU16(WToU8(a_sString));
}

U16String WToU16_TS(const wstring& a_sString)
{
	return U8ToU16_TS(WToU8_TS(a_sString));
}
#endif

string AToU8(const string& a_sString)
{
	return WToU8(AToW(a_sString));
}

string AToU8_TS(const string& a_sString)
{
	return WToU8_TS(AToW_TS(a_sString));
}

string U8ToA(const string& a_sString)
{
	return WToA(U8ToW(a_sString));
}

string U8ToA_TS(const string& a_sString)
{
	return WToA_TS(U8ToW_TS(a_sString));
}

U16String AToU16(const string& a_sString)
{
	return WToU16(AToW(a_sString));
}

U16String AToU16_TS(const string& a_sString)
{
	return WToU16_TS(AToW_TS(a_sString));
}

string U16ToA(const U16String& a_sString)
{
	return WToA(U16ToW(a_sString));
}

string U16ToA_TS(const U16String& a_sString)
{
	return WToA_TS(U16ToW_TS(a_sString));
}

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
wstring AToW(const string& a_sString)
{
	int nLength = MultiByteToWideChar(CP_ACP, 0, a_sString.c_str(), -1, nullptr, 0);
	wchar_t* pTemp = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, a_sString.c_str(), -1, pTemp, nLength);
	wstring sString = pTemp;
	delete[] pTemp;
	return sString;
}

wstring AToW_TS(const string& a_sString)
{
	return AToW(a_sString);
}

string WToA(const wstring& a_sString)
{
	int nLength = WideCharToMultiByte(CP_ACP, 0, a_sString.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* pTemp = new char[nLength];
	WideCharToMultiByte(CP_ACP, 0, a_sString.c_str(), -1, pTemp, nLength, nullptr, nullptr);
	string sString = pTemp;
	delete[] pTemp;
	return sString;
}

string WToA_TS(const wstring& a_sString)
{
	return WToA(a_sString);
}
#else
wstring AToW(const string& a_sString)
{
	return U8ToW(a_sString);
}

wstring AToW_TS(const string& a_sString)
{
	return U8ToW_TS(a_sString);
}

string WToA(const wstring& a_sString)
{
	return WToU8(a_sString);
}

string WToA_TS(const wstring& a_sString)
{
	return WToU8_TS(a_sString);
}
#endif

#if defined(SDW_XCONVERT)
#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
wstring XToW(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	int nLength = MultiByteToWideChar(a_nCodePage, 0, a_sString.c_str(), -1, nullptr, 0);
	wchar_t* pTemp = new wchar_t[nLength];
	MultiByteToWideChar(a_nCodePage, 0, a_sString.c_str(), -1, pTemp, nLength);
	wstring sString = pTemp;
	delete[] pTemp;
	return sString;
}

wstring XToW_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return XToW(a_sString, a_nCodePage, a_pCodeName);
}

string WToX(const wstring& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	int nLength = WideCharToMultiByte(a_nCodePage, 0, a_sString.c_str(), -1, nullptr, 0, nullptr, nullptr);
	char* pTemp = new char[nLength];
	WideCharToMultiByte(a_nCodePage, 0, a_sString.c_str(), -1, pTemp, nLength, nullptr, nullptr);
	string sString = pTemp;
	delete[] pTemp;
	return sString;
}

string WToX_TS(const wstring& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX(a_sString, a_nCodePage, a_pCodeName);
}
#else
wstring XToW(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return TSToS<string, wstring>(a_sString, a_pCodeName, "WCHAR_T");
}

wstring XToW_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return XToW(a_sString, a_nCodePage, a_pCodeName);
}

string WToX(const wstring& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return TSToS<wstring, string>(a_sString, "WCHAR_T", a_pCodeName);
}

string WToX_TS(const wstring& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX(a_sString, a_nCodePage, a_pCodeName);
}
#endif

string XToU8(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToU8(XToW(a_sString, a_nCodePage, a_pCodeName));
}

string XToU8_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToU8_TS(XToW_TS(a_sString, a_nCodePage, a_pCodeName));
}

string U8ToX(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX(U8ToW(a_sString), a_nCodePage, a_pCodeName);
}

string U8ToX_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX_TS(U8ToW_TS(a_sString), a_nCodePage, a_pCodeName);
}

U16String XToU16(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToU16(XToW(a_sString, a_nCodePage, a_pCodeName));
}

U16String XToU16_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToU16_TS(XToW_TS(a_sString, a_nCodePage, a_pCodeName));
}

string U16ToX(const U16String& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX(U16ToW(a_sString), a_nCodePage, a_pCodeName);
}

string U16ToX_TS(const U16String& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX_TS(U16ToW_TS(a_sString), a_nCodePage, a_pCodeName);
}

string XToA(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToA(XToW(a_sString, a_nCodePage, a_pCodeName));
}

string XToA_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToA_TS(XToW_TS(a_sString, a_nCodePage, a_pCodeName));
}

string AToX(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX(AToW(a_sString), a_nCodePage, a_pCodeName);
}

string AToX_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX_TS(AToW_TS(a_sString), a_nCodePage, a_pCodeName);
}

UString XToU(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToU(XToW(a_sString, a_nCodePage, a_pCodeName));
}

UString XToU_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToU_TS(XToW_TS(a_sString, a_nCodePage, a_pCodeName));
}

string UToX(const UString& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX(UToW(a_sString), a_nCodePage, a_pCodeName);
}

string UToX_TS(const UString& a_sString, int a_nCodePage, const char* a_pCodeName)
{
	return WToX_TS(UToW_TS(a_sString), a_nCodePage, a_pCodeName);
}
#endif

string Format(const char* a_szFormat, ...)
{
	va_list vaList;
	va_start(vaList, a_szFormat);
	int nBufferSize = vsnprintf(nullptr, 0, a_szFormat, vaList);
	va_end(vaList);
	if (nBufferSize <= 0)
	{
		return "";
	}
	string sBuffer;
	sBuffer.resize(nBufferSize + 1);
	va_start(vaList, a_szFormat);
	vsnprintf(&*sBuffer.begin(), nBufferSize + 1, a_szFormat, vaList);
	va_end(vaList);
	sBuffer.erase(nBufferSize);
	return sBuffer;
}

wstring Format(const wchar_t* a_szFormat, ...)
{
	va_list vaList;
	va_start(vaList, a_szFormat);
	int nBufferSize = vswprintf(nullptr, 0, a_szFormat, vaList);
	va_end(vaList);
	if (nBufferSize <= 0)
	{
		return L"";
	}
	wstring sBuffer;
	sBuffer.resize(nBufferSize + 1);
	va_start(vaList, a_szFormat);
	vswprintf(&*sBuffer.begin(), nBufferSize + 1, a_szFormat, vaList);
	va_end(vaList);
	sBuffer.erase(nBufferSize);
	return sBuffer;
}
