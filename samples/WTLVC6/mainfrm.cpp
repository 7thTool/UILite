// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "webappView.h"
#include "WTLVC6view.h"
#include "ChildFrm.h"
#include "MainFrm.h"

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

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

	CreateSimpleStatusBar();

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

	RegisterHotKey(m_hWnd, 1001, MOD_ALT, 'F');

	//PostMessage(WM_COMMAND, ID_FILE_NEW, 0L);

	//ShowWindow(SW_MAXIMIZE);

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_CmdBar.AttachMenu(NULL);

	UnregisterHotKey(m_hWnd, 1001);

	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

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

#include "WTLVC6Script.h"

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	Test(m_hWnd);
	return 0;

	CAboutDlg dlg;
	/*dlg.DoModal(::GetActiveWindow(), 
		_T("<CAboutDlg title=\"AboutDlg\" style=\"0\" exstyle\"0\" id=\"100\" >\
		<BUTTON name=\"btnX1\" rect=\"50,50,150,150\" title=\"btnX1\" style=\"0\" ></BUTTON>\
		<BUTTON name=\"btnX2\" rect=\"100,100,200,200\" title=\"btnX2\" style=\"0\" ></BUTTON>\
		<BUTTON name=\"btnX2_2\" rect=\"10,10,100,100\" title=\"btnX2_2\" style=\"2\" ></BUTTON>\
		<UIXWnd2Test name=\"test1\" rect=\"400,200,600,400\" title=\"test1\" style=\"0\" > \
			<BUTTON name=\"btnX2\" rect=\"100,100,200,200\" title=\"btnX2\" style=\"4\" ></BUTTON>\
			<BUTTON name=\"btnX1\" rect=\"50,50,150,150\" title=\"btnX1\" style=\"0x50000004\" ></BUTTON>\
		</UIXWnd2Test>\
		<UIXWnd2Test name=\"test2\" rect=\"0,200,400,500\" title=\"test2\" style=\"0\" >\
			<BUTTON name=\"btnX2\" rect=\"100,100,200,200\" title=\"btnX2\" style=\"2\" ></BUTTON>\
			<BUTTON name=\"btnX1\" rect=\"50,50,150,150\" title=\"btnX1\" style=\"0\" ></BUTTON>\
		</UIXWnd2Test>\
		</CAboutDlg>"), XML_FLAG_STREAM);*/
	/*dlg.DoModal(::GetActiveWindow(), 
		_T("<CAboutDlg title=\"AboutDlg\" rect=\"0,0,380,280\" style=\"0x56010000\" exstyle\"0\" id=\"100\" >\
				<SYSBUTTON name=\"MIN\" rect=\"313,0,341,20\" title=\"MIN\" style=\"0x56000000\" ></SYSBUTTON>\
				<SYSBUTTON name=\"MAX\" rect=\"285,0,313,20\" title=\"MAX\" style=\"0x56000000\" ></SYSBUTTON>\
				<SYSBUTTON name=\"close\" rect=\"341,0,380,20\" title=\"CLOSE\" style=\"0x56000000\" ></SYSBUTTON>\
				<STATIC name=\"photo\" rect=\"16,139,103,226\" title=\"\" style=\"0x56000000\" ></STATIC>\
				<EDIT name=\"username\" rect=\"112,142,311,170\" title=\"\" style=\"0x56010000\" ></BUTTON>\
				<EDIT name=\"password\" rect=\"112,176,311,204\" title=\"\" style=\"0x56010020\" ></BUTTON>\
				<BUTTON name=\"multi_account\" rect=\"7,251,76,273\" title=\"多帐号\" style=\"0x56010000\" ></BUTTON>\
				<BUTTON name=\"setting\" rect=\"84,251,153,273\" title=\"设置\" style=\"0x56010000\" ></BUTTON>\
				<BUTTON name=\"login\" rect=\"304,251,373,273\" title=\"登录\" style=\"0x56010000\" ></BUTTON>\
				<BUTTON name=\"check_password\" rect=\"156,213,226,230\" title=\"记住密码\" style=\"0x56010002\" ></BUTTON>\
				<BUTTON name=\"auto_login\" rect=\"236,213,306,230\" title=\"自动登录\" style=\"0x56010002\" ></BUTTON>\
			</CAboutDlg>"), XML_FLAG_STREAM);*/
	CString strXmlFile;
	strXmlFile.Format(_T("%s\\AboutDlg.xml"), _pUISkinManager->GetSkinPath());
	dlg.DoModal(::GetActiveWindow(),strXmlFile);
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

#include "Public.h"

LRESULT CMainFrame::OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//bHandled = FALSE;
	UINT ModKey = (UINT) LOWORD(lParam);  
	UINT VirKey = (UINT) HIWORD(lParam);
	switch (ModKey)
	{
	case MOD_ALT:
		{
			switch(VirKey)
			{
			case 'F':
				{
					FindFromHwnd(GetForegroundWindow());
				}
				break;
			}
		}
		break;
	}
	return bHandled;
}
