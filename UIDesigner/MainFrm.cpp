// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "ChildView.h"
#include "ChildFrm.h"
#include "MainFrm.h"

//////////////////////////////////////////////////////////////////////////

LRESULT QToolBarCtrl::OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPaintDC dc(m_hWnd);

	DWORD  nHotItem = GetHotItem();
	int nItemCount = GetButtonCount();

	for (int i=0;i<nItemCount;++i)
	{
		TBBUTTONINFO pbtnifo;
		ZeroMemory(&pbtnifo,sizeof(TBBUTTONINFO));
		pbtnifo.cbSize = sizeof(TBBUTTONINFO);
		pbtnifo.dwMask = TBIF_BYINDEX|TBIF_STATE|TBIF_COMMAND;
		GetButtonInfo(i,&pbtnifo);

		CRect rect;           
		GetRect(pbtnifo.idCommand,&rect);

		TCHAR szText[256]={0};
		GetButtonText(pbtnifo.idCommand,szText);
		CString strText=szText;

		if (pbtnifo.fsState & TBSTATE_PRESSED)
		{
		}
		else if(i == nHotItem)
		{

		}

		dc.SetTextColor(RGB(255,0,0));
		dc.TextOut(rect.left,rect.top,szText);
		//::FillRect(lpNMCustomDraw->hdc, &lpNMCustomDraw->rc, GetStockBrush(DKGRAY_BRUSH));
	}

	bHandled = TRUE;
	return 0;
}

DWORD QToolBarCtrl::OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
{
	return CDRF_NOTIFYITEMDRAW;
}

DWORD QToolBarCtrl::OnPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD QToolBarCtrl::OnPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD QToolBarCtrl::OnPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD QToolBarCtrl::OnItemPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw)
{
	return CDRF_SKIPDEFAULT;
}

DWORD QToolBarCtrl::OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD QToolBarCtrl::OnItemPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD QToolBarCtrl::OnItemPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

#if (_WIN32_IE >= 0x0400)
DWORD QToolBarCtrl::OnSubItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_DODEFAULT;
}
#endif // (_WIN32_IE >= 0x0400)

//////////////////////////////////////////////////////////////////////////

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(UIMDIFrameImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	HWND hWnd = MDIGetActive();
	if(hWnd != NULL)
		return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);

	return FALSE;
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE | TBSTYLE_LIST);
	m_ToolBar.SubclassWindow(hWndToolBar);

	//m_ToolBar.AddButton(123, BTNS_CHECK | BTNS_AUTOSIZE | BTNS_CHECKGROUP, TBSTATE_ENABLED, -1, _T("12323123"), (DWORD_PTR)0);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	m_Rebar.SubclassWindow(m_hWndToolBar);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);
	
	SizeSimpleReBarBands();

	m_Rebar.LockBands(false);

	CreateSimpleStatusBar();
	m_StatusBar.SubclassWindow(m_hWndStatusBar);

	CreateMDIClient();
	m_CmdBar.SetMDIClient(m_hWndMDIClient);

	UIAddToolBar(hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_CmdBar.AttachMenu(NULL);

	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	Invalidate();
	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CChildFrame* pChild = new CChildFrame;
	pChild->CreateEx(m_hWndClient);

	// TODO: add code to initialize document

	return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	//CAboutDlg dlg;
	//dlg.DoModal();
	CAboutDlg dlg;
	CString strXmlFile;
	strXmlFile.Format(_T("%s\\AboutDlg.xml"), _pUISkinManager->GetSkinPath());
	dlg.DoModal(m_hWnd,strXmlFile);
	return 0;
}

LRESULT CMainFrame::OnWindowCascade(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MDICascade();
	return 0;
}

LRESULT CMainFrame::OnWindowTile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MDITile();
	return 0;
}

LRESULT CMainFrame::OnWindowArrangeIcons(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	MDIIconArrange();
	return 0;
}

DWORD CMainFrame::OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw)
{
	return CDRF_NOTIFYITEMDRAW;
}

DWORD CMainFrame::OnPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD CMainFrame::OnPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD CMainFrame::OnPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD CMainFrame::OnItemPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw)
{
	NMTBCUSTOMDRAW* pTBCD = reinterpret_cast<NMTBCUSTOMDRAW*>( lpNMCustomDraw );

	if (lpNMCustomDraw->hdr.hwndFrom==m_ToolBar)
	{
		/*pTBCD->clrText = RGB(250,250,250);
		::SetBkMode(lpNMCustomDraw->hdc,TRANSPARENT);
		::SetTextColor(lpNMCustomDraw->hdc, RGB(255,200,50));
		//::FillRect(lpNMCustomDraw->hdc, &lpNMCustomDraw->rc, GetStockBrush(DKGRAY_BRUSH));
		::TextOut(lpNMCustomDraw->hdc, lpNMCustomDraw->rc.left, lpNMCustomDraw->rc.top, L"123", 3);

		return CDRF_SKIPDEFAULT;*/
	}

	return CDRF_DODEFAULT;
}

DWORD CMainFrame::OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD CMainFrame::OnItemPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

DWORD CMainFrame::OnItemPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_SKIPDEFAULT;
}

#if (_WIN32_IE >= 0x0400)
DWORD CMainFrame::OnSubItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/)
{
	return CDRF_DODEFAULT;
}
#endif // (_WIN32_IE >= 0x0400)
