
#pragma once 

#ifndef _H_UIXMLWND_H_
#define _H_UIXMLWND_H_

#include "UILite.h"
#include <UI/UIWnd.h>
#include <XLib/XXml.h>

//////////////////////////////////////////////////////////////////////////

#ifndef _AFX

#define BEGIN_XML_WND_CREATE_MAP(theClass) \
	HWND Create(HWND hWndParent, RECT& rcPos \
	, LPCTSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, UINT nID = 0, LPVOID lpCreateParam = NULL) \
	{ \
		return Base::Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam); \
	} \
	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) \
	{ \
		HWND Res = NULL;

#define BEGIN_XML_WND_MODAL_MAP(theClass) \
	int DoModal(HWND hWndParent = ::GetActiveWindow(), LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) \
	{ \
		int Res = 0; 

#define BEGIN_XML_WND_MODELESS_MAP(theClass) \
	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) \
	{ \
		HWND Res = NULL;
		
#define BEGIN_XML_WND_HANDLER() \
		ATLASSERT(m_hWnd == NULL); \
		BEGIN_XML_MAP(T::GetWndClassName())

#define XML_WND_HANDLER_CREATE_DEFAULT() \
		T* pT = static_cast<T*>(this); \
		std::tstring strnull; \
		std::tstring strval; \
		\
		RECT rcPos = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str()); \
		std::tstring strTitle; \
		LPCTSTR szWindowName = xml->GetAttributeString(strnull, std::tstring(_T("title")), strTitle).c_str(); \
		DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str()); \
		DWORD dwExStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval).c_str()); \
		UINT nID = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0); \
		\
		Res = pT->Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, (LPVOID)xml);

#define XML_WND_HANDLER_MODAL_DEFAULT() \
		Res = Base::DoModal(hWndParent, (LPARAM)xml);

#define XML_WND_HANDLER_MODELESS_DEFAULT() \
		Res = Base::Create(hWndParent, (LPARAM)xml);

#else

#define BEGIN_XML_WND_CREATE_MAP(theClass) \
	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) \
	{ \
		HWND Res = NULL;

#define BEGIN_XML_WND_MODAL_MAP(theClass) \
	int DoModal(LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) \
	{ \
		int Res = 0; 

#define BEGIN_XML_WND_MODELESS_MAP(theClass) \
	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE) \
	{ \
		HWND Res = NULL;

#define BEGIN_XML_WND_HANDLER() \
		ATLASSERT(m_hWnd == NULL); \
		LPCTSTR lpszWndClass = T::GetWndClassName(); \
		BEGIN_XML_MAP(lpszWndClass)

#define XML_WND_HANDLER_CREATE_DEFAULT() \
		T* pT = static_cast<T*>(this); \
		std::tstring strnull; \
		std::tstring strval; \
		\
		RECT rcPos = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str()); \
		std::tstring strTitle; \
		LPCTSTR szWindowName = xml->GetAttributeString(strnull, std::tstring(_T("title")), strTitle).c_str(); \
		DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str()); \
		DWORD dwExStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval).c_str()); \
		UINT nID = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0); \
		lpCreateParams = (LPVOID)xml; \
		if(dynamic_cast<CWnd*>(pT)->CreateEx(dwExStyle, lpszWndClass, szWindowName, dwStyle, rcPos, CWnd::FromHandle(hWndParent), nID)) \
		{ \
			Res = pT->m_hWnd; \
		} 

#define XML_WND_HANDLER_CREATE_CONTROL() \
		T* pT = static_cast<T*>(this); \
		std::tstring strnull; \
		std::tstring strval; \
		\
		RECT rcPos = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str()); \
		std::tstring strTitle; \
		LPCTSTR szWindowName = xml->GetAttributeString(strnull, std::tstring(_T("title")), strTitle).c_str(); \
		DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str()); \
		DWORD dwExStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval).c_str()); \
		UINT nID = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0); \
		lpCreateParams = (LPVOID)xml; \
		if(dynamic_cast<CWnd*>(pT)->CreateEx(dwExStyle, GetWndClassName(), szWindowName, dwStyle, rcPos, CWnd::FromHandle(hWndParent), nID)) \
		{ \
			Res = pT->m_hWnd; \
		} 

#define XML_WND_HANDLER_MODAL_DEFAULT() \
		lpCreateParams = (LPVOID)xml; \
		Res = Base::DoModal();

#define XML_WND_HANDLER_MODELESS_DEFAULT() \
		T* pT = static_cast<T*>(this); \
		std::tstring strnull; \
		std::tstring strval; \
		\
		RECT rcPos = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str()); \
		std::tstring strTitle; \
		LPCTSTR szWindowName = xml->GetAttributeString(strnull, std::tstring(_T("title")), strTitle).c_str(); \
		DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str()); \
		DWORD dwExStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval).c_str()); \
		UINT nID = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0); \
		lpCreateParams = (LPVOID)xml; \
		if(CWnd::CreateEx(dwExStyle, _T("#32770"), szWindowName, dwStyle, rcPos, CWnd::FromHandle(hWndParent), nID)) \
		{ \
			Res = pT->m_hWnd; \
		} 

#endif//_AFX

#define CHAIN_XML_CREATE_MAP(theChainClass) \
		if(Res == NULL) { \
			Res = theChainClass::Create(hWndParent, lpszXml, XmlFlag); \
		}

#define END_XML_WND_HANDLER() \
		END_XML_MAP()

#define END_XML_WND_CREATE_MAP() \
		return Res; \
	}

#define END_XML_WND_MODAL_MAP		END_XML_WND_CREATE_MAP
#define END_XML_WND_MODELESS_MAP	END_XML_WND_CREATE_MAP

#define BEGIN_XML_WND_PRECREATED_MAP(theClass) \
	BOOL PreInitWindow(CREATESTRUCT& cs) \
	{ \
		T* pT = static_cast<T*>(this); \
		if (cs.lpCreateParams) { \
			Markup* xml = (Markup*)cs.lpCreateParams; 

#ifndef _AFX

#define BEGIN_XML_WND_PREINITDIALOG_MAP(theClass) \
	BOOL PreInitDialog(LPARAM lParam) \
	{ \
		T* pT = static_cast<T*>(this); \
		if (lParam) { \
			Markup* xml = (Markup*)lParam;
#else

#define BEGIN_XML_WND_PREINITDIALOG_MAP(theClass) \
	void PreInitDialog() \
	{ \
		T* pT = static_cast<T*>(this); \
		if (xml) { \

#endif//_AFX

#define BEGIN_XML_WND_PRECREATED_HANDLER() \
			std::tstring strname; \
			std::tstring strattr; \
			std::tstring strval; \
			\
			for (long attrcookie = xml->FirstAttributeString(strattr, strval); attrcookie; attrcookie = xml->NextAttributeString(strattr, strval, attrcookie)) \
			{ \
				pT->SetAttributeString(strattr.c_str(), strval.c_str(), 0); \
			} 
			
#define BEGIN_XML_WND_CONTROL_HANDLER() \
			for(long cookie = xml->First(); cookie; cookie = xml->Next(cookie)) \
			{ \
				if(xml->GetType(true)!=node_element) { continue; } \
				xml->IntoElem(); \
				\
				std::tstring strname; \
				std::tstring strval; \
				std::tstring classname;xml->GetName(classname); \
				std::tstring objectname;xml->GetAttributeString(strname, std::tstring(_T("name")), objectname); \
				UINT idctrl = tcsto<UINT>(xml->GetAttributeString(strname, std::tstring(_T("id")), strval)); \
				HWND hWndCtrl = 

#define XML_WND_CONTROL_HANDLER_DEFAULT() \
				pT->CreateControl(*pT, classname.c_str(), objectname.c_str(), idctrl, (LPCTSTR)xml, XML_FLAG_MARKUP); 

#define XML_WND_CONTROL_HANDLER(func) \
				func(*pT, classname.c_str(), objectname.c_str(), idctrl, (LPCTSTR)xml, XML_FLAG_MARKUP); 
				
#define END_XML_WND_CONTROL_HANDLER() \
				xml->OutofElem(); \
			} 

#define END_XML_WND_PRECREATED_HANDLER() \
			

#define END_XML_WND_PRECREATED_MAP() \
		} \
		return TRUE; \
	}

#ifndef _AFX

#define END_XML_WND_PREINITDIALOG_MAP	END_XML_WND_PRECREATED_MAP

#else

#define END_XML_WND_PREINITDIALOG_MAP \
		} \
	}

#endif//_AFX

#define BEGIN_XML_CONTROL_MAP(theClass) \
public: \
	HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag) \
	{ \
		HWND hWndCtrl = NULL; 

#define XML_CTRL_HANDLER(name,func) \
 		if(hWndCtrl == NULL && _tcsicmp(name, lpszWndClass) == 0) { \
 			hWndCtrl = func(hWndParent, lpszXml, XmlFlag); \
 		}

#define XML_ID_CTRL(id,ctrl) \
		if(hWndCtrl == NULL && (id) == nID) { \
			hWndCtrl = ctrl.Create(hWndParent, lpszXml, XmlFlag); \
		}

#define XML_NAME_CTRL(name,ctrl) \
		if(hWndCtrl == NULL && 0 == _tcsicmp(name, lpszCtrlName)) { \
			hWndCtrl = ctrl.Create(hWndParent, lpszXml, XmlFlag); \
		}

#define CHAIN_XML_CONTROL_MAP(theChainClass) \
		if(hWndCtrl == NULL) { \
			hWndCtrl = theChainClass::CreateControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag); \
		}

#define CHAIN_XML_DEFAULT_CONTROL_MAP() \
		if(hWndCtrl == NULL) { \
			hWndCtrl = CreateDefaultControl(hWndParent, lpszWndClass, lpszCtrlName, nID, lpszXml, XmlFlag); \
		}

#define CHAIN_XML_CONTROL_BEFORE_MAP(theChainClass) \
		CHAIN_XML_CONTROL_MAP(theChainClass) 

#define CHAIN_XML_CONTROL_AFTER_MAP(theChainClass) \
		if(hWndCtrl != NULL) { \
			theChainClass::OnCreateControl(hWndParent, hWndCtrl, lpszWndClass, lpszCtrlName, nID); \
		}

#define END_XML_CONTROL_MAP() \
		return hWndCtrl; \
	}

//////////////////////////////////////////////////////////////////////////
//CreateControl
/*HWND CreateControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag)
{
	ATLASSERT(hWndParent);
	if (!lpszXml || !XmlFlag) {
		return NULL;
	}

	HWND hWnd = NULL;

	BOOL bXmlOk = TRUE;
	Markup* xml;
	if (XmlFlag & XML_FLAG_FILE) {
		xml = new Markup();
		bXmlOk = xml->Open(lpszXml);
	} else if (XmlFlag & XML_FLAG_STREAM) {
		xml = new Markup();
		xml->Set(std::tstring(lpszXml));
	} else if (XmlFlag & XML_FLAG_MARKUP) {
		xml = (Markup*)lpszXml;
	}
	if (!(XmlFlag & XML_FLAG_MARKUP) && xml) {
		if (xml->Find(T::GetWndClassName())) {
			xml->IntoElem();
		} else {
			bXmlOk = FALSE;
		}
	}
	if (bXmlOk) {
		std::tstring strnull;
		std::tstring strval;

		RECT rcPos = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str());
		std::tstring strTitle;
		LPCTSTR szWindowName = xml->GetAttributeString(strnull, std::tstring(_T("title")), strTitle).c_str();
		DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str());
		DWORD dwExStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval).c_str());
		UINT nID = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0);

		hWnd = Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, (LPVOID)xml);
		//hWnd = Base::Create(hWndParent, rcPos, NULL, 0, 0, 0, (LPVOID)xml);
	}
	if (!(XmlFlag & XML_FLAG_MARKUP) && xml) {
		if (bXmlOk) {
			xml->OutofElem();
		}
		delete xml;
		xml = NULL;
	}

	return hWnd;
}*/
UILITE_API HWND CreateDefaultControl(HWND hWndParent, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID, LPCTSTR lpszXml, UINT XmlFlag);

//////////////////////////////////////////////////////////////////////////

#define DECLARE_XMLWND_CLASS(classname) \
public: \
	static LPCTSTR GetWndClassName() { return classname; } //\
	//\
	//virtual LPCTSTR GetThisClassName() { return classname; } 

#ifndef _AFX

typedef UIWnd UIXWnd;

//class UIXWnd : public UIWnd
//{
//	typedef UIWnd Base;
//public:
//	//disable hWnd
//	UIXWnd(HWND hWnd = NULL) : Base(hWnd) { }
//
//	//////////////////////////////////////////////////////////////////////////
//	//ClassName
//	//virtual LPCTSTR GetThisClassName() { return GetWndClassName(); }
//	//virtual BOOL IsClassName(LPCTSTR lpszClassName) { return _tcsicmp(lpszClassName, GetThisClassName()) == 0 ? TRUE : FALSE; }
//
//public:
//	//////////////////////////////////////////////////////////////////////////
//	//Window/Dialog Create or DoModal
//
//	/*//为了兼容标准控件Create,避免Create无法匹配,因为下面的virtual HWND Create也是Create
//	HWND Create(LPCTSTR lpstrWndClass, HWND hWndParent, _U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
//		DWORD dwStyle = 0, DWORD dwExStyle = 0,
//		_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
//	{
//		return Base::Create(lpstrWndClass, hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
//	}
//
//	HWND Create(HWND hWndParent, RECT& rcPos
//		, LPCTSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, UINT nID = 0, LPVOID lpCreateParam = NULL)
//	{
//		return NULL;
//	}*/
//
//	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE)
//	{
//		return NULL;
//	}
//
//	int DoModal(HWND hWndParent = ::GetActiveWindow(), LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE)
//	{
//		return 0;
//	}
//
//	//////////////////////////////////////////////////////////////////////////
//	//SetAttribute/GetAttribute
//	LRESULT SetAttributeString(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
//    {
//		return 0L;
//	}
//
//	LRESULT GetAttributeString(LPCTSTR lpszAttr, LPCSTR lpszValue, int nValueLen, UINT uFlags = 0)
//	{
//		return 0L;
//	}
//};

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIXWndMap
{
	typedef UIXWndMap<T> This;
protected:
	CString m_strWindowName;
public:
	UIXWndMap() {}

	void SetWindowName(LPCSTR lpszName) { m_strWindowName = lpszName; }
	LPCTSTR GetWindowName() { return m_strWindowName; }

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("name"), OnAttributeName)
		ATTRIBUTE_HANDLER(_T("addstyle"), OnAttributeAddStyle)
		ATTRIBUTE_HANDLER(_T("delstyle"), OnAttributeDelStyle)
		ATTRIBUTE_HANDLER(_T("addexstyle"), OnAttributeAddExStyle)
		ATTRIBUTE_HANDLER(_T("delexstyle"), OnAttributeDelExStyle)
	END_ATTRIBUTE_MAP()

	LRESULT OnAttributeName(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		m_strWindowName = lpszValue;
		return 1;
	}

	LRESULT OnAttributeAddStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyle(0, dwStyle);
		}
		return 1;
	}

	LRESULT OnAttributeDelStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyle(dwStyle, 0);
		}
		return 1;
	}

	LRESULT OnAttributeAddExStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyleEx(0, dwStyle);
		}
		return 1;
	}

	LRESULT OnAttributeDelExStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyleEx(dwStyle, 0);
		}
		return 1;
	}
};

template<class T>
class UIXDialogMap : public UIXWndMap<T>
{
	typedef UIXDialogMap<T> This;
	typedef UIXWndMap<T> Base;
public:
	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("title"), OnAttributeTitle)
		ATTRIBUTE_HANDLER(_T("rect"), OnAttributeRect)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()

	LRESULT OnAttributeTitle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		pT->SetWindowText(lpszValue);
		return 1;
	}

	LRESULT OnAttributeRect(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		RECT rc = _RECT(lpszValue);
		pT->SetWindowPos(NULL, &rc, 
			SWP_NOMOVE|SWP_NOREPOSITION|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
		return 1;
	}
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase = UIXWnd, class TWinTraits = CControlWinTraits>
class UIXWndImpl 
	: public UIWndImpl<T, TBase, TWinTraits>
	, public UIXWndMap<T>
{
	typedef UIXWndImpl<T, TBase, TWinTraits> This;
	typedef UIWndImpl<T, TBase, TWinTraits> Base;
	typedef UIXWndMap<T> WndMap;
public:
	//DECLARE_XMLWND_CLASS(_T("UIXWnd"))
	
	BEGIN_XML_WND_CREATE_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_CREATE_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_CREATE_MAP()

	BEGIN_XML_WND_PRECREATED_MAP(This)
		BEGIN_XML_WND_PRECREATED_HANDLER()
			BEGIN_XML_WND_CONTROL_HANDLER()
				XML_WND_CONTROL_HANDLER_DEFAULT()
			END_XML_WND_CONTROL_HANDLER()
		END_XML_WND_PRECREATED_HANDLER()
	END_XML_WND_PRECREATED_MAP()

	BEGIN_ATTRIBUTE_MAP(This)
		CHAIN_ATTRIBUTE_MAP(WndMap)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		//
	END_XML_CONTROL_MAP()
};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase = UIXWnd>
class UIXDialogImpl 
	: public UIDialogImpl<T, TBase>
	, public UIXDialogMap<T>
{
	typedef UIXDialogImpl<T, TBase> This;
	typedef UIDialogImpl<T, TBase> Base;
	typedef UIXDialogMap<T> DialogMap;

public:
	/*int DoModal(HWND hWndParent = ::GetActiveWindow(), LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE)
	{
		int nRet = 0;
		if (!lpszXml || !XmlFlag) {
			nRet = Base::DoModal(hWndParent);
		} else {
			BOOL bXmlOk = TRUE;
			Markup* xml;
			if (XmlFlag & XML_FLAG_FILE) {
				xml = new Markup();
				bXmlOk = xml->Open(lpszXml);
			} else if (XmlFlag & XML_FLAG_STREAM) {
				xml = new Markup();
				xml->Set(std::tstring(lpszXml));
			} else if (XmlFlag & XML_FLAG_MARKUP) {
				xml = (Markup*)lpszXml;
			}
			if (!(XmlFlag & XML_FLAG_MARKUP) && xml) {
				if (xml->Find(T::GetWndClassName())) {
					xml->IntoElem();
				} else {
					bXmlOk = FALSE;
				}
			}
			if (bXmlOk) {
				nRet = Base::DoModal(hWndParent, (LPARAM)xml);
			}
			if (!(XmlFlag & XML_FLAG_MARKUP) && xml) {
				if (bXmlOk) {
					xml->OutofElem();
				}
				delete xml;
				xml = NULL;
			}
		}
		return nRet;
	}

	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE)
	{
		ATLASSERT(m_hWnd == NULL);
		
		if (!lpszXml || !XmlFlag) {
			return Base::Create(hWndParent, lpszXml);
		}
		
		HWND hWnd = NULL;
		BOOL bXmlOk = TRUE;
		Markup* xml;
		if (XmlFlag & XML_FLAG_FILE) {
			xml = new Markup();
			bXmlOk = xml->Open(lpszXml);
		} else if (XmlFlag & XML_FLAG_STREAM) {
			xml = new Markup();
			xml->Set(std::tstring(lpszXml));
		} else if (XmlFlag & XML_FLAG_MARKUP) {
			xml = (Markup*)lpszXml;
		}
		if (!(XmlFlag & XML_FLAG_MARKUP) && xml) {
			if (xml->Find(T::GetWndClassName())) {
				xml->IntoElem();
			} else {
				bXmlOk = FALSE;
			}
		}
		if (bXmlOk) {
			hWnd = Base::Create(hWndParent, (LPARAM)xml);
		}
		if (!(XmlFlag & XML_FLAG_MARKUP) && xml) {
			if (bXmlOk) {
				xml->OutofElem();
			}
			delete xml;
			xml = NULL;
		}

		return hWnd;
	}*/
	BEGIN_XML_WND_MODAL_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_MODAL_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_MODAL_MAP()

	BEGIN_XML_WND_MODELESS_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_MODELESS_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_MODELESS_MAP()

	/*BOOL PreInitDialog(LPARAM lParam)
	{
		T* pT = static_cast<T*>(this);
		if (lParam) {
			Markup* xml = (Markup*)lParam;
			std::tstring strname;
			std::tstring strattr;
			std::tstring strval;
			long cookie = 0;
			
			for (cookie = xml->FirstAttributeString(strattr, strval); cookie; cookie = xml->NextAttributeString(strattr, strval, cookie))
			{
				pT->SetAttributeString(strattr.c_str(), strval.c_str(), 0);
			}
			
			for(cookie = xml->First(); cookie; cookie = xml->Next(cookie)) 
			{ 
				xml->IntoElem();
				
				std::tstring classname;xml->GetName(classname); 
				std::tstring objectname;xml->GetAttributeString(strname, std::tstring(_T("name")), objectname); 
				//ASSERT(!classname.empty()); 
				UINT idctrl = tcsto<UINT>(xml->GetAttributeString(strname, std::tstring(_T("id")), strval));
				HWND hWndCtrl = pT->CreateControl(*pT, 
					classname.c_str(), objectname.c_str(), idctrl, (LPCTSTR)xml, XML_FLAG_MARKUP);
				
				xml->OutofElem();
			}
		}
		return TRUE;
	}*/
	BEGIN_XML_WND_PREINITDIALOG_MAP(This)
		BEGIN_XML_WND_PRECREATED_HANDLER()
			BEGIN_XML_WND_CONTROL_HANDLER()
				XML_WND_CONTROL_HANDLER_DEFAULT()
			END_XML_WND_CONTROL_HANDLER()
		END_XML_WND_PRECREATED_HANDLER()
	END_XML_WND_PREINITDIALOG_MAP()

	BEGIN_ATTRIBUTE_MAP(This)
		CHAIN_ATTRIBUTE_MAP(DialogMap)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
	//
	END_XML_CONTROL_MAP()
};

//////////////////////////////////////////////////////////////////////////

#else 

typedef UIWnd UIXWnd;

template<class T>
class UIXWndMap
{
	typedef UIXWndMap<T> This;
protected:
	CString m_strWindowName;
public:
	UIXWndMap() {}

	void SetWindowName(LPCSTR lpszName) { m_strWindowName = lpszName; }
	LPCTSTR GetWindowName() { return m_strWindowName; }

	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("name"), OnAttributeName)
		ATTRIBUTE_HANDLER(_T("addstyle"), OnAttributeAddStyle)
		ATTRIBUTE_HANDLER(_T("delstyle"), OnAttributeDelStyle)
		ATTRIBUTE_HANDLER(_T("addexstyle"), OnAttributeAddExStyle)
		ATTRIBUTE_HANDLER(_T("delexstyle"), OnAttributeDelExStyle)
	END_ATTRIBUTE_MAP()

	LRESULT OnAttributeName(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		m_strWindowName = lpszValue;
		return 1;
	}

	LRESULT OnAttributeAddStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyle(0, dwStyle);
		}
		return 1;
	}

	LRESULT OnAttributeDelStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyle(dwStyle, 0);
		}
		return 1;
	}

	LRESULT OnAttributeAddExStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyleEx(0, dwStyle);
		}
		return 1;
	}

	LRESULT OnAttributeDelExStyle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		DWORD dwStyle = _HEXVALUE(lpszValue);
		if (dwStyle) {
			pT->ModifyStyleEx(dwStyle, 0);
		}
		return 1;
	}
};

template<class T>
class UIXDialogMap : public UIXWndMap<T>
{
	typedef UIXDialogMap<T> This;
	typedef UIXWndMap<T> Base;
public:
	BEGIN_ATTRIBUTE_MAP(This)
		ATTRIBUTE_HANDLER(_T("title"), OnAttributeTitle)
		ATTRIBUTE_HANDLER(_T("rect"), OnAttributeRect)
		CHAIN_ATTRIBUTE_MAP(Base)
	END_ATTRIBUTE_MAP()


	LRESULT OnAttributeTitle(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		pT->SetWindowText(lpszValue);
		return 1;
	}

	LRESULT OnAttributeRect(LPCTSTR lpszAttr, LPCTSTR lpszValue, UINT uFlags = 0)
	{
		T* pT = static_cast<T*>(this);
		RECT rc = _RECT(lpszValue);
		pT->SetWindowPos(NULL, rc.left, rc.top, rc.right, rc.bottom, 
			SWP_NOMOVE|SWP_NOREPOSITION|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
		return 1;
	}
};

__declspec(selectany,thread) LPVOID lpCreateParams = NULL;

template<class T, class TBase = UIXWnd>
class UIXWndImpl : public UIWndImpl<T, TBase>, public UIXWndMap<T>
{
	typedef UIXWndImpl<T,TBase> This;
	typedef UIWndImpl<T, TBase> Base;
	typedef UIXWndMap<T> WndMap;
public:
	UIXWndImpl(HWND hWnd = NULL):Base(hWnd),WndMap() { }

	BEGIN_XML_WND_CREATE_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_CREATE_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_CREATE_MAP()

	BOOL PreInitWindow(CREATESTRUCT& cs)
	{
		T* pT = static_cast<T*>(this);
		Markup* xml = (Markup*)lpCreateParams;
		if(xml) {
			BEGIN_XML_WND_PRECREATED_HANDLER()
				BEGIN_XML_WND_CONTROL_HANDLER()
					XML_WND_CONTROL_HANDLER_DEFAULT()
				END_XML_WND_CONTROL_HANDLER()
			END_XML_WND_PRECREATED_HANDLER()
		}
		return TRUE;
	}

	BEGIN_ATTRIBUTE_MAP(This)
		CHAIN_ATTRIBUTE_MAP(WndMap)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		//
	END_XML_CONTROL_MAP()
};

template<class T, class TBase = UIDialog>
class UIXDialogImpl : public UIDialogImpl<T,TBase>, public UIXDialogMap<T>
{
	typedef UIXDialogImpl<T,TBase> This;
	typedef UIDialogImpl<T,TBase> Base;
	typedef UIXDialogMap<T> DialogMap;
public:
	UIXDialogImpl(HWND hWnd = NULL):Base(hWnd) {}
	explicit UIXDialogImpl(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):Base(lpszTemplateName,pParentWnd) {}
	explicit UIXDialogImpl(UINT nIDTemplate, CWnd* pParentWnd = NULL):Base(nIDTemplate,pParentWnd) {}

	BEGIN_XML_WND_MODAL_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_MODAL_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_MODAL_MAP()

	BEGIN_XML_WND_MODELESS_MAP(This)
		BEGIN_XML_WND_HANDLER()
			XML_WND_HANDLER_MODELESS_DEFAULT()
		END_XML_WND_HANDLER()
	END_XML_WND_MODELESS_MAP()

	BOOL PreInitWindow(CREATESTRUCT& cs)
	{
		T* pT = static_cast<T*>(this);
		Markup* xml = (Markup*)lpCreateParams;
		if(xml) {
			BEGIN_XML_WND_PRECREATED_HANDLER()
				BEGIN_XML_WND_CONTROL_HANDLER()
					XML_WND_CONTROL_HANDLER_DEFAULT()
				END_XML_WND_CONTROL_HANDLER()
			END_XML_WND_PRECREATED_HANDLER()
		}
		return TRUE;
	}

	BEGIN_ATTRIBUTE_MAP(This)
		CHAIN_ATTRIBUTE_MAP(DialogMap)
	END_ATTRIBUTE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		//
	END_XML_CONTROL_MAP()
};

#endif//_AFX

#endif//_H_UIXMLWND_H_