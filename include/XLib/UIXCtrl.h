#ifndef _H_UIXMLCTRL_H_
#define _H_UIXMLCTRL_H_

#include <UI/UICtrl.h>
#include "UIXWnd.h"
#include "UIXSkin.h"

template<class T>
class UICtrlMap
{
	typedef UICtrlMap<T> This;
public:
	BOOL IsNotify() { return FALSE; }

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDBClick)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_RBUTTONDBLCLK, OnRButtonDBClick)
		MESSAGE_HANDLER(WM_RBUTTONDOWN, OnRButtonDown)
		MESSAGE_HANDLER(WM_RBUTTONUP, OnRButtonUp)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()

	LRESULT OnLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->Notify(pT->GetParent(), NM_DBLCLK);
		}
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->SetCapture();
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			if(pT->GetCapture() == *pT) {
				pT->ReleaseCapture();

				pT->Invalidate();

				POINT pt;
				POINTSTOPOINT(pt, lParam);
				RECT rcClient;
				pT->GetClientRect(&rcClient);
				if (::PtInRect(&rcClient, pt)) {
					pT->NotifyCommand(pT->GetParent(), NM_CLICK);
				}
			}
		}
		return bHandled;
	}

	LRESULT OnRButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->Notify(pT->GetParent(), NM_RDBLCLK);
		}
		return bHandled;
	}

	LRESULT OnRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->SetCapture();
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			if(pT->GetCapture() == *pT) {
				pT->ReleaseCapture();

				pT->Invalidate();

				POINT pt;
				POINTSTOPOINT(pt, lParam);
				RECT rcClient;
				pT->GetClientRect(&rcClient);
				if (::PtInRect(&rcClient, pt)) {
					pT->Notify(pT->GetParent(), NM_RCLICK);
				}
			}
		}
		return bHandled;
	}

	LRESULT OnMouseHover(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->Notify(pT->GetParent(), NM_SETFOCUS);
		}
		return bHandled;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->Notify(pT->GetParent(), NM_KILLFOCUS);
		}
		return bHandled;
	}
};

#ifndef _AFX

template<class T, class TBase = UIXWnd, class TWinTraits = CControlWinTraits>
class UIXCtrlImpl : public UIXWndImpl<T, TBase, TWinTraits>
{
	typedef UIXCtrlImpl<T, TBase, TWinTraits> This;
	typedef UIXWndImpl<T, TBase, TWinTraits> Base;
public:
	
	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("ok"), OnAttributeOK)
	END_ATTRIBUTE_MAP()
		
	LRESULT OnAttributeOK(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		//
		return 1L;
	}
};

#define DEFINE_XML_CMMCTRL_CLASS(classname,basename) \
	typedef basename##T<UIXWnd> X##basename; \
	template<class T,class TBase=X##basename> \
	class classname##Impl : public UIXCtrlImpl<T,TBase> \
	{ \
	}; \
	class classname : public classname##Impl<classname> \
	{ \
		DECLARE_XMLWND_CLASS(basename::GetWndClassName()) \
	};


#define DEFINE_XML_SKINCTRL_CLASS(classname,basename) \
	typedef basename##T<UIXWnd> X##basename; \
	template<class T,class TBase=X##basename> \
	class classname##Impl : public UIXCtrlImpl<T,TBase> \
	{ \
	}; \
	class classname : public classname##Impl<classname>, public classname##SkinMap<classname> \
	{ \
		typedef classname This; \
		typedef classname##Impl<classname> Base; \
		typedef classname##SkinMap<classname> SkinMap; \
		DECLARE_XMLWND_CLASS(basename::GetWndClassName()) \
	public: \
	\
		BEGIN_MSG_MAP(This) \
			CHAIN_MSG_MAP(SkinMap) \
			CHAIN_MSG_MAP(Base) \
		END_MSG_MAP() \
	};

DEFINE_XML_CMMCTRL_CLASS(UIXStatic,UIStatic)
DEFINE_XML_CMMCTRL_CLASS(UIXListBox,UIListBox)
DEFINE_XML_CMMCTRL_CLASS(UIXComboBox,UIComboBox)
DEFINE_XML_CMMCTRL_CLASS(UIXEdit,UIEdit)
DEFINE_XML_CMMCTRL_CLASS(UIXScrollBar,UIScrollBar)
DEFINE_XML_SKINCTRL_CLASS(UIXButton,UIButton)
DEFINE_XML_CMMCTRL_CLASS(UIXListCtrl,UIListCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXTreeCtrl,UITreeCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXHeaderCtrl,UIHeaderCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXToolBarCtrl,UIToolBarCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXStatusBarCtrl,UIStatusBarCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXTabCtrl,UITabCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXToolTipCtrl,UIToolTipCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXTrackBarCtrl,UITrackBarCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXUpDownCtrl,UIUpDownCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXProgressBarCtrl,UIProgressBarCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXHotKeyCtrl,UIHotKeyCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXAnimateCtrl,UIAnimateCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXRichEditCtrl,UIRichEditCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXDragListBox,UIDragListBox)
DEFINE_XML_CMMCTRL_CLASS(UIXReBarCtrl,UIReBarCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXComboBoxEx,UIComboBoxEx)
DEFINE_XML_CMMCTRL_CLASS(UIXDateTimePickerCtrl,UIDateTimePickerCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXMonthCalendarCtrl,UIMonthCalendarCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXFlatScrollBar,UIFlatScrollBar)
DEFINE_XML_CMMCTRL_CLASS(UIXIPAddressCtrl,UIIPAddressCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXPagerCtrl,UIPagerCtrl)
DEFINE_XML_CMMCTRL_CLASS(UIXLinkCtrl,UILinkCtrl)

class UIXSysButton
	: public UIXButtonImpl<UIXSysButton>
	, public UISysButtonMap<UIXSysButton>
	, public UIXSysButtonSkinMap<UIXSysButton>
{
	typedef UIXSysButton This;
	typedef UIXButtonImpl<UIXSysButton> Base;
	typedef UISysButtonMap<UIXSysButton> FuncMap;
	typedef UIXSysButtonSkinMap<UIXSysButton> SkinMap;
	DECLARE_XMLWND_CLASS(_T("SYSBUTTON"))
public:

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

#else

template<class T, class TBase>
class UIXCtrlImpl : public UIXWndImpl<T,TBase>
{
	typedef UIXCtrlImpl<T,TBase> This;
	typedef UIXWndImpl<T,TBase> Base;
public:
	UIXCtrlImpl(HWND hWnd = NULL):Base(hWnd) { }

	BEGIN_XML_WND_CREATE_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_CREATE_CONTROL()
		END_XML_WND_HANDLER()
	END_XML_WND_CREATE_MAP()

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("ok"), OnAttributeOK)
	END_ATTRIBUTE_MAP()

	LRESULT OnAttributeOK(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		//
		return 1L;
	}
};

#define DEFINE_XML_CMMCTRL_CLASS(classname) \
	class UIX##classname : public UIXCtrlImpl<UIX##classname,UI##classname> \
	{ \
		typedef UIX##classname This; \
		typedef UIXCtrlImpl<UIX##classname,UI##classname> Base; \
		DECLARE_XMLWND_CLASS(_T(#classname)) \
	public: \
		UIX##classname(HWND hWnd = NULL) : Base(hWnd) { } \
		This & operator =(HWND hWnd) { m_hWnd = hWnd; return *this; } \
	}; 

#define DEFINE_XML_SKINCTRL_CLASS(classname) \
	class UIX##classname : public UIXCtrlImpl<UIX##classname,UI##classname>, public UIX##classname##SkinMap<UIX##classname> \
	{ \
		typedef UIX##classname This; \
		typedef UIXCtrlImpl<UIX##classname,UI##classname> Base; \
		typedef UIX##classname##SkinMap<UIX##classname> SkinMap; \
		DECLARE_XMLWND_CLASS(_T(#classname)) \
	public: \
		UIX##classname(HWND hWnd = NULL) : Base(hWnd) { } \
		This & operator =(HWND hWnd) { m_hWnd = hWnd; return *this; } \
	\
		BOOL OnEraseBkgnd(HDC hdc) { return TRUE; } \
		void OnPaint(HDC hdc) { SkinMap::Paint(hdc); } \
	\
		BEGIN_MSG_MAP(This) \
			CHAIN_MSG_MAP(SkinMap) \
			CHAIN_MSG_MAP(Base) \
		END_MSG_MAP() \
	}; 

/*class UIXStatic
	: public UIXCtrlImpl<UIXStatic,UIStatic>
{
	typedef UIXStatic This;
	typedef UIXCtrlImpl<UIXStatic,UIStatic> Base;
	DECLARE_XMLWND_CLASS(_T("Static"))
public:
	UIXStatic(HWND hWnd = NULL) : Base(hWnd) { } 
	This & operator =(HWND hWnd) { m_hWnd = hWnd; return *this; } 
};*/
DEFINE_XML_CMMCTRL_CLASS(Static)
DEFINE_XML_CMMCTRL_CLASS(ListBox)
DEFINE_XML_CMMCTRL_CLASS(ComboBox)
DEFINE_XML_CMMCTRL_CLASS(Edit)
DEFINE_XML_CMMCTRL_CLASS(ScrollBar)
DEFINE_XML_SKINCTRL_CLASS(Button)
DEFINE_XML_CMMCTRL_CLASS(ListCtrl)
DEFINE_XML_CMMCTRL_CLASS(TreeCtrl)
DEFINE_XML_CMMCTRL_CLASS(HeaderCtrl)
DEFINE_XML_CMMCTRL_CLASS(ToolBar)
DEFINE_XML_CMMCTRL_CLASS(StatusBar)
DEFINE_XML_CMMCTRL_CLASS(TabCtrl)
DEFINE_XML_CMMCTRL_CLASS(ToolTipCtrl)
DEFINE_XML_CMMCTRL_CLASS(SpinButtonCtrl)
DEFINE_XML_CMMCTRL_CLASS(ProgressCtrl)
DEFINE_XML_CMMCTRL_CLASS(HotKeyCtrl)
DEFINE_XML_CMMCTRL_CLASS(AnimateCtrl)
DEFINE_XML_CMMCTRL_CLASS(RichEditCtrl)
DEFINE_XML_CMMCTRL_CLASS(ReBarCtrl)
DEFINE_XML_CMMCTRL_CLASS(ComboBoxEx)
DEFINE_XML_CMMCTRL_CLASS(DateTimeCtrl)
DEFINE_XML_CMMCTRL_CLASS(MonthCalCtrl)
DEFINE_XML_CMMCTRL_CLASS(IPAddressCtrl)
DEFINE_XML_CMMCTRL_CLASS(PagerCtrl)
#if (_WIN32_WINNT >= 0x0501) && !defined(_WIN32_WCE)
DEFINE_XML_CMMCTRL_CLASS(LinkCtrl)
#endif//(_WIN32_WINNT >= 0x0501) && !defined(_WIN32_WCE)

class UIXSysButton
	: public UIXCtrlImpl<UIXSysButton,UIButton>
	, public UISysButtonMap<UIXSysButton>
	, public UIXSysButtonSkinMap<UIXSysButton>
{
	typedef UIXSysButton This;
	typedef UIXCtrlImpl<UIXSysButton,UIButton> Base;
	typedef UISysButtonMap<UIXSysButton> FuncMap;
	typedef UIXSysButtonSkinMap<UIXSysButton> SkinMap;
	DECLARE_XMLWND_CLASS(_T("SYSBUTTON"))
public:
	UIXSysButton(HWND hWnd = NULL) : Base(hWnd) { } 
	This & operator =(HWND hWnd) { m_hWnd = hWnd; return *this; } 
		
	BOOL OnEraseBkgnd(HDC hdc) { return TRUE; }
	void OnPaint(HDC hdc) { SkinMap::Paint(hdc); }
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

#endif//_AFX

#endif//_H_UIXMLCTRL_H_