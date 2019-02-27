#pragma once

namespace CommonLib
{

	class str_utils
	{
	public:
		static wstr WStrInt8(int8_t val);
		static wstr WStrUint8(uint8_t val);
		static wstr WStrInt16(int16_t val);
		static wstr WStrUint16(uint16_t val);
		static wstr WStrInt32(int32_t val);
		static wstr WStrUint32(uint32_t val);
		static wstr WStrInt64(int64_t val);
		static wstr WStrUint64(uint64_t val);
		static wstr WStrFloat(float val);
		static wstr WStrDouble(double val);


		static wstr WStrTo(const wchar_t *ptrStr)
		{
			return wstr(ptrStr);
		}

		static wstr WStrTo(const wstr& val)
		{
			return val;
		}

		static  wstr WStrTo(const int8_t& val)
		{
			return WStrInt8(val);
		}


		static  wstr WStrTo(const uint8_t& val)
		{
			return WStrUint8(val);
		}


		static  wstr WStrTo(const int16_t& val)
		{
			return WStrInt16(val);
		}

		static  wstr WStrTo(const uint16_t& val)
		{
			return WStrUint16(val);
		}


		static  wstr WStrTo(const int32_t& val)
		{
			return WStrInt32(val);
		}


		static  wstr WStrTo(const uint32_t& val)
		{
			return WStrUint32(val);
		}


		static  wstr WStrTo(const int64_t& val)
		{
			return WStrInt64(val);
		}


		static  wstr WStrTo(const uint64_t& val)
		{
			return WStrUint64(val);
		}


		static wstr WStrTo(const float& val)
		{
			return WStrFloat(val);
		}

		static  wstr WStrTo(const double& val)
		{
			return WStrDouble(val);
		}


		static astr AStrInt8(int8_t val);
		static astr AStrUint8(uint8_t val);
		static astr AStrInt16(int16_t val);
		static astr AStrUint16(uint16_t val);
		static astr AStrInt32(int32_t val);
		static astr AStrUint32(uint32_t val);
		static astr AStrInt64(int64_t val);
		static astr AStrUint64(uint64_t val);
		static astr AStrFloat(float val);
		static astr AStrDouble(double val);
		static astr AStrTo(const wchar_t *ptrStr);
		static astr AStrTo(const wstr& val);

		//template<class TVal>
		//static astr AStrTo(const TVal& val) {}

		static astr AStrTo(const astr& val)
		{
			return val;
		}

		static  astr AStrTo(const int8_t& val)
		{
			return AStrInt8(val);
		}

		static  astr AStrTo(const uint8_t& val)
		{
			return AStrUint8(val);
		}


		static  astr AStrTo(const int16_t& val)
		{
			return AStrInt16(val);
		}

		static  astr AStrTo(const uint16_t& val)
		{
			return AStrUint16(val);
		}

		static  astr AStrTo(const int32_t& val)
		{
			return AStrInt32(val);
		}

		static  astr AStrTo(const uint32_t& val)
		{
			return AStrUint32(val);
		}

		static  astr AStrTo(const int64_t& val)
		{
			return AStrInt64(val);
		}

		static  astr AStrTo(const uint64_t& val)
		{
			return AStrUint64(val);
		}

		static astr AStrTo(const float& val)
		{
			return AStrFloat(val);
		}

		static  astr AStrTo(const double& val)
		{
			return AStrDouble(val);
		}

	};

}