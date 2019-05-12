#pragma once
#include "stream.h"


namespace CommonLib
{

	template<class I>
	class TMemoryStreamBaseEmpty : public I, public IMemoryStream
	{

	private:
		TMemoryStreamBaseEmpty(const TMemoryStreamBaseEmpty& stream) {}
		TMemoryStreamBaseEmpty& operator=(const TMemoryStreamBaseEmpty& stream) {}
	public:

		TMemoryStreamBaseEmpty(std::shared_ptr<IAlloc> pAlloc = std::shared_ptr<IAlloc>())
		{
			m_bIsBigEndian = IStream::IsBigEndian();

		}

		~TMemoryStreamBaseEmpty()
		{}

		//IStream
		virtual uint32_t Size() const
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Size isn't implemented");
		}

		virtual uint64_t Size64() const
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Size64 isn't implemented");
		}

		virtual void Seek(int32_t position, enSeekOffset offset)
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Seek isn't implemented");
		}
		virtual void Seek64(int64_t position, enSeekOffset offset)
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Seek64 isn't implemented");
		}
		virtual uint32_t Pos() const
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Pos isn't implemented");
		}
		virtual uint64_t Pos64() const
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Pos64 isn't implemented");
		}
		virtual void Reset()
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Reset isn't implemented");
		}
		virtual void Attach(TStreamPtr pStream, int32_t nPos = -1, int32_t nSize = -1, bool bSeekPos = false)
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Attach isn't implemented");
		}
		virtual void Attach64(TStreamPtr pStream, int64_t nPos = -1, int64_t nSize = -1, bool bSeek = false)
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Attach64 isn't implemented");
		}
		virtual TStreamPtr Deattach()
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Deattach isn't implemented");
		}
		virtual void Close()
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Close isn't implemented");
		}


		//IMemoryStream
		virtual void AttachBuffer(byte_t* pBuffer, uint32_t nSize, bool bCopy = false)
		{
			throw CExcBase("TMemoryStreamBaseEmpty: AttachBuffer isn't implemented");
		}

		virtual byte_t* DeattachBuffer()
		{
			throw CExcBase("TMemoryStreamBaseEmpty: DeattachBuffer isn't implemented");
		}
		virtual byte_t* Buffer()
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Buffer isn't implemented");
		}
		virtual const byte_t* Buffer() const
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Buffer isn't implemented");
		}
		virtual void Create(uint32_t nSize)
		{
			throw CExcBase("TMemoryStreamBaseEmpty: Create isn't implemented");
		}

		virtual void Resize(uint32_t nSize) { throw CExcBase("TMemoryStreamBaseEmpty: resize isn't implemented"); }
	protected:
		bool m_bIsBigEndian;
	};
}