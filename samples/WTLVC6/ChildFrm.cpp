// ChildFrm.cpp : implementation of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "webappView.h"
#include "WTLVC6view.h"
#include "ChildFrm.h"

#include <XLib/XConfig.h>

void CChildFrame::OnFinalMessage(HWND /*hWnd*/)
{
	delete this;
}

LRESULT CChildFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	//std::tstring strname;
	//std::tstring strvalue;
	TCHAR szValue[MAX_PATH];
	TCHAR szValue2[MAX_PATH];

	CString strXml;
	strXml.Format(_T("%s\\%s.xml"), _Module.GetAppPath(), _Module.GetName());

	Markup xml;
	xml.Open(strXml);

	if(xml.Find(_T("root/autoclick"))) {
		xml.IntoElem();
		if(tcsto<DWORD>(xml.GetAttributeString(_T(""), _T("enable"), szValue, MAX_PATH-1), 0)
			//xml.GetAttributeT<DWORD>(_T(""), _T("enable"), 0)
			) {
			m_dwTimeOut = tcsto<DWORD>(xml.GetAttributeString(_T(""), _T("timeout"), szValue, MAX_PATH-1, _T("6"))) * 1000;
				//xml.GetAttributeT<DWORD>(_T(""), _T("timeout"), 6) * 1000;
			m_loop = tcsto<int>(xml.GetAttributeString(_T(""), _T("loop"), szValue, MAX_PATH-1, _T("0")));
				//xml.GetAttributeT<int>(_T(""), _T("loop"), 0);
			for(long sitecookie = xml.First(); sitecookie; sitecookie = xml.Next(sitecookie))
			{
				xml.IntoElem();
				if(tcsto<DWORD>(xml.GetAttributeString(_T(""), _T("enable"), szValue, MAX_PATH-1, _T("0")))
					//xml.GetAttributeT<DWORD>(_T(""), _T("enable"), 0)
					) {
					;
				} else {
					CString strSite = xml.GetAttributeString(_T(""), _T("url"), szValue, MAX_PATH);
					if (!strSite.IsEmpty()) {
						for(long keyvaluecookie = xml.First(); keyvaluecookie; keyvaluecookie = xml.Next(keyvaluecookie))
						{
							xml.IntoElem();
							xml.GetAttributeString(_T(""), _T("key"), szValue, MAX_PATH);
							xml.GetAttributeString(_T(""), _T("value"), szValue2, MAX_PATH);
							m_AutoClickInfos.Add(CAutoClickInfo(strSite, szValue, szValue2));
							xml.OutofElem();
						}
					}
				}
				xml.OutofElem();
			}
		}
		xml.OutofElem();
	}
	m_nCurAutoClickPos = 0;

	//m_view.SetAutoClickKeyValue(
	//	m_Config.GetAttributeString(_T("root/autoclick/website/keyvalue"), _T("key"), szValue, MAX_PATH),
	//	m_Config.GetAttributeString(_T("root/autoclick/website/keyvalue"), _T("value"), szValue2, MAX_PATH));

	//TODO: Replace with a URL of your choice
	m_hWndClient = m_view.Create(m_hWnd, rcDefault
		//, _T("about:blank")
		, _T("http://hz.f.17guagua.com/jetty/nowVideo?roomid=427686&r=1366607149090&_1366607148361=")
		//, m_Config.GetAttributeString(_T("root/autoclick/website"), _T("url"), szValue, MAX_PATH)
		, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE);
	ATLASSERT(m_hWndClient);
	m_view.SetSilent(TRUE);
	m_view.SetVisible(FALSE);
	
	SetTimer(GetDlgCtrlID(), 100);


	/*m_hWndClient = m_view2.Create(m_hWnd, rcDefault, _T("http://f.guagua.cn/open_qlrj.html")
		, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_HSCROLL | WS_VSCROLL, WS_EX_CLIENTEDGE);*/

	HINSTANCE hinstMSHTML = LoadLibrary(TEXT("MSHTML.DLL"));
	if (hinstMSHTML)
	{
		/*SHOWHTMLDIALOGFN* pfnShowHTMLDialog;
		pfnShowHTMLDialog = (SHOWHTMLDIALOGFN*)GetProcAddress(hinstMSHTML,
			"ShowHTMLDialog");
		if (pfnShowHTMLDialog)
		{
			IMoniker *pURLMoniker;
			BSTR bstrURL = SysAllocString(L"http://f.guagua.cn/open_qlrj.html");
			CreateURLMoniker(NULL, bstrURL, &pURLMoniker);
			
			if (pURLMoniker)
			{
				(*pfnShowHTMLDialog)(NULL, pURLMoniker, NULL, NULL, NULL);
				pURLMoniker->Release();
			}

			SysFreeString(bstrURL);
		}*/


		/*SHOWHTMLDIALOGEXFN* pfnShowHTMLDialogEx;
		pfnShowHTMLDialogEx = (SHOWHTMLDIALOGEXFN*)GetProcAddress(hinstMSHTML,
			"ShowHTMLDialogEx");
		if (pfnShowHTMLDialogEx)
		{
			IMoniker *pURLMoniker;
			BSTR bstrURL = SysAllocString(L"http://f.guagua.cn/open_qlrj.html");
			CreateURLMoniker(NULL, bstrURL, &pURLMoniker);

			if (pURLMoniker)
			{
				DWORD dwFlags = HTMLDLG_MODELESS | HTMLDLG_VERIFY | HTMLDLG_ALLOW_UNKNOWN_THREAD;
				(*pfnShowHTMLDialogEx)(NULL, pURLMoniker, dwFlags, NULL, NULL, NULL);

				pURLMoniker->Release();
			}

			SysFreeString(bstrURL);
		}*/


		/*SHOWMODELESSHTMLDIALOGFN* pfnShowModelessHTMLDialog;
		pfnShowModelessHTMLDialog =
			(SHOWMODELESSHTMLDIALOGFN*)GetProcAddress(hinstMSHTML,
			"ShowModelessHTMLDialog");
		if (pfnShowModelessHTMLDialog)
		{
			IMoniker *pURLMoniker;
			BSTR bstrURL =
				SysAllocString(L"http://f.guagua.cn/open_qlrj.html");
			CreateURLMoniker(NULL, bstrURL, &pURLMoniker);

			if (pURLMoniker)
			{
				DWORD dwFlags = HTMLDLG_MODELESS | HTMLDLG_VERIFY | HTMLDLG_ALLOW_UNKNOWN_THREAD;
				(*pfnShowModelessHTMLDialog)(NULL, pURLMoniker, NULL,
					NULL, NULL);

				pURLMoniker->Release();
			}

			SysFreeString(bstrURL);
		}*/

		FreeLibrary(hinstMSHTML);
	}
	
	ShowWindow(SW_MAXIMIZE);
	//PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE)
	bHandled = FALSE;
	return 1;
}

LRESULT CChildFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	KillTimer(GetDlgCtrlID());

	if (m_view.IsWindow()) {
		m_view.DestroyWindow();
	}
	if (m_view2.IsWindow()) {
		m_view2.DestroyWindow();
	}
	return bHandled;
}

LRESULT CChildFrame::OnForwardMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	LPMSG pMsg = (LPMSG)lParam;

	if(CMDIChildWindowImpl<CChildFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);

	//return m_view2.PreTranslateMessage(pMsg);

	return FALSE;
}

LRESULT CChildFrame::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	KillTimer(100);

	if(m_nCurAutoClickPos < m_AutoClickInfos.GetSize()) {
		m_view.SetAutoClickKeyValue(m_AutoClickInfos[m_nCurAutoClickPos].Site,
			m_AutoClickInfos[m_nCurAutoClickPos].Key,m_AutoClickInfos[m_nCurAutoClickPos].Value);
		m_nCurAutoClickPos++;
	} else {
		if (m_loop < 0) {
			m_nCurAutoClickPos = 0;
		} else if (m_loop > 0) {
			m_loop--;
			m_nCurAutoClickPos = 0;
		}
	}

	SetTimer(100, 6000);

	return bHandled;
}
