#pragma once
#include "../exception/exc_base.h"

namespace CommonLib
{
enum enSeekOffset
{
    soFromBegin,
    soFromCurrent,
    soFromEnd,
};

class IAlloc;
class IStream;


typedef std::shared_ptr<IStream> TStreamPtr;

class IStream
{
public:
	virtual uint32_t Size() const = 0;
	virtual uint64_t Size64() const = 0;
	virtual void Seek(int32_t position, enSeekOffset offset) = 0;
	virtual void Seek64(int64_t position, enSeekOffset offset) = 0;
	virtual uint32_t Pos() const = 0;
	virtual uint64_t Pos64() const = 0;
	virtual void Reset() = 0;
	virtual void Close() = 0;
	virtual void Attach(TStreamPtr pStream, int32_t nPos = -1, int32_t nSize = -1, bool bSeekPos = false) = 0;
	virtual void Attach64(TStreamPtr pStream, int64_t nPos = -1, int64_t nSize = -1, bool bSeekPos = false) = 0;
	virtual TStreamPtr Deattach() = 0;

	static bool IsBigEndian()
	{
		static const uint16_t word = 0xFF00;
		return *((uint8_t*)& word) != 0;

	}
};


class IMemoryStream
{
public:
	virtual void AttachBuffer(byte_t* pBuffer, uint32_t nSize, bool bCopy = false) = 0;
	virtual byte_t* DeattachBuffer() = 0;

	virtual byte_t* Buffer() = 0;
	virtual const byte_t* Buffer() const = 0;
	virtual void Create(uint32_t nSize) = 0;
	virtual void Resize(uint32_t nSize) = 0;
};


class IWriteStream : public IStream
{
public:
	
	IWriteStream(){}
	virtual ~IWriteStream() {}

	virtual void Write(const byte_t* pBuffer, uint32_t bufLen) = 0;
	virtual void Write(bool value) = 0;
	virtual void Write(uint8_t value) = 0;
	virtual void Write(char value) = 0;
	virtual void Write(int16_t value) = 0;
	virtual void Write(uint16_t value) = 0;
	virtual void Write(uint32_t value) = 0;
	virtual void Write(int32_t value) = 0;
	virtual void Write(int64_t value) = 0;
	virtual void Write(uint64_t value) = 0;
	virtual void Write(float value) = 0;
	virtual void Write(double value) = 0;
	virtual void Write(const astr& str) = 0;
	virtual void Write(const wstr& str) = 0;
	virtual void Write(IStream *pStream, int32_t nPos = -1, int32_t nSize = -1) = 0;
};

typedef std::shared_ptr<IWriteStream> WriteStreamPtr;


class IReadStream : public IStream
{
public:

	virtual ~IReadStream() {}
	IReadStream() {}
	virtual void Read(byte_t* pBuffer, uint32_t bufLen) = 0;
	virtual void Read(bool& value) = 0;
	virtual void Read(char& value) = 0;
	virtual void Read(byte_t& value) = 0;
	virtual void Read(int16_t& value) = 0;
	virtual void Read(uint16_t& value) = 0;
	virtual void Read(uint32_t& value) = 0;
	virtual void Read(int32_t& value) = 0;
	virtual void Read(int64_t& value) = 0;
	virtual void Read(uint64_t& value) = 0;
	virtual void Read(float& value) = 0;
	virtual void Read(double& value) = 0;
	virtual void Read(astr& str) = 0;
	virtual void Read(wstr& str) = 0;
	virtual void Read(IStream *pStream, bool bAttach = false) = 0;

	virtual bool ReadSafe(byte_t* pBuffer, uint32_t bufLen) = 0;
	virtual bool ReadSafe(bool& value) = 0;
	virtual bool ReadSafe(char& value) = 0;
	virtual bool ReadSafe(byte_t& value) = 0;
	virtual bool ReadSafe(int16_t& value) = 0;
	virtual bool ReadSafe(uint16_t& value) = 0;
	virtual bool ReadSafe(uint32_t& value) = 0;
	virtual bool ReadSafe(int32_t& value) = 0;
	virtual bool ReadSafe(int64_t& value) = 0;
	virtual bool ReadSafe(uint64_t& value) = 0;
	virtual bool ReadSafe(float& value) = 0;
	virtual bool ReadSafe(double& value) = 0;
	virtual bool ReadSafe(astr& str) = 0;
	virtual bool ReadSafe(wstr& str) = 0;
	virtual bool ReadSafe(IStream *pStream, bool bAttach = false) = 0;

	virtual bool         ReadBool() = 0;
	virtual byte_t       ReadByte() = 0;
	virtual char         ReadChar() = 0;
	virtual int16_t      Readint16() = 0;
	virtual uint16_t     Readintu16() = 0;
	virtual uint32_t     ReadDword() = 0;
	virtual int32_t      ReadInt32() = 0;
	virtual uint32_t     ReadIntu32() = 0;
	virtual int64_t      ReadInt64() = 0;
	virtual uint64_t     ReadIntu64() = 0;
	virtual float        ReadFloat() = 0;
	virtual double       ReadDouble() = 0;
	virtual astr         ReadAstr() = 0;
	virtual wstr	     ReadWstr() = 0;

};

typedef std::shared_ptr<IReadStream> ReadStreamPtr;

class IWriteStreamBase : public IWriteStream
{
public:
	IWriteStreamBase() {}
	virtual ~IWriteStreamBase() {}



	template <typename T>
	void WriteT(const T& value)
	{
		if (IStream::IsBigEndian())
			WriteInverse((byte_t*)&value, sizeof(T));
		else
			WriteBytes((byte_t*)&value, sizeof(T));
	}


	virtual void WriteBytes(const byte_t* buffer, uint32_t size) = 0;
	virtual void WriteInverse(const byte_t* buffer, uint32_t size) = 0;
	virtual void WriteStream(IStream *pStream, int32_t nPos = -1, int32_t nSize = -1) = 0;

	virtual void Write(const byte_t* pBuffer, uint32_t bufLen);
	virtual void Write(bool value);
	virtual void Write(uint8_t value);
	virtual void Write(char value);
	virtual void Write(int16_t value);
	virtual void Write(uint16_t value);
	virtual void Write(uint32_t value);
	virtual void Write(int32_t value);
	virtual void Write(int64_t value);
	virtual void Write(uint64_t value);
	virtual void Write(float value);
	virtual void Write(double value);
	virtual void Write(const astr& str);
	virtual void Write(const wstr& str);
	virtual void Write(IStream *pStream, int32_t nPos = -1, int32_t nSize = -1);
};

template<class I>
class TMemoryStreamBase : public I, public IMemoryStream
{

private:
	TMemoryStreamBase(const TMemoryStreamBase& stream) {}
	TMemoryStreamBase& operator=(const TMemoryStreamBase& stream) {}
public:

	TMemoryStreamBase(std::shared_ptr<IAlloc> pAlloc = std::shared_ptr<IAlloc>()) : m_pAlloc(pAlloc), m_pBuffer(0)
		, m_nPos(0)
		, m_nSize(0)
		, m_bAttach(false)
		, m_pAttachStream(NULL)

	{
		m_bIsBigEndian = IStream::IsBigEndian();

	}

	~TMemoryStreamBase()
	{
		if (!m_bAttach && m_pBuffer)
		{
			m_pAlloc->Free(m_pBuffer);
			m_pBuffer = 0;
		}
	}

	//IStream
	virtual uint32_t Size() const
	{
		return m_nSize;
	}

	virtual uint64_t Size64() const
	{
		return (uint64_t)m_nSize;
	}

	virtual void Seek(int32_t position, enSeekOffset offset)
	{
		try
		{
			if (!m_pBuffer)
				throw CExcBase(L"buffer is null", position);

			uint32_t newpos = 0;
			switch (offset)
			{
			case soFromBegin:
				newpos = position;
				break;
			case soFromCurrent:
				newpos = m_nPos + position;
				break;
			case soFromEnd:
				newpos = m_nSize + position;
				break;
			}
			if (newpos > m_nSize && m_bAttach)
				throw CExcBase(L"out of range  and buffer is attached", position, m_nSize);

			if (newpos > m_nSize && !m_bAttach)
			{
				Resize(newpos - m_nSize);
			}
			m_nPos = newpos;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Can't seek stream pos: %1", position);
			throw;
		}
	}
	virtual void Seek64(int64_t position, enSeekOffset offset)
	{
		 Seek((int32_t)position, offset);
	}
	virtual uint32_t Pos() const
	{
		return m_nPos;
	}
	virtual uint64_t Pos64() const
	{
		return (uint64_t)m_nPos;
	}
	virtual void Reset()
	{
		m_nPos = 0;
	}
	virtual void Attach(TStreamPtr pStream, int32_t nPos = -1, int32_t nSize = -1, bool bSeekPos = false)
	{
		try
		{
			IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream.get());
			if (!pMemStream)
				throw CExcBase(L"IStream isn't memstream");

			uint32_t _nPos = (nPos != -1 ? nPos : 0);
			uint32_t _nSize = (nSize != -1 ? nSize : pStream->Size());

			if ((pStream->Size() - _nPos) < _nSize)
			{
				pMemStream->Resize(pStream->Size() + _nSize);
			}

			AttachBuffer(pMemStream->Buffer() + _nPos, _nSize, false);

			m_pAttachStream = pStream;
			if (bSeekPos)
				pStream->Seek(_nPos + _nSize, CommonLib::soFromBegin);
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Can't attach to IStream");
			throw;
		}		
	}
	virtual void Attach64(TStreamPtr pStream, int64_t nPos = -1, int64_t nSize = -1, bool bSeek = false)
	{
		Attach(pStream, int32_t(nPos), int32_t(nSize), bSeek);
	}
	virtual TStreamPtr Deattach()
	{
		if (!m_pAttachStream.get())
			return TStreamPtr();

		DeattachBuffer();
		TStreamPtr pTmp = m_pAttachStream;
		m_pAttachStream = TStreamPtr();
		return pTmp;


	}
	virtual void Close()
	{
		try
		{
			m_nPos = 0;
			m_nSize = 0;
			m_pBuffer = 0;

			if (!m_bAttach && m_pBuffer)
			{
				if (m_pAlloc.get() == nullptr)
					throw CExcBase(L"Allocator is null");

				m_pAlloc->Free(m_pBuffer);
				m_pBuffer = 0;
			}
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Can't close stream");
			throw;
		}
	}


	//IMemoryStream
	virtual void AttachBuffer(byte_t* pBuffer, uint32_t nSize, bool bCopy = false)
	{
		try
		{
			if (bCopy)
			{
				Create(nSize);
				memcpy(m_pBuffer, pBuffer, nSize);
				m_bAttach = false;
			}
			else
			{
				m_pBuffer = pBuffer;
				m_bAttach = true;

			}
			if (m_pAttachStream)
				m_pAttachStream = NULL;

			m_nPos = 0;
			m_nSize = nSize;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsg(L"Can't attach to buffer");
			throw;
		}
	}

	virtual byte_t* DeattachBuffer()
	{
		byte_t* tmp = m_pBuffer;
		m_nPos = 0;
		m_nSize = 0;
		m_pBuffer = 0;
		m_bAttach = false;
		return tmp;
	}
	virtual byte_t* Buffer()
	{
		return m_pBuffer;
	}
	virtual const byte_t* Buffer() const
	{
		return m_pBuffer;
	}
	virtual void Create(uint32_t nSize)
	{
		try
		{

			if (m_pAlloc.get() == nullptr)
				throw CExcBase(L"Allocator is null");

			if (!m_bAttach && m_pBuffer)
			{
				m_pAlloc->Free(m_pBuffer);
			}

			m_pAttachStream = NULL;
			m_pBuffer = (byte_t*)m_pAlloc->Alloc(sizeof(byte_t) * nSize);
			m_nPos = 0;
			m_nSize = nSize;
			m_bAttach = false;
		}
		catch (CExcBase& exc)
		{
			exc.AddMsgT(L"Can't create stream size: %1", nSize);
			throw;
		}
	}

	virtual void Resize(uint32_t nSize) { throw CExcBase(L"TMemoryStreamBase: resize isn't implemented"); }
protected:

	byte_t * m_pBuffer;
	uint32_t  m_nPos;
	uint32_t   m_nSize;
	bool m_bIsBigEndian;
	std::shared_ptr<IAlloc> m_pAlloc;
	bool m_bAttach;
	TStreamPtr m_pAttachStream;
 };




 class IReadStreamBase : public IReadStream
 {
 public:


	 IReadStreamBase() {}
	 virtual ~IReadStreamBase() {}

	 template <typename T>
	 void ReadT(T& val)
	 {
		 if (IStream::IsBigEndian())
			 ReadInverse((byte_t*)&val, sizeof(T));
		 else
			 ReadBytes((byte_t*)&val, sizeof(T));
	 }


	 template <typename T>
	 T ReadTR()
	 {
		 T ret;
		 if (IStream::IsBigEndian())
			 ReadInverse((byte_t*)&ret, sizeof(T));
		 else
			 ReadBytes((byte_t*)&ret, sizeof(T));

		 return ret;
	 }


	 template <typename T>
	 bool SafeReadT(T& val)
	 {
		 if (IStream::IsBigEndian())
			 return ReadBytesSafe((byte_t*)&val, sizeof(T));
		 else
			 return ReadInverseSafe((byte_t*)&val, sizeof(T));
	 }

	 virtual void ReadBytes(byte_t* dst, uint32_t size) = 0;
	 virtual void ReadInverse(byte_t* buffer, uint32_t size) = 0;
	 virtual void ReadStream(IStream *pStream, bool bAttach) = 0;


	 virtual bool ReadBytesSafe(byte_t* dst, uint32_t size) = 0;
	 virtual bool ReadInverseSafe(byte_t* buffer, uint32_t size) = 0;
	 virtual bool ReadStreamSafe(IStream *pStream, bool bAttach) = 0;



	 virtual void Read(byte_t* pBuffer, uint32_t bufLen);
	 virtual void Read(bool& value);
	 virtual void Read(char& value);
	 virtual void Read(byte_t& value) ;
	 virtual void Read(int16_t& value);
	 virtual void Read(uint16_t& value);
	 virtual void Read(uint32_t& value);
	 virtual void Read(int32_t& value);
	 virtual void Read(int64_t& value) ;
	 virtual void Read(uint64_t& value);
	 virtual void Read(float& value) ;
	 virtual void Read(double& value);
	 virtual void Read(astr& str);
	 virtual void Read(wstr& str);
	 virtual void Read(IStream *pStream, bool bAttach = false);

	 virtual bool ReadSafe(byte_t* pBuffer, uint32_t bufLen);
	 virtual bool ReadSafe(bool& value);
	 virtual bool ReadSafe(char& value);
	 virtual bool ReadSafe(byte_t& value);
	 virtual bool ReadSafe(int16_t& value);
	 virtual bool ReadSafe(uint16_t& value);
	 virtual bool ReadSafe(uint32_t& value);
	 virtual bool ReadSafe(int32_t& value);
	 virtual bool ReadSafe(int64_t& value);
	 virtual bool ReadSafe(uint64_t& value);
	 virtual bool ReadSafe(float& value);
	 virtual bool ReadSafe(double& value);
	 virtual bool ReadSafe(astr& str);
	 virtual bool ReadSafe(wstr& str);
	 virtual bool ReadSafe(IStream *pStream, bool bAttach = false);

	 virtual bool         ReadBool();
	 virtual byte_t       ReadByte();
	 virtual char         ReadChar();
	 virtual int16_t      Readint16();
	 virtual uint16_t     Readintu16();
	 virtual uint32_t     ReadDword();
	 virtual int32_t      ReadInt32();
	 virtual uint32_t     ReadIntu32();
	 virtual int64_t      ReadInt64();
	 virtual uint64_t     ReadIntu64();
	 virtual float        ReadFloat();
	 virtual double       ReadDouble();
	 virtual astr         ReadAstr();
	 virtual wstr	      ReadWstr();
 };


}
