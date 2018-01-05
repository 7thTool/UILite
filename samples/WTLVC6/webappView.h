// webappView.h : interface of the CWebappView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <ui/UIWebBrowser.h>

class CWebappView : public UIWebBrowserWndImpl<CWebappView, 100>
{
	typedef UIWebBrowserWndImpl<CWebappView, 100> Base;
public:
	//DECLARE_WND_SUPERCLASS(NULL, UIWebBrowserWnd::GetWndClassName())
	CWebappView():m_bAutoClickKey(FALSE),m_bAutoClickValue(FALSE) {}

	CString m_strUrl;

	BOOL m_bAutoClickKey;
	BOOL m_bAutoClickValue;
	CString m_strAutoClickKey;
	CString m_strAutoClickValue;
	void SetAutoClickKeyValue(LPCTSTR lpszSite, LPCTSTR lpszKey, LPCTSTR lpszValue);

	HRESULT OnDocument(IHTMLDocument2* pDocument);
	HRESULT OnElement(IHTMLElement* pElement);
	HRESULT OnForm(IHTMLFormElement* pFromElement);

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CWebappView)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	void OnStatusTextChange(const CString& strText);
	void OnProgressChange(long progress, long progressMax);
	void OnCommandStateChange(long Command, BOOL bEnable);
	void OnDownloadBegin();
	void OnDownloadComplete();
	void OnTitleChange(const CString& strTitle);
	void OnNavigateComplete2(IDispatch* pDisp, const CString& strURL);
	void OnBeforeNavigate2(IDispatch* pDisp, const CString& strURL, DWORD nFlags,
		const CString& strTargetFrameName, CArray<BYTE>& baPostedData, const CString& strHeaders, BOOL& bCancel);
	void OnPropertyChange(const CString& strProperty);
	void OnNewWindow2(IDispatch** ppDisp, BOOL& bCancel);
	void OnDocumentComplete(IDispatch* pDisp, const CString& strURL);
	void OnQuit();
	void OnVisible(BOOL bVisible);
	void OnToolBar(BOOL bToolBar);
	void OnMenuBar(BOOL bMenuBar);
	void OnStatusBar(BOOL bStatusBar);
	void OnFullScreen(BOOL bFullScreen);
	void OnTheaterMode(BOOL bTheaterMode);

	void OnStateConnecting();
	void OnStateDownloading();
	void OnStateCompleted();
};
