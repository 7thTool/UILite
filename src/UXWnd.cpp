#include "stdafx.h"
#include "UXWnd.h"

IMPLEMENT_DYNCCREATE_FACTORY(UXWnd)

class UXWndCreater : public UXWndMap<UXWndCreater>
{

};

UXWndCreater _UXWndCreater;

HWND UXWndFactory::CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
{
	HWND hWndCtrl = _UXWndCreater.CreateControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag);
	if (!hWndCtrl) {
		hWndCtrl = CreateDefaultControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag);
	}
	return hWndCtrl;
}

#ifndef _AFX

DEFINE_XWND_SKINCTRL_CLASS(Static)
DEFINE_XWND_CMMCTRL_CLASS(ListBox)
DEFINE_XWND_CMMCTRL_CLASS(ComboBox)
DEFINE_XWND_CMMCTRL_CLASS(Edit)
DEFINE_XWND_SKINCTRL_CLASS(ScrollBar)
//DEFINE_XWND_SKINCTRL_CLASS(Button)
DEFINE_XWND_CMMCTRL_CLASS(ListCtrl)
DEFINE_XWND_CMMCTRL_CLASS(TreeCtrl)
DEFINE_XWND_CMMCTRL_CLASS(HeaderCtrl)
//DEFINE_XWND_CMMCTRL_CLASS(ToolBarCtrl)
//DEFINE_XWND_CMMCTRL_CLASS(StatusBarCtrl)
DEFINE_XWND_CMMCTRL_CLASS(TabCtrl)
//DEFINE_XWND_CMMCTRL_CLASS(ToolTipCtrl)
DEFINE_XWND_CMMCTRL_CLASS(TrackBarCtrl)
DEFINE_XWND_CMMCTRL_CLASS(UpDownCtrl)
DEFINE_XWND_CMMCTRL_CLASS(ProgressBarCtrl)
DEFINE_XWND_CMMCTRL_CLASS(HotKeyCtrl)
DEFINE_XWND_CMMCTRL_CLASS(AnimateCtrl)
DEFINE_XWND_CMMCTRL_CLASS(RichEditCtrl)
DEFINE_XWND_CMMCTRL_CLASS(DragListBox)
DEFINE_XWND_CMMCTRL_CLASS(ReBarCtrl)
DEFINE_XWND_CMMCTRL_CLASS(ComboBoxEx)
DEFINE_XWND_CMMCTRL_CLASS(DateTimePickerCtrl)
DEFINE_XWND_CMMCTRL_CLASS(MonthCalendarCtrl)
DEFINE_XWND_CMMCTRL_CLASS(FlatScrollBar)
DEFINE_XWND_CMMCTRL_CLASS(IPAddressCtrl)
DEFINE_XWND_CMMCTRL_CLASS(PagerCtrl)
DEFINE_XWND_CMMCTRL_CLASS(LinkCtrl)

IMPLEMENT_DYNCREATE_WND_OBJECTER(UXButton,UXWnd)

class UXSysButton
	: public UXButtonImpl<UXSysButton>
	, public UISysButtonMap<UXSysButton>
	, public UIXSysButtonSkinMap<UXSysButton>
{
	typedef UXSysButton This;
	typedef UXButtonImpl<UXSysButton> Base;
	typedef UISysButtonMap<UXSysButton> FuncMap;
	typedef UIXSysButtonSkinMap<UXSysButton> SkinMap;
	DECLARE_XMLWND_CLASS(_T("SYSBUTTON"))
	DECLARE_DYNCREATE_WND_OBJECTER(UXSysButton,UXWnd) 
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
}; 
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXSysButton,UXWnd)

#else

DEFINE_XWND_SKINCTRL_CLASS(Static)
DEFINE_XWND_CMMCTRL_CLASS(ListBox)
DEFINE_XWND_CMMCTRL_CLASS(ComboBox)
DEFINE_XWND_CMMCTRL_CLASS(Edit)
DEFINE_XWND_CMMCTRL_CLASS(ScrollBar)
//DEFINE_XWND_SKINCTRL_CLASS(Button)
DEFINE_XWND_CMMCTRL_CLASS(ListCtrl)
DEFINE_XWND_CMMCTRL_CLASS(TreeCtrl)
DEFINE_XWND_CMMCTRL_CLASS(HeaderCtrl)
//DEFINE_XWND_CMMCTRL_CLASS(ToolBar)
//DEFINE_XWND_CMMCTRL_CLASS(StatusBar)
DEFINE_XWND_CMMCTRL_CLASS(TabCtrl)
//DEFINE_XWND_CMMCTRL_CLASS(ToolTipCtrl)
DEFINE_XWND_CMMCTRL_CLASS(SpinButtonCtrl)
DEFINE_XWND_CMMCTRL_CLASS(ProgressCtrl)
DEFINE_XWND_CMMCTRL_CLASS(HotKeyCtrl)
DEFINE_XWND_CMMCTRL_CLASS(AnimateCtrl)
DEFINE_XWND_CMMCTRL_CLASS(RichEditCtrl)
DEFINE_XWND_CMMCTRL_CLASS(ReBarCtrl)
DEFINE_XWND_CMMCTRL_CLASS(ComboBoxEx)
DEFINE_XWND_CMMCTRL_CLASS(DateTimeCtrl)
DEFINE_XWND_CMMCTRL_CLASS(MonthCalCtrl)
DEFINE_XWND_CMMCTRL_CLASS(IPAddressCtrl)
DEFINE_XWND_CMMCTRL_CLASS(PagerCtrl)
#if (_WIN32_WINNT >= 0x0501) && !defined(_WIN32_WCE)
DEFINE_XWND_CMMCTRL_CLASS(LinkCtrl)
#endif//(_WIN32_WINNT >= 0x0501) && !defined(_WIN32_WCE)

IMPLEMENT_DYNCREATE_WND_OBJECTER(UXButton,UXWnd)

class UXSysButton
	: public UXCtrlImpl<UXSysButton,UIButton>
	, public UISysButtonMap<UXSysButton>
	, public UIXSysButtonSkinMap<UXSysButton>
	, public UXWnd
{
	typedef UXSysButton This;
	typedef UXCtrlImpl<UXSysButton,UIButton> Base;
	typedef UISysButtonMap<UXSysButton> FuncMap;
	typedef UIXSysButtonSkinMap<UXSysButton> SkinMap;
	DECLARE_XMLWND_CLASS(_T("SYSBUTTON"))
	DECLARE_DYNCREATE_WND_OBJECTER(UXSysButton,UXWnd) 
public:
	UXSysButton(HWND hWnd = NULL) : Base(hWnd) { } 
	This & operator =(HWND hWnd) { m_hWnd = hWnd; return *this; } 

	virtual HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) { return Base::Create(hWndParent, lpszXml, XmlFlag); } 
	virtual void Destroy() { Base::DestroyWindow(); }

	BOOL OnEraseBkgnd(HDC hdc) { return TRUE; } 
	void OnPaint(HDC hdc) { SkinMap::OnPaint(hdc); }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
}; 
IMPLEMENT_DYNCREATE_WND_OBJECTER(UXSysButton,UXWnd)

#endif//_AFX

//////////////////////////////////////////////////////////////////////////

//IMPLEMENT_DYNCREATE_WND_OBJECTER(UXContainer,UXWnd)
//
//BOOL UXContainer::OnEraseBkgnd(HDC hdc) 
//{ 
//	return PaintMap::OnEraseBkgnd(hdc);
//}
//
//void UXContainer::OnFinalMessage(HWND /*hWnd*/)
//{
//	delete this;
//}
