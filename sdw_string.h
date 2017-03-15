#ifndef LIBSUNDAOWEN_SDW_STRING_H_
#define LIBSUNDAOWEN_SDW_STRING_H_

#include "sdw_platform.h"
#include "sdw_type.h"

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

string WToU8(const wstring& a_sString);
string U16ToU8(const U16String& a_sString);
wstring U8ToW(const string& a_sString);
wstring U16ToW(const U16String& a_sString);
U16String U8ToU16(const string& a_sString);
U16String WToU16(const wstring& a_sString);
string AToU8(const string& a_sString);
wstring AToW(const string& a_sString);

#if SDW_PLATFORM == SDW_PLATFORM_WINDOWS
#define U16ToU(x) U16ToW(x)
#define UToU16(x) WToU16(x)
#define AToU(x) AToW(x)
#else
#define U16ToU(x) U16ToU8(x)
#define UToU16(x) U8ToU16(x)
#define AToU(x) string(x)
#endif

string FormatV(const char* a_szFormat, va_list a_vaList);
wstring FormatV(const wchar_t* a_szFormat, va_list a_vaList);
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
	for (typename T::size_type uOffset = 0; uOffset < a_sString.size(); uOffset += a_sSeparator.size())
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
	if (vString.empty())
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
	for (typename T::const_iterator it = a_sString.begin(); it != a_sString.end(); ++it)
	{
		typename T::const_iterator itPos = find_first_of(it, a_sString.end(), a_sSeparatorSet.begin(), a_sSeparatorSet.end());
		if (itPos != a_sString.end())
		{
			vString.push_back(a_sString.substr(it - a_sString.begin(), itPos - it));
			it = itPos;
		}
		else
		{
			vString.push_back(a_sString.substr(it - a_sString.begin()));
			break;
		}
	}
	if (vString.empty())
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
	basic_regex<typename T::value_type> rgx(a_sSeparatorSet, regex_constants::ECMAScript);
	match_results<typename T::const_iterator> match;
	typename T::size_type uPos0 = 0;
	typename T::size_type uPos1 = 0;
	while (regex_search(a_sString.begin() + uPos1, a_sString.end(), match, rgx))
	{
		uPos1 += match.position();
		if (uPos1 != uPos0)
		{
			vString.push_back(a_sString.substr(uPos0, uPos1 - uPos0));
			uPos0 = uPos1;
		}
		uPos1 += match.length();
	}
	if (uPos0 != a_sString.size())
	{
		vString.push_back(a_sString.substr(uPos0));
	}
	if (vString.empty())
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
	basic_regex<typename T::value_type> rgx(a_sSeparatorSet, regex_constants::ECMAScript);
	match_results<typename T::const_iterator> match;
	typename T::size_type uPos0 = 0;
	typename T::size_type uPos1 = 0;
	while (regex_search(a_sString.begin() + uPos1, a_sString.end(), match, rgx))
	{
		uPos1 += match.position();
		typename T::size_type uSize = match.length();
		if (uPos1 != uPos0)
		{
			vString.push_back(a_sString.substr(uPos0, uPos1 - uPos0));
		}
		vString.push_back(a_sString.substr(uPos1, uSize));
		uPos0 = uPos1 + uSize;
		uPos1 = uPos0;
	}
	if (uPos0 != a_sString.size())
	{
		vString.push_back(a_sString.substr(uPos0));
	}
	if (vString.empty())
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
bool StartWith(const T& a_sString, const T& a_sPrefix, u32 a_uStart = 0)
{
	if (a_uStart > static_cast<u32>(a_sString.size()))
	{
		return false;
	}
	else
	{
		return a_sString.compare(a_uStart, a_sPrefix.size(), a_sPrefix) == 0;
	}
}

template<typename T>
bool StartWith(const T& a_sString, const typename T::value_type* a_pPrefix, u32 a_uStart = 0)
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
