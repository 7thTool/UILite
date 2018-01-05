#pragma once

#ifndef _H_UIUSER_H_
#define _H_UIUSER_H_

#include <UI/UIBase.h>
#include <XLib/UILite.h>
#include <XLib/XUser.h>

//////////////////////////////////////////////////////////////////////////
#if _MSC_VER <= 1500

#ifndef _WIN32_WINNT_NT4
#define _WIN32_WINNT_NT4                    0x0400
#endif//
#ifndef _WIN32_WINNT_WIN2K
#define _WIN32_WINNT_WIN2K                  0x0500
#endif//
#ifndef _WIN32_WINNT_WINXP
#define _WIN32_WINNT_WINXP                  0x0501
#endif//
#ifndef _WIN32_WINNT_WS03
#define _WIN32_WINNT_WS03                   0x0502
#endif//
#ifndef _WIN32_WINNT_WIN6
#define _WIN32_WINNT_WIN6                   0x0600
#endif//
#ifndef _WIN32_WINNT_VISTA
#define _WIN32_WINNT_VISTA                  0x0600
#endif//
#ifndef _WIN32_WINNT_WS08
#define _WIN32_WINNT_WS08                   0x0600
#endif//
#ifndef _WIN32_WINNT_LONGHORN
#define _WIN32_WINNT_LONGHORN               0x0600
#endif//
#ifndef _WIN32_WINNT_WIN7
#define _WIN32_WINNT_WIN7                   0x0601
#endif//
#ifndef _WIN32_WINNT_WIN8
#define _WIN32_WINNT_WIN8                   0x0602
#endif//
#ifndef _WIN32_WINNT_WINBLUE
#define _WIN32_WINNT_WINBLUE                0x0603
#endif//
#ifndef _WIN32_WINNT_WINTHRESHOLD
#define _WIN32_WINNT_WINTHRESHOLD           0x0A00 /* ABRACADABRA_THRESHOLD*/
#endif//
#ifndef _WIN32_WINNT_WIN10
#define _WIN32_WINNT_WIN10                  0x0A00 /* ABRACADABRA_THRESHOLD*/
#endif//

UILITE_API BOOL IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor);
UILITE_API BOOL IsWindowsXPOrGreater();
UILITE_API BOOL IsWindowsXPSP1OrGreater();
UILITE_API BOOL IsWindowsXPSP2OrGreater();
UILITE_API BOOL IsWindowsXPSP3OrGreater();
UILITE_API BOOL IsWindowsVistaOrGreater();
UILITE_API BOOL IsWindowsVistaSP1OrGreater();
UILITE_API BOOL IsWindowsVistaSP2OrGreater();
UILITE_API BOOL IsWindows7OrGreater();
UILITE_API BOOL IsWindows7SP1OrGreater();
UILITE_API BOOL IsWindows8OrGreater();
UILITE_API BOOL IsWindows8Point1OrGreater();
UILITE_API BOOL IsWindowsThresholdOrGreater();
UILITE_API BOOL IsWindows10OrGreater();

#else

#include <VersionHelpers.h>

#endif//

//////////////////////////////////////////////////////////////////////////
///User API
//////////////////////////////////////////////////////////////////////////

//Copy or Move File to Clipboard
UILITE_API BOOL SHCopyClipFile(const CStringArray& strFiles, BOOL bCopy = TRUE);
//Paste Clipboard File to Path
//UILITE_API BOOL SHPasteFile(const CString& strPath);
//Delete File
UILITE_API BOOL SHDeleteFile(const CStringArray& strFiles, BOOL bRecycle = TRUE);
//Rename File
//UILITE_API BOOL SHRenameFile(const CString& strFile, const CString& strNewFile);
//Get Spectial Folder
UILITE_API BOOL SHGetFolderPath(CString& strPath, int CSIDL, BOOL bCreate = FALSE);
UILITE_API CString SHGetFolderPath(int CSIDL, BOOL bCreate = FALSE);

//////////////////////////////////////////////////////////////////////////////////////

typedef std::set<CString,CStringLess> StrSet;
typedef set<CString,CStringNoCaseLess> StrNoCaseSet;

/////////////////////////////////////////////////////////////////////////////
// CHandle

#if (_ATL_VER < 0x0700)

class CHandle
{
public:
	HANDLE m_h;

	CHandle(HANDLE hSrc = INVALID_HANDLE_VALUE) : m_h(hSrc)
	{ }

	~CHandle()
	{
		Close();
	}

	operator HANDLE() const { return m_h; };

	LPHANDLE operator&()
	{
		ATLASSERT(!IsValid());
		return &m_h;
	}

	CHandle& operator=(HANDLE h)
	{
		ATLASSERT(!IsValid());
		m_h = h;
		return *this;
	}

	bool IsValid() const { return m_h != INVALID_HANDLE_VALUE; };

	void Attach(HANDLE h)
	{
		if( IsValid() ) ::CloseHandle(m_h);
		m_h = h;
	}   
	HANDLE Detach()
	{
		HANDLE h = m_h;
		m_h = INVALID_HANDLE_VALUE;
		return h;
	}

	BOOL Close()
	{
		BOOL bRes = FALSE;
		if( m_h != INVALID_HANDLE_VALUE ) {
			bRes = ::CloseHandle(m_h);
			m_h = INVALID_HANDLE_VALUE;
		}
		return bRes;
	}

	BOOL Duplicate(HANDLE hSource, bool bInherit = false)
	{
		ATLASSERT(!IsValid());
		HANDLE hOurProcess = ::GetCurrentProcess();
		BOOL b = ::DuplicateHandle(hOurProcess, 
			hSource,
			hOurProcess, 
			&m_h,
			DUPLICATE_SAME_ACCESS,
			bInherit,
			DUPLICATE_SAME_ACCESS);
		ATLASSERT(b);
		return b;
	}
};

#endif // _ATL_VER

#endif//_H_UIUSER_H_