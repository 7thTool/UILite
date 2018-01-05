#ifndef _H_UIXPANE_H_
#define _H_UIXPANE_H_

#include <UI/UIPane.h>
#include "UIXWnd.h"

#define BEGIN_XML_PANE_HANDLER() \
		ATLASSERT(m_hWnd == NULL); \
		BEGIN_XML_MAP(T::GetXmlPaneName())

#define XML_PANE_HANDLER_CREATE_DEFAULT() \
		T* pT = static_cast<T*>(this); \
		std::tstring strnull; \
		std::tstring strval; \
		\
		RECT rcPos = _RECT(xml->GetAttributeString(strnull, std::tstring(_T("rect")), strval).c_str()); \
		DWORD dwStyle = _HEXVALUE(xml->GetAttributeString(strnull, std::tstring(_T("style")), strval).c_str()); \
		std::tstring name;xml->GetAttributeString(strnull, std::tstring(_T("name")), name); \
		SetRect(&rcPos); \
		SetStyle(dwStyle); \
		SetName(name.c_str()); \
		Res = (HWND)pT; \
		\
		long cookie = 0; \
		for(cookie = xml->First(); cookie; cookie = xml->Next(cookie)) \
		{ \
			xml->IntoElem(); \
			\
			std::tstring classname;xml->GetName(classname); \
			std::tstring objectname;xml->GetAttributeString(strnull, std::tstring(_T("name")), objectname); \
			UINT idctrl = tcsto<UINT>(xml->GetAttributeString(strnull, std::tstring(_T("id")), strval)); \
			HWND hWndCtrl = pT->CreateControl(hWndParent, classname.c_str(), objectname.c_str(), idctrl, (LPCTSTR)xml, XML_FLAG_MARKUP); \
			\
			xml->OutofElem(); \
		} 

#define XML_NAME_PANE_HANDLER(name) \
		if(hWndCtrl==NULL && 0 == _tcsicmp(name, lpszWndClass)) { \
			Pane* pP = LastChild(new Pane()); \
			hWndCtrl = pP->Create(hWndParent, lpszXml, XmlFlag); \
		}

#define XML_NAME_PANESPLITTER_HANDLER(name) \
		if(hWndCtrl==NULL && 0 == _tcsicmp(name, lpszWndClass)) { \
			if(!m_pP) { \
				m_pP = new Pane(); \
				hWndCtrl = m_pP->Create(hWndParent, lpszXml, XmlFlag); \
				if(hWndCtrl) { \
					hWndCtrl = (HWND)m_pP; \
				} \
			} else { \
				hWndCtrl = (HWND)m_pP; \
			} \
		}

#define END_XML_PANE_HANDLER() \
		END_XML_MAP()


//如果Pane没有关联窗口，支持直接在Pane里绘制静态文本，图片，XML，网页等内容
enum
{
	PANEL_STYLE_RIGHT		= 0X00000100,		//右对齐
	PANEL_STYLE_CENTER		= 0X00000200,		//居中
	PANEL_STYLE_BOTTOM		= 0X00000400,		//底对齐
	PANEL_STYLE_VCENTER		= 0X00000800,		//垂直居中

	PANEL_STYLE_RES			= 0X00001000,		//资源（图片，XML，html等）
	PANEL_STYLE_CUSTOM		= 0X00002000,		//自定义
};

//UIWnd2用来关联HWND句柄用,Pane不创建窗口，只是关联HWND
template<class T, class TBase = UIWnd>
class UIXPaneT : public UIPaneT<T,TBase>
{
	typedef UIXPaneT<T,TBase> This;
	typedef UIPaneT<T,TBase> Base;
	typedef T Pane;
public:
	static LPCTSTR GetXmlPaneName() 
	{
		return _T("Pane");
	}
protected:
	CString m_Name;
public:
	UIXPaneT(HWND hWnd = NULL) : Base(hWnd)
	{
	
	}

// 	~UIXPaneT()
// 	{
// 		
// 	}

	LPCTSTR SetName(LPCTSTR lpszName)
	{
		m_Name = lpszName;
		return m_Name;
	}

	LPCTSTR GetName()
	{
		return m_Name;
	}

	T* PaneFromName(LPCTSTR lpszName)
	{
		T* pT = static_cast<T*>(this);
		if(_tcsicmp(GetName(),lpszName)) {
			T* pP = NULL;
			T* pC = pT->FirstChild();
			for (; pC; pC = pC->Next())
			{
				pP = pC->PaneFromName(lpszName);
				if (pP) {
					break;
				}
			}
			return pP;
		} else {
			return pT;
		}
		return NULL;
	}

	HWND WindowFromName(LPCTSTR lpszName)
	{
		T* pT = static_cast<T*>(this);
		T* pP = pT->PaneFromName(lpszName);
		if(pP) {
			return *pP;
		}
		return NULL;
	}

	T* ChildPaneFromName(LPCTSTR lpszName)
	{
		T* pT = static_cast<T*>(this);
		T* pP = NULL;
		T* pC = pT->FirstChild();
		for (; pC; pC = pC->Next())
		{
			if (_tcsicmp(pC->GetName(),lpszName)==0) {
				pP = pC;
				break;
			}
		}
		return pP;
		return NULL;
	}

	HWND ChildWindowFromName(LPCTSTR lpszName)
	{
		T* pT = static_cast<T*>(this);
		T* pP = pT->ChildPaneFromName(lpszName);
		if(pP) {
			return *pP;
		}
		return NULL;
	}

	void Format(Markup* xml)
	{
		T* pT = static_cast<T*>(this);
		ASSERT(xml);
		TCHAR szValue[1024] = {0};
		xml->SetAttributeString(_T(""), _T("name"), (TCHAR*)pT->GetName());
		RECT rc = {0};
		pT->GetRect(&rc);
		_stprintf(szValue, _T("%d,%d,%d,%d"), rc.left, rc.top, rc.right, rc.bottom);
		xml->SetAttributeString(_T(""), _T("rect"), szValue);
		xml->SetAttributeT<unsigned long>(_T(""), _T("style"), pT->GetStyle());
		for (T* pC = FirstChild(); pC; pC = pC->Next())
		{
			xml->New(std::tstring(T::GetXmlPaneName()));
			xml->IntoElem();
			pC->Format(xml);
			xml->OutofElem();
		}
	}

	BEGIN_XML_WND_CREATE_MAP(This)
		BEGIN_XML_PANE_HANDLER()
			XML_PANE_HANDLER_CREATE_DEFAULT()
		END_XML_PANE_HANDLER()
	END_XML_WND_CREATE_MAP()

	BEGIN_XML_CONTROL_MAP(This)
		XML_NAME_PANE_HANDLER(T::GetXmlPaneName())
		CHAIN_XML_CONTROL_AFTER_MAP(This)
	END_XML_CONTROL_MAP()

	LRESULT OnCreateControl(HWND hWndParent, HWND hWndCtrl, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName, UINT nID)
	{
		LRESULT lRes = 0L;
		//绑定名字才会发这个消息
		if (lpszCtrlName && lpszCtrlName[0]) { 
			TBase wndParent;
			wndParent.m_hWnd = hWndParent;
			lRes = wndParent.SendMessage(WM_COMMAND, (WPARAM)ID_PANE_CREATE, (LPARAM)hWndCtrl);
			wndParent.m_hWnd = NULL;
		}
		return 0L;
	}
};

class UIXPane : public UIXPaneT<UIXPane,UIWnd>
{
	typedef UIXPane This;
	typedef UIXPaneT<UIXPane,UIWnd> Base;
	typedef UIXPane Pane;
protected:

public:
	UIXPane(HWND hWnd = NULL) : Base(hWnd)
	{

	}

	// 	~UIXPane()
	// 	{
	// 		
	// 	}
};

template <class T, class TPane>
class UIXPaneSplitterImpl : public UIPaneSplitterImpl<T,TPane>
{
public:
	typedef UIXPaneSplitterImpl<T,TPane> This;
	typedef UIPaneSplitterImpl<T,TPane> Base;
	typedef TPane Pane;
protected:
	
public:
	UIXPaneSplitterImpl()
	{
		
	}

// 	~UIXPaneSplitterImpl()
// 	{
// 	}
	
	Pane* PaneFromName(LPCTSTR lpszName, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->PaneFromName(lpszName);
		}
		return NULL;
	}

	HWND WindowFromName(LPCTSTR lpszName, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->WindowFromName(lpszName);
		}
		return NULL;
	}

	Pane* ChildPaneFromName(LPCTSTR lpszName, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->ChildPaneFromName(lpszName);
		}
		return NULL;
	}

	HWND ChildWindowFromName(LPCTSTR lpszName, Pane* pP = NULL)
	{
		if(!pP) {
			pP = m_pP;
		}
		if(pP) {
			return pP->ChildWindowFromName(lpszName);
		}
		return NULL;
	}

	void FormatChildWindow(Markup* xml, LPCTSTR lpszName)
	{

	}

	void Format(Markup* xml)
	{
		T* pT = static_cast<T*>(this);
		if (m_pP) {
			xml->New(std::tstring(Pane::GetXmlPaneName()));
			xml->IntoElem();
			m_pP->Format(xml);
			xml->OutofElem();
		}
	}

	void Format(LPCTSTR lpszXml, UINT XmlFlag = XML_FLAG_FILE)
	{
		BEGIN_XML_WRITE_MAP(T::GetWndClassName())
			XML_HANDLER(Format)
		END_XML_WRITE_MAP()
	}

	void InsertChilds(Pane* pP, long nChilds)
	{
		ASSERT(!pP->Child());
		ASSERT(nChilds > 0);
		ASSERT(pP->GetStyle()&(PANEL_STYLE_LR|PANEL_STYLE_TB));
		long i;
		RECT rc;
		pP->GetRect(&rc);
		unsigned long Style = pP->GetStyle();
		CString strName = pP->GetName();
		RECT rcC = rc;
		for (i = 0; i < nChilds; i++)
		{
			Pane* pC = new Pane();
			if (Style & PANEL_STYLE_LR) {
				if(i == nChilds-1) {
					rcC.right = rc.right;
				} else {
					rcC.right = rcC.left + ((rc.right-rc.left)-(nChilds-1)*Pane::GetHBorder())/nChilds;
				}
				pC->SetRect(&rcC);
				pC->SetStyle(PANEL_STYLE_SCALE|PANEL_STYLE_L_SIZED|PANEL_STYLE_R_SIZED);
				rcC.left = rcC.right + Pane::GetHBorder();
			} else {
				if(i == nChilds-1) {
					rcC.bottom = rc.bottom;
				} else {
					rcC.bottom = rcC.top + ((rc.bottom-rc.top)-(nChilds-1)*Pane::GetVBorder())/nChilds;
				}
				pC->SetRect(&rcC);
				pC->SetStyle(PANEL_STYLE_SCALE|PANEL_STYLE_T_SIZED|PANEL_STYLE_B_SIZED);
				rcC.top = rcC.bottom + Pane::GetVBorder();
			}

			CString strNameC;
			if (strName.IsEmpty()) {
				strNameC.Format(_T("%d"), i);
			} else {
				strNameC.Format(_T("%s_%d"), (LPCTSTR)strName, i);
			}
			pC->SetName(strNameC);

			pP->LastChild(pC);
		}
	}

	void RemoveChilds(Pane* pP, BOOL bDestoryWindow = FALSE)
	{
		T* pT = static_cast<T*>(this);
		ASSERT (pP);
		while (Pane* pC = pP->Child()) 
		{
			//先脱离，再移除，这样就不会调整布局了
			pC->Free();
			pT->Remove(pC, bDestoryWindow);
		}
	}

	void Insert(Pane* pPane, Pane* pBefore = NULL, Pane* pParent = NULL)
	{
		T* pT = static_cast<T*>(this);
		Base::Insert(pPane, pBefore, pParent);
		pT->OnCreateControl((*pT), (HWND)pPane, Pane::GetXmlPaneName(), pPane->GetName(), 0);
		//return pPane;
	}

	void Insert(LPCRECT lpRect, long nStyle, LPCTSTR lpszName, Pane* pBefore = NULL, Pane* pParent = NULL)
	{
		T* pT = static_cast<T*>(this);
		Pane* pPane = new Pane();
		pPane->SetRect(lpRect);
		pPane->SetStyle(nStyle);
		pPane->SetName(lpszName);
		pT->Insert(pPane, pBefore, pParent);
		//return pPane;
	}

	void Insert(LPCRECT lpRect, long nStyle, LPCTSTR lpszName, int nPos = -1, Pane* pParent = NULL)
	{
		T* pT = static_cast<T*>(this);
		if (pParent) {
			pT->Insert(lpRect, nStyle, lpszName, pParent->ChildPaneFromPos(nPos));
		} else {
			pT->Insert(lpRect, nStyle, lpszName, ChildPaneFromPos(nPos));
		}
		//return pPane;
	}

	void Remove(Pane* pP, BOOL bDestoryWindow = FALSE)
	{
		T* pT = static_cast<T*>(this);

		ASSERT(pP);

		pT->RemoveChilds(pP, bDestoryWindow);

		pT->OnCloseControl((HWND)pP, pP->GetXmlPaneName(), pP->GetName());

		if (*pP) {
			if (bDestoryWindow) {
				pP->DestroyWindow();
			}
			pP->Detach();
		}

		Base::Remove(pP);

		delete pP;
		pP = NULL;
	}

	void RemoveAll(BOOL bDestoryWindow = FALSE)
	{
		if (m_pP) {
			Remove(m_pP, bDestoryWindow);
		}
	}

	BOOL OnPaneCreate(HWND hwndCtrl)
	{
		T* pT = static_cast<T*>(this);
		Pane* pP = (Pane*)hwndCtrl;
		OnCreateControl(*pT, hwndCtrl, pP->GetXmlPaneName(), pP->GetName(), 0);
		return TRUE;
	}

	BOOL OnPaneClose(HWND hwndCtrl)
	{
		T* pT = static_cast<T*>(this);
		BOOL bHandled = FALSE;
		if (!hwndCtrl) {
			bHandled = TRUE;
		} else if (hwndCtrl == pT->m_hWnd) {
			bHandled = TRUE;
		} else if (hwndCtrl == (HWND)m_pP1) {
			//Pane* pParent = m_pP1->Parent();
			pT->Remove(m_pP1, TRUE);
			//节点整理
			/*while(pParent) 
			{
				Pane* pC = pParent->Child();
				if (!pC->Prev() && !pC->Next()) {
					pC->Free();			//先脱离节点
					pParent->Next(pC);	//插入上一级
					pParent->Free();	//脱离空节点
					if (pParent == m_pP) {
						m_pP = pC;
					}
					pT->Remove(pParent);//移除空节点
					pParent = pC;
				} else {
					break;
				}
				pParent = pParent->Parent();
			}*/
			bHandled = TRUE;
		} else {
			bHandled = Base::OnPaneClose(hwndCtrl);
		}
		return bHandled;
	}

	BEGIN_XML_CONTROL_MAP(This)
		XML_NAME_PANESPLITTER_HANDLER(Pane::GetXmlPaneName())
		//CHAIN_XML_CONTROL_AFTER_MAP(This)
	END_XML_CONTROL_MAP()

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
			Pane* pP = pT->PaneFromName(lpszCtrlName);
			ASSERT(pP);
			if (pP) {
				pP->m_hWnd = hWndCtrl;
			}
		}
	}

	void OnCloseControl(HWND hWndCtrl, LPCTSTR lpszWndClass, LPCTSTR lpszCtrlName)
	{
		//这里不关闭窗口
		ASSERT(hWndCtrl);
		if (!lpszCtrlName || !lpszCtrlName[0]) {
			return;
		}
		if (_tcsicmp(Pane::GetXmlPaneName(), lpszWndClass) == 0) {
			//PANE
			Pane* pP = (Pane*)hWndCtrl;
			if(pP->m_hWnd) {
				pP->m_hWnd = NULL;
				//pP->DestroyWindow();
			}
		} else {
			//HWND
			Pane* pP = PaneFromName(lpszCtrlName);
			if (pP) {
				pP->m_hWnd = NULL;
				//pP->DestroyWindow();
			}
		}
	}

	void InnerPaintP(HDC hdc, Pane* pP)
	{
		T* pT = static_cast<T*>(this);
		if (!pP->m_hWnd) {
			pT->PaintP(hdc, pP);
		}
		for (Pane* pC = pP->FirstChild(); pC; pC = pC->Next())
		{
			pT->PaintP(hdc, pC);
		}
	}

	void PaintP(HDC hdc)
	{
		if (hdc && m_pP) {
			InnerPaintP(hdc, m_pP);
		}
	}

	void PaintP(HDC hdc, Pane* pP)
	{
		long Style = pP->GetStyle();
		CString strName = pP->GetName();
		if(Style&PANEL_STYLE_RES) {
			RECT rcP;
			pP->GetRect(&rcP);
			UINT uFormat = 0;
			if (Style&PANEL_STYLE_RIGHT) {
				uFormat |= DT_RIGHT;
			} else if (Style&PANEL_STYLE_CENTER) {
				uFormat |= DT_CENTER;
			} else {
				uFormat |= DT_LEFT;
			}
			if (Style&PANEL_STYLE_BOTTOM) {
				uFormat |= DT_BOTTOM;
			} else if (Style&PANEL_STYLE_VCENTER) {
				uFormat |= DT_VCENTER;
			} else {
				uFormat |= DT_TOP;
			}
			UIgdi::DrawText(hdc, strName,strName.GetLength(),&rcP,uFormat);
		}
	}

	BEGIN_MSG_MAP_EX(This)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		pT->RemoveAll();
		return 0;
	}
};


#endif//_H_UIXPANE_H_