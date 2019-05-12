#include "stdafx.h"
#include "StringEncoding.h"
#include "../exception/exc_base.h"

#ifdef _WIN32
	#include "../exception/WinExc.h"
#endif

#define  ERR_STR_CONVERT_MB_2_UNICODE "Multibyte string cannot be converted to unicode string. Source string: [%1]."
#define  ERR_STR_CONVERT_UTF8_2_UNICODE "Multibyte UTF8 string cannot be converted to unicode string. Source string: [%1]."

namespace CommonLib
{
namespace StringEncoding
{

	size_t cnv_uc16_to_utf8_length(const wstr& s)
	{
		size_t r = 0;

		wstr::const_iterator iter = s.begin();
		wstr::const_iterator enditer = s.end();

		for (; iter != enditer; ++iter)
		{
			uint16_t sc = uint16_t(*iter);

			if (sc < 0x0080)
				r++;
			else if (sc < 0x0800)
				r += 2;
			else
				r += 3;
		}

		return r;
	}


	void str_univ_w2utf8(const wstr& unicode, astr& utf8)
	{

		if (unicode.length() == 0)
		{
			utf8 = "";
			return;
		}

		utf8.resize(cnv_uc16_to_utf8_length(unicode));

		astr::iterator dst_p = utf8.begin();
		wstr::const_iterator src_iter = unicode.begin();
		wstr::const_iterator src_enditer = unicode.end();

		for (; src_iter != src_enditer; ++src_iter)
		{
			uint16_t sc = uint16_t(*src_iter);

			if (sc < 0x0080)
			{
				(*dst_p) = char(sc); ++dst_p;
			}
			else if (sc < 0x0800)
			{
				(*dst_p) = char(((uint8_t)(sc >> 6) & 0x1f) | 0xc0); ++dst_p;
				(*dst_p) = char(((uint8_t)(sc >> 0) & 0x3f) | 0x80); ++dst_p;
			}
			else
			{
				(*dst_p) = char(((uint8_t)(sc >> 12) & 0x0f) | 0xe0); ++dst_p;
				(*dst_p) = char(((uint8_t)(sc >> 6) & 0x3f) | 0x80); ++dst_p;
				(*dst_p) = char(((uint8_t)(sc >> 0) & 0x3f) | 0x80); ++dst_p;
			}
		}
	}


	
	

	size_t cnv_utf8_to_uc16_length(const astr& s)
	{
		size_t sl = s.length();
		size_t utf8len = 0;

		for (size_t l = 0; l < sl; utf8len++)
		{
			if ((uint8_t(s[l]) & 0x80) == 0x00)
			{
				l++;
			}
			else if ((uint8_t(s[l]) & 0xe0) == 0xc0)
			{
				l++;
				if (l >= sl)
					throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
				if ((uint8_t(s[l]) & 0xc0) != 0x80)
					throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
				l++;
			}
			else if ((uint8_t(s[l]) & 0xf0) == 0xe0)
			{
				l++;
				if (l >= sl)
					throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
				if ((uint8_t(s[l]) & 0xc0) != 0x80)
					throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
				l++;
				if (l >= sl)
					throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
				if ((uint8_t(s[l]) & 0xc0) != 0x80)
					throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
				l++;
			}
			else
				throw CExcBase(ERR_STR_CONVERT_UTF8_2_UNICODE, s);
		}

		return utf8len;
	}

	void str_univ_utf82w(const astr& utf8Str, wstr& unicode)
	{

		if (utf8Str.length() == 0)
		{
			unicode = L"";
			return;
		}

		size_t length = cnv_utf8_to_uc16_length(utf8Str);
		size_t i = 0;

		unicode.resize(length);

		for (size_t l = 0; l < length; l++)
		{
			if ((uint8_t(utf8Str[i]) & 0x80) == 0x00)
			{
				unicode[l] = wstr::value_type(uint16_t(utf8Str[i]) & 0x007f);
				i++;
			}
			else if ((uint8_t(utf8Str[i]) & 0xe0) == 0xc0)
			{
				unicode[l] = (wstr::value_type(uint16_t(utf8Str[i]) & 0x001f) << 6) +
					wstr::value_type(uint16_t(utf8Str[i + 1]) & 0x003f);
				i += 2;
			}
			else
			{
				unicode[l] = (wstr::value_type(uint16_t(utf8Str[i]) & 0x000f) << 12) +
					(wstr::value_type(uint16_t(utf8Str[i + 1]) & 0x003f) << 6) +
					wstr::value_type(uint16_t(utf8Str[i + 2]) & 0x003f);
				i += 3;
			}
		}
	}

	wstr str_univ_utf82w(const astr& stra)
	{
		wstr unicode;
		str_univ_utf82w(stra, unicode);
		return unicode;
	}


	astr str_univ_w2utf8_safe(const wstr& unicode)
	{
		try
		{
			astr utf8;
			str_univ_w2utf8(unicode, utf8);
			return utf8;
		}
		catch (...)
		{
			return astr("");
		}
	}

	wstr str_univ_utf82w_safe(const astr& utf8Str)
	{
		try
		{
			wstr unicode;
			str_univ_utf82w(utf8Str, unicode);
			return unicode;
		}
		catch (...)
		{
			return wstr(L"");
		}
	}


	void str_w2utf8(const wstr& unicode, astr& utf8)
	{
		if (unicode.length() == 0)
		{
			utf8 = "";
			return;
		}
#ifdef  _WIN32
		int  utf8_len = ::WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), (int)unicode.length() + 1, 0, 0, 0, 0);
		if (utf8_len <= 0)
			throw CWinExc("error convert unicode to utf8", GetLastError());
			 
		utf8.resize(utf8_len);
		int res = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), (int)unicode.length() + 1, &utf8[0], (int)utf8.length(), 0, 0);
		if (res <= 0)
			throw CWinExc("error convert unicode to utf8", GetLastError());
#else
		size_t  utf8_len = wcstombs(0, &unicode[0], 0);
		if (utf8_len == 0 || utf8_len == size_t(-1))
			throw CExcBase("Unicode string cannot be converted to multibyte string. Failed to get buffer size. ");

		utf8.resize(utf8_len);

		size_t  res = wcstombs(&utf8[0], &unicode[0], unicode.size());
		if (res == 0 || res == size_t(-1))
			throw CExcBase("Unicode string cannot be converted to multibyte string.");

#endif
	}

	astr str_w2utf8(const wstr& unicode)
	{
		astr utf8Str;
		str_w2utf8(unicode, utf8Str);

		return utf8Str;

	}

	void str_utf82w(const astr& utf8, wstr& unicode)
	{
		if (utf8.length() == 0)
		{
			unicode = L"";
			return;
		}
#ifdef  _WIN32
		int unicode_len = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), (int)utf8.length() + 1, 0, 0);
		if (unicode_len <= 0)
			throw CWinExc("error convert utf8 to unicode. Failed to get buffer size, Source string: %1", utf8, GetLastError());

		unicode.resize(unicode_len);
		int res = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), (int)utf8.length() + 1, &unicode[0], (int)unicode.length());
		if (res == 0)
			throw CWinExc("error convert utf8 to unicode, str %1", utf8, GetLastError());
#else
		size_t  unicode_len = mbstowcs(0, utf8.c_str(), 0);
		if (unicode_len == 0 || unicode_len == size_t(-1))
			throw CExcBase("Multibyte string cannot be converted to unicode string. Failed to get buffer size. Source string: [%1].", utf8);

		unicode.resize(unicode_len);
		size_t  res = mbstowcs(&unicode_len[0], utf8.c_str(), &utf8[0]);
		if (res == 0 || res == size_t(-1))
			throw  CExcBase("Multibyte string cannot be converted to unicode string. Source string: [%1].", utf8);
#endif
	}

	void str_utf82w_safe(const astr& utf8, wstr& unicode)
	{
		try
		{
			return str_utf82w(utf8, unicode);
		}
		catch (...)
		{
			unicode = L"";
		}
	}


	void str_w2utf8_safe(const wstr& unicode, astr& utf8)
	{
		try 
		{
			return str_w2utf8(unicode, utf8);
		}
		catch (...) 
		{
			utf8 = "";
		}
	}




	wstr str_utf82w_safe(const astr& utf8)
	{
		wstr unicode;
		str_utf82w_safe(utf8, unicode);

		return unicode;
	}

	astr str_w2utf8_safe(const wstr& unicode)
	{
		astr utf8;
		str_w2utf8_safe(unicode, utf8);

		return utf8;
	}

	void str_w2a(const wstr& src_str, astr& stra)
	{
		if (src_str.length() == 0)
		{
			stra = "";
			return;
		}

#ifdef  _WIN32
		int  i_req_buf_size = WideCharToMultiByte(CP_ACP, 0, src_str.c_str(), (int)src_str.length() + 1, 0, 0, 0, 0);
		if (i_req_buf_size <= 0)
			throw CWinExc(L"Error convert unicode to asci", GetLastError());


		std::vector<char> mb_str_buf(i_req_buf_size + 1, 0);
		int  i_conv_res = WideCharToMultiByte(CP_ACP, 0, src_str.c_str(), (int)src_str.length() + 1, &mb_str_buf[0], (int)mb_str_buf.size(), 0, 0);
		if (i_conv_res <= 0)
			throw CWinExc(L"Error convert unicode to asci", GetLastError());

#else
		size_t  i_req_buf_size = wcstombs(0, src_str.c_str(), 0);
		if (i_req_buf_size <= 0 || i_req_buf_size == size_t(-1))
			throw exc::runtime_exc_t("Unicode string cannot be converted to multibyte string. Failed to get buffer size. ");

		std::vector<char> mb_str_buf(i_req_buf_size + 1, 0);

		size_t  i_conv_res = wcstombs(mb_str_buf.GetData(), src_str.c_str(), mb_str_buf.GetByteSize());
		if (i_conv_res <= 0 || i_conv_res == size_t(-1))
			throw exc::runtime_exc_t("Unicode string cannot be converted to multibyte string.");

#endif

		stra = mb_str_buf[0];
	}


	astr str_w2a(const wstr& src_str)
	{
		astr str;
		str_w2a(src_str, str);

		return str;
	}

	astr str_w2a_safe(const wstr& src_str)
	{
		try
		{
			return str_w2a(src_str);
		}
		catch (...)
		{
			return astr("");
		}
	}

	wstr str_a2w(const astr& src_str)
	{
		wstr unicode;
		str_a2w(src_str, unicode);

		return unicode;

	}

	wstr str_a2w_safe(const astr& src_str)
	{
		try
		{
			return str_a2w(src_str);
		}
		catch (...)
		{
			return wstr(L"");
		}
	}

	void str_a2w(const astr& src_str, wstr& unicode)
	{
		if (src_str.length() == 0)
		{
			unicode =L"";
		}
#ifdef  _WIN32
		int i_req_buf_size = MultiByteToWideChar(CP_ACP, 0, src_str.c_str(), (int)src_str.length() + 1, 0, 0);
		if (i_req_buf_size <= 0)
			throw CWinExc(L"Error convert mb to unicode [%1]", src_str, GetLastError());

		std::vector< wchar_t >  unicode_str_buf(i_req_buf_size + 1, 0);
		int i_conv_res = MultiByteToWideChar(CP_ACP, 0, src_str.c_str(), (int)src_str.length() + 1, &unicode_str_buf[0], (int)unicode_str_buf.size());
		if (i_conv_res == 0)
			throw CWinExc(L"Error convert mb to unicode [%1]", src_str, GetLastError());
#else
		size_t  i_req_buf_size = mbstowcs(0, src_str.c_str(), 0);
		if (i_req_buf_size <= 0 || i_req_buf_size == size_t(-1))
			throw exc::runtime_exc_t("Multibyte string cannot be converted to unicode string. Failed to get buffer size. Source string: [%1].", src_str);

		std::vector< wchar_t > unicode_str_buf(i_req_buf_size + 1, 0);

		size_t  i_conv_res = mbstowcs(&unicode_str_buf[0], src_str.c_str(), unicode_str_buf.size()* sizeof(wchar_t));
		if (i_conv_res <= 0 || i_conv_res == size_t(-1))
			throw exc::runtime_exc_t("Multibyte string cannot be converted to unicode string. Source string: [%1].", src_str);
#endif
		unicode = &unicode_str_buf[0];
	}

	astr str_a2utf8(const astr& src_str)
	{
		return str_w2utf8(str_a2w(src_str));
	}

	astr str_a2utf8_safe(const astr& src_str)
	{
		try
		{
			return str_a2utf8(src_str);
		}
		catch (std::exception&)
		{
			return "";
		}
	}

}
}