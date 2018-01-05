#ifndef _H_UIXMLCTRL2_H_
#define _H_UIXMLCTRL2_H_

#include "UIXCtrl.h"
#include "UICtrl2.h"
#include "UIXWnd2.h"
#include "UIXSkin2.h"

template<class T, class TBase = UIXWnd2, class TWinTraits = CControlWinTraits>
class UIXCtrl2Impl : public UIXWnd2Impl<T, TBase, TWinTraits>
{
	typedef UIXCtrl2Impl<T, TBase, TWinTraits> This;
	typedef UIXWnd2Impl<T, TBase, TWinTraits> Base;
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

#define DEFINE_XML_CMMCTRL2_CLASS(classname,basename) \
	typedef basename##T<UIXWnd2> X##basename; \
	template<class T,class TBase=X##basename> \
	class classname##Impl : public UIXCtrl2Impl<T,TBase> \
	{ \
		DECLARE_XMLWND_CLASS(basename::GetWndClassName()) \
	}; 

DEFINE_XML_CMMCTRL2_CLASS(UIXStatic2,UIStatic2)
DEFINE_XML_CMMCTRL2_CLASS(UIXListBox2,UIListBox2)
DEFINE_XML_CMMCTRL2_CLASS(UIXComboBox2,UIComboBox2)
DEFINE_XML_CMMCTRL2_CLASS(UIXEdit2,UIEdit2)
DEFINE_XML_CMMCTRL2_CLASS(UIXScrollBar2,UIScrollBar2)
DEFINE_XML_CMMCTRL2_CLASS(UIXButton2,UIButton2)
DEFINE_XML_CMMCTRL2_CLASS(UIXListCtrl2,UIListCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXTreeCtrl2,UITreeCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXHeaderCtrl2,UIHeaderCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXToolBarCtrl2,UIToolBarCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXStatusBarCtrl2,UIStatusBarCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXTabCtrl2,UITabCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXToolTipCtrl2,UIToolTipCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXTrackBarCtrl2,UITrackBarCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXUpDownCtrl2,UIUpDownCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXProgressBarCtrl2,UIProgressBarCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXHotKeyCtrl2,UIHotKeyCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXAnimateCtrl2,UIAnimateCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXRichEditCtrl2,UIRichEditCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXDragListBox2,UIDragListBox2)
DEFINE_XML_CMMCTRL2_CLASS(UIXReBarCtrl2,UIReBarCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXComboBoxEx2,UIComboBoxEx2)
DEFINE_XML_CMMCTRL2_CLASS(UIXDateTimePickerCtrl2,UIDateTimePickerCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXMonthCalendarCtrl2,UIMonthCalendarCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXFlatScrollBar2,UIFlatScrollBar2)
DEFINE_XML_CMMCTRL2_CLASS(UIXIPAddressCtrl2,UIIPAddressCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXPagerCtrl2,UIPagerCtrl2)
DEFINE_XML_CMMCTRL2_CLASS(UIXLinkCtrl2,UILinkCtrl2)


//////////////////////////////////////////////////////////////////////////

class UIXStatic2
	: public UIXStatic2Impl<UIXStatic2>
	, public UIStatic2Map<UIXStatic2>
	, public UIXStaticSkinMap<UIXStatic2>
{
	typedef UIXStatic2 This;
	typedef UIXStatic2Impl<UIXStatic2> Base;
	typedef UIStatic2Map<UIXStatic2> FuncMap;
	typedef UIXStaticSkinMap<UIXStatic2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

class UIXHypeLink2
	: public UIXCtrl2Impl<UIXHypeLink2>
	, public UIHypeLink2Map<UIXHypeLink2>
	, public UIXHypeLinkSkinMap<UIXHypeLink2>
{
	typedef UIXHypeLink2 This;
	typedef UIXCtrl2Impl<UIXHypeLink2> Base;
	typedef UIHypeLink2Map<UIXHypeLink2> FuncMap;
	typedef UIXHypeLinkSkinMap<UIXHypeLink2> SkinMap;
public:
	DECLARE_XMLWND_CLASS(_T("HypeLink"))

	BOOL IsDirectUI() { return TRUE; }

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_STRING_HANDLER(_T("hypelink"), SetHypeLink)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

class UIXEdit2 
: public UIXEdit2Impl<UIXEdit2>
, public UIEdit2Map<UIXEdit2>
, public UIXEdit2SkinMap<UIXEdit2>
{
	typedef UIXEdit2 This;
	typedef UIXEdit2Impl<UIXEdit2> Base;
	typedef UIEdit2Map<UIXEdit2> FuncMap;
	typedef UIXEdit2SkinMap<UIXEdit2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

class UIXProgressBarCtrl2 
	: public UIXProgressBarCtrl2Impl<UIXProgressBarCtrl2>
	, public UIProgressBarCtrl2Map<UIXProgressBarCtrl2>
	, public UIXProgressBarCtrlSkinMap<UIXProgressBarCtrl2>
{
	typedef UIXProgressBarCtrl2 This;
	typedef UIXProgressBarCtrl2Impl<UIXProgressBarCtrl2> Base;
	typedef UIProgressBarCtrl2Map<UIXProgressBarCtrl2> FuncMap;
	typedef UIXProgressBarCtrlSkinMap<UIXProgressBarCtrl2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

class UIXButton2 
: public UIXButton2Impl<UIXButton2>
, public UIButton2Map<UIXButton2>
, public UIXButtonSkinMap<UIXButton2>
{
	typedef UIXButton2 This;
	typedef UIXButton2Impl<UIXButton2> Base;
	typedef UIButton2Map<UIXButton2> FuncMap;
	typedef UIXButtonSkinMap<UIXButton2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

class UIXSysButton2
: public UIXButton2Impl<UIXSysButton2>
, public UISysButton2Map<UIXSysButton2>
, public UIXSysButton2SkinMap<UIXSysButton2>
{
	typedef UIXSysButton2 This;
	typedef UIXButton2Impl<UIXSysButton2> Base;
	typedef UISysButton2Map<UIXSysButton2> FuncMap;
	typedef UIXSysButton2SkinMap<UIXSysButton2> SkinMap;
public:
	DECLARE_XMLWND_CLASS(_T("SYSBUTTON"))

	BOOL IsDirectUI() { return TRUE; }
	
	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

class UIXTabCtrl2 
	: public UIXTabCtrl2Impl<UIXTabCtrl2>
	, public UITabCtrl2Map<UIXTabCtrl2>
	, public UIXTabCtrlSkinMap<UIXTabCtrl2>
{
	typedef UIXTabCtrl2 This;
	typedef UIXTabCtrl2Impl<UIXTabCtrl2> Base;
	typedef UITabCtrl2Map<UIXTabCtrl2> FuncMap;
	typedef UIXTabCtrlSkinMap<UIXTabCtrl2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

class UIXHeaderCtrl2 
	: public UIXHeaderCtrl2Impl<UIXHeaderCtrl2>
	, public UIHeaderCtrl2Map<UIXHeaderCtrl2>
	, public UIXHeaderCtrlSkinMap<UIXHeaderCtrl2>
{
	typedef UIXHeaderCtrl2 This;
	typedef UIXHeaderCtrl2Impl<UIXHeaderCtrl2> Base;
	typedef UIHeaderCtrl2Map<UIXHeaderCtrl2> FuncMap;
	typedef UIXHeaderCtrlSkinMap<UIXHeaderCtrl2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

class UIXScrollBar2 
	: public UIXScrollBar2Impl<UIXScrollBar2>
	, public UIScrollBar2Map<UIXScrollBar2>
	, public UIXScrollBarSkinMap<UIXScrollBar2>
{
	typedef UIXScrollBar2 This;
	typedef UIXScrollBar2Impl<UIXScrollBar2> Base;
	typedef UIScrollBar2Map<UIXScrollBar2> FuncMap;
	typedef UIXScrollBarSkinMap<UIXScrollBar2> SkinMap;
public:
	BOOL IsDirectUI() { return TRUE; }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(SkinMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

/*class UIXImage  : public UIXCtrl2Impl<UIXImage>, public UIBkgnd<UIXImage>
{
	typedef UIXImage This;
	typedef UIXCtrlImpl<UIXImage> Base;
public:
	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_VALUE(_T("image_style"), UINT, m_bgStyle)
		ATTRIBUTE_VALUE_HANDLER(_T("image_color"), COLORREF, m_bgColor.SetFromCOLORREF)
		ATTRIBUTE_VALUE_POINTER(_T("image_ptr"), Image, m_pBg)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CPaintDCT<UIXImage> dc(this,(HDC)wParam);
		PaintBkgnd(dc);
	}
};*/

#endif//_H_UIXMLCTRL2_H_