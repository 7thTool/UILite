
#pragma once

#ifndef _H_UIWND_H_
#define _H_UIWND_H_

#define BEGIN_BEFORE_MSG_MAP(theClass) \
public: \
	BOOL BeforeProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
	{ \
		BOOL bHandled = TRUE; \
		hWnd; \
		uMsg; \
		wParam; \
		lParam; \
		lResult; \
		bHandled; \
		switch(dwMsgMapID) \
		{ \
		case 0:

#define CHAIN_BEFORE_MSG_MAP(theChainClass) \
		{ \
			if(theChainClass::BeforeProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
				return TRUE; \
		}

#define END_BEFORE_MSG_MAP() \
	END_MSG_MAP()

#define BEGIN_AFTER_MSG_MAP(theClass) \
public: \
	BOOL AfterProcessWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID = 0) \
	{ \
		BOOL bHandled = TRUE; \
		hWnd; \
		uMsg; \
		wParam; \
		lParam; \
		lResult; \
		bHandled; \
		switch(dwMsgMapID) \
		{ \
		case 0:

#define CHAIN_AFTER_MSG_MAP(theChainClass) \
		{ \
			if(theChainClass::AfterProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
				return TRUE; \
		}

#define END_AFTER_MSG_MAP() \
	END_MSG_MAP()

#ifndef _AFX

#include <atlcom.h>
#include <atlhost.h>
#include <atlwin.h>
#include <atlctl.h>

#include <wtl/atlscrl.h>
#include <wtl/atlframe.h>
#include <wtl/atlctrls.h>
#include <wtl/atldlgs.h>
#include <wtl/atlctrlw.h>
#include <wtl/atlctrlx.h>
#include <wtl/atlsplit.h>

#include "UIApp.h"
#include "UIgdi.h"
#include <vector>

template<class T>
class UIPreTranslateMessageMap
{
	typedef UIPreTranslateMessageMap<T> This;
public:
	UIPreTranslateMessageMap()
	{
	}

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		return FALSE;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_FORWARDMSG, OnForwardMsg)
	END_MSG_MAP()

	LRESULT OnForwardMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->PreTranslateMessage((MSG*)lParam);
		return bHandled;
	}
};

template<class TBase>
class UIWndBase : public TBase
{
	typedef TBase Base;
public:
	UIWndBase(HWND hWnd = NULL) : Base(hWnd) { }

public:

	BOOL IsDirectUI() { return FALSE; }
	
	BOOL IsAutoDelete() { return FALSE; }

	BOOL IsWindowVisible(BOOL bDeep = FALSE)
	{
		if (bDeep) {
			ASSERT(m_hWnd);
			HWND hWnd = m_hWnd;
			do 
			{
				if (!::IsWindowVisible(hWnd))
					return FALSE;
			} while(hWnd = ::GetParent(hWnd));
			return TRUE;
		}
		return Base::IsWindowVisible();
	}

	BOOL SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SetLayeredWindowAttributes(m_hWnd, crKey, bAlpha, dwFlags);
	}

	BOOL GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetLayeredWindowAttributes(m_hWnd, pcrKey, pbAlpha, pdwFlags);
	}

	void SetAlpha(BYTE bAlpha)
	{
		DWORD dwExStyle = GetExStyle();
		if (!(dwExStyle & WS_EX_LAYERED)) 
			ModifyStyleEx(0, WS_EX_LAYERED);
		SetLayeredWindowAttributes(0, bAlpha, LWA_ALPHA);
	}

	void SetColorKey(COLORREF crKey)
	{
		DWORD dwExStyle = GetExStyle();
		if (!(dwExStyle & WS_EX_LAYERED))
			ModifyStyleEx(0, WS_EX_LAYERED);
		SetLayeredWindowAttributes(crKey, 0, LWA_COLORKEY);
	}

	void SetWindowZOrder(HWND hWndInsertAfter)
	{
		SetWindowPos(hWndInsertAfter, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOREPOSITION);
	}

	void GetWindowSize(LPSIZE lpSize)
	{
		ATLASSERT(lpSize);
		RECT rcWnd;
		GetWindowRect(&rcWnd);
		lpSize->cx = rcWnd.right - rcWnd.left;
		lpSize->cy = rcWnd.bottom - rcWnd.top;
	}

	SIZE GetWindowSize()
	{
		SIZE sz = {0};
		GetWindowSize(&sz);
		return sz;
	}

	void GetClientSize(LPSIZE lpSize)
	{
		ATLASSERT(lpSize);
		RECT rcClient;
		GetClientRect(&rcClient);
		lpSize->cx = rcClient.right;
		lpSize->cy = rcClient.bottom;
	}

	SIZE GetClientSize()
	{
		SIZE sz = {0};
		GetClientSize(&sz);
		return sz;
	}

	void SetWindowRect(LPCRECT lpRect, BOOL bRedraw = TRUE)
	{
		MoveWindow(lpRect, bRedraw);
	}

	void SetWindowSize(INT cx, INT cy)
	{
		SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOMOVE);
	}

	void SetWindowSize(SIZE sz)
	{
		SetWindowSize(sz.cx, sz.cy);
	}

	void SetClientRect(LPCRECT lpRect, BOOL bRedraw = TRUE)
	{
		RECT rcClient;
		GetClientRect(&rcClient);
		RECT rcNewClient = *lpRect;
		RECT rcWnd;
		GetWindowRect(&rcWnd);
		rcWnd.left += rcNewClient.left - rcClient.left;
		rcWnd.top += rcNewClient.top - rcClient.top;
		rcWnd.right += rcNewClient.right - rcClient.right;
		rcWnd.bottom += rcNewClient.bottom - rcClient.bottom;
		SetWindowRect(&rcWnd, bRedraw);
	}

	void SetClientSize(SIZE szNew)
	{
		SetClientSize(szNew.cx, szNew.cy);
	}

	void SetClientSize(int cxNew, int cyNew)
	{
		SIZE szClient;
		GetClientSize(&szClient);
		SIZE szWnd;
		GetWindowSize(&szWnd);
		szWnd.cx += cxNew - szClient.cx;
		szWnd.cy += cyNew - szClient.cy;
		SetWindowSize(szWnd);
	}

#if _MSC_VER<=1200
	int GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const throw()
#else
	int GetWindowText(_Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpszStringBuf, _In_ int nMaxCount) const throw()
#endif//
	{
		return Base::GetWindowText(lpszStringBuf, nMaxCount);
	}
	/*int GetWindowText(CString& strText) const
	{
		return Base::GetWindowText(strText);
	}*/
	int GetWindowText(CString& rString) const
	{
		ASSERT(::IsWindow(m_hWnd));
		int nLen = ::GetWindowTextLength(m_hWnd);
		::GetWindowText(m_hWnd, rString.GetBufferSetLength(nLen), nLen + 1);
		rString.ReleaseBuffer();
		return nLen;
	}
#ifdef _OLEAUTO_H_
	BOOL GetWindowText(BSTR* pbstrText) throw()
	{
		return Base::GetWindowText(pbstrText);
	}
	BOOL GetWindowText(BSTR& bstrText) throw()
	{
		return Base::GetWindowText(bstrText);
	}
#endif//

	HWND GetSafeHwnd() 
	{ 
		ATLASSERT(::IsWindow(m_hWnd));

		return m_hWnd; 
	}

	HWND GetTopWindow() const throw()
	{
		ATLASSERT(::IsWindow(m_hWnd));

		return ::GetTopWindow(m_hWnd);
	}

	HWND GetTopLevelParent() const throw()
	{
		ATLASSERT(::IsWindow(m_hWnd));

		HWND hWndParent = m_hWnd;
		HWND hWndTmp;
		while((hWndTmp = ::GetParent(hWndParent)) != NULL)
			hWndParent = hWndTmp;

		return hWndParent;
	}

	HWND GetTopLevelWindow() const throw()
	{
		ATLASSERT(::IsWindow(m_hWnd));

		HWND hWndParent;
		HWND hWndTmp = m_hWnd;

		do
		{
			hWndParent = hWndTmp;
			hWndTmp = (::GetWindowLong(hWndParent, GWL_STYLE) & WS_CHILD) ? ::GetParent(hWndParent) : ::GetWindow(hWndParent, GW_OWNER);
		}
		while(hWndTmp != NULL);

		return hWndParent;
	}

#if _MSC_VER<=1200
	UINT GetDlgItemText(int nID, LPTSTR lpStr, int nMaxCount) const throw()
#else
	UINT GetDlgItemText(_In_ int nID, _Out_z_cap_post_count_(nMaxCount, return + 1) LPTSTR lpStr, _In_ int nMaxCount) const throw()
#endif//
	{
		return ::GetDlgItemText(m_hWnd, nID, lpStr, nMaxCount);
	}

	/*UINT GetDlgItemText(int nID, CString& strText) const
	{
		return Base::GetDlgItemText(nID, strText);
	}*/
	int GetDlgItemText(int nID, CString& rString) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		HWND hItem = GetDlgItem(nID);
		if (hItem) {
#if 0
			int nLength;
			LPTSTR pszText;
			nLength = ::GetWindowTextLength(hItem);
			pszText = rString.GetBuffer(nLength + 1);
			nLength = ::GetWindowText(hItem, pszText, nLength + 1);
			rString.ReleaseBuffer(nLength);
			return nLength;
#else
			int nLen = ::GetWindowTextLength(hItem);
			::GetWindowText(hItem, rString.GetBufferSetLength(nLen), nLen + 1);
			rString.ReleaseBuffer();
			return nLen;
#endif//
		}
		return 0;
	}
#ifdef _OLEAUTO_H_
	BOOL GetDlgItemText(int nID, BSTR* pbstrText) const throw()
	{
		ATLASSERT(pbstrText);
		return Base::GetDlgItemText(nID, *pbstrText);
	}
	BOOL GetDlgItemText(int nID, BSTR& bstrText) const throw()
	{
		return Base::GetDlgItemText(nID, bstrText);
	}
#endif // _OLEAUTO_H_

	static BOOL PostMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		return ::PostMessage(hWnd, message, wParam, lParam);
	}

	BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::PostMessage(message,wParam,lParam);
	}

	LRESULT PostDlgItemMessage(int nID, UINT message, WPARAM wParam = 0, LPARAM lParam = 0) throw()
	{
		ATLASSERT(::IsWindow(m_hWnd));
		HWND hWnd = GetDlgItem(nID);
		if (hWnd) {
			return ::PostMessage(hWnd, message, wParam, lParam);
		}
		ATLASSERT(0);
		return 0L;
	}

	BOOL TrackMouseEvent(DWORD dwFalgs = TME_LEAVE)
	{
		TRACKMOUSEEVENT   tme = {0};     
		tme.cbSize = sizeof(TRACKMOUSEEVENT);     
		tme.dwFlags = dwFalgs;
		tme.hwndTrack = m_hWnd;  
		tme.dwHoverTime = 0;//HOVER_DEFAULT;
		return _TrackMouseEvent(&tme);
	}

	HWND Create(LPCTSTR lpstrWndClass, HWND hWndParent, _U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL) throw()
	{
#if _MSC_VER<=1200
		return Base::Create(lpstrWndClass, hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
#else
		return Base::Create(lpstrWndClass, hWndParent, rect, szWindowName, dwStyle, dwExStyle, MenuOrID, lpCreateParam);
#endif//
	}

	//LRESULT Create(LPVOID lpCreateParam, HWND hWndParent)
	//{//处理动态创建，和应用配置
	//	return 0;
	//}

	// Message Functions
	
	LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SendMessage(m_hWnd,message,wParam,lParam);
	}
	
	BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::PostMessage(m_hWnd,message,wParam,lParam);
	}
	
	BOOL SendNotifyMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::SendNotifyMessage(m_hWnd, message, wParam, lParam);
	}
	
	// support for C style macros
	static LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ATLASSERT(::IsWindow(hWnd));
		return ::SendMessage(hWnd, message, wParam, lParam);
	}

	HWND GetFocus() 
	{
		return ::GetFocus();
	}

	HWND SetFocus() 
	{
		return ::SetFocus(m_hWnd);
	}

	HWND GetHover()
	{
		POINT pt;
		GetCursorPos(&pt);
		return WindowFromPoint(pt);
	}

	//HWND SetCapture()

	HWND GetCapture()
	{
		return ::GetCapture();
	}
	
	BOOL ReleaseCapture()
	{
		return ::ReleaseCapture();
	}

	BOOL GetWindowInfo(PWINDOWINFO pwi)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetWindowInfo(m_hWnd, pwi);
	}

	BOOL GetTitleBarInfo(PTITLEBARINFO pti)
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetTitleBarInfo(m_hWnd, pti);
	}

	BOOL GetMenuBarInfo(LONG idObject, LONG idItem, PMENUBARINFO pmbi) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetMenuBarInfo(m_hWnd, idObject, idItem, pmbi);
	}

	BOOL GetScrollBarInfo(LONG idObject, PSCROLLBARINFO pScrollBarInfo) const
	{
		ATLASSERT(::IsWindow(m_hWnd));
		return ::GetScrollBarInfo(m_hWnd, idObject, pScrollBarInfo);
	}
};

typedef UIWndBase<ATL::CWindow> UIWnd;
typedef UIWndBase<ATL::CAxWindow> UIAxWnd;
#if _MSC_VER<=1200
#else
typedef UIWndBase<ATL::CAxWindow2> UIAxWnd2;
#endif//
typedef UIWndBase<WTL::CMDIWindow> UIMDIWnd;

//////////////////////////////////////////////////////////////////////////

template<class T>
class UIWndMap
{
	typedef UIWndMap<T> This;
public:

	//////////////////////////////////////////////////////////////////////////

	LRESULT Notify(HWND hWnd, int code)
	{
		T* pT = static_cast<T*>(this);
		NMHDR nmh = {0};
		nmh.hwndFrom = *pT;
		nmh.idFrom = pT->GetDlgCtrlID();
		nmh.code = code;
		return pT->Notify(hWnd, (LPNMHDR)&nmh);
	}

	LRESULT Notify(HWND hWnd, LPNMHDR lphdr)
	{
		T* pT = static_cast<T*>(this);
		return T::SendMessage(hWnd, WM_NOTIFY, (WPARAM)lphdr->code, (LPARAM)lphdr);
	}

	LRESULT NotifyCommand(HWND hWnd, int code)
	{
		T* pT = static_cast<T*>(this);
		return T::SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(code,pT->GetDlgCtrlID()), (LPARAM)(HWND)(*pT));
	}

	//////////////////////////////////////////////////////////////////////////

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnBeforeMouseMove)
	END_BEFORE_MSG_MAP()

	LRESULT OnBeforeMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		pT->TrackMouseEvent(TME_HOVER|TME_LEAVE);
		return bHandled;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_DPICHANGED,OnDpiChanged)
	END_MSG_MAP()

	LRESULT OnDpiChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		int dpi = LOWORD(wParam);  // Set the new DPI, retrieved from the wParam
		LPCRECT lprcWnd = (LPCRECT)lParam;
		pT->SetWindowPos(NULL, lprcWnd->left, lprcWnd->top, lprcWnd->right-lprcWnd->left, lprcWnd->bottom-lprcWnd->top, SWP_NOZORDER | SWP_NOACTIVATE);

		return bHandled;
	}

	BEGIN_AFTER_MSG_MAP(This)
		//
	END_AFTER_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = CControlWinTraits>
class UIWndImpl 
	: public CWindowImpl<T, TBase, TWinTraits>
	, public UIWndMap<T>
{
	typedef UIWndImpl<T, TBase, TWinTraits> This;
	typedef CWindowImpl<T, TBase, TWinTraits> Base;
	typedef UIWndMap<T> WndMap;
public:
	//DECLARE_WND_CLASS(_T("UIWnd"))

	UIWndImpl():Base()
	{
	}

	virtual WNDPROC GetWindowProc()
	{
		return WindowProc;
	}

	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lResBefore = 0, lRes = 0, lResAfter = 0;
		This* pThis = (This*)hWnd;
		ATLASSERT(pThis);
		T* pT = static_cast<T*>(pThis);
		ATLASSERT(pT);

		HWND hWndMyself = pT->m_hWnd;

		if(pT->BeforeProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lResBefore, 0)) {
			return lResBefore;
		}

		lRes = Base::WindowProc(hWnd, uMsg, wParam, lParam);

		if(uMsg != WM_NCDESTROY) {
			if(pT->AfterProcessWindowMessage(hWndMyself, uMsg, wParam, lParam, lResAfter, 0)) {
				return lResAfter;
			}
		}
		
		return lRes;
	}

	//Before Handle WM_CREATE function.
	BOOL PreInitWindow(CREATESTRUCT& cs)
	{
		return TRUE;
	}

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_NCCREATE, OnBeforeNcCreate)
		MESSAGE_HANDLER(WM_CREATE, OnBeforeCreate)
		CHAIN_BEFORE_MSG_MAP(WndMap)
	END_BEFORE_MSG_MAP()

	LRESULT OnBeforeNcCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		pT->SetWindowLongPtr(GWLP_USERDATA, reinterpret_cast<LONG>(pT));
		return 0L;
	}

	LRESULT OnBeforeCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(!pT->PreInitWindow(*(CREATESTRUCT*)lParam)) {
			pT->DefWindowProc(uMsg, wParam, lParam);
			pT->DestroyWindow();
			return FALSE;
		}
		bHandled = FALSE;
		return 0L;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(WndMap)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	BEGIN_AFTER_MSG_MAP(This)
		CHAIN_AFTER_MSG_MAP(WndMap)
	END_AFTER_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = ATL::CControlWinTraits>
class UIScrollWndImpl 
	: public WTL::CScrollWindowImpl<T, TBase, TWinTraits>
{
	typedef UIScrollWndImpl<T, TBase, TWinTraits> This;
	typedef WTL::CScrollWindowImpl<T, TBase, TWinTraits> Base;
public:
	UIScrollWndImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = ATL::CControlWinTraits>
class UIMapScrollWindowImpl 
	: public WTL::CMapScrollWindowImpl<T, TBase, TWinTraits>
{
	typedef UIMapScrollWindowImpl<T, TBase, TWinTraits> This;
	typedef WTL::CMapScrollWindowImpl<T, TBase, TWinTraits> Base;
public:
	UIMapScrollWindowImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = ATL::CControlWinTraits>
class UIZoomScrollWindowImpl 
	: public WTL::CZoomScrollWindowImpl<T, TBase, TWinTraits>
{
	typedef UIZoomScrollWindowImpl<T, TBase, TWinTraits> This;
	typedef WTL::CZoomScrollWindowImpl<T, TBase, TWinTraits> Base;
public:
	UIZoomScrollWindowImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = ATL::CControlWinTraits>
class UIScrollContainerImpl 
	: public WTL::CScrollContainerImpl<T, TBase, TWinTraits>
{
	typedef UIScrollContainerImpl<T, TBase, TWinTraits> This;
	typedef WTL::CScrollContainerImpl<T, TBase, TWinTraits> Base;
public:
	UIScrollContainerImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = ATL::CFrameWinTraits>
class UIFrameImpl 
	: public ATL::CWindowImpl<T, TBase, TWinTraits>
{
	typedef UIFrameImpl<T, TBase, TWinTraits> This;
	typedef ATL::CWindowImpl<T, TBase, TWinTraits> Base;
public:
	UIFrameImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase = UIWnd, class TWinTraits = ATL::CFrameWinTraits>
class UISDIFrameImpl : public WTL::CFrameWindowImpl<T, TBase, TWinTraits>
{
	typedef UISDIFrameImpl<T, TBase, TWinTraits> This;
	typedef WTL::CFrameWindowImpl<T, TBase, TWinTraits> Base;
public:
	UISDIFrameImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Base)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase  = UIMDIWnd, class TWinTraits = ATL::CFrameWinTraits>
class UIMDIFrameImpl : public WTL::CMDIFrameWindowImpl<T, TBase, TWinTraits>
{
	typedef UIMDIFrameImpl<T, TBase, TWinTraits> This;
	typedef WTL::CMDIFrameWindowImpl<T, TBase, TWinTraits> Base;
public:
	UIMDIFrameImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Base)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase  = UIMDIWnd, class TWinTraits = ATL::CMDIChildWinTraits>
class UIMDIChildFrameImpl : public WTL::CMDIChildWindowImpl<T, TBase, TWinTraits>
{
	typedef UIMDIChildFrameImpl<T, TBase, TWinTraits> This;
	typedef WTL::CMDIChildWindowImpl<T, TBase, TWinTraits> Base;
public:
	UIMDIChildFrameImpl():Base()
	{
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(Base)
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()
};

template <class T, class TBase = UIWnd>
class UIDialogImpl : public ATL::CDialogImpl<T, TBase>
{
	typedef UIDialogImpl<T, TBase> This;
	typedef ATL::CDialogImpl<T, TBase> Base;
public:
#ifndef _DEBUG
	bool m_bModal;
	UIDialogImpl() : m_bModal(false), Base() { }
#else
	UIDialogImpl() : Base() { }
#endif //_DEBUG

#ifndef _DEBUG
	// modal dialogs
	INT_PTR DoModal(HWND hWndParent = ::GetActiveWindow(), LPARAM dwInitParam = NULL)
	{
		m_bModal = true;
		INT_PTR nRet = Base::DoModal(hWndParent, dwInitParam);
		m_bModal = false;
		return nRet;
	}
	// modeless dialogs
	HWND Create(HWND hWndParent, LPARAM dwInitParam = NULL)
	{
		m_bModal = false;
		return Base::Create(hWndParent, dwInitParam);
	}
	// for CComControl
	HWND Create(HWND hWndParent, RECT&, LPARAM dwInitParam = NULL)
	{
		return Create(hWndParent, dwInitParam);
	}
#endif//

	void OnOK()
	{
		T* pT = static_cast<T*>(this);
		if (m_bModal) {
			pT->EndDialog(IDOK);
		} else {
			pT->DestroyWindow();
		}
	}
	
	void OnCancel()
	{
		T* pT = static_cast<T*>(this);
		if (m_bModal) {
			pT->EndDialog(IDCANCEL);
		} else {
			pT->DestroyWindow();
		}
	}

	BEGIN_MSG_MAP(This)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		//CHAIN_MSG_MAP(Base) 不能调用
		//REFLECT_NOTIFICATIONS()
	END_MSG_MAP()

	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		pT->OnOK();
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		T* pT = static_cast<T*>(this);
		pT->OnCancel();
		return 0;
	}
};

template<class TBase>
class UIWndSuperT : public TBase
{
protected:
	DWORD m_bAutoDelete:1;
public:
	UIWndSuperT():m_bAutoDelete(0) {}

	BOOL SetAutoDelete(BOOL bAutoDelete = TRUE) { m_bAutoDelete = bAutoDelete; }

	BOOL IsAutoDelete() { return m_bAutoDelete; }

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		if (m_bAutoDelete) {
			delete this;
		}
	}
};

/*
DlgResize_Init - warning: top level dialog without the WS_THICKFRAME style - user cannot resize it
DLGRESIZE_CONTROL(ControlID, Flags)
ControlID就是控件的ID了,Flags有如下几个值:
DLSZ_SIZE_X: Resize the width of the control as the dialog resizes horizontally. 
DLSZ_SIZE_Y: Resize the height of the control as the dialog resizes vertically. 
DLSZ_MOVE_X: Move the control horizontally as the dialog resizes horizontally. 
DLSZ_MOVE_Y: Move the control vertically as the dialog resizes vertically. 
DLSZ_REPAINT: Invalidate the control after every move/resize so it repaints every time. 
			  Note that you cannot move and size a control in the same dimension. If you specify, say DLSZ_MOVE_X and DLSZ_SIZE_X together, the size flag is ignored.
			  You can also group controls together so that they move and size proportionally to each other. I will cover this subject later.
示例如下:
			 BEGIN_DLGRESIZE_MAP(CTabProcessView)
				 DLGRESIZE_CONTROL( IDC_PROCESS_TREE, DLSZ_SIZE_X | DLSZ_SIZE_Y)
			 END_DLGRESIZE_MAP()
*/
template <class T>
class UIDialogResize : public WTL::CDialogResize<T>
{
public:
};

template <class T, class TBase = UIWnd>
class UIDialogResizeImpl
	: public UIDialogImpl<T, TBase>
	, public UIDialogResize<T>
{
	typedef UIDialogResizeImpl<T, TBase> This;
	typedef UIDialogImpl<T, TBase> Base;
public:
	UIDialogResizeImpl():Base()
	{
	}
	BEGIN_MSG_MAP(This)
//		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		CHAIN_MSG_MAP(UIDialogResize<T>)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

// 	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
// 	{
// 		bHandled = FALSE;
// 		DlgResize_Init();
// 
// 		return bHandled;
// 	}
};

#else

#include "UIgdi.h"
#include <vector>

typedef CWnd UIWnd;
typedef CDialog UIDialog;

template<class T>
class UIWndMap
{
	typedef UIWndMap<T> This;
public:

	BOOL IsDirectUI() { return FALSE; }

	BOOL TrackMouseEvent(DWORD dwFalgs = TME_LEAVE)
	{
		T* pT = static_cast<T*>(this);
		TRACKMOUSEEVENT   tme = {0};     
		tme.cbSize = sizeof(TRACKMOUSEEVENT);     
		tme.dwFlags = dwFalgs;
		tme.hwndTrack = pT->m_hWnd;  
		tme.dwHoverTime = 0;//HOVER_DEFAULT;
		return _TrackMouseEvent(&tme);
	}

	BOOL ReleaseCapture()
	{
		return ::ReleaseCapture();
	}


	//////////////////////////////////////////////////////////////////////////
	
	LRESULT Notify(UIWnd* pWnd, int code)
	{
		T* pT = static_cast<T*>(this);
		NMHDR nmh = {0};
		nmh.hwndFrom = *pT;
		nmh.idFrom = pT->GetDlgCtrlID();
		nmh.code = code;
		return pT->Notify(pWnd, (LPNMHDR)&nmh);
	}

	LRESULT Notify(UIWnd* pWnd, LPNMHDR lphdr)
	{
		T* pT = static_cast<T*>(this);
		return T::SendMessage(pWnd->GetSafeHwnd(), WM_NOTIFY, (WPARAM)lphdr->code, (LPARAM)lphdr);
	}

	LRESULT NotifyCommand(UIWnd* pWnd, int code)
	{
		T* pT = static_cast<T*>(this);
		return T::SendMessage(pWnd->GetSafeHwnd(), WM_COMMAND, MAKEWPARAM(code,pT->GetDlgCtrlID()), (LPARAM)(HWND)(*pT));
	}

	//////////////////////////////////////////////////////////////////////////

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_MOUSEMOVE,OnBeforeMouseMove)
	END_BEFORE_MSG_MAP()

	LRESULT OnBeforeMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		T* pT = static_cast<T*>(this);
		pT->TrackMouseEvent(TME_HOVER|TME_LEAVE);
		return bHandled;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_DPICHANGED,OnDpiChanged)
	END_MSG_MAP()

	LRESULT OnDpiChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		int dpi = LOWORD(wParam);  // Set the new DPI, retrieved from the wParam
		LPCRECT lprcWnd = (LPCRECT)lParam;
		pT->SetWindowPos(NULL, lprcWnd->left, lprcWnd->top, lprcWnd->right-lprcWnd->left, lprcWnd->bottom-lprcWnd->top, SWP_NOZORDER | SWP_NOACTIVATE);

		return bHandled;
	}

	BEGIN_AFTER_MSG_MAP(This)
		//
	END_AFTER_MSG_MAP()
};

template<class T, class TBase = UIWnd>
class UIWndImpl : public TBase, public UIWndMap<T>
{
	typedef UIWndImpl<T,TBase> This;
	typedef TBase Base;
	typedef UIWndMap<T> WndMap;
public:
	UIWndImpl(HWND hWnd = NULL):Base() { m_hWnd = hWnd; }

	LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::SendMessage(message,wParam,lParam);
	}

	BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::PostMessage(message,wParam,lParam);
	}

	BOOL SendNotifyMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::SendNotifyMessage(message, wParam, lParam);
	}

	// support for C style macros
	static LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(::IsWindow(hWnd));
		return ::SendMessage(hWnd, message, wParam, lParam);
	}

	static LRESULT PostMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(::IsWindow(hWnd));
		return ::PostMessage(hWnd, message, wParam, lParam);
	}

	static LRESULT SendNotifyMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(::IsWindow(hWnd));
		return ::SendNotifyMessage(hWnd, message, wParam, lParam);
	}

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lResult = 0L;

		LRESULT lResBefore = 0L;
		if(pT->BeforeProcessWindowMessage(m_hWnd, message, wParam, lParam, lResBefore, 0)) {
			return lResBefore;
		}

		if(pT->ProcessWindowMessage(m_hWnd, message, wParam, lParam, lResult)) {
			return lResult;
		}
		lResult = Base::WindowProc(message, wParam, lParam);

		if(message != WM_NCDESTROY) {
			LRESULT lResAfter = 0L;
			if(pT->AfterProcessWindowMessage(m_hWnd, message, wParam, lParam, lResAfter, 0)) {
				return lResAfter;
			}
		} else {
			pT->OnFinalMessage(NULL);
		}
		
		return lResult;
	}

	//Pre Handle WM_CREATE function.
	BOOL PreInitWindow(CREATESTRUCT& cs)
	{
		return TRUE;
	}

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnBeforeCreate)
		CHAIN_BEFORE_MSG_MAP(WndMap)
	END_BEFORE_MSG_MAP()

	LRESULT OnBeforeCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(!pT->PreInitWindow(*(CREATESTRUCT*)lParam)) {
			pT->DefWindowProc(uMsg, wParam, lParam);
			pT->DestroyWindow();
			return FALSE;
		}
		bHandled = FALSE;
		return 0L;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(WndMap)
	END_MSG_MAP()

	BEGIN_AFTER_MSG_MAP(This)
		CHAIN_AFTER_MSG_MAP(WndMap)
	END_AFTER_MSG_MAP()

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		//
	}
};

template<class T, class TBase = UIDialog>
class UIDialogImpl : public TBase, public UIWndMap<T>
{
	typedef UIDialogImpl<T,TBase> This;
	typedef TBase Base;
	typedef UIWndMap<T> WndMap;
public:
	UIDialogImpl(HWND hWnd = NULL):Base() { m_hWnd = hWnd; }
	explicit UIDialogImpl(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL):Base(lpszTemplateName,pParentWnd) {}
	explicit UIDialogImpl(UINT nIDTemplate, CWnd* pParentWnd = NULL):Base(nIDTemplate,pParentWnd) {}

	LRESULT SendMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::SendMessage(message,wParam,lParam);
	}

	BOOL PostMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::PostMessage(message,wParam,lParam);
	}

	BOOL SendNotifyMessage(UINT message, WPARAM wParam = 0, LPARAM lParam = 0)
	{
		return Base::SendNotifyMessage(m_hWnd, message, wParam, lParam);
	}

	// support for C style macros
	static LRESULT SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(::IsWindow(hWnd));
		return ::SendMessage(hWnd, message, wParam, lParam);
	}

	static LRESULT PostMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(::IsWindow(hWnd));
		return ::PostMessage(hWnd, message, wParam, lParam);
	}

	static LRESULT SendNotifyMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		ASSERT(::IsWindow(hWnd));
		return ::SendNotifyMessage(hWnd, message, wParam, lParam);
	}

	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lResult = 0L;

		LRESULT lResBefore = 0L;
		if(pT->BeforeProcessWindowMessage(m_hWnd, message, wParam, lParam, lResBefore, 0)) {
			return lResBefore;
		}

		if(pT->ProcessWindowMessage(m_hWnd, message, wParam, lParam, lResult)) {
			return lResult;
		}
		lResult = Base::WindowProc(message, wParam, lParam);

		if(message != WM_NCDESTROY) {
			LRESULT lResAfter = 0L;
			if(pT->AfterProcessWindowMessage(m_hWnd, message, wParam, lParam, lResAfter, 0)) {
				return lResAfter;
			}
		} else {
			pT->OnFinalMessage(NULL);
		}

		return lResult;
	}

	//Pre Handle WM_CREATE function.
	BOOL PreInitWindow(CREATESTRUCT& cs)
	{
		return TRUE;
	}

	BEGIN_BEFORE_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnBeforeCreate)
		CHAIN_BEFORE_MSG_MAP(WndMap)
	END_BEFORE_MSG_MAP()

	LRESULT OnBeforeCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(!pT->PreInitWindow(*(CREATESTRUCT*)lParam)) {
			pT->DefWindowProc(uMsg, wParam, lParam);
			pT->OnCancel();
			return FALSE;
		}
		bHandled = FALSE;
		return 0L;
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(WndMap)
	END_MSG_MAP()

	BEGIN_AFTER_MSG_MAP(This)
		CHAIN_AFTER_MSG_MAP(WndMap)
	END_AFTER_MSG_MAP()

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		//
	}
};

#endif//_AFX

template<class T>
class UIEnableMove
{
	typedef UIEnableMove<T> This;
protected:
	BOOL m_bMove;

public:
	UIEnableMove()
	{
		m_bMove = FALSE;
	}

	void EnableMove(BOOL bMove = TRUE)
	{
		m_bMove = bMove;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
	END_MSG_MAP()
	
	LRESULT OnLButtonDown(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (m_bMove) {
			//禁止显示移动矩形窗体框
			::SystemParametersInfo(SPI_SETDRAGFULLWINDOWS,TRUE,NULL,0);
			//非标题栏移动整个窗口
			/*SendMessage(WM_SYSCOMMAND,0xF012,0);
			if (border.IsInuse())
			border.SendMessage(WM_SYSCOMMAND,0xF012,0);*/
			pT->PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, lParam);
		} else {
			bHandled = FALSE;
		}
		return 0;
	}
};

//////////////////////////////////////////////////////////////////////////

/*template<class T>
class UIBkgnd
{
protected:
	enum 
	{
		UI_BK_STYLE_COLOR				= 0,
		UI_BK_STYLE_STRETCH, 
		UI_BK_STYLE_TITLE, 
		UI_BK_STYLE_CENTER,
		UI_BK_STYLE_MASK				= 0X0000000F,
		UI_BK_STYLE_HORIZONTAL	= 0X00000010,
		UI_BK_EFFECT_ALPHA_VERT		= 0X00000020,
		UI_BK_EFFECT_MASK				= 0X0000FFF0,
		UI_BK_VALUE_MASK				= 0XFFFF0000,
	};
	UINT		m_bgFlags;
	COLORREF	m_bgColor;
	Image*		m_bgImage;
public:
	UIBkgnd() : m_bgImage(0), m_bgFlags(0), m_bgColor(CLR_INVALID)
	{

	}
	~UIBkgnd() 
	{
		m_bgImage = NULL;
		//m_bgFlags = UI_BK_STYLE_COLOR;
	}

	void SetBgColor(COLORREF crBg)
	{
		m_bgColor = crBg;
	}

	void SetBgImage(COLORREF crBg)
	{
		m_bgFlags = UI_BK_STYLE_COLOR;
		SetBgColor(crBg);
	}

	void SetBgImage(Image* pImage, UINT bgFlags = UI_BK_STYLE_STRETCH)
	{
		m_bgImage = pImage;
		m_bgFlags = bgFlags;
	}

	COLORREF GetBgColor()
	{ 
		return m_bgColor;
	}

	Image* GetBgImage() 
	{ 
		return m_bgImage;
	}

	UINT GetBgFlags()
	{
		return m_bgFlags;
	}

	BOOL PaintBkgnd(HDC hdc)
	{
		T* pT = static_cast<T*>(this);

		DWORD dwExStyle = pT->GetExStyle();
		UINT uBgFlags = pT->GetBgFlags();
		DWORD bgStyle = uBgFlags & UI_BK_STYLE_MASK;
		DWORD bgEffect = uBgFlags & UI_BK_EFFECT_MASK;

		CRect rcClient;
		pT->GetClientRect(&rcClient);

		//CDCHandle dc(hdc);
		CMemDC MemDC(hdc, &rcClient);

		// 填充背景颜色
		COLORREF color;
		if (dwExStyle & WS_EX_LAYERED) {
			DWORD dwFlag = 0;
			COLORREF crKey = CLR_INVALID;
			pT->GetLayeredWindowAttributes(&crKey, NULL, &dwFlag);
			if (dwFlag & LWA_COLORKEY) {
				color = crKey;
			}
		} else {
			color = pT->GetBgColor();
		}
		if(color != CLR_INVALID) {
			MemDC.FillSolidRect(&rcClient, color);
		}

		// 画背景图片
		if (bgStyle) {
			Image* pImage = pT->GetBgImage();
			if (pImage) {
				Graphics graphics(MemDC);
				// 反锯齿
				graphics.SetSmoothingMode(SmoothingModeHighQuality);
				//
				pImage = pImage->Clone();
				switch(bgStyle)
				{
				case UI_BK_STYLE_COLOR:
					break;
				case UI_BK_STYLE_STRETCH:
					{
						graphics.DrawImage(pImage, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height());
					}
					break;
				case UI_BK_STYLE_CENTER:
					{
						int nWidth = rcClient.Width(), nHeight = rcClient.Height();
						int nBgWidth = pImage->GetWidth(), nBgHeight = pImage->GetHeight();
						int x = (nWidth - nBgWidth) / 2, y = (nHeight - nBgHeight) / 2;
						graphics.DrawImage(pImage, x > 0 ? x : 0, y > 0 ? y : 0, x < 0 ? -x : 0, y < 0 ? -y : 0, nBgWidth, nBgHeight, UnitPixel);
					}
					break;
				case UI_BK_STYLE_TITLE:
					{
						int ixOrg = 0, iyOrg = 0;
						UINT nWidth = pImage->GetWidth(), nHeight = pImage->GetHeight();
						for (iyOrg = 0; iyOrg < rcClient.Height(); iyOrg += nHeight)
						{
							for (ixOrg = 0; ixOrg < rcClient.Width(); ixOrg += nWidth)
							{
								graphics.DrawImage(pImage, ixOrg, iyOrg, 0, 0, pImage->GetWidth(), pImage->GetHeight(), UnitPixel);
							}
						}
					}
					break;
				}
				delete pImage;
				//
				graphics.ReleaseHDC(MemDC);

				//特效处理
				if (bgEffect & (UI_BK_STYLE_HORIZONTAL|UI_BK_EFFECT_ALPHA_VERT)) {
					UIgdi::FillSolidRect(hdc, &rcClient, UIgdi::AverageColorFromDC(MemDC)); 

					UIgdi::AlphaBlendTransition(hdc, rcClient.left, rcClient.top, rcClient.right-rcClient.left, rcClient.bottom-rcClient.top
						, MemDC, rcClient.left, rcClient.top, FALSE);

					MemDC.DeleteDC();
				}
			}
		}
		
		return TRUE;
	}
};*/

template<class T>
class UIPaint
{
	typedef UIPaint<T> This;
public:
	HDC GetHDC()
	{
		return NULL;
	}

	BOOL RefreshWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
	{
		T* pT = static_cast<T*>(this);
#ifndef _AFX
		return pT->RedrawWindow(lpRectUpdate, hRgnUpdate, flags);
#else
		return pT->RedrawWindow(lpRectUpdate, CRgn::FromHandle(hRgnUpdate), flags);
#endif//
	}

	BOOL OnEraseBkgnd(HDC hdc)
	{
		return FALSE;
	}

	void Paint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		::DefWindowProc((HWND)*pT, WM_PAINT, (WPARAM)hdc, (LPARAM)0L);
	}

	void OnPaint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		pT->Paint(hdc);
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_PRINTCLIENT, OnPaint)
	END_MSG_MAP()

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->OnEraseBkgnd((HDC)wParam);
		return TRUE;
	}

	LRESULT OnPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		HDC hdc = (HDC)wParam;
		if (hdc) {
			pT->OnPaint(hdc);
		} else {
			PAINTSTRUCT PaintS = {0};
			hdc = 
#ifndef _AFX
				pT->BeginPaint(&PaintS);
#else
				pT->BeginPaint(&PaintS)->GetSafeHdc();
#endif//
			pT->OnPaint(hdc);
			pT->EndPaint(&PaintS);
		}
		return 0;
	}
};

template<class T>
class UIEraseBkgnd// : public UIBkgnd<T>
{
	typedef UIEraseBkgnd<T> This;
public:
	HDC GetHDC()
	{
		return NULL;
	}

	BOOL RefreshWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
	{
		T* pT = static_cast<T*>(this);
#ifndef _AFX
		return pT->RedrawWindow(lpRectUpdate, hRgnUpdate, flags);
#else
		return pT->RedrawWindow(lpRectUpdate, CRgn::FromHandle(hRgnUpdate), flags);
#endif//
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_ERASEBKGND, OnEraseBkgnd)
	END_MSG_MAP()

	LRESULT OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->OnEraseBkgnd((HDC)wParam);
		return TRUE;
	}

	BOOL OnEraseBkgnd(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		return pT->EraseBkgnd(hdc);
	}

	BOOL EraseBkgnd(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		return FALSE;//pT->PaintBkgnd(hdc);
	}
};

template<class T>
class UIEraseBkgndF : public UIEraseBkgnd<T>
{
	typedef UIEraseBkgndF<T> This;
	typedef UIEraseBkgnd<T> Base;
protected:
	BOOL m_bEraseBkgnd;
	WTL::CMemDC m_DC;

public:
	UIEraseBkgndF() : m_bEraseBkgnd(FALSE) { }

	HDC GetHDC()
	{
		return m_DC;
	}

	WTL::CMemDCHandle GetDCHandle()
	{
		return m_DC;
	}

	BOOL RefreshWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW)
	{
		T* pT = static_cast<T*>(this);
		if (flags & RDW_ERASE) {
			m_bEraseBkgnd = TRUE;
		} else {
			flags |= RDW_ERASE;
		}
#ifndef _AFX
		return pT->RedrawWindow(lpRectUpdate, hRgnUpdate, flags);
#else
		return pT->RedrawWindow(lpRectUpdate, CRgn::FromHandle(hRgnUpdate), flags);
#endif//
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_SIZE,OnSize)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnSize(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			m_DC.DeleteDC();
		}
		return 0;
	}

	BOOL OnEraseBkgnd(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		CRect rcClient;
		pT->GetClientRect(&rcClient);
		if (!m_DC) {
			m_DC.CreateCompatibleDC(hdc, &rcClient);
			m_bEraseBkgnd = TRUE;
		}
		if (m_bEraseBkgnd) {
			pT->EraseBkgnd(m_DC);
			m_bEraseBkgnd = FALSE;
		}
		::BitBlt(hdc, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), m_DC, 0, 0, SRCCOPY);
		return TRUE;
	}

	/*BOOL EraseBkgnd(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
	}*/
};

template<class T>
class UIPaintF : public UIPaint<T>
{
	typedef UIPaintF<T> This;
	typedef UIPaint<T> Base;
protected:
	WTL::CMemDC m_DC;
public:
	HDC GetHDC()
	{
		return m_DC;
	}

	WTL::CMemDCHandle GetDCHandle()
	{
		return m_DC;
	}

	BOOL RefreshWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE)
	{
		T* pT = static_cast<T*>(this);
#ifndef _AFX
		return pT->RedrawWindow(lpRectUpdate, hRgnUpdate, flags);
#else
		return pT->RedrawWindow(lpRectUpdate, CRgn::FromHandle(hRgnUpdate), flags);
#endif//
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_SIZE,OnSize)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnSize(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			m_DC.DeleteDC();
		}
		return 0;
	}

	BOOL OnEraseBkgnd(HDC hdc)
	{
		return TRUE;
	}

	void OnPaint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		CRect rcClient;
		pT->GetClientRect(&rcClient);
		PAINTSTRUCT PaintS = {0};
#ifndef _AFX
		WTL::CDCHandle dc(hdc);
		if (!hdc) {
			dc = pT->BeginPaint(&PaintS);
		}
	
		if (!m_DC) 
			m_DC.CreateCompatibleDC(dc, &rcClient);
		pT->Paint(m_DC);
		dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), m_DC, 0, 0, SRCCOPY);
#else
		CDC* pDC = NULL;
		if(hdc) {
			pDC = CDC::FromHandle(hdc);
		} else {
			pDC = pT->BeginPaint(&PaintS);
		}

		if (!m_DC) 
			m_DC.CreateCompatibleDC(pDC->GetSafeHdc(), &rcClient);
		pT->Paint(m_DC);
		::BitBlt(pDC->GetSafeHdc(), rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), m_DC, 0, 0, SRCCOPY);
#endif//
		if (!hdc) {
			pT->EndPaint(&PaintS);
		}
	}

	/*void Paint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
	}*/
};

template<class T>
class UIPaintFF : public UIPaintF<T>, public UIEraseBkgndF<T>
{
	typedef UIPaintFF<T> This;
public:

	HDC GetHDC(BOOL bBkDC = FALSE)
	{
		return bBkDC ? UIEraseBkgndF::m_DC : UIPaintF::m_DC;
	}

	WTL::CMemDCHandle GetDCHandle(BOOL bBkDC = FALSE)
	{
		return bBkDC ? UIEraseBkgndF::m_DC : UIPaintF::m_DC;
	}

	BOOL RefreshWindow(LPCRECT lpRectUpdate = NULL, HRGN hRgnUpdate = NULL, UINT flags = RDW_INVALIDATE | RDW_UPDATENOW)
	{
		T* pT = static_cast<T*>(this);
		if (flags & RDW_ERASE) {
			UIEraseBkgndF::m_bEraseBkgnd = TRUE;
			flags &= ~RDW_ERASE;
		}
#ifndef _AFX
		return pT->RedrawWindow(lpRectUpdate, hRgnUpdate, flags);
#else
		return pT->RedrawWindow(lpRectUpdate, CRgn::FromHandle(hRgnUpdate), flags);
#endif//
	}

	BEGIN_MSG_MAP(This)
		CHAIN_MSG_MAP(UIPaintF<T>)
		CHAIN_MSG_MAP(UIEraseBkgndF<T>)
	END_MSG_MAP()

	BOOL OnEraseBkgnd(HDC hdc)
	{
		return TRUE;
	}

	void OnPaint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		WTL::CDCHandle dc(hdc);
		PAINTSTRUCT PaintS = {0};
		if (!hdc) {
			hdc = 
#ifndef _AFX
				pT->BeginPaint(&PaintS);
#else
				pT->BeginPaint(&PaintS)->GetSafeHdc();
#endif//
		}

		CRect rcClient;
		pT->GetClientRect(&rcClient);
		if (!UIPaintF::m_DC) 
			UIPaintF::m_DC.CreateCompatibleDC(dc, &rcClient);

		if (!UIEraseBkgndF::m_DC) {
			UIEraseBkgndF::m_DC.CreateCompatibleDC(dc, &rcClient);
			UIEraseBkgndF::m_bEraseBkgnd = TRUE;
		}
		if (UIEraseBkgndF::m_bEraseBkgnd) {
			pT->EraseBkgnd(UIEraseBkgndF::m_DC);
			UIEraseBkgndF::m_bEraseBkgnd = FALSE;
		}
		UIPaintF::m_DC.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), UIEraseBkgndF::m_DC, 0, 0, SRCCOPY);

		pT->Paint(UIPaintF::m_DC);

		dc.BitBlt(rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), UIPaintF::m_DC, 0, 0, SRCCOPY);

		if (!hdc) {
			pT->EndPaint(&PaintS);
		}
	}
};

/*enum
{
	PAINT_EFFECT_NONE = 0,
	PAINT_EFFECT_BLEND,
	//PAINT_EFFECT_
};

template<class T>
class UIPaintEffect : public UIPaintF<T>
{
	typedef UIPaintEffect<T> This;
	typedef UIPaintF<T> Base;
protected:
	HMEMDC m_hEffectDC;		// 特效DC
	WORD m_EffectType;		//0 表示没有特效
	BYTE m_EffectTime;		//特效次数
	BYTE m_NowEffectTime;	//现在特效的次数
public:
	UIPaintEffect() : m_EffectType(0), m_EffectTime(0), m_NowEffectTime(0) {}

	void StartEffect(WORD EffectType = PAINT_EFFECT_BLEND, BYTE EffectTime = 3)
	{
		m_EffectType = EffectType;
		m_EffectTime = EffectTime;
		m_NowEffectTime = 0;
	}

	void StopEffect()
	{
		m_EffectType = 0;
		m_EffectTime = 0;
		m_NowEffectTime = 0;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_SIZE,OnSize)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnSize(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			m_hEffectDC.DeleteDC();
		}
		return bHandled;
	}

	void OnPaint(HDC hdc)
	{
		T* pT = static_cast<T*>(this);
		CRect rcClient;
		pT->GetClientRect(&rcClient);
		if (!m_EffectType || !m_EffectTime || !m_NowEffectTime) {
			//完整绘制
			if (!m_hDC) {
				m_hDC.CreateCompatibleDC(hdc, rcClient.Width(), rcClient.Height());
			} 
			if (!m_hEffectDC) {
				m_hEffectDC.CreateCompatibleDC(hdc, rcClient.Width(), rcClient.Height());
			}
			::BitBlt(m_hEffectDC, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(), m_hDC, 0, 0, SRCCOPY);
			pT->Paint(m_hDC);
		} else {
			//特效绘制
			switch (m_EffectType)
			{
			case PAINT_EFFECT_BLEND:
			default:
				AlphaBlend((m_NowEffectTime * 255) / m_EffectTime);
			}
			
			m_NowEffectTime++;

			if (m_NowEffectTime >= m_EffectTime) {
				StopEffect();
			} else {
				pT->Invalidate(FALSE);
				::BitBlt(hdc, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
					m_hEffectDC, 0, 0, SRCCOPY);
				return;
			}
		}
		::BitBlt(hdc, rcClient.left, rcClient.top, rcClient.Width(), rcClient.Height(),
			m_hDC, 0, 0, SRCCOPY);
	}

	void AlphaBlend(BYTE Alpha)
	{
		T* pT = static_cast<T*>(this);
		CRect rcClient;
		pT->GetClientRect(&rcClient);

		BLENDFUNCTION bf = {0};
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = Alpha;
		::AlphaBlend(m_hEffectDC, 0, 0, rcClient.Width(), rcClient.Height(),
			m_hDC, 0, 0, rcClient.Width(), rcClient.Height(), bf);
	}
};*/

template<class T>
class UINcPaintF
{
	typedef UINcPaintF<T> This;
protected:
	enum HTBSTATE { Normal = 0, Hover, Pushed, Disabled};
	typedef struct tagHTButton
	{
		INT			Id;		//HTMINBUTTON HTMAXBUTTON HTCLOSE,,,
		INT			Command;//SC_CLOSE
		UINT		Type;
		INT			Part;
		BYTE		State;
		DWORD_PTR	Data;
		RECT		rc;
	}HTBUTTON,*PHTBUTTON,*LPHTBUTTON;
	typedef std::vector<HTBUTTON> HTBUTTONARRAY;
	HTBUTTONARRAY m_NcButtons;
	WTL::CMemDC m_NcDC;
public:
	WTL::CMemDCHandle GetNcDCHandle()
	{
		return m_NcDC;
	}

	BOOL AddNcButton(HTBUTTON& button) 
	{
		m_NcButtons.push_back(button);
		return TRUE;
	}
	BOOL RemoveNcButton(HTBUTTON& button)
	{
		for (size_t i=0,j=m_NcButtons.size(); i<j; ++i)
		{
			if (m_NcButtons[i].Id==button.Id && m_NcButtons[i].Command==button.Command) {
				m_NcButtons.erase(m_NcButtons.begin()+i);
				return TRUE;
			}
		}
		return FALSE;
	}
	BOOL GetNcButton(HTBUTTON& button)
	{
		for (size_t i=0,j=m_NcButtons.size(); i<j; ++i)
		{
			if (m_NcButtons[i].Id==button.Id && m_NcButtons[i].Command==button.Command) {
				button = m_NcButtons[i];
				return TRUE;
			}
		}
		return FALSE;
	}
	BOOL SetNcButton(HTBUTTON& button)
	{
		for (size_t i=0,j=m_NcButtons.size(); i<j; ++i)
		{
			if (m_NcButtons[i].Id==button.Id && m_NcButtons[i].Command==button.Command) {
				m_NcButtons[i] = button;
				return TRUE;
			}
		}
		return FALSE;
	}
	
	BEGIN_MSG_MAP_EX(This)
		MESSAGE_HANDLER(WM_NCCREATE,OnNcCreate)
		//MSG_WM_ERASEBKGND(OnEraseBkgnd)
		MESSAGE_HANDLER(WM_SIZE,OnSize)
		MESSAGE_HANDLER(WM_NCPAINT,OnNcPaint)
		MESSAGE_HANDLER(WM_NCACTIVATE,OnNcActivate)
//case 0x00AE://WM_NCUAHDRAWCAPTION
//case 0x00AF://WM_NCUAHDRAWFRAME
		MESSAGE_HANDLER(0x00AE,OnNcHandle)
		MESSAGE_HANDLER(0x00AF,OnNcHandle)
		MESSAGE_HANDLER(WM_NCLBUTTONDOWN,OnNcLButtonDown)
		MESSAGE_HANDLER(WM_NCLBUTTONUP,OnNcLButtonUp)
		MESSAGE_HANDLER(WM_NCMOUSEMOVE,OnNcMouseMove)
		MESSAGE_HANDLER(WM_NCMOUSELEAVE,OnNcMouseLeave)
		MESSAGE_HANDLER(WM_NCHITTEST,OnNcHitTest)
	END_MSG_MAP()

	LRESULT OnNcCreate(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		HTBUTTON button = {0};
		button.rc.right = GetSystemMetrics(SM_CXSIZE);
		button.rc.bottom = GetSystemMetrics(SM_CYSIZE);
		LPCREATESTRUCT lpCreateStruct = LPCREATESTRUCT(lParam);
		if (lpCreateStruct->style & (WS_SYSMENU | WS_CAPTION | WS_THICKFRAME))
		{
			button.Id = HTCLOSE;
			button.Command = SC_CLOSE;
			button.Type = DFC_CAPTION;
			button.Part = DFCS_CAPTIONCLOSE;
			AddNcButton(button);
			if (lpCreateStruct->style & WS_MAXIMIZEBOX) {
				button.Command = SC_MAXIMIZE;
				button.Id = HTMAXBUTTON;
				button.Part = DFCS_CAPTIONMAX;
				AddNcButton(button);
			}
			if (lpCreateStruct->style & WS_MINIMIZEBOX) {
				button.Id = HTMINBUTTON;
				button.Command = SC_MINIMIZE;
				button.Part = DFCS_CAPTIONMIN;
				AddNcButton(button);
			}
			if (lpCreateStruct->dwExStyle & WS_EX_CONTEXTHELP) {
				button.Id = HTHELP;
				button.Command = SC_CONTEXTHELP;
				button.Part = DFCS_CAPTIONHELP;
				AddNcButton(button);
			}
		}
		return 0;
	}
	LRESULT OnSize(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED || lParam != 0) {
			m_NcDC.DeleteDC();
			//T* pT = static_cast<T*>(this);
			//pT->PostMessage(WM_NCPAINT, 0, 0);
		}
		return 0;
	}
	LRESULT OnNcPaint(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = pT->OnNcPaint();
		return 0;
	}
	LRESULT OnNcActivate(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//pT->PostMessage(WM_NCPAINT, 0, 0);
		return 0;
	}
	LRESULT OnNcHandle(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0;
	}
	LRESULT OnNcLButtonDown(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		BOOL bDrawNc = FALSE;
		RECT rcWnd; 
		pT->GetWindowRect(&rcWnd); 
		POINT pt = {GET_X_LPARAM(lParam) - rcWnd.left, GET_Y_LPARAM(lParam) - rcWnd.top};
		for (size_t i = 0, j = m_NcButtons.size(); i < j; i++)
		{
			if (m_NcButtons[i].State == HTBSTATE::Disabled) {
				continue;
			}
			//if (wParam == m_NcButtons[i].Id) {
			if (PtInRect(&m_NcButtons[i].rc, pt)) {
				m_NcButtons[i].State = HTBSTATE::Pushed;
				bDrawNc = TRUE;
				bHandled = TRUE;
			}
		}
		if (bDrawNc) {
			pT->SendMessage(WM_NCPAINT, 0, 0);
		}
		return 0;
	}

	LRESULT OnNcLButtonUp(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		BOOL bDrawNc = FALSE;
		RECT rcWnd; 
		pT->GetWindowRect(&rcWnd); 
		POINT pt = {GET_X_LPARAM(lParam) - rcWnd.left, GET_Y_LPARAM(lParam) - rcWnd.top};
		for (size_t i = 0, j = m_NcButtons.size(); i < j; i++)
		{
			if (m_NcButtons[i].State == HTBSTATE::Disabled) {
				continue;
			}
			//if (wParam == m_NcButtons[i].Id) {
			if (PtInRect(&m_NcButtons[i].rc, pt)) {
				bHandled = TRUE;
				m_NcButtons[i].State = HTBSTATE::Normal;
				bDrawNc = TRUE;
				pT->PostMessage(WM_SYSCOMMAND, m_NcButtons[i].Command, 0);
				break;
			}
		}
		if (bDrawNc) {
			pT->SendMessage(WM_NCPAINT, 0, 0);
		}
		return 0;
	}

	LRESULT OnNcMouseMove(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		BOOL bDrawNc = FALSE;
		RECT rcWnd; 
		pT->GetWindowRect(&rcWnd); 
		POINT pt = {GET_X_LPARAM(lParam) - rcWnd.left, GET_Y_LPARAM(lParam) - rcWnd.top};
		for (size_t i = 0, j = m_NcButtons.size(); i < j; i++)
		{
			if (m_NcButtons[i].State == HTBSTATE::Disabled) {
				continue;
			}
			//if (wParam == m_NcButtons[i].Id) {
			if (PtInRect(&m_NcButtons[i].rc, pt)) {
				bHandled = TRUE;
				if (m_NcButtons[i].State != HTBSTATE::Hover) {
					if(m_NcButtons[i].State != HTBSTATE::Pushed) {
						m_NcButtons[i].State = HTBSTATE::Hover;
						bDrawNc = TRUE;
					}
				}
			} else if (m_NcButtons[i].State == HTBSTATE::Hover) {
				bHandled = TRUE;
				m_NcButtons[i].State = HTBSTATE::Normal;
				bDrawNc = TRUE;
			}
		}
		if (bDrawNc) {
			pT->SendMessage(WM_NCPAINT, 0, 0);
		}
		return 0;
	}

	LRESULT OnNcMouseLeave(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		BOOL bDrawNc = FALSE;
		for (size_t i = 0, j = m_NcButtons.size(); i < j; i++)
		{
			if (m_NcButtons[i].State == HTBSTATE::Disabled) {
				continue;
			}
			if (m_NcButtons[i].State != HTBSTATE::Normal) {
				bHandled = TRUE;
				m_NcButtons[i].State = HTBSTATE::Normal;
				bDrawNc = TRUE;
			}
		}
		if(bDrawNc) {
			pT->SendMessage(WM_NCPAINT, 0, 0);
		}
		return 0;
	}

	LRESULT OnNcHitTest(UINT , WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lResult = ::DefWindowProc(*pT, WM_NCHITTEST, wParam, lParam);
		if(lResult == HTMAXBUTTON || lResult == HTMINBUTTON || lResult == HTCLOSE)
			lResult = HTCAPTION;

		RECT rcWnd; 
		pT->GetWindowRect(&rcWnd); 
		POINT pt = {GET_X_LPARAM(lParam) - rcWnd.left, GET_Y_LPARAM(lParam) - rcWnd.top};
		for (size_t i = 0, j = m_NcButtons.size(); i < j; i++)
		{
			if (PtInRect(&m_NcButtons[i].rc, pt)) {
				lResult = m_NcButtons[i].Id;
				break;
			}
		}
		return lResult;
	}

	//////////////////////////////////////////////////////////////////////////

	BOOL OnNcPaint() 
	{
		int cxFrame,cyFrame,cxSize,cySize
			//,
			//cxIcon,
			//cyIcon, 
			//cxIconSpace,
			//cxSMSize, cySMSize, cxMinSpace, cyMinSpace, cxBorder, cyBorder
			;
		cxFrame		= GetSystemMetrics(SM_CXFRAME);
		cyFrame		= GetSystemMetrics(SM_CYFRAME);
		cxSize		= GetSystemMetrics(SM_CXSIZE);
		cySize		= GetSystemMetrics(SM_CYSIZE);
		//cxIcon		= GetSystemMetrics(SM_CXSMICON);
		//cyIcon		= GetSystemMetrics(SM_CYSMICON);
		//cxIconSpace = GetSystemMetrics(SM_CXICONSPACING);
		//cxSMSize	= GetSystemMetrics(SM_CXSMSIZE);
		//cySMSize	= GetSystemMetrics(SM_CYSMSIZE);
		//cxMinSpace	= GetSystemMetrics(SM_CXMINSPACING);
		//cyMinSpace	= GetSystemMetrics(SM_CYMINSPACING);
		//cxBorder	= GetSystemMetrics(SM_CXBORDER);
		//cyBorder	= GetSystemMetrics(SM_CYBORDER);

		T* pT = static_cast<T*>(this);
		CRect rcWnd, rcClient; 
		pT->GetWindowRect(rcWnd); 
		pT->GetClientRect(rcClient); 

		CWindowDC dc(*pT);
		pT->ClientToScreen(rcClient);
		rcClient.OffsetRect(-rcWnd.TopLeft());
		dc.ExcludeClipRect(rcClient);
		if (!m_NcDC) {
			m_NcDC.CreateCompatibleDC(dc, rcWnd.Width(), rcWnd.Height());
		}
#ifndef _AFX
		HFONT hOldFont = m_NcDC.SelectFont(pT->GetFont());
#else
		CFont* pOldFont = m_NcDC.SelectFont(pT->GetFont());
#endif//
		//取得整个窗口的矩形
 		RECT rcBackgnd;
 		rcBackgnd.left = 0;
 		rcBackgnd.top = 0;
 		rcBackgnd.right = rcBackgnd.left + rcWnd.Width();
 		rcBackgnd.bottom = rcBackgnd.top + rcWnd.Height();
		RECT rcAppBar;
		//取得整个TitleBar的矩形 
		rcAppBar.left	= cxFrame;
		rcAppBar.top	= cyFrame;
		rcAppBar.right	= (rcWnd.right - rcWnd.left) - cxFrame;
		rcAppBar.bottom	= rcAppBar.top + cySize;
		pT->DrawNcBackgnd(m_NcDC, rcBackgnd);
		pT->DrawNcCaption(m_NcDC, rcAppBar);
		pT->DrawNcButtons(m_NcDC, rcAppBar);
#ifndef _AFX
		m_NcDC.SelectFont(hOldFont);
#else
		m_NcDC.SelectFont(pOldFont);
#endif//
		dc.BitBlt(0, 0, rcWnd.Width(), rcWnd.Height(), m_NcDC, 0, 0, SRCCOPY);
		return TRUE;
	}

	void DrawNcBackgnd(HDC hdc, RECT & rect)
	{
		T* pT = static_cast<T*>(this);
		::DrawCaption(*pT, hdc, &rect, 
			(::GetActiveWindow()==*pT?DC_ACTIVE:0) | DC_ICON | DC_TEXT);
	}

	void DrawNcCaption(HDC hdc, RECT & rect)
	{
		T* pT = static_cast<T*>(this);
		::DrawCaption(*pT, hdc, &rect, 
			(GetActiveWindow()==*pT?DC_ACTIVE:0) | DC_ICON | DC_TEXT);
	}

	void DrawNcButtons(HDC hdc, RECT & rect)
	{
		T* pT = static_cast<T*>(this);
		RECT rc		= rect;
		rc.left		= rect.right;
		rc.top		= rc.top;
		rc.bottom	= rc.bottom;
		INT offset  = 0;
		for (size_t i = 0, j = m_NcButtons.size(); i < j; i++)
		{
			if (m_NcButtons[i].Id == HTMINBUTTON) {
				if (pT->IsIconic()) {
					m_NcButtons[i].Command = SC_RESTORE;
					m_NcButtons[i].Part = DFCS_CAPTIONRESTORE;
				} else {
					m_NcButtons[i].Command = SC_MINIMIZE;
					m_NcButtons[i].Part = DFCS_CAPTIONMIN;
				}
			}
			if (m_NcButtons[i].Id == HTMAXBUTTON) {
				if (pT->IsZoomed()) {
					m_NcButtons[i].Command = SC_RESTORE;
					m_NcButtons[i].Part = DFCS_CAPTIONRESTORE;
				} else {
					m_NcButtons[i].Command = SC_MAXIMIZE;
					m_NcButtons[i].Part = DFCS_CAPTIONMAX;
				}
			}

			rc.right	= rc.left - offset;
			rc.left		= rc.right - (m_NcButtons[i].rc.right-m_NcButtons[i].rc.left);
			m_NcButtons[i].rc = rc;
			offset = pT->DrawNcButton(m_NcDC, m_NcButtons[i]);
		}
	}

	INT  DrawNcButton(HDC hdc, HTBUTTON & button)
	{
		T* pT = static_cast<T*>(this);
		RECT rc = button.rc;
		if (button.State == HTBSTATE::Pushed) {
			rc.left += 1;
			rc.top += 1;
			button.Part |= DFCS_PUSHED;
		} else if (button.State == HTBSTATE::Hover) {
			button.Part |= DFCS_HOT;
		} else if (button.State == HTBSTATE::Disabled) {
			button.Part |= DFCS_INACTIVE;
		} else {
			button.Part &= ~(DFCS_PUSHED|DFCS_HOT|DFCS_INACTIVE);
		}
		::DrawFrameControl(hdc, &rc, button.Type, button.Part);
		return 1;
	}
};

template <class T>
class UIRoundRectHelper
{
	typedef UIRoundRectHelper<T> This;
protected:
	SIZE m_sizeWnd;

public:
    BEGIN_MSG_MAP_EX(This)
		MSG_WM_SIZE(OnSize)
	END_MSG_MAP()

    void OnSize(UINT nType, CSize size)
    {
        T *pT = static_cast<T*>(this);

        if (nType == SIZE_MINIMIZED)
            return;
		
        if (size == m_sizeWnd)
            return;
		
        CRect rcWindow, rcClient;
		WTL::CRgn rgnWindow, rgnMinus, rgnAdd;
		
        pT->GetWindowRect(rcWindow);
        pT->GetClientRect(rcClient);
        pT->ClientToScreen(rcClient);
		
        rcClient.OffsetRect(-rcWindow.TopLeft());
		
        rgnWindow.CreateRectRgn(rcClient.left, rcClient.top + 2, rcClient.right, rcClient.bottom - 2);
        rgnAdd.CreateRectRgn(rcClient.left + 2, rcClient.top, rcClient.right - 2, rcClient.top + 1);
        rgnWindow.CombineRgn(rgnAdd, RGN_OR);
        rgnAdd.OffsetRgn(0, rcClient.Height() - 1);
        rgnWindow.CombineRgn(rgnAdd, RGN_OR);
        rgnAdd.SetRectRgn(rcClient.left + 1, rcClient.top + 1, rcClient.right - 1, rcClient.top + 2);
        rgnWindow.CombineRgn(rgnAdd, RGN_OR);
        rgnAdd.OffsetRgn(0, rcClient.Height() - 3);
        rgnWindow.CombineRgn(rgnAdd, RGN_OR);
		
        pT->SetWindowRgn(rgnWindow,FALSE);
        m_sizeWnd = size;
    }
};

#endif//_H_UIWND_H_