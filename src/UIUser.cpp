#include "stdafx.h"
#include "UIUser.h"
#include <XLib/XStr.h>

//////////////////////////////////////////////////////////////////////////

#if _MSC_VER <= 1400

typedef LONG (NTAPI* lpfnRtlGetVersion)(PRTL_OSVERSIONINFOW lpVersionInformation);

BOOL IsWindowsVersionOrGreater(WORD wMajorVersion, WORD wMinorVersion, WORD wServicePackMajor)
{
	/*OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0 };
	DWORDLONG const dwlConditionMask = VerSetConditionMask(VerSetConditionMask(VerSetConditionMask(0, VER_MAJORVERSION, VER_GREATER_EQUAL), VER_MINORVERSION, VER_GREATER_EQUAL), VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
	osvi.dwMajorVersion = wMajorVersion;
	osvi.dwMinorVersion = wMinorVersion;
	osvi.wServicePackMajor = wServicePackMajor;
	return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;*/

	static RTL_OSVERSIONINFOEXW VerInfo = {0};
	if(VerInfo.dwOSVersionInfoSize == 0) {
		static lpfnRtlGetVersion RtlGetVersion = (lpfnRtlGetVersion)GetProcAddress(GetModuleHandle(_T("ntdll.dll")),"RtlGetVersion");
		if (RtlGetVersion) {
			VerInfo.dwOSVersionInfoSize = sizeof(VerInfo);
			RtlGetVersion((PRTL_OSVERSIONINFOW)&VerInfo);
		}
	}
	if(VerInfo.dwOSVersionInfoSize!=0) {
		if (VerInfo.dwMajorVersion > wMajorVersion) {
			return TRUE;
		} else if (VerInfo.dwMajorVersion < wMajorVersion) {
			return FALSE;
		}

		if (VerInfo.dwMinorVersion > wMinorVersion) {
			return TRUE;
		} else if (VerInfo.dwMinorVersion < wMinorVersion) {
			return FALSE;
		}

		if (VerInfo.wServicePackMajor >= wServicePackMajor) {
			return TRUE;
		}
	}
	return FALSE;
}

BOOL IsWindowsXPOrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 0);
}

BOOL IsWindowsXPSP1OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 1);
}

BOOL IsWindowsXPSP2OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 2);
}

BOOL IsWindowsXPSP3OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINXP), LOBYTE(_WIN32_WINNT_WINXP), 3);
}

BOOL IsWindowsVistaOrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 0);
}

BOOL IsWindowsVistaSP1OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 1);
}

BOOL IsWindowsVistaSP2OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_VISTA), LOBYTE(_WIN32_WINNT_VISTA), 2);
}

BOOL IsWindows7OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 0);
}

BOOL IsWindows7SP1OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN7), LOBYTE(_WIN32_WINNT_WIN7), 1);
}

BOOL IsWindows8OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WIN8), LOBYTE(_WIN32_WINNT_WIN8), 0);
}

BOOL IsWindows8Point1OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINBLUE), LOBYTE(_WIN32_WINNT_WINBLUE), 0);
}

BOOL IsWindowsThresholdOrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINTHRESHOLD), LOBYTE(_WIN32_WINNT_WINTHRESHOLD), 0);
}

BOOL IsWindows10OrGreater()
{
	return IsWindowsVersionOrGreater(HIBYTE(_WIN32_WINNT_WINTHRESHOLD), LOBYTE(_WIN32_WINNT_WINTHRESHOLD), 0);
}

#endif//

//////////////////////////////////////////////////////////////////////////

//Copy or Move File to Clipboard
//UILITE_API BOOL SHCopyClipFile(CStringArray& strFiles, BOOL bCopy = TRUE);
BOOL SHCopyClipFile(const CStringArray& strFiles, BOOL bCopy/* = TRUE*/)
{
	INT i, j;
	//建立源文件列表
	DWORD dwFilesSize = 0;
	for (i = 0, j = strFiles.GetSize(); i < j; ++i) {
		dwFilesSize += (strFiles[i].GetLength() + 1) * sizeof TCHAR;
	}
	LPTSTR pszFrom = (LPTSTR) new BYTE [dwFilesSize];
	memset(pszFrom, dwFilesSize, 0);
	LPTSTR pszFiles = pszFrom;
	for (i = 0, j = strFiles.GetSize(); i < j; ++i) {
		_tcscpy(pszFiles, strFiles[i]);
		pszFiles += strFiles[i].GetLength() + 1;
	}

	BOOL ret = SHCopyClipFile((LPBYTE)pszFrom, dwFilesSize, bCopy);
	delete [](LPBYTE)pszFrom;
	return ret;
}

//Paste Clipboard File to Path
//BOOL SHPasteFile(const CString& strPath)
//{
//	return SHPasteFile((LPCTSTR)strPath);
//}

//Delete File
//UILITE_API BOOL SHDeleteFile(CStringArray& strFiles, BOOL bRecycle = TRUE);
BOOL SHDeleteFile(const CStringArray& strFiles, BOOL bRecycle/* = TRUE*/)
{
	INT i, j;
	//建立源文件列表
	DWORD dwFilesSize = 0;
	for (i = 0, j = strFiles.GetSize(); i < j; ++i) {
		dwFilesSize += (strFiles[i].GetLength() + 1) * sizeof TCHAR;
	}
	LPTSTR pszFrom = (LPTSTR) new BYTE [dwFilesSize];
	memset(pszFrom, dwFilesSize, 0);
	LPTSTR pszFiles = pszFrom;
	for (i = 0, j = strFiles.GetSize(); i < j; ++i) {
		_tcscpy(pszFiles, strFiles[i]);
		pszFiles += strFiles[i].GetLength() + 1;
	}

	BOOL ret = SHDeleteFile((LPBYTE)pszFrom, dwFilesSize, bRecycle);
	delete [](LPBYTE)pszFrom;
	return ret;
}

//Rename File
//BOOL SHRenameFile(const CString& strFile, const CString& strNewFile)
//{
//	return SHRenameFile((LPCTSTR)strFile, (LPCTSTR)strNewFile);
//}

//Get Spectial Folder
BOOL SHGetFolderPath(CString& strPath, int CSIDL, BOOL bCreate)
{
	BOOL bOk = SHGetFolderPath(CSIDL, strPath.GetBuffer(MAX_PATH), bCreate);
	strPath.ReleaseBuffer();
	return bOk;
}
CString SHGetFolderPath(int CSIDL, BOOL bCreate)
{
	CString strPath;
	SHGetFolderPath(strPath, CSIDL, bCreate);
	return strPath;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

