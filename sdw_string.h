#ifndef LIBSUNDAOWEN_SDW_STRING_H_
#define LIBSUNDAOWEN_SDW_STRING_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#if SDW_COMPILER == SDW_COMPILER_MSC
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define wcscasecmp _wcsicmp
#define wcsncasecmp _wcsnicmp
#if SDW_COMPILER_VERSION < 1800
#define strtoll _strtoi64
#define strtoull _strtoui64
#define wcstoll _wcstoi64
#define wcstoull _wcstoui64
#endif
#endif
#define USTR(x) L##x
#define PRIUS USTR("ls")
#define UCscmp wcscmp
#define UCscasecmp wcscasecmp
#define UCsncasecmp wcsncasecmp
#define UCslen wcslen
#define UPrintf wprintf
#define UStat _wstat64
#else
#define USTR(x) x
#define PRIUS USTR("s")
#define UCscmp strcmp
#define UCscasecmp strcasecmp
#define UCsncasecmp strncasecmp
#define UCslen strlen
#define UPrintf printf
#define UStat stat
#endif

void SetLocale();

n8 SToN8(const string& a_sString, int a_nRadix = 10);
n8 SToN8(const wstring& a_sString, int a_nRadix = 10);
n16 SToN16(const string& a_sString, int a_nRadix = 10);
n16 SToN16(const wstring& a_sString, int a_nRadix = 10);
n32 SToN32(const string& a_sString, int a_nRadix = 10);
n32 SToN32(const wstring& a_sString, int a_nRadix = 10);
n64 SToN64(const string& a_sString, int a_nRadix = 10);
n64 SToN64(const wstring& a_sString, int a_nRadix = 10);
u8 SToU8(const string& a_sString, int a_nRadix = 10);
u8 SToU8(const wstring& a_sString, int a_nRadix = 10);
u16 SToU16(const string& a_sString, int a_nRadix = 10);
u16 SToU16(const wstring& a_sString, int a_nRadix = 10);
u32 SToU32(const string& a_sString, int a_nRadix = 10);
u32 SToU32(const wstring& a_sString, int a_nRadix = 10);
u64 SToU64(const string& a_sString, int a_nRadix = 10);
u64 SToU64(const wstring& a_sString, int a_nRadix = 10);
f32 SToF32(const string& a_sString);
f32 SToF32(const wstring& a_sString);
f64 SToF64(const string& a_sString);
f64 SToF64(const wstring& a_sString);

#if (SDW_COMPILER == SDW_COMPILER_GNUC && SDW_COMPILER_VERSION < 50400) || SDW_PLATFORM == SDW_PLATFORM_CYGWIN || (SDW_PLATFORM != SDW_PLATFORM_WINDOWS && defined(SDW_XCONVERT))
template<typename TSrc, typename TDest>
TDest TSToS(const TSrc& a_sString, const string& a_sSrcType, const string& a_sDestType)
{
	TDest sConverted;
	iconv_t cd = iconv_open(a_sDestType.c_str(), a_sSrcType.c_str());
	if (cd == reinterpret_cast<iconv_t>(-1))
	{
		return sConverted;
	}
	size_t uStringLeft = a_sString.size() * sizeof(typename TSrc::value_type);
	static const int c_nBufferSize = 1024;
	static const int c_nConvertBufferSize = c_nBufferSize - 4;
	char szBuffer[c_nBufferSize];
	typename TSrc::value_type* pString = const_cast<typename TSrc::value_type*>(a_sString.c_str());
	do
	{
		char* pBuffer = szBuffer;
		size_t uBufferLeft = c_nConvertBufferSize;
		int nError = static_cast<int>(iconv(cd, reinterpret_cast<char**>(&pString), &uStringLeft, &pBuffer, &uBufferLeft));
#if SDW_PLATFORM == SDW_PLATFORM_MACOS
		if (nError >= 0 || (nError == -1 && errno == E2BIG))
#else
		if (nError == 0 || (nError == -1 && errno == E2BIG))
#endif
		{
			*reinterpret_cast<typename TDest::value_type*>(szBuffer + c_nConvertBufferSize - uBufferLeft) = 0;
			sConverted += reinterpret_cast<typename TDest::value_type*>(szBuffer);
			if (nError == 0)
			{
				break;
			}
		}
		else
		{
			break;
		}
	} while (true);
	iconv_close(cd);
	return sConverted;
}
#endif

string WToU8(const wstring& a_sString);
string WToU8_TS(const wstring& a_sString);
string U16ToU8(const U16String& a_sString);
string U16ToU8_TS(const U16String& a_sString);
wstring U8ToW(const string& a_sString);
wstring U8ToW_TS(const string& a_sString);
wstring U16ToW(const U16String& a_sString);
wstring U16ToW_TS(const U16String& a_sString);
U16String U8ToU16(const string& a_sString);
U16String U8ToU16_TS(const string& a_sString);
U16String WToU16(const wstring& a_sString);
U16String WToU16_TS(const wstring& a_sString);
string AToU8(const string& a_sString);
string AToU8_TS(const string& a_sString);
string U8ToA(const string& a_sString);
string U8ToA_TS(const string& a_sString);
U16String AToU16(const string& a_sString);
U16String AToU16_TS(const string& a_sString);
string U16ToA(const U16String& a_sString);
string U16ToA_TS(const U16String& a_sString);
wstring AToW(const string& a_sString);
wstring AToW_TS(const string& a_sString);
string WToA(const wstring& a_sString);
string WToA_TS(const wstring& a_sString);

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#define U8ToU(x) U8ToW(x)
#define U8ToU_TS(x) U8ToW_TS(x)
#define UToU8(x) WToU8(x)
#define UToU8_TS(x) WToU8_TS(x)
#define WToU(x) wstring(x)
#define WToU_TS(x) wstring(x)
#define UToW(x) wstring(x)
#define UToW_TS(x) wstring(x)
#define U16ToU(x) U16ToW(x)
#define U16ToU_TS(x) U16ToW_TS(x)
#define UToU16(x) WToU16(x)
#define UToU16_TS(x) WToU16_TS(x)
#define AToU(x) AToW(x)
#define AToU_TS(x) AToW_TS(x)
#define UToA(x) WToA(x)
#define UToA_TS(x) WToA_TS(x)
#else
#define U8ToU(x) string(x)
#define U8ToU_TS(x) string(x)
#define UToU8(x) string(x)
#define UToU8_TS(x) string(x)
#define WToU(x) WToU8(x)
#define WToU_TS(x) WToU8_TS(x)
#define UToW(x) U8ToW(x)
#define UToW_TS(x) U8ToW_TS(x)
#define U16ToU(x) U16ToU8(x)
#define U16ToU_TS(x) U16ToU8_TS(x)
#define UToU16(x) U8ToU16(x)
#define UToU16_TS(x) U8ToU16_TS(x)
#define AToU(x) string(x)
#define AToU_TS(x) string(x)
#define UToA(x) string(x)
#define UToA_TS(x) string(x)
#endif

#if defined(SDW_XCONVERT)
wstring XToW(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
wstring XToW_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string WToX(const wstring& a_sString, int a_nCodePage, const char* a_pCodeName);
string WToX_TS(const wstring& a_sString, int a_nCodePage, const char* a_pCodeName);
string XToU8(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string XToU8_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string U8ToX(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string U8ToX_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
U16String XToU16(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
U16String XToU16_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string U16ToX(const U16String& a_sString, int a_nCodePage, const char* a_pCodeName);
string U16ToX_TS(const U16String& a_sString, int a_nCodePage, const char* a_pCodeName);
string XToA(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string XToA_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string AToX(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string AToX_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
UString XToU(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
UString XToU_TS(const string& a_sString, int a_nCodePage, const char* a_pCodeName);
string UToX(const UString& a_sString, int a_nCodePage, const char* a_pCodeName);
string UToX_TS(const UString& a_sString, int a_nCodePage, const char* a_pCodeName);
#endif

string Format(const char* a_szFormat, ...);
wstring Format(const wchar_t* a_szFormat, ...);

template<typename T>
T Replace(const T& a_sString, typename T::value_type a_cSubChar, typename T::value_type a_cReplacement)
{
	T sString = a_sString;
	replace(sString.begin(), sString.end(), a_cSubChar, a_cReplacement);
	return sString;
}

template<typename T>
T Replace(const T& a_sString, typename T::value_type a_cSubChar, const T& a_sReplacement)
{
	T sString = a_sString;
	typename T::size_type uPos = 0;
	while ((uPos = sString.find(a_cSubChar, uPos)) != T::npos)
	{
		sString.replace(uPos, 1, a_sReplacement);
		uPos += a_sReplacement.size();
	}
	return sString;
}

template<typename T>
T Replace(const T& a_sString, typename T::value_type a_cSubChar, const typename T::value_type* a_pReplacement)
{
	if (a_pReplacement == nullptr)
	{
		return a_sString;
	}
	else
	{
		return Replace(a_sString, a_cSubChar, T(a_pReplacement));
	}
}

template<typename T>
T Replace(const T& a_sString, const T& a_sSubString, const T& a_sReplacement)
{
	T sString = a_sString;
	typename T::size_type uPos = 0;
	while ((uPos = sString.find(a_sSubString, uPos)) != T::npos)
	{
		sString.replace(uPos, a_sSubString.size(), a_sReplacement);
		uPos += a_sReplacement.size();
	}
	return sString;
}

template<typename T>
T Replace(const T& a_sString, const T& a_sSubString, const typename T::value_type* a_pReplacement)
{
	if (a_pReplacement == nullptr)
	{
		return a_sString;
	}
	else
	{
		return Replace(a_sString, a_sSubString, T(a_pReplacement));
	}
}

template<typename T>
T Replace(const T& a_sString, const typename T::value_type* a_pSubString, const T& a_sReplacement)
{
	if (a_pSubString == nullptr)
	{
		return a_sString;
	}
	else
	{
		return Replace(a_sString, T(a_pSubString), a_sReplacement);
	}
}

template<typename T>
T Replace(const T& a_sString, const typename T::value_type* a_pSubString, const typename T::value_type* a_pReplacement)
{
	if (a_pSubString == nullptr || a_pReplacement == nullptr)
	{
		return a_sString;
	}
	else
	{
		return Replace(a_sString, T(a_pSubString), T(a_pReplacement));
	}
}

template<typename T>
vector<T> Split(const T& a_sString, const T& a_sSeparator)
{
	vector<T> vString;
	if (a_sSeparator.size() != 0)
	{
		for (typename T::size_type uOffset = 0; uOffset <= a_sString.size(); uOffset += a_sSeparator.size())
		{
			typename T::size_type uPos = a_sString.find(a_sSeparator, uOffset);
			if (uPos != T::npos)
			{
				vString.push_back(a_sString.substr(uOffset, uPos - uOffset));
				uOffset = uPos;
			}
			else
			{
				vString.push_back(a_sString.substr(uOffset));
				break;
			}
		}
	}
	else
	{
		vString.push_back(a_sString);
	}
	return vString;
}

template<typename T>
vector<T> Split(const T& a_sString, const typename T::value_type* a_pSeparator)
{
	if (a_pSeparator == nullptr)
	{
		vector<T> vString;
		vString.push_back(a_sString);
		return vString;
	}
	else
	{
		return Split(a_sString, T(a_pSeparator));
	}
}

template<typename T>
vector<T> SplitOf(const T& a_sString, const T& a_sSeparatorSet)
{
	vector<T> vString;
	if (a_sSeparatorSet.size() != 0)
	{
		for (typename T::size_type uOffset = 0; uOffset <= a_sString.size(); uOffset++)
		{
			typename T::size_type uPos = a_sString.find_first_of(a_sSeparatorSet, uOffset);
			if (uPos != T::npos)
			{
				vString.push_back(a_sString.substr(uOffset, uPos - uOffset));
				uOffset = uPos;
			}
			else
			{
				vString.push_back(a_sString.substr(uOffset));
				break;
			}
		}
	}
	else
	{
		vString.push_back(a_sString);
	}
	return vString;
}

template<typename T>
vector<T> SplitOf(const T& a_sString, const typename T::value_type* a_pSeparatorSet)
{
	if (a_pSeparatorSet == nullptr)
	{
		vector<T> vString;
		vString.push_back(a_sString);
		return vString;
	}
	else
	{
		return SplitOf(a_sString, T(a_pSeparatorSet));
	}
}

template<typename T>
vector<T> RegexSplitWith(const T& a_sString, const T& a_sSeparatorSet)
{
	vector<T> vString;
	if (a_sSeparatorSet.size() != 0)
	{
		basic_regex<typename T::value_type> rgx(a_sSeparatorSet, regex_constants::ECMAScript);
		match_results<typename T::const_iterator> match;
		typename T::size_type uOffset = 0;
		typename T::size_type uPos = uOffset;
		while (uOffset <= a_sString.size())
		{
			if (regex_search(a_sString.begin() + uPos, a_sString.end(), match, rgx))
			{
				typename T::size_type uSize = match.length();
				if (uSize == 0)
				{
					vString.push_back(a_sString.substr(uOffset));
					break;
				}
				uPos += match.position();
				vString.push_back(a_sString.substr(uOffset, uPos - uOffset));
				uOffset = uPos;
				uPos += uSize;
			}
			else
			{
				vString.push_back(a_sString.substr(uOffset));
				break;
			}
		}
	}
	else
	{
		vString.push_back(a_sString);
	}
	return vString;
}

template<typename T>
vector<T> RegexSplitWith(const T& a_sString, const typename T::value_type* a_pSeparatorSet)
{
	if (a_pSeparatorSet == nullptr)
	{
		vector<T> vString;
		vString.push_back(a_sString);
		return vString;
	}
	else
	{
		return RegexSplitWith(a_sString, T(a_pSeparatorSet));
	}
}

template<typename T>
vector<T> RegexSplitWithCut(const T& a_sString, const T& a_sSeparatorSet)
{
	vector<T> vString;
	if (a_sSeparatorSet.size() != 0)
	{
		basic_regex<typename T::value_type> rgx(a_sSeparatorSet, regex_constants::ECMAScript);
		match_results<typename T::const_iterator> match;
		typename T::size_type uOffset = 0;
		while (uOffset <= a_sString.size())
		{
			if (regex_search(a_sString.begin() + uOffset, a_sString.end(), match, rgx))
			{
				typename T::size_type uSize = match.length();
				if (uSize == 0)
				{
					vString.push_back(a_sString.substr(uOffset));
					break;
				}
				typename T::size_type uPos = uOffset + match.position();
				vString.push_back(a_sString.substr(uOffset, uPos - uOffset));
				vString.push_back(a_sString.substr(uPos, uSize));
				uOffset = uPos + uSize;
			}
			else
			{
				vString.push_back(a_sString.substr(uOffset));
				break;
			}
		}
	}
	else
	{
		vString.push_back(a_sString);
	}
	return vString;
}

template<typename T>
vector<T> RegexSplitWithCut(const T& a_sString, const typename T::value_type* a_pSeparatorSet)
{
	if (a_pSeparatorSet == nullptr)
	{
		vector<T> vString;
		vString.push_back(a_sString);
		return vString;
	}
	else
	{
		return RegexSplitWithCut(a_sString, T(a_pSeparatorSet));
	}
}

template<typename T>
bool StartWith(const T& a_sString, const T& a_sPrefix, typename T::size_type a_uStart = 0)
{
	if (a_uStart > a_sString.size())
	{
		return false;
	}
	else
	{
		return a_sString.compare(a_uStart, a_sPrefix.size(), a_sPrefix) == 0;
	}
}

template<typename T>
bool StartWith(const T& a_sString, const typename T::value_type* a_pPrefix, typename T::size_type a_uStart = 0)
{
	if (a_pPrefix == nullptr)
	{
		return false;
	}
	else
	{
		return StartWith(a_sString, T(a_pPrefix), a_uStart);
	}
}

template<typename T>
bool EndWith(const T& a_sString, const T& a_sSuffix)
{
	if (a_sString.size() < a_sSuffix.size())
	{
		return false;
	}
	else
	{
		return a_sString.compare(a_sString.size() - a_sSuffix.size(), a_sSuffix.size(), a_sSuffix) == 0;
	}
}

template<typename T>
bool EndWith(const T& a_sString, const typename T::value_type* a_pSuffix)
{
	if (a_pSuffix == nullptr)
	{
		return false;
	}
	else
	{
		return EndWith(a_sString, T(a_pSuffix));
	}
}

template<typename T>
T Trim(const T& a_sString)
{
	typename T::size_type uSize = a_sString.size();
	typename T::size_type uPos = 0;
	while (uPos < uSize && a_sString[uPos] >= 0 && a_sString[uPos] <= static_cast<typename T::value_type>(' '))
	{
		uPos++;
	}
	while (uPos < uSize && a_sString[uSize - 1] >= 0 && a_sString[uSize - 1] <= static_cast<typename T::value_type>(' '))
	{
		uSize--;
	}
	if (uPos > 0 || uSize < a_sString.size())
	{
		return a_sString.substr(uPos, uSize - uPos);
	}
	else
	{
		return a_sString;
	}
}

#endif	// LIBSUNDAOWEN_SDW_STRING_H_
