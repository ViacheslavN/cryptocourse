#pragma once

#include "File.h"

namespace CommonLib
{

	class CFileWin32 : public IFile
	{
	public:
		CFileWin32();
		~CFileWin32();

		virtual void Attach(FileHandle handle);
		virtual FileHandle Deattach();
		virtual FileHandle Handle() const;
		virtual void OpenFileA(const char *pszFileNameUtf8, enOpenFileMode mode, enAccesRights access, enShareMode share, enOpenFileType openType);
		virtual void OpenFile(const wchar_t *pszFileName, enOpenFileMode mode, enAccesRights access, enShareMode share, enOpenFileType openType);
		virtual uint64_t GetFileSize() const;
		virtual void SetFilePos64(uint64_t nPos, enSeekOffset offset);
		virtual void SetFilePos(uint32_t nPos, enSeekOffset offset);
		virtual uint64_t GetFilePos() const;
		virtual void SetFileEnd();
		virtual void SetFileBegin();
		virtual uint32_t WriteFile(const void* pData, uint32_t nSize);
		virtual uint32_t ReadFile(void* pData, uint32_t nSize);
		virtual void CloseFile();
		virtual bool IsValid() const;
		virtual void Flush();

		void OpenFileWin(const wchar_t *pszFileName, enOpenFileMode mode, enAccesRights access, enShareMode share, enOpenFileType openType, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);

	private:

		bool CloseFileImpl();
 
	private:

		FileHandle m_FileHandle{ INVALID_HANDLE_VALUE };
		bool m_Attach{false};
	};

	typedef CFileWin32 CFile;

}
