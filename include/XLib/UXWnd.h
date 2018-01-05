#ifndef _H_UXWND_H_
#define _H_UXWND_H_

#include "UILite.h"
#include "UIXCtrl.h"
#include "UIXSkin.h"
#include "UIXPane.h"
#include <XLib/XObjectEx.h>

//////////////////////////////////////////////////////////////////////////

enum
{
	LAYOUT_STYLE_XML	= 0,	//默认通过XML配置布局
	LAYOUT_STYLE_HORZ	= 1,
	LAYOUT_STYLE_VERT	= 2,
	LAYOUT_STYLE_MASK	= 0X0F,
};

template<class T, class TPane = UIXPane>
class UXLayoutImpl : public UIXPaneSplitterImpl<T,TPane>
{
	typedef UXLayoutImpl<T,TPane> This;
	typedef UIXPaneSplitterImpl<T,TPane> Base;
protected:
	DWORD m_dwLayoutStyle;
public:
	UXLayoutImpl():m_dwLayoutStyle(0)
	{

	}

	void SetLayoutStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		if (_tcsicmp(_T("Vertical"),lpszValue)==0) {
			m_dwLayoutStyle = LAYOUT_STYLE_VERT;
		} else if (_tcsicmp(_T("Horizontal"),lpszValue)==0) {
			m_dwLayoutStyle = LAYOUT_STYLE_HORZ;
		} else {
			m_dwLayoutStyle = 0;
		}
		if (m_dwLayoutStyle) {
			m_pP = new Pane();
			DWORD dwStyle = 0;
			if (m_dwLayoutStyle==LAYOUT_STYLE_VERT) {
				dwStyle = PANEL_STYLE_TB;
			} else if(m_dwLayoutStyle==LAYOUT_STYLE_HORZ) {
				dwStyle = PANEL_STYLE_LR;
			} else {
				ASSERT(0);
			}
			m_pP->SetStyle(dwStyle);
		}
	}

	BEGIN_ATTRIBUTE_MAP(This) 
		ATTRIBUTE_HANDLER(_T("layout"),SetLayoutStyle)
		//CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	//HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
	//{
	//	//T* pT = static_cast<T*>(this);
	//	if (_tcsicmp(lpszWndClass, Pane::GetXmlPaneName()) == 0) {
	//		ASSERT(!m_dwLayoutStyle); //如果使用了布局，创建窗口时自动创建布局，所以不应该走到这里
	//		return Base::CreateControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag);
	//	}
	//	return NULL;
	//}

	void OnCreateControl(HWND hWndParent, HWND hWndCtrl, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID)
	{
		T* pT = static_cast<T*>(this);
		ASSERT(hWndParent==*pT);
		ASSERT(hWndCtrl);
		if (!lpszCtrlName || !lpszCtrlName[0]) {
			return;
		}
		//这里限定了lpszCtrlName绑定HWND和Pane，一一对应，否则肯定出错。
		if (_tcsicmp(Pane::GetXmlPaneName(), lpszWndClass) == 0) {
			//Pane
		} else {
			//HWND
			//1、如果设置了布局，这里自动创建Pane
			if (m_dwLayoutStyle) {
				UIWnd wndCtrl;
				wndCtrl.m_hWnd = hWndCtrl;
				Pane* pP = m_pP->LastChild(new Pane());
				RECT rcPos;
				wndCtrl.GetWindowRect(&rcPos);
				wndCtrl.m_hWnd = NULL;
				pP->SetRect(&rcPos);
				DWORD dwStyle = 0;
				pP->SetStyle(dwStyle);
				pP->SetName(lpszCtrlName);
				pP->OnCreateControl(hWndParent, (HWND)pP, lpszWndClass, lpszCtrlName, nID);
			}
			//2、布局和窗口关联
			Base::OnCreateControl(hWndParent, hWndCtrl, lpszWndClass, lpszCtrlName, nID);
		}
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

#ifndef _AFX

DECLARE_DYNCCREATE_FACTORY_EX_EXPORT(UILITE_API,UXWnd,UIXWnd)

#else

class UXWnd;
DECLARE_DYNCCREATE_FACTORY_EXPORT(UILITE_API,UXWnd)

class UILITE_API UXWnd
{
public:
	template<class TUXWnd>
	static HWND CreateUXWnd(TUXWnd* & pObject, LPCTSTR lpszName, HWND hWndParent, LPCTSTR lpszXml, UINT XmlFlag)
	{
		pObject = dynamic_cast<TUXWnd*>(DYNCREATE_OBJECT(UXWnd,lpszName));
		if (pObject) {
			return pObject->Create(hWndParent, lpszXml, XmlFlag);
		}
		return NULL;
	}
	template<class TUXWnd>
	static void DestroyUXWnd(TUXWnd* & pObject)
	{
		if (pObject) {
			pObject->Destroy();
			DYNDELETE_OBJECT(pObject);
			pObject = NULL;
		}
	}
public:
	UXWnd() {}
	virtual ~UXWnd() {}

	//动态对象都应该实现GetThisClassName接口
	virtual LPCTSTR GetThisClassName() { return NULL; }

	//对于窗口要实现基于XML的动态创建接口
	virtual HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) { return NULL; }
	virtual void Destroy() { }
};

#endif//_AFX

template<class T>
class UXWndMap
{
public:

	BEGIN_MSG_MAP(This)
		//
	END_MSG_MAP()

	HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
	{
		T* pT = static_cast<T*>(this);
		UXWnd* pWnd = NULL;
		HWND hWndCtrl = UXWnd::CreateUXWnd(pWnd,lpszWndClass,hWndParent,lpszXml,XmlFlag);
		//
		return hWndCtrl;
	}
};

class UILITE_API UXWndFactory
{
public:
	static HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag);
};

#ifndef _AFX

template<class T, class TBase = UIXWnd, class TWinTraits = CControlWinTraits>
class UXWndImpl 
	: public UIXWndImpl<T, TBase, TWinTraits>
	, public UXWndMap<T>
{
	typedef UXWndImpl<T, TBase, TWinTraits> This;
	typedef UIXWndImpl<T, TBase, TWinTraits> Base;
	typedef UXWndMap<T> WndMap;
public:

	BEGIN_XML_WND_CREATE_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_CREATE_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_CREATE_MAP()
	virtual void Destroy() { Base::DestroyWindow(); }

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(WndMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(WndMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

template<class T, class TBase = UXWnd, class TWinTraits = CControlWinTraits>
class UXCtrlImpl : public UXWndImpl<T, TBase, TWinTraits>
{
	typedef UXCtrlImpl<T, TBase, TWinTraits> This;
	typedef UXWndImpl<T, TBase, TWinTraits> Base;
public:

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("ok"), OnAttributeOK)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	LRESULT OnAttributeOK(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		//
		return 1L;
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}
};

#define DEFINE_XWND_CMMCTRL_CLASS(classname) \
	typedef UI##classname##T<UXWnd> _X##classname; \
	template<class T,class TBase=_X##classname> \
	class UX##classname##Impl : public UXCtrlImpl<T,TBase> \
	{ \
		typedef TBase Base; \
	}; \
	class UX##classname : public UX##classname##Impl<UX##classname>, public UIEraseBkgndCtrl<UX##classname> \
	{ \
		typedef UX##classname This; \
		typedef UX##classname##Impl<UX##classname> Base; \
		typedef UIEraseBkgndCtrl<UX##classname> PaintMap; \
		DECLARE_XMLWND_CLASS(_T(#classname)) \
		DECLARE_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd) \
	public: \
	\
		BEGIN_MSG_MAP(This) \
			CHAIN_MSG_MAP(PaintMap) \
			CHAIN_MSG_MAP(Base) \
		END_MSG_MAP() \
	}; \
	IMPLEMENT_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd)

#define DEFINE_XWND_SKINCTRL_CLASS(classname) \
	typedef UI##classname##T<UXWnd> _X##classname; \
	template<class T,class TBase=_X##classname> \
	class UX##classname##Impl : public UXCtrlImpl<T,TBase> \
	{ \
		typedef TBase Base; \
	}; \
	class UX##classname : public UX##classname##Impl<UX##classname> \
						, public UIX##classname##SkinMap<UX##classname> \
	{ \
		typedef UX##classname This; \
		typedef UX##classname##Impl<UX##classname> Base; \
		typedef UIX##classname##SkinMap<UX##classname> SkinMap; \
		DECLARE_XMLWND_CLASS(_T(#classname)) \
		DECLARE_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd) \
	public: \
	\
		BEGIN_MSG_MAP(This) \
			CHAIN_MSG_MAP(SkinMap) \
			CHAIN_MSG_MAP(Base) \
		END_MSG_MAP() \
	}; \
	IMPLEMENT_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd)


typedef UIButtonT<UXWnd> _XButton; 
template<class T,class TBase=_XButton> 
class UXButtonImpl : public UXCtrlImpl<T,TBase> 
{ 
	typedef TBase Base; 
};
class UXButton : public UXButtonImpl<UXButton>, public UIXButtonSkinMap<UXButton>, public UIButtonMap<UXButton>
{ 
	typedef UXButton This; 
	typedef UXButtonImpl<UXButton> Base; 
	typedef UIXButtonSkinMap<UXButton> SkinMap;
	typedef UIButtonMap<UXButton> FuncMap; 
	//DECLARE_XMLWND_CLASS(UIButton::GetWndClassName())
	DECLARE_DYNCREATE_WND_OBJECTER(UXButton,UXWnd) 
public: 

	BEGIN_MSG_MAP(This) 
		CHAIN_MSG_MAP(SkinMap) 
		CHAIN_MSG_MAP(FuncMap) 
		CHAIN_MSG_MAP(Base) 
	END_MSG_MAP() 
}; 

#else

template<class T, class TBase = UIWnd>
class UXWndImpl 
	: public UIXWndImpl<T, TBase>
	, public UXWndMap<T> 
{
	typedef UIXWndImpl<T, TBase> Base;
	typedef UXWndMap<T> WndMap;
public:
	UXWndImpl(HWND hWnd = NULL):Base(hWnd) { }

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(WndMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(WndMap)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

template<class T, class TBase = UIControlBar>
class UXCtrlImpl : public UXWndImpl<T, TBase>
{
	typedef UXCtrlImpl<T, TBase> This;
	typedef UXWndImpl<T, TBase> Base;
public:
	UXCtrlImpl(HWND hWnd = NULL):Base(hWnd) { }

	BEGIN_XML_WND_CREATE_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_CREATE_CONTROL()
		END_XML_WND_HANDLER()
	END_XML_WND_CREATE_MAP()

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("ok"), OnAttributeOK)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	LRESULT OnAttributeOK(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		//
		return 1L;
	}

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}
};

#define DEFINE_XWND_CMMCTRL_CLASS(classname) \
	class UX##classname : public UXCtrlImpl<UX##classname,UI##classname>, public UIEraseBkgndCtrl<UX##classname>, public UXWnd \
	{ \
		typedef UXCtrlImpl<UX##classname,UI##classname> Base; \
		typedef UIEraseBkgndCtrl<UX##classname> PaintMap; \
		DECLARE_XMLWND_CLASS(_T(#classname)) \
		DECLARE_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd) \
	public:\
		virtual HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) { return Base::Create(hWndParent, lpszXml, XmlFlag); } \
		virtual void Destroy() { Base::DestroyWindow(); } \
	\
		BOOL OnEraseBkgnd(HDC hdc) { return PaintMap::OnEraseBkgnd(hdc); } \
	\
		BEGIN_MSG_MAP(This) \
			CHAIN_MSG_MAP(PaintMap) \
			CHAIN_MSG_MAP(Base) \
		END_MSG_MAP() \
	}; \
	IMPLEMENT_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd)


#define DEFINE_XWND_SKINCTRL_CLASS(classname) \
	class UX##classname : public UXCtrlImpl<UX##classname,UI##classname>, public UIX##classname##SkinMap<UX##classname>, public UXWnd \
	{ \
		typedef UXCtrlImpl<UX##classname,UI##classname> Base; \
		typedef UIX##classname##SkinMap<UX##classname> SkinMap; \
		DECLARE_XMLWND_CLASS(_T(#classname)) \
		DECLARE_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd) \
	public:\
		virtual HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) { return Base::Create(hWndParent, lpszXml, XmlFlag); } \
		virtual void Destroy() { Base::DestroyWindow(); } \
	\
		BOOL OnEraseBkgnd(HDC hdc) { return TRUE; } \
		void OnPaint(HDC hdc) { SkinMap::OnPaint(hdc); } \
	\
		BEGIN_MSG_MAP(This) \
			CHAIN_MSG_MAP(SkinMap) \
			CHAIN_MSG_MAP(Base) \
		END_MSG_MAP() \
	}; \
	IMPLEMENT_DYNCREATE_WND_OBJECTER(UX##classname,UXWnd)

class UXButton : public UXCtrlImpl<UXButton,UIButton>, public UIXButtonSkinMap<UXButton>, public UIButtonMap<UXButton>, public UXWnd 
{ 
	typedef UXCtrlImpl<UXButton,UIButton> Base; 
	typedef UIXButtonSkinMap<UXButton> SkinMap;
	typedef UIButtonMap<UXButton> FuncMap;
	DECLARE_XMLWND_CLASS(_T("Button"))
	DECLARE_DYNCREATE_WND_OBJECTER(UXButton,UXWnd) 
public:
	virtual HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) { return Base::Create(hWndParent, lpszXml, XmlFlag); } 
	virtual void Destroy() { Base::DestroyWindow(); } 

	BOOL OnEraseBkgnd(HDC hdc) { return TRUE; } 
	void OnPaint(HDC hdc) { SkinMap::OnPaint(hdc); }

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(SkinMap) 
		CHAIN_MSG_MAP(FuncMap)
		CHAIN_MSG_MAP(Base) 
	END_MSG_MAP() 
}; 

#endif

//////////////////////////////////////////////////////////////////////////

#ifndef _AFX

template<class T, class TBase = UXWnd, class TWinTraits = CControlWinTraits>
class UXWndLayoutImpl
	: public UXWndImpl<T,TBase,TWinTraits>
	, public UXLayoutImpl<T>
{ 
	typedef UXWndLayoutImpl<T,TBase,TWinTraits> This;
	typedef UXWndImpl<T,TBase,TWinTraits> Base;
	typedef UXLayoutImpl<T> LayoutMap;
public:

	BEGIN_ATTRIBUTE_MAP(This) 
		CHAIN_ATTRIBUTE_MAP(LayoutMap)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(LayoutMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(LayoutMap)
		CHAIN_MSG_MAP(Base) 
	END_MSG_MAP() 
}; 

//class UILITE_API UXContainer 
//	: public UXWndLayoutImpl<UXContainer>
//	, public UIEraseBkgndCtrl<UXContainer>
//{ 
//	typedef UXContainer This;
//	typedef UXWndLayoutImpl<UXContainer> Base; 
//	typedef UIEraseBkgndCtrl<UXContainer> PaintMap;
//	DECLARE_XMLWND_CLASS(_T("Container"))
//	DECLARE_DYNCREATE_WND_OBJECTER(UXContainer,UXWnd) 
//public:
//
//	BEGIN_ATTRIBUTE_MAP(This) 
//		CHAIN_ATTRIBUTE_MAP(Base)
//	END_ATTRIBUTE_MAP()
//
//	BEGIN_XML_CONTROL_MAP(This)
//		CHAIN_XML_CONTROL_MAP(Base)
//	END_XML_CONTROL_MAP()
//
//	BOOL OnEraseBkgnd(HDC hdc);
//
//	BEGIN_MSG_MAP(This)
//		CHAIN_MSG_MAP(PaintMap)
//		CHAIN_MSG_MAP(Base) 
//	END_MSG_MAP() 
//
//	virtual void OnFinalMessage(HWND /*hWnd*/);
//}; 

template<class T, class TBase = UIXWnd>
class UXDialogImpl 
	: public UIXDialogImpl<T, TBase>
	, public UXLayoutImpl<T>
	, public UXWndMap<T>
	, public UIXSkinThemeImpl<T>
	, public UIBkgndSkinDrawMap<T>
{
	typedef UXDialogImpl<T, TBase> This;
	typedef UIXDialogImpl<T, TBase> Base;
	typedef UXLayoutImpl<T> LayoutMap;
	typedef UXWndMap<T> WndMap;
	typedef UIXSkinThemeImpl<T> SkinTheme;
	typedef UIBkgndSkinDrawMap<T> SkinDraw;
public:

	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);

		UINT nBkStyle = tcsto(_pUISkinManager->GetString(MAKESKINSTRRESID2(_T("Style"),_T("Background")), _T(""), pT->GetWndClassName()), UINT(0));
		if(IsBkColor(nBkStyle&UI_BK_TYPE_MASK)) {
			COLORREF crBkColor = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color"),_T("Background")), CLR_INVALID, pT->GetWndClassName());
			if (crBkColor!=CLR_INVALID) {
				COLORREF crBkColor2 = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color2"),_T("Background")), CLR_INVALID, pT->GetWndClassName());
				pT->SetBkColor(crBkColor, crBkColor2, nBkStyle);
			} else {
				pT->SetBkColor(crBkColor);
			}
		} else {
			Image* pBkImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("Background")), NULL,pT->GetWndClassName());
			if (pBkImage) {
				pT->SetBkImage(pBkImage, nBkStyle==0?UI_BK_STYLE_STRETCH:nBkStyle);
			} else {

			}
		}

		return SkinTheme::OpenThemeData();
	}

	BEGIN_ATTRIBUTE_MAP(This) 
		CHAIN_ATTRIBUTE_MAP(LayoutMap)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(LayoutMap)
		CHAIN_XML_CONTROL_MAP(WndMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(LayoutMap)
		CHAIN_MSG_MAP(WndMap)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDraw)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

#else

template<class T, class TBase = UIWnd>
class UXWndLayoutImpl
	: public UXWndImpl<T,TBase>
	, public UXLayoutImpl<T>
{ 
	typedef UXWndLayoutImpl<T,TBase> This;
	typedef UXWndImpl<T,TBase> Base;
	typedef UXLayoutImpl<T> LayoutMap;
public:

	BEGIN_ATTRIBUTE_MAP(This) 
		CHAIN_ATTRIBUTE_MAP(LayoutMap)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(LayoutMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(LayoutMap)
		CHAIN_MSG_MAP(Base) 
	END_MSG_MAP() 
}; 

//class UILITE_API UXContainer 
//	: public UXWndLayoutImpl<UXContainer>
//	, public UIEraseBkgndCtrl<UXContainer>
//	, public UXWnd 
//{ 
//	typedef UXContainer This;
//	typedef UXWndLayoutImpl<UXContainer> Base; 
//	typedef UIEraseBkgndCtrl<UXContainer> PaintMap;
//	DECLARE_XMLWND_CLASS(_T("Container"))
//	DECLARE_DYNCREATE_WND_OBJECTER(UXContainer,UXWnd) 
//public:
//	virtual HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) { return Base::Create(hWndParent, lpszXml, XmlFlag); }
//	virtual void Destroy() { Base::DestroyWindow(); }
//
//	BEGIN_ATTRIBUTE_MAP(This) 
//		CHAIN_ATTRIBUTE_MAP(Base)
//	END_ATTRIBUTE_MAP()
//
//	BEGIN_XML_CONTROL_MAP(This)
//		CHAIN_XML_CONTROL_MAP(Base)
//	END_XML_CONTROL_MAP()
//
//	BOOL OnEraseBkgnd(HDC hdc);
//
//	BEGIN_MSG_MAP(This)
//		CHAIN_MSG_MAP(PaintMap)
//		CHAIN_MSG_MAP(Base) 
//	END_MSG_MAP() 
//
//	virtual void OnFinalMessage(HWND /*hWnd*/);
//}; 

template<class T, class TBase = UIDialog>
class UXDialogImpl 
	: public UIXDialogImpl<T, TBase>
	, public UXLayoutImpl<T>
	, public UXWndMap<T> 
	, public UIXSkinThemeImpl<T>
	, public UIBkgndSkinDrawMap<T>
{
	typedef UXDialogImpl<T, TBase> This;
	typedef UIXDialogImpl<T, TBase> Base;
	typedef UXLayoutImpl<T> LayoutMap;
	typedef UXWndMap<T> WndMap;
	typedef UIXSkinThemeImpl<T> SkinTheme;
	typedef UIBkgndSkinDrawMap<T> SkinDraw;
public:
	explicit UXDialogImpl(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):Base(lpszTemplateName,pParentWnd) {}
	explicit UXDialogImpl(UINT nIDTemplate, CWnd* pParentWnd = NULL):Base(nIDTemplate,pParentWnd) {}

	HTHEME OpenThemeData()
	{
		T* pT = static_cast<T*>(this);
		
		UINT nBkStyle = tcsto(_pUISkinManager->GetString(MAKESKINSTRRESID2(_T("Style"),_T("Background")), _T(""), pT->GetWndClassName()), UINT(0));
		if(IsBkColor(nBkStyle&UI_BK_TYPE_MASK)) {
			COLORREF crBkColor = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color"),_T("Background")), CLR_INVALID, pT->GetWndClassName());
			if (crBkColor!=CLR_INVALID) {
				COLORREF crBkColor2 = _pUISkinManager->GetCOLORREF(MAKESKINSTRRESID2(_T("Color2"),_T("Background")), CLR_INVALID, pT->GetWndClassName());
				pT->SetBkColor(crBkColor, crBkColor2, nBkStyle);
			} else {
				pT->SetBkColor(crBkColor);
			}
		} else {
			Image* pBkImage = _pUISkinManager->GetImage(MAKESKINSTRRESID2(_T("Image"),_T("Background")), NULL,pT->GetWndClassName());
			if (pBkImage) {
				pT->SetBkImage(pBkImage, nBkStyle==0?UI_BK_STYLE_STRETCH:nBkStyle);
			} else {

			}
		}

		return SkinTheme::OpenThemeData();
	}

	BEGIN_ATTRIBUTE_MAP(This) 
		CHAIN_ATTRIBUTE_MAP(LayoutMap)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		CHAIN_XML_CONTROL_MAP(LayoutMap)
		CHAIN_XML_CONTROL_MAP(WndMap)
		CHAIN_XML_CONTROL_MAP(Base)
	END_XML_CONTROL_MAP()

	virtual BOOL OnInitDialog()
	{
		BOOL bRet = Base::OnInitDialog();

		T* pT = static_cast<T*>(this);

		//CRect rcLayout;
		//pT->GetLayoutRect(&rcLayout);
		//pT->Relayout(&rcLayout);
		pT->Relayout();

		return bRet;
	}

	BOOL OnEraseBkgnd(HDC hdc)
	{
		return SkinDraw::OnEraseBkgnd(hdc);
	}

	void OnPaint(HDC hdc)
	{
		SkinDraw::OnPaint(hdc);
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(LayoutMap)
		CHAIN_MSG_MAP(WndMap)
		CHAIN_MSG_MAP(SkinTheme)
		CHAIN_MSG_MAP(SkinDraw)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

#endif
	
#endif//_H_UXWND_H_