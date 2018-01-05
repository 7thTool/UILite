#pragma once

#ifndef _H_UIWEBBROWSER_H_
#define _H_UIWEBBROWSER_H_

#include "UIcom.h"
#include <exdispid.h>

//////////////////////////////////////////////////////////////////////////
///UIWebBrowser2
//////////////////////////////////////////////////////////////////////////
class UIWebBrowser2
{
public:
	CComPtr<IWebBrowser2> m_spBrowser;

	// Ctor
	UIWebBrowser2(IWebBrowser2* pBrowser = NULL) : m_spBrowser(pBrowser)
	{
	}

	BOOL IsBrowserNull() 
	{
		return m_spBrowser == NULL ? TRUE : FALSE;
	}

	// properties
	void SetRegisterAsBrowser(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_RegisterAsBrowser(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetRegisterAsDropTarget(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_RegisterAsDropTarget(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetTheaterMode(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_TheaterMode(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetVisible(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_Visible(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetMenuBar(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_MenuBar(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetToolBar(int nNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_ToolBar(nNewValue);
	}
	void SetOffline(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_Offline(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetSilent(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_Silent(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void GoBack()
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->GoBack();
	}
	void GoForward()
	{ 
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->GoForward();
	}
	void GoHome()
	{
		ATLASSERT(m_spBrowser != NULL); 
		m_spBrowser->GoHome();
	}
	void GoSearch()
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->GoSearch();
	}
	void Refresh()
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->Refresh();
	}
	void Refresh2(int nLevel)
	{
		ATLASSERT(m_spBrowser != NULL);
		CComVariant v((long)nLevel);
		m_spBrowser->Refresh2(&v); 
	}
	void Stop()
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->Stop();
	}
	void SetFullScreen(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_FullScreen(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetAddressBar(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_AddressBar(bNewValue ? VARIANT_TRUE : VARIANT_FALSE);
	}
	void SetHeight(long nNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_Height(nNewValue);
	}
	void PutProperty(LPCTSTR lpszPropertyName, long lValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		PutProperty(lpszPropertyName, CComVariant(lValue));
	}
	void PutProperty(LPCTSTR lpszPropertyName, short nValue)
	{
		ATLASSERT(m_spBrowser != NULL); 
		PutProperty(lpszPropertyName, CComVariant(nValue));
	}
	void PutProperty(LPCTSTR lpszPropertyName, LPCTSTR lpszValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		PutProperty(lpszPropertyName, CComVariant(lpszValue)); 
	}
	void PutProperty(LPCTSTR lpszPropertyName, double dValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		PutProperty(lpszPropertyName, CComVariant(dValue));
	}
	void SetTop(long nNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_Top(nNewValue);
	}
	void SetLeft(long nNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_Left(nNewValue);
	}
	void SetStatusBar(BOOL bNewValue)
	{
		ATLASSERT(m_spBrowser != NULL);
		m_spBrowser->put_StatusBar(bNewValue ? VARIANT_TRUE : VARIANT_FALSE); 
	}

	CString GetType() const
	{
		ATLASSERT(m_spBrowser != NULL);

		CComBSTR bstr;
		m_spBrowser->get_Type(&bstr);
		return CString(bstr);
	}

	long GetLeft() const
	{
		ATLASSERT(m_spBrowser != NULL);

		long result;
		m_spBrowser->get_Left(&result);
		return result;
	}

	long GetTop() const
	{
		ATLASSERT(m_spBrowser != NULL);
		long result;
		m_spBrowser->get_Top(&result);
		return result;
	}

	int GetToolBar() const
	{
		ATLASSERT(m_spBrowser != NULL);
		int result;
		m_spBrowser->get_ToolBar(&result);
		return result;
	}

	long GetHeight() const
	{
		ATLASSERT(m_spBrowser != NULL);
		long result;
		m_spBrowser->get_Height(&result);
		return result;
	}

	bool GetVisible() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_Visible(&result);
		return (result == VARIANT_TRUE);
	}

	CString GetLocationName() const
	{
		ATLASSERT(m_spBrowser != NULL);

		CComBSTR bstr;
		m_spBrowser->get_LocationName(&bstr);
		return CString(bstr);
	}

	CString GetLocationURL() const
	{
		ATLASSERT(m_spBrowser != NULL);

		CComBSTR bstr;
		m_spBrowser->get_LocationURL(&bstr);
		return CString(bstr);
	}

	BOOL GetBusy() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_Busy(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	READYSTATE GetReadyState() const
	{
		ATLASSERT(m_spBrowser != NULL);

		READYSTATE result;
		m_spBrowser->get_ReadyState(&result);
		return result;
	}

	BOOL GetOffline() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_Offline(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetSilent() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_Silent(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	IDispatch* GetApplication() const
	{
		ATLASSERT(m_spBrowser != NULL);

		IDispatch* result;
		m_spBrowser->get_Application(&result);
		return result;
	}


	IDispatch* GetParentBrowser() const
	{
		ATLASSERT(m_spBrowser != NULL);

		IDispatch* result;
		m_spBrowser->get_Parent(&result);
		return result;
	}

	IDispatch* GetContainer() const
	{
		ATLASSERT(m_spBrowser != NULL);

		IDispatch* result;
		m_spBrowser->get_Container(&result);
		return result;
	}

	IDispatch* GetDocument() const
	{
		ATLASSERT(m_spBrowser != NULL);

		IDispatch* result;
		m_spBrowser->get_Document(&result);
		return result;
	}

	IHTMLElement* GetActiveElement() const
	{
		CComQIPtr<IHTMLDocument2> spDocument = GetDocument();
		if (spDocument) {
			IHTMLElement* result;
			spDocument->get_activeElement(&result);
			return result;
		}
		return NULL;
	}

	BOOL GetTopLevelContainer() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_TopLevelContainer(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetMenuBar() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_MenuBar(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetFullScreen() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_FullScreen(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetStatusBar() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_StatusBar(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	OLECMDF QueryStatusWB(OLECMDID cmdID) const
	{
		ATLASSERT(m_spBrowser != NULL);

		OLECMDF result;
		m_spBrowser->QueryStatusWB(cmdID, &result);
		return result;
	}

	void ExecWB(OLECMDID cmdID, OLECMDEXECOPT cmdexecopt,
		VARIANT* pvaIn, VARIANT* pvaOut)
	{
		ATLASSERT(m_spBrowser != NULL);

		m_spBrowser->ExecWB(cmdID, cmdexecopt, pvaIn, pvaOut);
	}

	BOOL GetRegisterAsBrowser() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_RegisterAsBrowser(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetRegisterAsDropTarget() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_RegisterAsDropTarget(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetTheaterMode() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_TheaterMode(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	BOOL GetAddressBar() const
	{
		ATLASSERT(m_spBrowser != NULL);

		VARIANT_BOOL result;
		m_spBrowser->get_AddressBar(&result);
		return (result == VARIANT_TRUE) ? TRUE : FALSE;
	}

	// operations
	BOOL LoadFromResource(HINSTANCE hInstance, STRINGorID ResOrID)
	{
		CString strResourceURL;
		TCHAR szModule[_MAX_PATH];
		if (::GetModuleFileName(hInstance, szModule, _MAX_PATH)) {
			strResourceURL.Format(_T("res://%s/%s"), szModule, ResOrID);
			Navigate(strResourceURL, 0, 0, 0);
			return TRUE;
		}
		return FALSE;
	}

	void LoadFromStream(LPSTREAM lpStream)
	{
		CComPtr<IDispatch> spDocument = GetDocument();
		if (spDocument) {
			CComQIPtr<IPersistStreamInit> spPersistStreamInit(spDocument);
			if (spPersistStreamInit) { 
				if (SUCCEEDED(spPersistStreamInit->InitNew())) {
					spPersistStreamInit->Load(lpStream);
				} 
			}
		}
	}

	void LoadFromStream(LPBYTE lpBytes, SIZE_T dwBytes)
	{
		HGLOBAL hGlobal = GlobalAlloc(GMEM_FIXED, dwBytes);
		if (hGlobal) {
			memcpy(GlobalLock(hGlobal), lpBytes, dwBytes);
			CComPtr<IStream> spStm;
			CreateStreamOnHGlobal(hGlobal, FALSE, &spStm);
			if (spStm) {
				LoadFromStream(spStm);
			}
			GlobalUnlock(hGlobal);
			GlobalFree(hGlobal);
		}
	}

	void LoadFromString(const CString& strSting, BOOL bAppend = FALSE)
	{
		CComPtr<IDispatch> spDocument = GetDocument();
		if (spDocument) {
			CComQIPtr<IHTMLDocument2> spHtmlDoc(spDocument);
			if (!bAppend) {
				//Close
				spHtmlDoc->close();
				//Open
				VARIANT	open_name, open_features, open_replace;
				::VariantInit(&open_name);
				open_name.vt = VT_BSTR;
				open_name.bstrVal = ::SysAllocString(L"_self");
				::VariantInit(&open_features);
				::VariantInit(&open_replace);
				CComPtr<IDispatch> spWindow;
				spHtmlDoc->open(::SysAllocString(L"text/html"), open_name, open_features, open_replace, &spWindow);
				if (spWindow) {
					//Write
					SAFEARRAY *safe_array = SafeArrayCreateVector(VT_VARIANT,0,1);
					VARIANT *variant;
					SafeArrayAccessData(safe_array,(LPVOID *)&variant);
					variant->vt      = VT_BSTR;
					variant->bstrVal = strSting.AllocSysString();
					SafeArrayUnaccessData(safe_array);
					spHtmlDoc->write(safe_array);
				}
			} else {
				//Write
				SAFEARRAY *safe_array = SafeArrayCreateVector(VT_VARIANT,0,1);
				VARIANT *variant;
				SafeArrayAccessData(safe_array,(LPVOID *)&variant);
				variant->vt      = VT_BSTR;
				variant->bstrVal = strSting.AllocSysString();
				SafeArrayUnaccessData(safe_array);
				spHtmlDoc->write(safe_array);
			}
		}
	}

	void Navigate(LPCTSTR lpszURL, DWORD dwFlags = 0 ,
		LPCTSTR lpszTargetFrameName = NULL,
		LPCTSTR lpszHeaders = NULL,
		LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0)
	{
		ATLASSERT(m_spBrowser != NULL);
		CComBSTR bstrURL(lpszURL);
		CComSafeArray vPostData;
		if (lpvPostData != NULL) {
			vPostData.CreateOneDim(VT_UI1, dwPostDataLen, lpvPostData);
		}
		CComVariant vHeaders;
		CComVariant vTargetFrameName;
		CComVariant vFlags((long)dwFlags);
		if (lpszHeaders)
			vHeaders = lpszHeaders;
		if (lpszTargetFrameName)
			vTargetFrameName = lpszTargetFrameName;

		m_spBrowser->Navigate(bstrURL, &vFlags, &vTargetFrameName, vPostData, &vHeaders);
	}

	void Navigate2(LPITEMIDLIST pIDL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL)
	{
		ATLASSERT(m_spBrowser != NULL);

		CComVariant vPIDL; 
		UIInitVariantFromItemIDList(vPIDL, pIDL);
		CComVariant empty;
		CComVariant vTargetFrameName(lpszTargetFrameName);
		CComVariant vFlags((long)dwFlags);

		m_spBrowser->Navigate2(&vPIDL,
			&vFlags,
			&vTargetFrameName,
			&empty, &empty);
	}

	void Navigate2(LPCTSTR lpszURL, DWORD dwFlags = 0,
		LPCTSTR lpszTargetFrameName = NULL,
		LPCTSTR lpszHeaders = NULL,
		LPVOID lpvPostData = NULL, DWORD dwPostDataLen = 0)
	{
		ATLASSERT(m_spBrowser != NULL);

		CComSafeArray vPostData;
		if (lpvPostData != NULL) {
			if (dwPostDataLen == 0)
				dwPostDataLen = lstrlen((LPCTSTR) lpvPostData);
			vPostData.CreateOneDim(VT_UI1, dwPostDataLen, lpvPostData);
		}

		CComVariant vURL;
		CComVariant vHeaders;
		CComVariant vTargetFrameName;
		CComVariant vFlags((long)dwFlags);
		if (lpszURL)
			vURL = lpszURL;
		if (lpszHeaders)
			vHeaders = lpszHeaders;
		if (lpszTargetFrameName)
			vTargetFrameName = lpszTargetFrameName;

		m_spBrowser->Navigate2(&vURL,
			&vFlags, &vTargetFrameName, &vPostData, &vHeaders);
	}

	void PutProperty(LPCTSTR lpszProperty, const VARIANT& vtValue)
	{
		ATLASSERT(m_spBrowser != NULL);

		CComBSTR bstrProp(lpszProperty);
		m_spBrowser->PutProperty(bstrProp, vtValue);
	}

	CString GetProperty(LPCTSTR lpszProperty)
	{
		ATLASSERT(m_spBrowser != NULL);

		CComBSTR bstrProperty(lpszProperty);
		CComVariant vReturn;
		vReturn.vt = VT_BSTR;
		vReturn.bstrVal = NULL;
		HRESULT hr = m_spBrowser->GetProperty(bstrProperty, &vReturn);
		if (SUCCEEDED(hr)) {
			return CString(vReturn.bstrVal);
		}
		return _T("");
	}

// 	CComVariant GetProperty(LPCTSTR lpszProperty)
// 	{
// 		ATLASSERT(m_spBrowser != NULL);
// 
// 		CComVariant result;
// 		CComQIPtr<IDispatch> spDisp = m_spBrowser;
// 		CComDispatchDriver::GetProperty(spDisp, 0x12f, &result);
// 		return result;
// 	}

	CString GetFullName() const
	{
		ATLASSERT(m_spBrowser != NULL);

		BSTR bstr;
		m_spBrowser->get_FullName(&bstr);
		return CString(bstr);
	}
};

//////////////////////////////////////////////////////////////////////////
//IWebBrowserEvents2Base
//////////////////////////////////////////////////////////////////////////
class IWebBrowserEvents2Base
{
public:
	static _ATL_FUNC_INFO StatusTextChangeInfo;
	static _ATL_FUNC_INFO DownloadBeginInfo ;
	static _ATL_FUNC_INFO NewWindow2Info; 
	static _ATL_FUNC_INFO CommandStateChangeInfo;
	static _ATL_FUNC_INFO BeforeNavigate2Info;
	static _ATL_FUNC_INFO ProgressChangeInfo;
	static _ATL_FUNC_INFO NavigateComlete2Info;
	static _ATL_FUNC_INFO OnVisibleInfo;
};

__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::StatusTextChangeInfo = {CC_STDCALL, VT_EMPTY, 1, {VT_BSTR}};
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::DownloadBeginInfo = {CC_STDCALL, VT_EMPTY, 0, {NULL}};
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::NewWindow2Info = {CC_STDCALL, VT_EMPTY, 2, {VT_BYREF|VT_BOOL,VT_BYREF|VT_DISPATCH}}; 
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::CommandStateChangeInfo = {CC_STDCALL, VT_EMPTY, 2, {VT_I4,VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::BeforeNavigate2Info = {CC_STDCALL, VT_EMPTY, 7,
{VT_DISPATCH,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_VARIANT,VT_BYREF|VT_BOOL}};
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::ProgressChangeInfo = {CC_STDCALL, VT_EMPTY, 2, {VT_I4,VT_I4}};
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::NavigateComlete2Info = {CC_STDCALL, VT_EMPTY, 2, {VT_DISPATCH, VT_BYREF|VT_VARIANT}};
__declspec(selectany) _ATL_FUNC_INFO IWebBrowserEvents2Base::OnVisibleInfo = {CC_STDCALL, VT_EMPTY, 1, {VT_BOOL}};

template <class T, UINT nID>
class IWebBrowserEvents2Impl :
	public IDispEventSimpleImpl<nID, IWebBrowserEvents2Impl<T, nID>, &DIID_DWebBrowserEvents2>,
	public IWebBrowserEvents2Base
{
public:
	typedef IWebBrowserEvents2Impl<T, nID> This;

	// Constructor
	IWebBrowserEvents2Impl()
		: m_nDownloadCounter(0)
	{
	}

	// Methods
	void WebBrowserEvents2Advise()
	{
		T* pT = static_cast<T*>(this);
		DispEventAdvise(pT->m_spBrowser, &DIID_DWebBrowserEvents2);
	}

	void WebBrowserEvents2Unadvise()
	{
		T* pT = static_cast<T*>(this);
		DispEventUnadvise(pT->m_spBrowser, &DIID_DWebBrowserEvents2);
	}

	BOOL IsPageIWebBrowser(IDispatch* pDisp)
	{//Knowledge Base Q180366
		T* pT = static_cast<T*>(this);

		CComPtr<IDispatch> spDispatch;
		HRESULT hr = pT->m_spBrowser->QueryInterface(IID_IDispatch, (void**)&spDispatch);
		if (FAILED(hr))
			return FALSE;

		if (pDisp == spDispatch)
			return TRUE;
		else
			return FALSE;
	}

	static BOOL IsRefreshBeforeNavigate2(IDispatch* pDisp)
	{
		CComQIPtr<IWebBrowser2> spBrowser = pDisp;
		if (!spBrowser)
			return FALSE;

		CComBSTR bstr;
		spBrowser->get_LocationURL(&bstr);
		CString str(bstr);
		if (str.IsEmpty() || str == _T("about:blank"))
			return TRUE;
		else
			return FALSE;
	}

	// Overridables
	void OnStatusTextChange(const CString& strText) { }
	void OnProgressChange(long progress, long progressMax) { }
	void OnCommandStateChange(long Command, BOOL bEnable) { }
	void OnDownloadBegin() { }
	void OnDownloadComplete() { }
	void OnTitleChange(const CString& strTitle) { }
	void OnNavigateComplete2(IDispatch* pDisp, const CString& strURL) { }
	void OnBeforeNavigate2(IDispatch* pDisp, const CString& strURL, DWORD nFlags,
		const CString& strTargetFrameName, CArray<BYTE>& baPostedData, const CString& strHeaders, BOOL& bCancel) { }
	void OnPropertyChange(const CString& strProperty) { }
	void OnNewWindow2(IDispatch** ppDisp, BOOL& bCancel) { }
	void OnDocumentComplete(IDispatch* pDisp, const CString& strURL) { }
	void OnQuit() { }
	void OnVisible(BOOL bVisible) { }
	void OnToolBar(BOOL bToolBar) { }
	void OnMenuBar(BOOL bMenuBar) { }
	void OnStatusBar(BOOL bStatusBar) { }
	void OnFullScreen(BOOL bFullScreen) { }
	void OnTheaterMode(BOOL bTheaterMode) { }

	// For downloading state
	int m_nDownloadCounter;

	void OnStateConnecting() { }
	void OnStateDownloading() { }
	void OnStateCompleted() { }

	// Sink map and event handlers
	BEGIN_SINK_MAP(This)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 102, __StatusTextChange, &StatusTextChangeInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 108, __ProgressChange, &ProgressChangeInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 105, __CommandStateChange, &CommandStateChangeInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 106, __DownloadBegin, &DownloadBeginInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 104, __DownloadComplete, &DownloadBeginInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 113, __TitleChange, &StatusTextChangeInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 252, __NavigateComplete2, &NavigateComlete2Info)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 250, __BeforeNavigate2, &BeforeNavigate2Info)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 112, __PropertyChange, &StatusTextChangeInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 251, __NewWindow2, &NewWindow2Info)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 259, __DocumentComplete, &NavigateComlete2Info)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 253, __OnQuit, &DownloadBeginInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 254, __OnVisible, &OnVisibleInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 255, __OnToolBar, &OnVisibleInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 256, __OnMenuBar, &OnVisibleInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 257, __OnStatusBar, &OnVisibleInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 258, __OnFullScreen, &OnVisibleInfo)
		SINK_ENTRY_INFO(nID, DIID_DWebBrowserEvents2, 260, __OnTheaterMode, &OnVisibleInfo)
	END_SINK_MAP()

	void __stdcall __StatusTextChange(/*[in]*/ BSTR bstrText)
	{
		T* pT = static_cast<T*>(this);
		CString strStatusBar(bstrText);
		pT->OnStatusTextChange(strStatusBar);
	}

	void __stdcall __ProgressChange(/*[in]*/ long progress, /*[in]*/ long progressMax)
	{
		T* pT = static_cast<T*>(this);
		pT->OnProgressChange(progress, progressMax);
	}

	void __stdcall __CommandStateChange(/*[in]*/ long Command, /*[in]*/ VARIANT_BOOL Enable)
	{
		T* pT = static_cast<T*>(this);
		BOOL bEnable = (Enable == VARIANT_TRUE) ? TRUE : FALSE;
		pT->OnCommandStateChange(Command, bEnable);
	}

	void __stdcall __DownloadBegin()
	{
		T* pT = static_cast<T*>(this);
		pT->OnDownloadBegin();

		if (m_nDownloadCounter++ == 0)
			pT->OnStateConnecting();	// yes, connecting
	}

	void __stdcall __DownloadComplete()
	{
		T* pT = static_cast<T*>(this);
		pT->OnDownloadComplete();

		if (--m_nDownloadCounter == 0)
			pT->OnStateCompleted();		// complete!
	}

	void __stdcall __TitleChange(/*[in]*/ BSTR bstrText)
	{
		CString strTitle(bstrText);
		T* pT = static_cast<T*>(this);
		pT->OnTitleChange(strTitle);
	}

	void __stdcall __NavigateComplete2(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL)
	{
		ATLASSERT(V_VT(URL) == VT_BSTR);

		CString strURL(V_BSTR(URL));
		T* pT = static_cast<T*>(this);
		pT->OnNavigateComplete2(pDisp, strURL);

		if (m_nDownloadCounter > 0)
			pT->OnStateDownloading();
	}

	void __stdcall __BeforeNavigate2(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL, /*[in]*/ VARIANT* Flags, 
		/*[in]*/ VARIANT* TargetFrameName, /*[in]*/ VARIANT* PostData, /*[in]*/ VARIANT* Headers, 
		/*[out]*/ VARIANT_BOOL* Cancel)
	{
		ATLASSERT(V_VT(URL) == VT_BSTR);
		ATLASSERT(V_VT(TargetFrameName) == VT_BSTR);
		ATLASSERT(V_VT(PostData) == (VT_VARIANT | VT_BYREF));
		ATLASSERT(V_VT(Headers) == VT_BSTR);
		ATLASSERT(Cancel != NULL);

		CArray<BYTE> array;
		VARIANT* vtPostedData = V_VARIANTREF(PostData);
		if (V_VT(vtPostedData) & VT_ARRAY)
		{
			// must be a vector of bytes
			ATLASSERT(vtPostedData->parray->cDims == 1 && vtPostedData->parray->cbElements == 1);

			vtPostedData->vt |= VT_UI1;
			CComSafeArray safe(vtPostedData);
			DWORD dwSize = safe.GetOneDimSize();
			LPVOID pVoid;
			safe.AccessData(&pVoid);
			array.SetSize(dwSize);
			LPBYTE lpByte = array.GetData();
			::memcpy(lpByte, pVoid, dwSize);
			safe.UnaccessData();
		}

		CString strTargetFrameName(V_BSTR(TargetFrameName));
		CString strURL(V_BSTR(URL));
		CString strHeaders(V_BSTR(Headers));
		DWORD nFlags = V_I4(Flags);
		BOOL bCancel = FALSE;

		T* pT = static_cast<T*>(this);
		pT->OnBeforeNavigate2(pDisp, strURL, nFlags, strTargetFrameName,
			array, strHeaders, bCancel);

		*Cancel = bCancel ? VARIANT_TRUE : VARIANT_FALSE;

		if (!bCancel) {
			if (IsPageIWebBrowser(pDisp))
				if (m_nDownloadCounter++ == 0)
					pT->OnStateConnecting();
		}
	}

	void __stdcall __PropertyChange(/*[in]*/ BSTR bstrProperty)
	{
		CString strProperty(bstrProperty);
		T* pT = static_cast<T*>(this);
		pT->OnPropertyChange(strProperty);
	}

	void __stdcall __NewWindow2(/*[out]*/ IDispatch** ppDisp, /*[out]*/ VARIANT_BOOL* Cancel)
	{
		BOOL bCancel = FALSE;
		T* pT = static_cast<T*>(this);
		pT->OnNewWindow2(ppDisp, bCancel);
		*Cancel = bCancel ? VARIANT_TRUE : VARIANT_FALSE;
	}

	void __stdcall __DocumentComplete(/*[in]*/ IDispatch* pDisp, /*[in]*/ VARIANT* URL)
	{
		ATLASSERT(V_VT(URL) == VT_BSTR);

		CString strURL(V_BSTR(URL));
		T* pT = static_cast<T*>(this);
		pT->OnDocumentComplete(pDisp, strURL);

		if (IsPageIWebBrowser(pDisp)) {// downloading over
			m_nDownloadCounter = 0;
			pT->OnStateCompleted();
		}
	}

	void __stdcall __OnQuit()
	{
		T* pT = static_cast<T*>(this);
		pT->OnQuit();
	}

	void __stdcall __OnVisible(/*[in]*/ VARIANT_BOOL Visible)
	{
		T* pT = static_cast<T*>(this);
		pT->OnVisible(Visible == VARIANT_TRUE ? TRUE : FALSE);
	}

	void __stdcall __OnToolBar(/*[in]*/ VARIANT_BOOL ToolBar)
	{
		T* pT = static_cast<T*>(this);
		pT->OnToolBar(ToolBar == VARIANT_TRUE ? TRUE : FALSE);
	}

	void __stdcall __OnMenuBar(/*[in]*/ VARIANT_BOOL MenuBar)
	{
		T* pT = static_cast<T*>(this);
		pT->OnMenuBar(MenuBar == VARIANT_TRUE ? TRUE : FALSE);
	}

	void __stdcall __OnStatusBar(/*[in]*/ VARIANT_BOOL StatusBar)
	{
		T* pT = static_cast<T*>(this);
		pT->OnStatusBar(StatusBar == VARIANT_TRUE ? TRUE : FALSE);
	}

	void __stdcall __OnFullScreen(/*[in]*/ VARIANT_BOOL FullScreen)
	{
		T* pT = static_cast<T*>(this);
		pT->OnFullScreen(FullScreen == VARIANT_TRUE ? TRUE : FALSE);
	}

	void __stdcall __OnTheaterMode(/*[in]*/ VARIANT_BOOL TheaterMode)
	{
		T* pT = static_cast<T*>(this);
		pT->OnTheaterMode(TheaterMode == VARIANT_TRUE ? TRUE : FALSE);
	}
};

//////////////////////////////////////////////////////////////////////////
///UIWebBrowserCommandHandler
//////////////////////////////////////////////////////////////////////////
// Undocumented command ids
static const CLSID CGID_IWebBrowser = {0xED016940L,0xBD5B,0x11cf,0xBA, 0x4E,0x00,0xC0,0x4F,0xD7,0x08,0x16};
#define HTMLID_FIND			1
#define HTMLID_VIEWSOURCE	2
#define HTMLID_OPTIONS		3

template <class T>
class UIWebBrowserCommandHandler
{
public:
	// Message map and handlers
	BEGIN_MSG_MAP_EX(UIWebBrowserCommandHandler)
		COMMAND_ID_HANDLER_EX(ID_FILE_SAVE_AS, OnFileSaveAs)
		COMMAND_ID_HANDLER_EX(ID_FILE_PAGE_SETUP, OnFilePageSetup)
		COMMAND_ID_HANDLER_EX(ID_FILE_PRINT, OnFilePrint)
		COMMAND_ID_HANDLER_EX(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview) // suggested by DOGSTORE, thanks
		//COMMAND_ID_HANDLER_EX(ID_FILE_PROPERTIES, OnFileProperties)
		COMMAND_ID_HANDLER_EX(ID_EDIT_CUT, OnEditCut)
		COMMAND_ID_HANDLER_EX(ID_EDIT_COPY, OnEditCopy)
		COMMAND_ID_HANDLER_EX(ID_EDIT_PASTE, OnEditPaste)
		COMMAND_ID_HANDLER_EX(ID_EDIT_FIND, OnEditFind)
		COMMAND_ID_HANDLER_EX(ID_EDIT_SELECT_ALL, OnEditSelectAll)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_BACK, OnViewBack)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_FORWARD, OnViewForward)
		COMMAND_ID_HANDLER_EX(ID_VIEW_REFRESH, OnViewRefresh)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_STOP, OnViewStop)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_HOME, OnViewHome)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_FONT_LARGEST, OnViewFontLargest)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_FONT_LARGER, OnViewFontLarger)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_FONT_MEDIUM, OnViewFontMedium)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_FONT_SMALLER, OnViewFontSmaller)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_FONT_SMALLEST, OnViewFontSmallest)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_SOURCE, OnViewSource)
		//COMMAND_ID_HANDLER_EX(ID_VIEW_OPTION, OnViewOption)
	END_MSG_MAP()

	void OnFileSaveAs(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_SAVEAS, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnFilePageSetup(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_PAGESETUP, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnFilePrint(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_PRINT, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnFilePrintPreview(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_PRINTPREVIEW, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnFileProperties(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_PROPERTIES, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnEditCut(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{	
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_CUT, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnEditCopy(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_COPY, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnEditPaste(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_PASTE, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnEditFind(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		CComQIPtr<IOleCommandTarget> spCmdTarget = pT->m_spBrowser;
		spCmdTarget->Exec(&CGID_IWebBrowser, HTMLID_FIND, 0, NULL, NULL);
		// this is just file search
		//	m_spBrowser->ExecWB(OLECMDID_FIND, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}
	void OnEditSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_SELECTALL, OLECMDEXECOPT_DODEFAULT, NULL, NULL);
	}

	void OnViewBack(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->GoBack();
	}
	void OnViewForward(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->GoForward();
	}
	void OnViewRefresh(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->Refresh();
	}
	void OnViewStop(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->Stop();
	}
	void OnViewHome(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->GoHome();
	}
	void OnViewOption(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		CComQIPtr<IOleCommandTarget> spCmdTarget = pT->m_spBrowser;
		spCmdTarget->Exec(&CGID_IWebBrowser, HTMLID_OPTIONS, 0, NULL, NULL);
		// this is modeless
		// ::ShellExecute(0, "open", "control.exe", "inetcpl.cpl", ".", SW_SHOW);
	}

	// zoom font
	void OnViewFontLargest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		CComVariant vaZoomFactor(4L);
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
			&vaZoomFactor, NULL);
	}
	void OnViewFontLarger(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		CComVariant vaZoomFactor(3L);
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
			&vaZoomFactor, NULL);
	}
	void OnViewFontMedium(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		CComVariant vaZoomFactor(2L);
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
			&vaZoomFactor, NULL);
	}
	void OnViewFontSmaller(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		CComVariant vaZoomFactor(1L);
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
			&vaZoomFactor, NULL);
	}
	void OnViewFontSmallest(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		CComVariant vaZoomFactor(0L);
		T* pT = static_cast<T*>(this);
		pT->m_spBrowser->ExecWB(OLECMDID_ZOOM, OLECMDEXECOPT_DONTPROMPTUSER,
			&vaZoomFactor, NULL);
	}

	void OnViewSource(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/)
	{
		T* pT = static_cast<T*>(this);
		CComQIPtr<IOleCommandTarget> spCmdTarget = pT->m_spBrowser;
		spCmdTarget->Exec(&CGID_IWebBrowser, HTMLID_VIEWSOURCE, 0, NULL, NULL);
	}
};

typedef HRESULT (*pfnEnumWebBrowser)(IDispatch* pDisp, void* pParam);

class UIWebBrowserEnumHandler
{
public:
	
};

//////////////////////////////////////////////////////////////////////////
///UIHtml
//////////////////////////////////////////////////////////////////////////

class UIWebBrowserWnd : public UIAxWnd
{
	typedef UIWebBrowserWnd This;
	typedef UIAxWnd Base;
public:

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		if((pMsg->message < WM_KEYFIRST || pMsg->message > WM_KEYLAST) &&
			(pMsg->message < WM_MOUSEFIRST || pMsg->message > WM_MOUSELAST))
			return FALSE;

		// give HTML page a chance to translate this message
		return (BOOL)SendMessage(WM_FORWARDMSG, 0, (LPARAM)pMsg);
	}
};

//为了在 Web 页上调用脚本函数存在，您必须使用自动化 ；换而言之，IDispatch。使用以下步骤来调用存在 Visual C++ 应用程序从 Web 页的脚本函数：
//获取 HTML 文档的 IDispatch。
//调用 IDispatch::GetIDsOfNames 来获取脚本函数的 ID。
//调用 IDispatch::Invoke 来执行此功能。
//下面的 Visual C++ 源代码演示如何在您自己的应用程序中实现。此代码使用智能指针由 #import 语句创建的。在其中一个源代码文件，最好是 stdafx.h 文件中必须包含此 #import 语句：
//#import "C:\winnt\system32\mshtml.tlb" // location of mshtml.tlb
//
//void CMyClass::ExecuteScriptFunction()
//{
//	// m_WebBrowser is an instance of IWebBrowser2
//	MSHTML::IHTMLDocument2Ptr spDoc(m_WebBrowser.GetDocument());
//
//	if (spDoc)
//	{
//		IDispatchPtr spDisp(spDoc->GetScript());
//		if (spDisp)
//		{
//			// Evaluate is the name of the script function.
//			OLECHAR FAR* szMember = L"evaluate";
//			DISPID dispid;
//
//			HRESULT hr = spDisp->GetIDsOfNames(IID_NULL, &szMember, 1,
//				LOCALE_SYSTEM_DEFAULT, &dispid);
//
//			if (SUCCEEDED(hr))
//			{
//				COleVariant vtResult;
//				static BYTE parms[] = VTS_BSTR;
//
//				COleDispatchDriver dispDriver(spDisp, FALSE);
//
//				dispDriver.InvokeHelper(dispid, DISPATCH_METHOD, VT_VARIANT,
//					(void*)&vtResult, parms,
//					"5+Math.sin(9)");
//			}
//		}
//	}
//}
//
//
//下面是包含计算函数的网页的 HTML：
//<HTML>
//<HEAD>
//<TITLE>Evaluate</TITLE>
//
//<SCRIPT>
//function evaluate(x)
//{
//	alert("hello")
//		return eval(x)
//}
//</SCRIPT>
//</HEAD>
//
//<BODY>
//</BODY>
//</HTML>


template<class T, UINT nID>
class UIWebBrowserMap
	:public IWebBrowserEvents2Impl<T, nID>
	,public UIWebBrowserCommandHandler<T>
	,public UIWebBrowser2
{
	typedef UIWebBrowserMap<T,nID> This;
public:
	LRESULT execScript(BSTR code, VARIANT *ret, BSTR language = L"javascript")
	{  
		HRESULT hr = S_OK;
		CComPtr<IDispatch> spDispDoc;     
		hr = m_spBrowser->get_Document(&spDispDoc);  
		if (SUCCEEDED(hr)) {  
			CComQIPtr<IHTMLDocument2> spDoc = spDispDoc;
			CComQIPtr<IHTMLWindow2> spHtmlWnd;
			hr = spDoc->get_parentWindow(&spHtmlWnd);  
			if (SUCCEEDED(hr)) {
				hr = spHtmlWnd->execScript(code, language, ret); 
			}
		}
		return SUCCEEDED(hr);
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_COMMANDS(UIWebBrowserCommandHandler<T>)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		LRESULT lRet = pT->DefWindowProc(uMsg, wParam, lParam);

		pT->QueryControl(IID_IWebBrowser2, (void**)&m_spBrowser);
		//SetRegisterAsBrowser(true);// for target name resolution
		WebBrowserEvents2Advise();

		return lRet;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		//SetRegisterAsBrowser(false);
		WebBrowserEvents2Unadvise();
		return 0;
	}
};

template<class T, UINT nID, class TBase = UIWebBrowserWnd>
class UIWebBrowserWndImpl 
	:public UIWndImpl<T,TBase>
	,public UIWebBrowserMap<T, nID>
{
	typedef UIWebBrowserWndImpl<T, nID, TBase> This;
	typedef UIWndImpl<T,TBase> Base;
	typedef UIWebBrowserMap<T, nID> WebBrowserBase;
public:
	DECLARE_WND_SUPERCLASS(_T("UIWebBrowserWnd"), UIWebBrowserWnd::GetWndClassName())

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Base)
		CHAIN_MSG_MAP(WebBrowserBase)
	END_MSG_MAP()
};

#endif//_H_UIWEBBROWSER_H_