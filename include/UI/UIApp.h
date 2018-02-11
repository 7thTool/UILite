
#pragma once

#ifndef _H_UIAPP_H_
#define _H_UIAPP_H_

#include "UIBase.h"

//////////////////////////////////////////////////////////////////////////
//UIApp
//////////////////////////////////////////////////////////////////////////

class UIMessageLoop : public WTL::CMessageLoop
{
	typedef WTL::CMessageLoop Base;
protected:
	HWND m_hMainWnd;

public:
	UIMessageLoop() : m_hMainWnd(NULL) {}
	~UIMessageLoop() {}

	/*void SetMainWnd(HWND hMainWnd) { m_hMainWnd = hMainWnd; }
	HWND GetMainWnd() { return m_hMainWnd; }

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		BOOL bRet = FALSE;//Base::PreTranslateMessage(pMsg);
		if(!bRet) {
			HWND hWnd = NULL;
			for (hWnd = pMsg->hwnd; hWnd != NULL; hWnd = GetParent(hWnd))
			{
				bRet = SendMessage(hWnd, WM_PRETRANSLATEMSG, 0, (LPARAM)pMsg);
				if (bRet) {
					return TRUE;
				}
				if (hWnd == m_hMainWnd) {
					return FALSE;
				}
			}
			if (m_hMainWnd) {
				if (pMsg->hwnd != m_hMainWnd) {
					bRet = SendMessage(m_hMainWnd, WM_PRETRANSLATEMSG, 0, (LPARAM)pMsg);
				}
			}
		}
		return bRet;
	}*/
};

template <class T>
class UIMessageFilter : public WTL::CMessageFilter
{
	typedef UIMessageFilter<T> This;
	typedef WTL::CMessageFilter Base;
public:
	BOOL PreTranslateMessage(MSG* pMsg)
	{
		T* pT = static_cast<T*>(this);
		//模仿MFC的PreTranslateMessage的实现
		for (HWND hWnd = pMsg->hwnd; hWnd != NULL; )
		{
			if (hWnd == pT->m_hWnd) {
				break;
			}
			if(::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg)) {
				return TRUE;
			}
			hWnd = ::GetParent(hWnd);
		}
		return FALSE;
	}
};

template<class TBase>
class UIModuleBase : public TBase
{
	typedef UIModuleBase<TBase> This;
	typedef TBase Base;
public:
	HRESULT Init(ATL::_ATL_OBJMAP_ENTRY* pObjMap, HINSTANCE hInstance, const GUID* pLibID = NULL)
	{
		TCHAR szPath[_MAX_PATH] = {0};
		GetModuleFileName(hInstance, szPath, MAX_PATH);
		_tsplitpath(szPath, m_szDrive, m_szDir, m_szName, m_szExt);

		_tcscpy(m_szAppPath, szPath);
		PathRemoveFileSpec(m_szAppPath);

		SHGetSpecialFolderPath(NULL, szPath, CSIDL_APPDATA, TRUE);
		_sntprintf(m_szAppData, _MAX_PATH, _T("%s\\%s"), szPath, m_szName);
		SHCreateDirectoryEx(NULL, m_szAppData, NULL);

		HRESULT hRet = Base::Init(pObjMap, hInstance, pLibID);
		if(FAILED(hRet))
			return hRet;

		m_gdiplusToken = 0;
		Gdiplus::GdiplusStartupInput gdiplusStartupInput;
		Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

		return hRet;
	}

	void Term()
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
		Base::Term();

		free((void*)m_pszAppName);
		free((void*)m_pszRegistryKey);
		//free((void*)m_pszExeName);
		//free((void*)m_pszHelpFilePath);
		free((void*)m_pszProfileName);
	}

	UIMessageLoop* GetMessageLoop(DWORD dwThreadID = ::GetCurrentThreadId()) const
	{
		return static_cast<UIMessageLoop*>(TBase::GetMessageLoop(dwThreadID));
	}

	inline LPCTSTR GetDrive()
	{
		return m_szDrive;
	}

	inline LPCTSTR GetDir()
	{
		return m_szDir;
	}

	inline LPCTSTR GetName()
	{
		return m_szName;
	}

	inline LPCTSTR GetExt()
	{
		return m_szExt;
	}

	inline LPCTSTR GetAppPath()
	{
		return m_szAppPath;
	}

	inline LPCTSTR GetAppData()
	{
		return m_szAppData;
	}

	//App RegistryKey
	void SetRegistryKey(LPCTSTR lpszRegistryKey)
	{
		ASSERT(m_pszRegistryKey == NULL);
		ASSERT(lpszRegistryKey != NULL);

		free((void*)m_pszRegistryKey);
		m_pszRegistryKey = _tcsdup(lpszRegistryKey);
	}

	void SetRegistryKey(UINT nIDRegistryKey)
	{
		ASSERT(m_pszRegistryKey == NULL);

		TCHAR szRegistryKey[256] = {0};
		LoadString(GetResourceInstance(), nIDRegistryKey, szRegistryKey, 255);
		SetRegistryKey(szRegistryKey);
	}

	void SetAppName(LPCTSTR lpszAppName)
	{
		ASSERT(m_pszAppName == NULL);
		ASSERT(lpszAppName != NULL);

		free((void*)m_pszAppName);
		m_pszAppName = _tcsdup(lpszAppName);
	}

	void SetAppName(UINT nIDAppName)
	{
		TCHAR szAppName[256] = {0};
		LoadString(GetResourceInstance(), nIDAppName, szAppName, 255);
		SetAppName(szAppName);
	}

	void SetProfileName(LPCTSTR lpszProfileName)
	{
		ASSERT(m_pszProfileName == NULL);
		ASSERT(lpszProfileName != NULL);

		free((void*)m_pszProfileName);
		m_pszProfileName = _tcsdup(lpszProfileName);
	}

	void SetProfileName(UINT nIDProfileName)
	{
		TCHAR szProfileName[256] = {0};
		LoadString(GetResourceInstance(), nIDProfileName, szProfileName, 255);
		SetAppName(szProfileName);
	}

	HKEY GetAppRegistryKey()
	{
		ASSERT(m_pszRegistryKey != NULL);

		HKEY hAppKey = NULL;
		HKEY hSoftKey = NULL;
		HKEY hCompanyKey = NULL;
		if (RegOpenKeyEx(HKEY_CURRENT_USER, _T("software"), 0, KEY_WRITE|KEY_READ,
			&hSoftKey) == ERROR_SUCCESS)
		{
			DWORD dw;
			if (RegCreateKeyEx(hSoftKey, m_pszRegistryKey, 0, REG_NONE,
				REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
				&hCompanyKey, &dw) == ERROR_SUCCESS)
			{
				RegCreateKeyEx(hCompanyKey, m_pszAppName, 0, REG_NONE,
					REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
					&hAppKey, &dw);
			}
		}
		if (hSoftKey != NULL)
			RegCloseKey(hSoftKey);
		if (hCompanyKey != NULL)
			RegCloseKey(hCompanyKey);

		return hAppKey;
	}

	// returns key for:
	//      HKEY_CURRENT_USER\"Software"\RegistryKey\AppName\lpszSection
	// creating it if it doesn't exist.
	// responsibility of the caller to call RegCloseKey() on the returned HKEY
	HKEY GetSectionKey(LPCTSTR lpszSection)
	{
		ASSERT(lpszSection != NULL);

		HKEY hSectionKey = NULL;
		HKEY hAppKey = GetAppRegistryKey();
		if (hAppKey == NULL)
			return NULL;

		DWORD dw;
		RegCreateKeyEx(hAppKey, lpszSection, 0, REG_NONE,
			REG_OPTION_NON_VOLATILE, KEY_WRITE|KEY_READ, NULL,
			&hSectionKey, &dw);
		RegCloseKey(hAppKey);
		return hSectionKey;
	}

	UINT GetProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nDefault)
	{
		ASSERT(lpszSection != NULL);
		ASSERT(lpszEntry != NULL);
		if (m_pszRegistryKey != NULL) // use registry
		{
			HKEY hSecKey = GetSectionKey(lpszSection);
			if (hSecKey == NULL)
				return nDefault;
			DWORD dwValue;
			DWORD dwType;
			DWORD dwCount = sizeof(DWORD);
			LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
				(LPBYTE)&dwValue, &dwCount);
			RegCloseKey(hSecKey);
			if (lResult == ERROR_SUCCESS)
			{
				ASSERT(dwType == REG_DWORD);
				ASSERT(dwCount == sizeof(dwValue));
				return (UINT)dwValue;
			}
			return nDefault;
		}
		else
		{
			ASSERT(m_pszProfileName != NULL);
			return ::GetPrivateProfileInt(lpszSection, lpszEntry, nDefault, m_pszProfileName);
		}
	}

	CString GetProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszDefault)
	{
		ASSERT(lpszSection != NULL);
		ASSERT(lpszEntry != NULL);
		if (m_pszRegistryKey != NULL)
		{
			HKEY hSecKey = GetSectionKey(lpszSection);
			if (hSecKey == NULL)
				return lpszDefault;
			CString strValue;
			DWORD dwType=REG_NONE;
			DWORD dwCount=0;
			LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
				NULL, &dwCount);
			if (lResult == ERROR_SUCCESS)
			{
				ASSERT(dwType == REG_SZ);
				lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
					(LPBYTE)strValue.GetBuffer(dwCount/sizeof(TCHAR)), &dwCount);
				strValue.ReleaseBuffer();
			}
			RegCloseKey(hSecKey);
			if (lResult == ERROR_SUCCESS)
			{
				ASSERT(dwType == REG_SZ);
				return strValue;
			}
			return lpszDefault;
		}
		else
		{
			ASSERT(m_pszProfileName != NULL);

			if (lpszDefault == NULL)
				lpszDefault = _T("");	// don't pass in NULL
			TCHAR szT[4096];
			DWORD dw = ::GetPrivateProfileString(lpszSection, lpszEntry,
				lpszDefault, szT, _countof(szT), m_pszProfileName);
			ASSERT(dw < 4095);
			return szT;
		}
	}

	BOOL GetProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, BYTE** ppData, UINT* pBytes)
	{
		ASSERT(lpszSection != NULL);
		ASSERT(lpszEntry != NULL);
		ASSERT(ppData != NULL);
		ASSERT(pBytes != NULL);
		*ppData = NULL;
		*pBytes = 0;
		if (m_pszRegistryKey != NULL)
		{
			HKEY hSecKey = GetSectionKey(lpszSection);
			if (hSecKey == NULL)
			{
				return FALSE;
			}

			// ensure destruction
			::ATL::CRegKey rkSecKey(hSecKey);

			DWORD dwType=0;
			DWORD dwCount=0; 
			LONG lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType, NULL, &dwCount);
			*pBytes = dwCount;
			if (lResult == ERROR_SUCCESS)
			{
				ASSERT(dwType == REG_BINARY);
				*ppData = new BYTE[*pBytes];
				lResult = RegQueryValueEx(hSecKey, (LPTSTR)lpszEntry, NULL, &dwType,
					*ppData, &dwCount);
			}
			if (lResult == ERROR_SUCCESS)
			{
				ASSERT(dwType == REG_BINARY);
				return TRUE;
			}
			else
			{
				delete [] *ppData;
				*ppData = NULL;
			}
			return FALSE;
		}
		else
		{
			ASSERT(m_pszProfileName != NULL);

			CString str = GetProfileString(lpszSection, lpszEntry, NULL);
			if (str.IsEmpty())
				return FALSE;
			ASSERT(str.GetLength()%2 == 0);
			INT_PTR nLen = str.GetLength();
			*pBytes = UINT(nLen)/2;
			*ppData = new BYTE[*pBytes];
			for (int i=0;i<nLen;i+=2)
			{
				(*ppData)[i/2] = (BYTE)
					(((str[i+1] - 'A') << 4) + (str[i] - 'A'));
			}
			return TRUE;
		}
	}


	BOOL WriteProfileInt(LPCTSTR lpszSection, LPCTSTR lpszEntry, int nValue)
	{
		ASSERT(lpszSection != NULL);
		ASSERT(lpszEntry != NULL);
		if (m_pszRegistryKey != NULL)
		{
			HKEY hSecKey = GetSectionKey(lpszSection);
			if (hSecKey == NULL)
				return FALSE;
			LONG lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_DWORD,
				(LPBYTE)&nValue, sizeof(nValue));
			RegCloseKey(hSecKey);
			return lResult == ERROR_SUCCESS;
		}
		else
		{
			ASSERT(m_pszProfileName != NULL);

			TCHAR szT[16];
			_stprintf_s(szT, _countof(szT), _T("%d"), nValue);
			return ::WritePrivateProfileString(lpszSection, lpszEntry, szT,
				m_pszProfileName);
		}
	}

	BOOL WriteProfileString(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPCTSTR lpszValue)
	{
		ASSERT(lpszSection != NULL);
		if (m_pszRegistryKey != NULL)
		{
			LONG lResult;
			if (lpszEntry == NULL) //delete whole section
			{
				HKEY hAppKey = GetAppRegistryKey();
				if (hAppKey == NULL)
					return FALSE;
				lResult = ::RegDeleteKey(hAppKey, lpszSection);
				RegCloseKey(hAppKey);
			}
			else if (lpszValue == NULL)
			{
				HKEY hSecKey = GetSectionKey(lpszSection);
				if (hSecKey == NULL)
					return FALSE;
				// necessary to cast away const below
				lResult = ::RegDeleteValue(hSecKey, (LPTSTR)lpszEntry);
				RegCloseKey(hSecKey);
			}
			else
			{
				HKEY hSecKey = GetSectionKey(lpszSection);
				if (hSecKey == NULL)
					return FALSE;
				lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_SZ,
					(LPBYTE)lpszValue, (lstrlen(lpszValue)+1)*sizeof(TCHAR));
				RegCloseKey(hSecKey);
			}
			return lResult == ERROR_SUCCESS;
		}
		else
		{
			ASSERT(m_pszProfileName != NULL);
			ASSERT(lstrlen(m_pszProfileName) < 4095); // can't read in bigger
			return ::WritePrivateProfileString(lpszSection, lpszEntry, lpszValue,
				m_pszProfileName);
		}
	}

	BOOL WriteProfileBinary(LPCTSTR lpszSection, LPCTSTR lpszEntry, LPBYTE pData, UINT nBytes)
	{
		ASSERT(lpszSection != NULL);
		if (m_pszRegistryKey != NULL)
		{
			LONG lResult;
			HKEY hSecKey = GetSectionKey(lpszSection);
			if (hSecKey == NULL)
				return FALSE;
			lResult = RegSetValueEx(hSecKey, lpszEntry, NULL, REG_BINARY,
				pData, nBytes);
			RegCloseKey(hSecKey);
			return lResult == ERROR_SUCCESS;
		}

		// convert to string and write out
		LPTSTR lpsz = new TCHAR[nBytes*2+1];
		UINT i;
		for (i = 0; i < nBytes; i++)
		{
			lpsz[i*2] = (TCHAR)((pData[i] & 0x0F) + 'A'); //low nibble
			lpsz[i*2+1] = (TCHAR)(((pData[i] >> 4) & 0x0F) + 'A'); //high nibble
		}
		lpsz[i*2] = 0;

		ASSERT(m_pszProfileName != NULL);

		BOOL bResult = WriteProfileString(lpszSection, lpszEntry, lpsz);
		delete[] lpsz;
		return bResult;
	}
protected:
	ULONG_PTR m_gdiplusToken;

	//
	TCHAR m_szDrive[_MAX_DRIVE];
	TCHAR m_szDir[_MAX_DIR];
	TCHAR m_szName[_MAX_FNAME];
	TCHAR m_szExt[_MAX_EXT];

	// App Path
	TCHAR m_szAppPath[MAX_PATH];

	// App Data
	TCHAR m_szAppData[MAX_PATH];

	// App Name
	LPCTSTR m_pszAppName;

	// Name of registry key for this application. See
	// SetRegistryKey() member function.
	LPCTSTR m_pszRegistryKey;

	// Name of profile name for this application.
	LPCTSTR m_pszProfileName;
};

typedef UIModuleBase<WTL::CAppModule> UIAppModule;
typedef UIModuleBase<WTL::CServerAppModule> UIServerAppModule;

namespace UIHelper
{
	inline OSVERSIONINFO GetOSVertion()
	{
		OSVERSIONINFO ovi = {sizeof(OSVERSIONINFO), 0};
		::GetVersionEx(&ovi);
		return ovi;
	}

#ifndef _WIN32_WCE
	static bool IsVista()
	{
		return WTL::RunTimeHelper::IsVista();
	}

	static bool IsWin7()
	{
		return WTL::RunTimeHelper::IsWin7();
	}
#endif // !_WIN32_WCE

	inline BOOL IsWindowsServer()
	{
		OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, {0}, 0, 0, 0, VER_NT_WORKSTATION };
		DWORDLONG const dwlConditionMask = VerSetConditionMask(0, VER_PRODUCT_TYPE, VER_EQUAL);
		return !VerifyVersionInfoW(&osvi, VER_PRODUCT_TYPE, dwlConditionMask);
	}

	inline HINSTANCE GetModuleInstance()
	{
		return WTL::ModuleHelper::GetModuleInstance();
	}

	inline HINSTANCE GetResourceInstance()
	{
		return WTL::ModuleHelper::GetResourceInstance();
	}
	inline HINSTANCE SetResourceInstance(HINSTANCE hInst)
	{
#if (_ATL_VER >= 0x0700)
		return ATL::_AtlBaseModule.SetResourceInstance(hInst);
#else // !(_ATL_VER >= 0x0700)
		return ATL::_pModule->SetResourceInstance(hInst);
#endif // !(_ATL_VER >= 0x0700)
	}

	// Windows version helper
	inline bool IsOldWindows()
	{
		return WTL::AtlIsOldWindows();
	}

	// Common Controls initialization helper
	inline BOOL InitCommonControls(DWORD dwFlags)
	{
		return WTL::AtlInitCommonControls(dwFlags);
	}

#ifndef _WIN32_WCE
	/*static bool IsCommCtrl6()
	{
		return WTL::RunTimeHelper::IsCommCtrl6();
	}*/

	static bool IsThemeAvailable()
	{
		return WTL::RunTimeHelper::IsThemeAvailable();
	}

	static bool IsRibbonUIAvailable()
	{
		return WTL::RunTimeHelper::IsRibbonUIAvailable();
	}

#endif // !_WIN32_WCE

	static int SizeOf_REBARBANDINFO()
	{
		return WTL::RunTimeHelper::SizeOf_REBARBANDINFO();
	}

#if (_WIN32_WINNT >= 0x501)
	static int SizeOf_LVGROUP()
	{
		return WTL::RunTimeHelper::SizeOf_LVGROUP();
	}

	static int SizeOf_LVTILEINFO()
	{
		return WTL::RunTimeHelper::SizeOf_LVTILEINFO();
	}
#endif // (_WIN32_WINNT >= 0x501)

	static int SizeOf_MCHITTESTINFO()
	{
		return WTL::RunTimeHelper::SizeOf_MCHITTESTINFO();
	}

#ifndef _WIN32_WCE
	static int SizeOf_NONCLIENTMETRICS()
	{
		return WTL::RunTimeHelper::SizeOf_NONCLIENTMETRICS();
	}
#endif // !_WIN32_WCE


	/*static HRESULT GetDllVersion(HINSTANCE hInstDLL, DLLVERSIONINFO* pDllVersionInfo)
	{
		return ATL::AtlGetDllVersion(hInstDLL, pDllVersionInfo);
	}

	static HRESULT GetDllVersion(LPCTSTR lpstrDllName, DLLVERSIONINFO* pDllVersionInfo)
	{
		return ATL::AtlGetDllVersion(lpstrDllName, pDllVersionInfo);
	}

	// Common Control Versions:
	//   Win95/WinNT 4.0    maj=4 min=00
	//   IE 3.x     maj=4 min=70
	//   IE 4.0     maj=4 min=71
	static HRESULT GetCommCtrlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
	{
		return ATL::AtlGetCommCtrlVersion(pdwMajor, pdwMinor);
	}

	// Shell Versions:
	//   Win95/WinNT 4.0                    maj=4 min=00
	//   IE 3.x, IE 4.0 without Web Integrated Desktop  maj=4 min=00
	//   IE 4.0 with Web Integrated Desktop         maj=4 min=71
	//   IE 4.01 with Web Integrated Desktop        maj=4 min=72
	static HRESULT GetShellVersion(LPDWORD pdwMajor, LPDWORD pdwMinor)
	{
		return ATL::AtlGetShellVersion(pdwMajor, pdwMinor);
	}*/
};

#endif//_H_UIAPP_H_