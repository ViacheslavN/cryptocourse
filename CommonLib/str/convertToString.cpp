#include "stdafx.h"
#include "convertToString.h"
#include "StringEncoding.h"

namespace CommonLib
{
	wstr str_utils::WStrInt8(int8_t val)
	{
		return WStrInt32(int32_t(val));
	}

	wstr str_utils::WStrUint8(uint8_t val)
	{
		return WStrUint32(uint32_t(val));
	}

	wstr str_utils::WStrInt16(int16_t val)
	{
		return WStrInt32(int32_t(val));
	}

	wstr str_utils::WStrUint16(uint16_t val)
	{
		return WStrUint32(uint32_t(val));
	}

	wstr str_utils::WStrInt32(int32_t val)
	{
		wchar_t  buf[32];
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%d", val);
		return buf;
	}

	wstr str_utils::WStrUint32(uint32_t val)
	{
		wchar_t  buf[32];
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%u", val);
		return buf;
	}

	wstr str_utils::WStrInt64(int64_t val)
	{
		wchar_t  buf[32];
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%I64d", val);
		return buf;
	}

	wstr str_utils::WStrUint64(uint64_t val)
	{
		wchar_t  buf[32];
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%I64u", val);
		return buf;
	}

	wstr str_utils::WStrFloat(float val)
	{
		wchar_t  buf[32];
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%.3f", val);
		return buf;
	}

	wstr str_utils::WStrDouble(double val)
	{
		wchar_t buf[32];
		swprintf_s(buf, sizeof(buf) / sizeof(wchar_t), L"%.3lf", val);
		return buf;
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////



	astr str_utils::AStrInt8(int8_t val)
	{
		return AStrInt32(int32_t(val));
	}

	astr str_utils::AStrUint8(uint8_t val)
	{
		return AStrUint32(uint32_t(val));
	}

	astr str_utils::AStrInt16(int16_t val)
	{
		return AStrInt32(int32_t(val));
	}

	astr str_utils::AStrUint16(uint16_t val)
	{
		return AStrUint32(uint32_t(val));
	}

	astr str_utils::AStrInt32(int32_t val)
	{
		char  buf[32];
		sprintf_s(buf, sizeof(buf), "%d", val);
		return buf;
	}

	astr str_utils::AStrUint32(uint32_t val)
	{
		char  buf[32];
		sprintf_s(buf, sizeof(buf), "%u", val);
		return buf;
	}

	astr str_utils::AStrInt64(int64_t val)
	{
		char  buf[32];
		sprintf_s(buf, sizeof(buf), "%I64d", val);
		return buf;
	}

	astr str_utils::AStrUint64(uint64_t val)
	{
		char  buf[32];
		sprintf_s(buf, sizeof(buf), "%I64u", val);
		return buf;
	}

	astr str_utils::AStrFloat(float val)
	{
		char  buf[32];
		sprintf_s(buf, sizeof(buf), "%.3f", val);
		return buf;
	}

	astr str_utils::AStrDouble(double val)
	{
		char buf[32];
		sprintf_s(buf, sizeof(buf), "%.3lf", val);
		return buf;
	}

	astr str_utils::AStrTo(const wchar_t *ptrStr)
	{
		return StringEncoding::str_w2utf8_safe(ptrStr);
	}

	astr str_utils::AStrTo(const wstr& val)
	{
		return StringEncoding::str_w2utf8_safe(val);
	}
}