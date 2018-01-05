
#pragma once 

#ifndef _H_UIXMLWND2_H_
#define _H_UIXMLWND2_H_

#include "UIWnd2.h"
#include "UIXWnd.h"

//////////////////////////////////////////////////////////////////////////

typedef UIWnd2 UIXWnd2;

//class UIXWnd2 : public UIWnd2
//{
//	typedef UIWnd2 Base;
//public:
//	//disable hWnd
//	UIXWnd2(HWND hWnd = NULL) : Base(hWnd) { }
//
//	//////////////////////////////////////////////////////////////////////////
//	//IsDirectUI
//	//virtual BOOL IsDirectUI() { return FALSE; }
//
//	//////////////////////////////////////////////////////////////////////////
//	//ClassName
//	//virtual LPCTSTR GetThisClassName() { return GetWndClassName(); }
//	//virtual BOOL IsClassName(LPCTSTR lpszClassName) { return _tcsicmp(lpszClassName, GetThisClassName()) == 0 ? TRUE : FALSE; }
//
//private: 
//	//////////////////////////////////////////////////////////////////////////
//	//disable to attach or detach
//	void Attach(HWND hWndNew)
//	{
//		Base::Attach(hWndNew);
//	}
//	
//	HWND Detach()
//	{
//		return Base::Detach();
//	}
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
//
//	//////////////////////////////////////////////////////////////////////////
//	//other
//
//};

//////////////////////////////////////////////////////////////////////////

template<class T, class TBase = UIXWnd2, class TWinTraits = CControlWinTraits>
class UIXWnd2Impl 
	: public UIWnd2Impl<T, TBase, TWinTraits>
	, public UIXWndMap<T>
{
	typedef UIXWnd2Impl<T, TBase, TWinTraits> This;
	typedef UIWnd2Impl<T, TBase, TWinTraits> Base;
	typedef UIXWndMap<T> WndMap;
public:
	//DECLARE_XMLWND_CLASS(_T("UIXWnd2"))

	/*HWND Create(HWND hWndParent, RECT& rcPos
		, LPCTSTR szWindowName = NULL, DWORD dwStyle = 0, DWORD dwExStyle = 0, UINT nID = 0, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID, lpCreateParam);
	}
	
	HWND Create(HWND hWndParent, LPCTSTR lpszXml = NULL, UINT XmlFlag = XML_FLAG_FILE)
	{
		ATLASSERT(m_hWnd == NULL);
		
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
			std::tstring strWindowName;
			LPCTSTR szWindowName = xml->GetAttributeString(strnull, std::tstring(_T("title")), strWindowName).c_str();
			DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str());
			DWORD dwExStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("exstyle")), strval).c_str());
			UINT nID = data_cast<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval), 0);
			
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
	}

	BOOL PreCreateWindow(CREATESTRUCT& cs)
	{
		T* pT = static_cast<T*>(this);
		if (cs.lpCreateParams) {
			Markup* xml = (Markup*)cs.lpCreateParams;
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
				UINT idctrl = data_cast<UINT>(xml->GetAttributeString(strname, std::tstring(_T("id")), strval));
				HWND hWndCtrl = pT->CreateControl(*pT, 
					classname.c_str(), objectname.c_str(), idctrl, (LPCTSTR)xml, XML_FLAG_MARKUP);

				xml->OutofElem();
			}
		}
		return TRUE;
	}*/
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

template<class T, class TBase = UIXWnd2>
class UIXScrollWnd2Impl 
	: public UIScrollWnd2Impl<T, TBase>
	, public UIXWndMap<T>
{
	typedef UIXScrollWnd2Impl<T, TBase> This;
	typedef UIScrollWnd2Impl<T, TBase> Base;
	typedef UIXWndMap<T> WndMap;
public:
	DECLARE_XMLWND_CLASS(_T("UIXScrollWnd2"))

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

template<class T, class TBase = UIWnd2>
class UIXDialog2Impl 
	: public UIDialog2Impl<T, TBase>
	, public UIXDialogMap<T>
{
	typedef UIXDialog2Impl<T, TBase> This;
	typedef UIDialog2Impl<T, TBase> Base;
	typedef UIXDialogMap<T> DialogMap;
public:

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

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

//////////////////////////////////////////////////////////////////////////

#endif//_H_UIXMLWND2_H_