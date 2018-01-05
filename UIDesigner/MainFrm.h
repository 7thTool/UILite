// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
//////////////////////////////////////////////////////////////////////////

class QReBarCtrl 
	: public UIWndImpl<QReBarCtrl, UIReBarCtrl>
	, public UIEraseBkgndCtrl<QReBarCtrl>
{
	typedef QReBarCtrl This;
	typedef UIWndImpl<QReBarCtrl, UIReBarCtrl> Base;
	typedef UIEraseBkgndCtrl<QReBarCtrl> SkinMap;
public:
	BEGIN_MSG_MAP_EX(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

class QToolBarCtrl : public UIWndImpl<QToolBarCtrl, UIToolBarCtrl>
	,public UIOwnerDraw<QToolBarCtrl>
	,public UICustomDraw<QToolBarCtrl>
	//,public UIPaintBkgnd<QToolBarCtrl>
{
	typedef QToolBarCtrl This;
	typedef UIWndImpl<QToolBarCtrl, UIToolBarCtrl> Base;
public:

	BEGIN_MSG_MAP_EX(This)
		//MESSAGE_HANDLER(WM_PAINT,OnPaint)
		CHAIN_MSG_MAP(UIOwnerDraw<QToolBarCtrl>)
		CHAIN_MSG_MAP(UICustomDraw<QToolBarCtrl>)
		//CHAIN_MSG_MAP(UIPaintBkgnd<QToolBarCtrl>)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw);
	DWORD OnPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw);
	DWORD OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
#if (_WIN32_IE >= 0x0400)
	DWORD OnSubItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
#endif // (_WIN32_IE >= 0x0400)
};

//////////////////////////////////////////////////////////////////////////

class QStatusBarCtrl 
	: public UIWndImpl<QStatusBarCtrl, UIStatusBarCtrl>
	, public UIEraseBkgndCtrl<QStatusBarCtrl>
{
	typedef QStatusBarCtrl This;
	typedef UIWndImpl<QStatusBarCtrl, UIStatusBarCtrl> Base;
	typedef UIEraseBkgndCtrl<QStatusBarCtrl> SkinMap;
public:

	/*BOOL OnEraseBkgnd(HDC hdc)
	{
		CRect rcClient;
		GetClientRect(&rcClient);

		UIgdi::FillSolidRect(hdc, &rcClient, RGB(215,215,215));
		//::DrawCaption(*this, hdc, &rcClient, (::GetActiveWindow()==*this?DC_ACTIVE:0) | DC_ICON | DC_TEXT);
		return TRUE;
	}*/

	BEGIN_MSG_MAP_EX(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

class CMainFrame : 
	public UIMDIFrameImpl<CMainFrame>, 
	public UIXWindowSkinMap<CMainFrame>,
	public UIEraseBkgnd<CMainFrame>
	,public UIOwnerDraw<CMainFrame>
	,public UICustomDraw<CMainFrame>
	,public CUpdateUI<CMainFrame>,
	public CMessageFilter, public CIdleHandler
{
	typedef UIXWindowSkinMap<CMainFrame> SkinMap;
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	UIMDICommandBarCtrl m_CmdBar;
	QToolBarCtrl m_ToolBar;
	QReBarCtrl m_Rebar;
	QStatusBarCtrl m_StatusBar;

	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnIdle();

	BEGIN_UPDATE_UI_MAP(CMainFrame)
		UPDATE_ELEMENT(ID_VIEW_TOOLBAR, UPDUI_MENUPOPUP)
		UPDATE_ELEMENT(ID_VIEW_STATUS_BAR, UPDUI_MENUPOPUP)
	END_UPDATE_UI_MAP()

	BOOL OnEraseBkgnd(HDC hdc)
	{
		CRect rcWnd, rcClient;
		GetWindowRect(rcWnd);
		GetClientRect(&rcClient);
		ClientToScreen(&rcClient);
		//rcWnd.OffsetRect(-rcWnd.TopLeft());
		rcClient.OffsetRect(-rcWnd.TopLeft());

		::BitBlt(hdc, 0, 0, rcClient.Width(), rcClient.Height(), (HDC)m_NcDC, rcClient.left, rcClient.top, SRCCOPY);

		return TRUE;
	}

	BEGIN_MSG_MAP_EX(CMainFrame)
		CHAIN_MSG_MAP(UIEraseBkgnd<CMainFrame>)
		CHAIN_MSG_MAP(SkinMap)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		COMMAND_ID_HANDLER(ID_APP_EXIT, OnFileExit)
		COMMAND_ID_HANDLER(ID_FILE_NEW, OnFileNew)
		COMMAND_ID_HANDLER(ID_VIEW_TOOLBAR, OnViewToolBar)
		COMMAND_ID_HANDLER(ID_VIEW_STATUS_BAR, OnViewStatusBar)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(ID_WINDOW_CASCADE, OnWindowCascade)
		COMMAND_ID_HANDLER(ID_WINDOW_TILE_HORZ, OnWindowTile)
		COMMAND_ID_HANDLER(ID_WINDOW_ARRANGE, OnWindowArrangeIcons)
		CHAIN_MSG_MAP(UIOwnerDraw<CMainFrame>)
		CHAIN_MSG_MAP(UICustomDraw<CMainFrame>)
		CHAIN_MSG_MAP(CUpdateUI<CMainFrame>)
		CHAIN_MSG_MAP(UIMDIFrameImpl<CMainFrame>)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnWindowCascade(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnWindowTile(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnWindowArrangeIcons(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	DWORD OnPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW lpNMCustomDraw);
	DWORD OnPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPrePaint(int idCtrl, LPNMCUSTOMDRAW lpNMCustomDraw);
	DWORD OnItemPostPaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPreErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
	DWORD OnItemPostErase(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
#if (_WIN32_IE >= 0x0400)
	DWORD OnSubItemPrePaint(int /*idCtrl*/, LPNMCUSTOMDRAW /*lpNMCustomDraw*/);
#endif // (_WIN32_IE >= 0x0400)
};
