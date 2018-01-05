#ifndef _H_UXWND2_H_
#define _H_UXWND2_H_

#include "UILite.h"
#include "UIXCtrl2.h"
#include "UIXPane2.h"
#include <XLib/XObjectEx.h>

DECLARE_DYNCCREATE_FACTORY_EX_EXPORT(UILITE_API,UXWnd2,UIXWnd2)

template<class T>
class UXWnd2Map
{
public:
	HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
	{
		T* pT = static_cast<T*>(this);
		UXWnd2* pWnd = NULL;
		HWND hWndCtrl = UXWnd2::CreateUXWnd2(pWnd,lpszWndClass,hWndParent,lpszXml,XmlFlag);
		if (hWndCtrl) {
			_pUIWnd2Manager->SetAutoDelete(hWndCtrl);
		}
		return hWndCtrl;
	}
};

class UILITE_API UXWnd2Factory
{
public:
	static HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag);
};

template<class T, class TBase = UXWnd2, class TWinTraits = CControlWinTraits>
class UXWnd2Impl 
	: public UIXWnd2Impl<T, TBase, TWinTraits>
	, public UXWnd2Map<T>
{
	typedef UIXWnd2Impl<T, TBase, TWinTraits> Base;
	typedef UXWnd2Map<T> FuncMap;
public:
	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(FuncMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()
};

template<class T, class TBase = UXWnd2>
class UXScrollWnd2Impl 
	: public UIXScrollWnd2Impl<T, TBase>
	, public UXWnd2Map<T>
{
	typedef UIXScrollWnd2Impl<T, TBase> Base;
	typedef UXWnd2Map<T> FuncMap;
public:
	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(FuncMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()
};

template<class T, class TBase = UXWnd2>
class UXDialog2Impl 
	: public UIXDialog2Impl<T, TBase>
	, public UXWnd2Map<T>
{
	typedef UIXDialog2Impl<T, TBase> Base;
	typedef UXWnd2Map<T> FuncMap;
public:
	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(FuncMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()
};

template<class T, class TBase = UXWnd2, class TWinTraits = CControlWinTraits>
class UXCtrl2Impl : public UXWnd2Impl<T, TBase, TWinTraits>
{
	typedef UXCtrl2Impl<T, TBase, TWinTraits> This;
	typedef UXWnd2Impl<T, TBase, TWinTraits> Base;
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

#define DEFINE_XWND_CMMCTRL2_CLASS(classname,basename) \
	typedef basename##T<UXWnd2> _X##basename; \
	template<class T,class TBase=_X##basename> \
	class classname##Impl : public UXCtrl2Impl<T,TBase> \
	{ \
		DECLARE_XMLWND_CLASS(basename::GetWndClassName()) \
	}; 

DEFINE_XWND_CMMCTRL2_CLASS(UXStatic2,UIStatic2)
DEFINE_XWND_CMMCTRL2_CLASS(UXListBox2,UIListBox2)
DEFINE_XWND_CMMCTRL2_CLASS(UXComboBox2,UIComboBox2)
DEFINE_XWND_CMMCTRL2_CLASS(UXEdit2,UIEdit2)
DEFINE_XWND_CMMCTRL2_CLASS(UXScrollBar2,UIScrollBar2)
DEFINE_XWND_CMMCTRL2_CLASS(UXButton2,UIButton2)
DEFINE_XWND_CMMCTRL2_CLASS(UXListCtrl2,UIListCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXTreeCtrl2,UITreeCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXHeaderCtrl2,UIHeaderCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXToolBarCtrl2,UIToolBarCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXStatusBarCtrl2,UIStatusBarCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXTabCtrl2,UITabCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXToolTipCtrl2,UIToolTipCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXTrackBarCtrl2,UITrackBarCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXUpDownCtrl2,UIUpDownCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXProgressBarCtrl2,UIProgressBarCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXHotKeyCtrl2,UIHotKeyCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXAnimateCtrl2,UIAnimateCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXRichEditCtrl2,UIRichEditCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXDragListBox2,UIDragListBox2)
DEFINE_XWND_CMMCTRL2_CLASS(UXReBarCtrl2,UIReBarCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXComboBoxEx2,UIComboBoxEx2)
DEFINE_XWND_CMMCTRL2_CLASS(UXDateTimePickerCtrl2,UIDateTimePickerCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXMonthCalendarCtrl2,UIMonthCalendarCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXFlatScrollBar2,UIFlatScrollBar2)
DEFINE_XWND_CMMCTRL2_CLASS(UXIPAddressCtrl2,UIIPAddressCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXPagerCtrl2,UIPagerCtrl2)
DEFINE_XWND_CMMCTRL2_CLASS(UXLinkCtrl2,UILinkCtrl2)

//////////////////////////////////////////////////////////////////////////

#endif//_H_UXWND2_H_