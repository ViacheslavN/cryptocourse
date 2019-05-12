#include "stdafx.h"
#include "str.h"
#include "convertToString.h"

namespace CommonLib
{

template <class TChar>
long TStrtol(const TChar * str, TChar ** endptr, int base)
{

}

template<>
long TStrtol<wchar_t>(const wchar_t * str, wchar_t ** endptr, int base)
{
	return  wcstol(str, endptr, base);
}


template<>
long TStrtol<char>(const char * str, char ** endptr, int base)
{
	return  strtol(str, endptr, base);
}

template <class TChar, class TStr, class TContainer>
TStr StrFormatSafeT(const TStr& format, const TContainer& args, TChar checkSymbol)
{
	std::basic_stringstream<TChar>  outBuf;

	const TChar* pFormaStr = format.c_str();
	while (*pFormaStr != 0)
	{

		if (*pFormaStr != checkSymbol)
		{
			outBuf << *pFormaStr;
			pFormaStr++;
		}
		else
		{
			pFormaStr++;

			TChar* pSubStrAfterNumber = 0;
			long  arg = TStrtol<TChar>(pFormaStr, &pSubStrAfterNumber, 10);

			if (pSubStrAfterNumber == pFormaStr)
				outBuf << checkSymbol;
			else if ((arg - 1) >= (long)args.size() || arg < 1)
			{
				outBuf << checkSymbol;
				outBuf << arg;
			}
			else
				outBuf << args[arg - 1];

			pFormaStr = pSubStrAfterNumber;
		}
	}

	return outBuf.str();

}

wstr str_format::StrFormatSafe(const wstr& str)
{
	return str;
}

wstr str_format::StrFormatSafe(const wstr& format, const wstrvec& args)
{
	return StrFormatSafeT(format, args, L'%');
}

wstr str_format::StrFormatSafe(const wstr& format, const wstr& arg1)
{
	wstrvec  args;
	args.push_back(arg1);

	return StrFormatSafe(format, args);
}

wstr str_format::StrFormatSafe(const wstr& format, const wstr& arg1, const wstr& arg2)
{
	wstrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);

	return StrFormatSafe(format, args);
}

wstr str_format::StrFormatSafe(const wstr& format, const wstr& arg1, const wstr& arg2, const wstr& arg3)
{
	wstrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);

	return StrFormatSafe(format, args);
}

wstr str_format::StrFormatSafe(const wstr& format, const wstr& arg1, const wstr& arg2, const wstr& arg3, const wstr& arg4)
{
	wstrvec args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);

	return StrFormatSafe(format, args);
}

wstr str_format::StrFormatSafe(const wstr& format, const wstr& arg1, const wstr& arg2, const wstr& arg3, const wstr& arg4, const wstr& arg5)
{
	wstrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);

	return StrFormatSafe(format, args);
}

wstr str_format::StrFormatSafe(const wstr& format, const wstr& arg1, const wstr& arg2, const wstr& arg3, const wstr& arg4, const wstr& arg5, const wstr& arg6)
{
	wstrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);

	return StrFormatSafe(format, args);
}
//////////////////////////////////////////////////////////////////////////////////////


astr str_format::StrFormatSafe(const astr& format, const astrvec& args)
{
	return StrFormatSafeT(format, args, '%');
}

astr str_format::StrFormatSafe(const astr& str)
{
	return str;
}

astr str_format::StrFormatSafe(const astr& format, const astr& arg1)
{
	astrvec  args;
	args.push_back(arg1);

	return StrFormatSafe(format, args);
}
astr str_format::StrFormatSafe(const astr& format, const astr& arg1, const astr& arg2)
{
	astrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);

	return StrFormatSafe(format, args);
}

astr str_format::StrFormatSafe(const astr& format, const astr& arg1, const astr& arg2, const astr& arg3)
{
	astrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);

	return StrFormatSafe(format, args);
}

astr str_format::StrFormatSafe(const astr& format, const astr& arg1, const astr& arg2, const astr& arg3, const astr& arg4)
{
	astrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);

	return StrFormatSafe(format, args);
}

astr str_format::StrFormatSafe(const astr& format, const astr& arg1, const astr& arg2, const astr& arg3, const astr& arg4, const astr& arg5)
{
	astrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);

	return StrFormatSafe(format, args);
}


astr str_format::StrFormatSafe(const astr& format, const astr& arg1, const astr& arg2, const astr& arg3, const astr& arg4, const astr& arg5, const astr& arg6)
{
	astrvec  args;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
	args.push_back(arg4);
	args.push_back(arg5);
	args.push_back(arg6);

	return StrFormatSafe(format, args);
}

}