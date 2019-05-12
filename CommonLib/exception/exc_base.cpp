#include "stdafx.h"
#include "exc_base.h"


namespace CommonLib
{
	CExcBase::CExcBase() : m_srcThreadId(CThread::GetCurThreadId())
	{}

	CExcBase::CExcBase(const CExcBase& exc) : m_srcThreadId(exc.m_srcThreadId), m_msgChain(exc.m_msgChain)
	{

	}

	CExcBase::CExcBase(const astr& msg) : m_srcThreadId(CThread::GetCurThreadId())
	{
		AddMsg(msg);
	}

	CExcBase::CExcBase(const wstr& msg) : m_srcThreadId(CThread::GetCurThreadId())
	{
		AddMsg(StringEncoding::str_w2utf8_safe(msg));
	}

	CExcBase::~CExcBase()
	{

	}
	
	std::shared_ptr<CExcBase> CExcBase::Clone() const
	{
		std::shared_ptr<CExcBase> ptrExc( new CExcBase(*this));
		return ptrExc;
	}

	void CExcBase::Throw()
	{
		throw *this;
	}

	const char*  CExcBase::what() const
	{
		m_what.clear();

		for (size_t i = 0, sz = m_msgChain.size(); i < sz; ++i)
		{
			if (i != 0)
				m_what += "\r\n";

			m_what += m_msgChain[i];
		}

		return m_what.c_str();
	}

	void CExcBase::AddMsg(const astr& msg)
	{
		m_msgChain.push_back(msg);
	}

	void CExcBase::AddMsg(const astr& format, const astr& msg)
	{
		m_msgChain.push_back(str_format::StrFormatSafe(format, msg));
	}

	void CExcBase::AddMsg(const astr& format, const astr& msg1, const astr& msg2)
	{
		m_msgChain.push_back(str_format::StrFormatSafe(format, msg1, msg2));
	}

	void CExcBase::AddMsg(const astr& format, const astr& msg1, const astr& msg2, const astr& msg3)
	{
		m_msgChain.push_back(str_format::StrFormatSafe(format, msg1, msg2, msg3));
	}

	void CExcBase::AddMsg(const astr& format, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4)
	{
		m_msgChain.push_back(str_format::StrFormatSafe(format, msg1, msg2, msg3, msg4));
	}

	void CExcBase::AddMsg(const wstr& msg)
	{
		AddMsg(StringEncoding::str_w2utf8_safe(msg));
	}

	void CExcBase::AddMsg(const wstr& format, const wstr& msg)
	{
		AddMsg(StringEncoding::str_w2utf8_safe(format), StringEncoding::str_w2utf8_safe(msg));
	}


	void CExcBase::AddMsg(const wstr& format, const wstr& msg1, const wstr& msg2)
	{
		AddMsg(StringEncoding::str_w2utf8_safe(format), StringEncoding::str_w2utf8_safe(msg1), StringEncoding::str_w2utf8_safe(msg2));
	}

	void CExcBase::AddMsg(const wstr& format, const wstr& msg1, const wstr& msg2, const wstr& msg3)
	{
		AddMsg(StringEncoding::str_w2utf8_safe(format), StringEncoding::str_w2utf8_safe(msg1), StringEncoding::str_w2utf8_safe(msg2), StringEncoding::str_w2utf8_safe(msg3));
	}

	void CExcBase::AddMsg(const wstr& format, const wstr& msg1, const wstr& msg2, const wstr& msg3, const wstr& msg4)
	{
		AddMsg(StringEncoding::str_w2utf8_safe(format), StringEncoding::str_w2utf8_safe(msg1), StringEncoding::str_w2utf8_safe(msg2), StringEncoding::str_w2utf8_safe(msg3), StringEncoding::str_w2utf8_safe(msg4));
	}
		
	void CExcBase::RegenExc(const astr& msg, std::exception& exc_src)
	{
		CExcBase* pExcBase = dynamic_cast<CExcBase*>(&exc_src);
		if (pExcBase != NULL)
		{
			pExcBase->AddMsg(msg);
			throw;
		}
		else
		{
			astr msgWhat;
			if (const char* msg = exc_src.what())
				msgWhat = msg;

			CExcBase exc(msgWhat);
			throw exc;
		}
	}

	void CExcBase::RegenExc(const astr& format, const astr& msg, std::exception& exc_src)
	{
		RegenExc(str_format::StrFormatSafe(format, msg), exc_src);
	}

	void CExcBase::RegenExc(const astr& format, const astr& msg1, const astr& msg2, std::exception& exc_src)
	{
		RegenExc(str_format::StrFormatSafe(format, msg1, msg2), exc_src);
	}

	void CExcBase::RegenExc(const astr& format, const astr& msg1, const astr& msg2, const astr& msg3, std::exception& exc_src)
	{
		RegenExc(str_format::StrFormatSafe(format, msg1, msg2, msg3), exc_src);
	}

	void CExcBase::RegenExc(const astr& format, const astr& msg1, const astr& msg2, const astr& msg3, const astr& msg4, std::exception& exc_src)
	{
		RegenExc(str_format::StrFormatSafe(format, msg1, msg2, msg3, msg4), exc_src);
	}

}