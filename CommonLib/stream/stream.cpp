#include "stdafx.h"
#include "stream.h"

namespace CommonLib
{

	void  IWriteStreamBase::Write(const byte_t* pBuffer, uint32_t bufLen)
	{
		if (IStream::IsBigEndian())
			WriteInverse(pBuffer, bufLen);
		else
			WriteBytes(pBuffer, bufLen);
	}
	void IWriteStreamBase::Write(bool value)
	{
		WriteT<byte_t>(value ? (byte_t)1 : (byte_t)0);
	}
	void IWriteStreamBase::Write(byte_t value)
	{
		WriteT<byte_t>(value);
	}
	void IWriteStreamBase::Write(char value)
	{
		WriteT<char>(value);
	}
	void IWriteStreamBase::Write(int16_t value)
	{
		WriteT<int16_t>(value);
	}
	void IWriteStreamBase::Write(uint16_t value)
	{
		WriteT<uint16_t>(value);
	}

	void IWriteStreamBase::Write(uint32_t value)
	{
		WriteT<uint32_t>(value);
	}

	void IWriteStreamBase::Write(int32_t value)
	{
		WriteT<int32_t>(value);
	}

	void IWriteStreamBase::Write(int64_t value)
	{
		WriteT<int64_t>(value);
	}
	void IWriteStreamBase::Write(uint64_t value)
	{
		WriteT<uint64_t>(value);
	}

	void IWriteStreamBase::Write(float value)
	{
		WriteT<float>(value);
	}

	void IWriteStreamBase::Write(double value)
	{
		WriteT<double>(value);
	}
	 
	void IWriteStreamBase::Write(const astr& str)
	{
		uint32_t length = (uint32_t)str.length();
		Write(length);
		Write((byte_t*)str.c_str(), length);
	}
	void IWriteStreamBase::Write(const wstr& str)
	{
		uint32_t length = (uint32_t)str.length();
		Write(length);
		Write((byte_t*)str.c_str(), sizeof(wchar_t) * length);
	}

	void IWriteStreamBase::Write(IStream *pStream, int32_t nPos, int32_t nSize)
	{
		WriteStream(pStream, nPos, nSize);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////

	void IReadStreamBase::Read(byte_t* pBuffer, uint32_t bufLen)
	{
		if (IStream::IsBigEndian())
			ReadInverse((byte_t*)&pBuffer, bufLen);
		else
			ReadBytes((byte_t*)&pBuffer, bufLen);
	}

	void IReadStreamBase::Read(bool& value)
	{
		byte_t ret;
		ReadT<byte_t>(ret);
		value = (ret == 1) ? true : false;
	}

	void IReadStreamBase::Read(char& value)
	{
		ReadT<char>(value);
	}

	void IReadStreamBase::Read(byte_t& value)
	{
		ReadT<byte_t>(value);
	}

	void IReadStreamBase::Read(int16_t& value)
	{
		ReadT<int16_t>(value);
	}

	void IReadStreamBase::Read(uint16_t& value)
	{
		ReadT<uint16_t>(value);
	}

	void IReadStreamBase::Read(uint32_t& value)
	{
		ReadT<uint32_t>(value);
	}

	void IReadStreamBase::Read(int32_t& value)
	{
		ReadT<int32_t>(value);
	}

	void IReadStreamBase::Read(int64_t& value)
	{
		ReadT<int64_t>(value);
	}

	void IReadStreamBase::Read(uint64_t& value)
	{
		ReadT<uint64_t>(value);
	}

	void IReadStreamBase::Read(float& value)
	{
		ReadT<float>(value);
	}

	void IReadStreamBase::Read(double& value)
	{
		ReadT<double>(value);
	}

	void IReadStreamBase::Read(astr& str)
	{
		uint32_t nLen = ReadIntu32();
		if (nLen != 0)
		{
			str.resize(nLen);
			Read((byte_t*)&str[0], sizeof(char)*nLen);
		}
	}

	void IReadStreamBase::Read(wstr& str)
	{
		uint32_t nLen = ReadIntu32();
		if (nLen != 0)
		{
			str.resize(nLen);
			Read((byte_t*)&str[0], sizeof(wchar_t)*nLen);
		}
	}

	void IReadStreamBase::Read(IStream *pStream, bool bAttach)
	{
		ReadStream(pStream, bAttach);
	}


	bool IReadStreamBase::ReadSafe(byte_t* pBuffer, uint32_t bufLen)
	{
		if (IStream::IsBigEndian())
			return ReadInverseSafe((byte_t*)&pBuffer, bufLen);
		else
			return ReadBytesSafe((byte_t*)&pBuffer, bufLen);
	}

	bool IReadStreamBase::ReadSafe(bool& value)
	{
		return SafeReadT<bool>(value);
	}

	bool IReadStreamBase::ReadSafe(char& value)
	{
		return SafeReadT<char>(value);
	}

	bool IReadStreamBase::ReadSafe(byte_t& value)
	{
		return SafeReadT<byte_t>(value);
	}

	bool IReadStreamBase::ReadSafe(int16_t& value)
	{
		return SafeReadT<int16_t>(value);
	}

	bool IReadStreamBase::ReadSafe(uint16_t& value)
	{
		return SafeReadT<uint16_t>(value);
	}

	bool IReadStreamBase::ReadSafe(uint32_t& value)
	{
		return SafeReadT<uint32_t>(value);
	}

	bool IReadStreamBase::ReadSafe(int32_t& value)
	{
		return SafeReadT<int32_t>(value);
	}

	bool IReadStreamBase::ReadSafe(int64_t& value)
	{
		return SafeReadT<int64_t>(value);
	}

	bool IReadStreamBase::ReadSafe(uint64_t& value)
	{
		return SafeReadT<uint64_t>(value);
	}

	bool IReadStreamBase::ReadSafe(float& value)
	{
		return SafeReadT<float>(value);
	}

	bool IReadStreamBase::ReadSafe(double& value)
	{
		return SafeReadT<double>(value);
	}

	bool IReadStreamBase::ReadSafe(astr& str)
	{
		uint32_t nLen = 0;
		if (!ReadSafe(nLen))
			return false;

		if (nLen == 0)
			return true;

		str.resize(nLen);

		return ReadSafe((byte_t*)&str[0], sizeof(char)*nLen);
	}

	bool IReadStreamBase::ReadSafe(wstr& str)
	{
		uint32_t nLen = 0;
		if (!ReadSafe(nLen))
			return false;

		if (nLen == 0)
			return true;

		str.resize(nLen);

		return ReadSafe((byte_t*)&str[0], sizeof(wchar_t)*nLen);
	}

	bool IReadStreamBase::ReadSafe(IStream *pStream, bool bAttach)
	{
		return ReadStreamSafe(pStream, bAttach);
	}


	bool IReadStreamBase::ReadBool()
	{
		return (ReadTR<byte_t>() == 1) ? true : false;
	}

	byte_t IReadStreamBase::ReadByte()
	{
		return ReadTR<byte_t>();
	}

	char IReadStreamBase::ReadChar()
	{
		return ReadTR<char>();
	}

	int16_t IReadStreamBase::Readint16()
	{
		return ReadTR<int16_t>();
	}

	uint16_t IReadStreamBase::Readintu16()
	{
		return ReadTR<uint16_t>();
	}

	uint32_t IReadStreamBase::ReadDword()
	{
		return ReadTR<uint32_t>();
	}

	int32_t  IReadStreamBase::ReadInt32()
	{
		return ReadTR<int32_t>();
	}

	uint32_t IReadStreamBase::ReadIntu32()
	{
		return ReadTR<uint32_t>();
	}

	int64_t IReadStreamBase::ReadInt64()
	{
		return ReadTR<int64_t>();
	}

	uint64_t IReadStreamBase::ReadIntu64()
	{
		return ReadTR<uint64_t>();
	}

	float  IReadStreamBase::ReadFloat()
	{
		return ReadTR<float>();
	}

	double IReadStreamBase::ReadDouble()
	{
		return ReadTR<double>();
	}

	astr IReadStreamBase::ReadAstr()
	{
		astr str;
		Read(str);

		return str;
	}

	wstr IReadStreamBase::ReadWstr()
	{
		wstr str;
		Read(str);

		return str;
	}

}