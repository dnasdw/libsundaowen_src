#ifndef LIBSUNDAOWEN_SDW_STRING_H_
#define LIBSUNDAOWEN_SDW_STRING_H_

#include "sdw_platform.h"
#include "sdw_type.h"

#if SDW_COMPILER != SDW_COMPILER_MSC
template<typename TSrc, typename TDest>
TDest TToT(const TSrc& a_sString, const string& a_sSrcType, const string& a_sDestType)
{
	TDest sConverted;
	iconv_t cvt = iconv_open(a_sDestType.c_str(), a_sSrcType.c_str());
	if (cvt == reinterpret_cast<iconv_t>(-1))
	{
		return sConverted;
	}
	size_t uStringLeft = a_sString.size() * sizeof(typename TSrc::value_type);
	static const n32 c_nBufferSize = 1024;
	static const n32 c_nConvertBufferSize = c_nBufferSize - 4;
	char szBuffer[c_nBufferSize];
	typename TSrc::value_type* pString = const_cast<typename TSrc::value_type*>(a_sString.c_str());
	do
	{
		char* pBuffer = szBuffer;
		size_t uBufferLeft = c_nConvertBufferSize;
		n32 nError = iconv(cvt, reinterpret_cast<char**>(&pString), &uStringLeft, &pBuffer, &uBufferLeft);
		if (nError == 0 || (nError == static_cast<size_t>(-1) && errno == E2BIG))
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
	iconv_close(cvt);
	return sConverted;
}
#endif

string WToU8(const wstring& a_sString);
string U16ToU8(const U16String& a_sString);
wstring U8ToW(const string& a_sString);
wstring U16ToW(const U16String& a_sString);
U16String U8ToU16(const string& a_sString);
U16String WToU16(const wstring& a_sString);

string FormatV(const char* a_szFormat, va_list a_vaList);
wstring FormatV(const wchar_t* a_szFormat, va_list a_vaList);
string Format(const char* a_szFormat, ...);
wstring Format(const wchar_t* a_szFormat, ...);

template<typename T>
T Replace(const T& a_sString, const typename T::value_type a_cSubChar, const T& a_sReplacement)
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
T Replace(const T& a_sString, const typename T::value_type a_cSubChar, const typename T::value_type* a_pReplacement)
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
	return vString;
}

#endif	// LIBSUNDAOWEN_SDW_STRING_H_
