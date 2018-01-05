// UIDesignerView.h : interface of the CUIDesignerView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once



#if USE_DIRECTUI
#include <XLib/UIXPane2.h>
#include <XLib/UXWnd2.h>
#define CWndImpl UIXWnd2Impl
typedef UIXPane2 UXPane;
typedef UXWnd2Factory WndFactory;
#else
#include <XLib/UIXPane.h>
#include <XLib/UXWnd.h>
#define CWndImpl UIXWndImpl
typedef UIXPane UXPane;
typedef UXWndFactory WndFactory;
#endif//

#define MAX_GROUP_COUNT	4

class CChildView 
	: public CWndImpl<CChildView>
	, public UIPaintF<CChildView>
	, public UIXPaneSplitterImpl<CChildView,UXPane>
	, public UIXSkinThemeImpl<CChildView>
{
	typedef CChildView This;
	typedef CWndImpl<CChildView> Base;
	typedef UIPaintF<CChildView> PaintMap;
	typedef UIXPaneSplitterImpl<CChildView,UXPane> ViewSplitter;
	typedef UIXSkinThemeImpl<CChildView> SkinTheme;
public:
	DECLARE_WND_CLASS(_T("ChildView"))
	DECLARE_XMLWND_CLASS(_T("ChildView"))
	class PaneInfo : public UIBkgnd<PaneInfo>
	{
	public:
		PaneInfo()
		{
			SetBkColor(RGB(rand()%255,rand()%255,rand()%255));
		}
	};
protected:
	BOOL m_bEdit;
	CString m_strFile;
	typedef std::map<Pane*,PaneInfo> PaneInfos;
	PaneInfos m_pPInfos;
	std::vector<CString> m_strClassNames;

public:
	CChildView();
	~CChildView();

	void AddClassName(LPCTSTR lpszClassName);

	BEGIN_ATTRIBUTE_MAP(This)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(ViewSplitter)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	virtual void SaveLayout();

	virtual BOOL GetLayoutRect(LPRECT lpRect);

	virtual void Relayout(LPCRECT lpRect = NULL);

	BOOL PreTranslateMessage(MSG* pMsg);

	void PaintP(Pane* pP, HDC hdc)
	{
		PaneInfo& PInfo = m_pPInfos[pP];

		CDCHandle dc(hdc);
		RECT rcP;
		pP->GetRect(&rcP);
		PInfo.PaintBkgnd(hdc,&rcP);

		int nOldBkMode = dc.SetBkMode(TRANSPARENT);
		COLORREF crOldTextColor = dc.SetTextColor(UIgdi::InvertColor(PInfo.GetBkColor()));
		CString strName = pP->GetName();
		dc.DrawText(strName,strName.GetLength(),&rcP,DT_CENTER|DT_VCENTER);
		dc.SetTextColor(crOldTextColor);
		dc.SetBkMode(nOldBkMode);

		for (Pane* pC = pP->FirstChild(); pC; pC = pC->Next())
		{
			PaintP(pC, hdc);
		}
	}

	void Paint(HDC hdc)
	{
		CDCHandle dc(hdc);

		CRect rcClient;
		GetClientRect(&rcClient);

		dc.SetBkMode(TRANSPARENT);
		dc.FillSolidRect(&rcClient, RGB(255,255,255));

		if (m_pP) {
			PaintP(m_pP,hdc);
		}
	}

	//如果消息需要先调用Windows DefWindowProc处理的话，最好方式是主动调用基类消息处理函数，然后bHandled = TRUE
	//如果消息需要让基类先处理的话，也应该主动调用基类的处理方式，然后bHandled = TRUE
	//凡是主动调用了基类的消息处理函数的话，都要将bHandled = TRUE，不然就会后面基类有重复处理了这个消息
	//有些不注重执行先后顺序的，也可以不用显示调用
	//当然能正确区分到底有没有处理更好
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(ViewSplitter)
		CHAIN_MSG_MAP(PaintMap)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		//MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_CONTEXTMENU, OnContextMenu)
		MESSAGE_HANDLER(WM_COMMAND, OnCommand)
		MESSAGE_HANDLER(WM_TIMER, OnTimer)
		CHAIN_MSG_MAP(Base)
		REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		bHandled = FALSE;
		Invalidate();
		return bHandled;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);
	LRESULT OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

//////////////////////////////////////////////////////////////////////////

class CUIDesignerView : public UIWndImpl<CUIDesignerView>
{
public:
	//DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg);

	BEGIN_MSG_MAP(CUIDesignerView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};
