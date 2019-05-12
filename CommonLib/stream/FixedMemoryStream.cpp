#include "stdafx.h"
#include "../alloc/alloc.h"
#include "FixedMemoryStream.h"

namespace CommonLib
{


	CFxMemoryWriteStream::CFxMemoryWriteStream()
	{

	}

	CFxMemoryWriteStream::~CFxMemoryWriteStream()
	{

	}
		
	void CFxMemoryWriteStream::WriteBytes(const byte_t* buffer, uint32_t size)
	{
		if (size > 0)
		{
			if ((this->m_nPos + size) > m_nSize)
				throw CExcBase(L"CFxMemoryWriteStream: out of range pos: %1, read size: %2", m_nPos, size);

			::memcpy(m_pBuffer + m_nPos, buffer, size);
			m_nPos += size;
		}
	}

	void CFxMemoryWriteStream::WriteInverse(const byte_t* buffer, uint32_t size)
	{
		if (size > 0)
		{
			if ((this->m_nPos + size) > m_nSize)
				throw CExcBase(L"CFxMemoryWriteStream: out of range pos: %1, read size: %2", m_nPos, size);

			for (size_t i = 0; i < size; m_nPos++, i++)
				m_pBuffer[m_nPos + size - i - 1] = buffer[i];
		}
	}

	void CFxMemoryWriteStream::WriteStream(IStream *pStream, int32_t nPos, int32_t nSize)
	{
		IMemoryStream *pMemStream = dynamic_cast<IMemoryStream *>(pStream);
		if (pMemStream)
		{
			uint32_t _nPos = (nPos != -1 ? nPos : 0);
			uint32_t _nSize = (nSize != -1 ? nSize : pStream->Size());

			Write(_nSize);
			Write(pMemStream->Buffer() + _nPos, _nSize);
		}
	}
}