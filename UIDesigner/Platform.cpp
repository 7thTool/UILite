// Platform.cpp : main source file for Platform.exe
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Platform.h"

Platform _Platform;

Platform::Platform()
{
	
}

Platform::~Platform()
{

}

long Platform::Init()
{
	long rlt = UXModule::Init();

	TCHAR szTemp[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	TCHAR szTempPath[MAX_PATH];

	CurrentDirectory curdir;
	//
	_stprintf(szPath, _T("%s\\%s.xml"), _Module.GetAppPath(), _Module.GetName());
	m_Name2pMarkup[_T("")] = new Markup(szPath);

	if (!File::IsFileExist(_Module.GetAppData())) {
		File::CreateDirectory(_Module.GetAppData());
	}
	_stprintf(szPath, _T("%s\\%s.xml"), _Module.GetAppData(), _Module.GetName());
	m_Name2pMarkup[APPFILE] = new Markup(szPath,TRUE);//app data goto.xml for global store data.

	m_Name2pMarkup[MEMFILE] = new Markup();

	//THEME
	memset(szTemp, 0, sizeof(szTemp));
	memset(szPath, 0, sizeof(szPath));
	if(RLT_OK == ReadValue(_T("name"), szTemp, MAX_PATH, _T("root/theme"), APPFILE)) {
		_stprintf(szPath, _T("%s\\theme\\%s"), _Module.GetAppData(), szTemp);
	}
	if (!PathFileExists(szPath)) {
		_stprintf(szPath, _T("%s\\default"), _Module.GetAppPath());
	}
	curdir.SetCurrentDirectory(szPath);
	Markup* xml = new Markup(_T("theme.xml"));
	m_Name2pMarkup[THEMEFILE] = xml;
	xml->Find(UIX_SKIN_ROOT);
	xml->IntoElem();
	LoadSkin((LPCTSTR)xml, XML_FLAG_MARKUP);
	xml->OutofElem();
	//UxModule::LoadSkin(_T("theme.xml"));
	curdir.RestoreCurrentDirectory();

	return rlt;
}

void Platform::Term()
{
	Name2pMarkup::iterator iter = m_Name2pMarkup.begin();
	for (;iter != m_Name2pMarkup.end(); ++iter)
	{
		if (iter->second) {
			delete iter->second;
		}
	}
	m_Name2pMarkup.clear();

	UXModule::Term();
}

Markup* Platform::OpenMarkup(LPCTSTR lpszFile)
{
	if(!lpszFile || !lpszFile[0]) {
		return m_Name2pMarkup[_T("")];
	}
	Name2pMarkup::iterator iter = m_Name2pMarkup.find(lpszFile);
	if (iter != m_Name2pMarkup.end()) {
		return iter->second;
	} else {
		//
	}
	return NULL;
}

void Platform::CloseMarkup(LPCTSTR lpszFile)
{
	Name2pMarkup::iterator it = m_Name2pMarkup.find(lpszFile);
	if(it != m_Name2pMarkup.end()) {
		it->second->Close();
		delete it->second;
		m_Name2pMarkup.erase(it);
	}
}

long Platform::WriteValue(LPCSTR lpszName, LPCSTR lpszValue, int nValueCount, LPCSTR lpszSpec, LPCSTR lpszFile)
{
	long rlt = RLT_UNKNOWN;
#ifdef UNICODE
	std::string name(lpszName), val(lpszValue);
	std::wstring wname, wval;
	mb2wc(name, wname, CP_OEMCP);
	mb2wc(val, wval, CP_OEMCP);
	if (!lpszFile || !lpszFile[0]) {
		if (lpszSpec == NULL || lpszSpec[0]==0) {
			rlt = WriteValue(wname.c_str(), wval.c_str(), wval.length());
		} else {
			std::string spec(lpszSpec);
			std::wstring wspec;
			mb2wc(spec, wspec, CP_OEMCP);
			rlt = WriteValue(wname.c_str(), wval.c_str(), wval.length(), wspec.c_str());
		}
	} else {
		std::string config(lpszFile);
		std::wstring wconfig;
		mb2wc(config, wconfig, CP_OEMCP);
		if (lpszSpec == NULL || lpszSpec[0]==0) {
			rlt = WriteValue(wname.c_str(), wval.c_str(), wval.length(), NULL, wconfig.c_str());
		} else {
			std::string spec(lpszSpec);
			std::wstring wspec;
			mb2wc(spec, wspec, CP_OEMCP);
			rlt = WriteValue(wname.c_str(), wval.c_str(), wval.length(), wspec.c_str(), wconfig.c_str());
		}
	}
#else
#endif
	return rlt;
	return RLT_UNKNOWN;
}

long Platform::ReadValue(LPCSTR lpszName, LPSTR lpszValue, int nValueCount, LPCSTR lpszSpec, LPCSTR lpszFile)
{
	long rlt = RLT_UNKNOWN;
#ifdef UNICODE
	std::string name(lpszName), val(lpszValue, nValueCount);
	std::wstring wname, wval(nValueCount, 0), wspec, wconfig;
	mb2wc(name, wname, CP_OEMCP);
	if (lpszSpec) {
		mb2wc(std::string(lpszSpec), wspec, CP_OEMCP);
	}
	if (lpszFile) {
		mb2wc(std::string(lpszFile), wconfig, CP_OEMCP);
	}
	rlt = ReadValue((LPCWSTR)wname.c_str(), (LPWSTR)wval.c_str(), nValueCount,
		lpszSpec ? (LPCWSTR)wspec.c_str() : NULL, lpszFile ? (LPCWSTR)wconfig.c_str() : NULL);
	if(rlt >= 0) {
		rlt = wc2mb((wchar_t*)wval.c_str(), rlt, lpszValue, nValueCount, CP_OEMCP);
	}
#else

#endif//
	return rlt;
	return RLT_UNKNOWN;
}

long Platform::WriteValue(LPCWSTR lpszName, LPCWSTR lpszValue, int nValueCount, LPCWSTR lpszSpec, LPCWSTR lpszFile)
{
	return RLT_UNKNOWN;
}

long Platform::ReadValue(LPCWSTR lpszName, LPWSTR lpszValue, int nValueCount, LPCWSTR lpszSpec, LPCWSTR lpszFile)
{
	long rlt = RLT_UNKNOWN;
#ifdef UNICODE
	bool bOk = false;
	if ((!lpszSpec || !lpszSpec[0]) && (!lpszFile || !lpszFile[0])) {
		if (wcsicmp(lpszName, WORKDIRW) == 0) {
			bOk = true;
			rlt = MIN(wcslen(_Module.GetAppPath()), nValueCount);
			wcsncpy(lpszValue, _Module.GetAppPath(), rlt);
		} else if (wcsicmp(lpszName, DATADIRW) == 0) {
			bOk = true;
			rlt = MIN(wcslen(_Module.GetAppData()), nValueCount);
			wcsncpy(lpszValue, _Module.GetAppData(), rlt);
		} else if (wcsicmp(lpszName, USERDIRW) == 0) {
			bOk = true;
			rlt = MIN(wcslen(_Module.GetAppData()), nValueCount);
			wcsncpy(lpszValue, _Module.GetAppData(), rlt);
		}
		if (bOk) {
			return rlt;
		}
	}
	Markup* pConfig = OpenMarkup(lpszFile);
	if(pConfig) {
		pConfig->ResetPos();
		if (!lpszSpec || !lpszSpec[0]) {
			wcsref strrefname((wchar_t*)lpszName), strrefval;
			if (pConfig->Find(strrefname)) {
				bOk = true;
				if(pConfig->Get(strrefname, strrefval)) {
					rlt = MIN(strrefval.second, nValueCount);
					wcsncpy(lpszValue, strrefval.first, rlt);
				}
			}
		} else {
			wcsref strrefname((wchar_t*)lpszName), strrefattr((wchar_t*)lpszSpec), strrefval;
			if(pConfig->Find(strrefname)) {
				if(pConfig->Get(strrefname, strrefattr, strrefval)) {
					bOk = true;
					rlt = MIN(strrefval.second, nValueCount - 1);
					wcsncpy(lpszValue, strrefval.first, rlt);
				}
			}
		}
	}
	if(!bOk) {
		if (!lpszFile || !lpszFile[0]) {
		} else if (wcsicmp(lpszFile, MEMFILEW) == 0) {
			rlt = ReadValue(lpszName, lpszValue, nValueCount, lpszSpec, USERFILEW);
		} else if (wcsicmp(lpszFile, USERFILEW) == 0) {
			rlt = ReadValue(lpszName, lpszValue, nValueCount, lpszSpec, APPFILEW);
		}
	} 
#else

#endif//
	return RLT_UNKNOWN;
}

