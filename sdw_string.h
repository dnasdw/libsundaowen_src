#ifndef LIBSUNDAOWEN_SDW_STRING_H_
#define LIBSUNDAOWEN_SDW_STRING_H_

#include "sdw_type.h"

string FormatV(const char* a_szFormat, va_list a_vaList);
wstring FormatV(const wchar_t* a_szFormat, va_list a_vaList);
string Format(const char* a_szFormat, ...);
wstring Format(const wchar_t* a_szFormat, ...);

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
