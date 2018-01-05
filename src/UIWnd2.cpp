#include "stdafx.h"
#include "UIWnd2.h"

//////////////////////////////////////////////////////////////////////////

UIWnd2Manager* g_pUIWnd2Manager = NULL;

UIWnd2Manager* getUIWnd2Manager()
{
	return g_pUIWnd2Manager;
}

//////////////////////////////////////////////////////////////////////////

class HUIWnd2
{
public:
	WNDCLASSEX wc;
	HWND m_hWndParent;
	HWND m_hWndPrev;
	HWND m_hWndNext;
	HWND m_hWndChild;
	HWND m_hWndCurChild;
	UINT m_nID;
	CRect m_rc;
	DWORD m_dwStyle;
	DWORD m_dwExStyle;
	DWORD m_dwState;
	LONG m_UserData;
	CString m_strText;
	//CString m_strToolTipText;

	SCROLLINFO* m_pHScrollInfo;
	SCROLLINFO* m_pVScrollInfo;
	SCROLLBARINFO* m_pHScrollBarInfo;
	SCROLLBARINFO* m_pVScrollBarInfo;

	HFONT m_hFont;

	HRGN m_hRgnInvalidate;
	//RECT m_rcInvalidate; //无效区域
	//BOOL m_bInvalidate;
	UINT m_psRef;
	PAINTSTRUCT m_ps;
	CMemDC m_memDC;

	DWORD m_dwThreadId;
	//typedef std::vector<HWND> HChildsList;
	//HChildsList m_hChilds;
	//HChildsList::iterator m_curChilds;

	BOOL m_bAutoDelete;

public:
	HUIWnd2(HWND hWndParent = NULL);
	HUIWnd2(WNDCLASSEX& wc, HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName, DWORD dwStyle, DWORD dwExStyle, UINT nID);
	HUIWnd2(const HUIWnd2& hUIWnd);
	~HUIWnd2();
};

HUIWnd2::HUIWnd2(HWND hWndParent)
{
	memset(&wc, 0, sizeof(wc));
	m_hWndParent = hWndParent;
	m_hWndPrev = NULL;
	m_hWndNext = NULL;
	m_hWndChild = NULL;
	m_hWndCurChild = NULL;
	m_nID = 0;
	m_dwStyle = 0;
	m_dwExStyle = 0;
	m_dwState = 0;
	m_UserData = 0;
	m_strText;

	m_pHScrollInfo = NULL;
	m_pVScrollInfo = NULL;
	m_pHScrollBarInfo = NULL;
	m_pVScrollBarInfo = NULL;

	m_hFont = NULL;

	m_hRgnInvalidate = NULL;
	//m_bInvalidate = FALSE;
	m_psRef = 0;
	memset(&m_ps, 0, sizeof(m_ps));
	m_memDC = NULL;

	//m_dwThreadId = 0;
	//m_hChilds

	m_bAutoDelete = FALSE;
}
HUIWnd2::HUIWnd2(WNDCLASSEX& wc, HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName, DWORD dwStyle, DWORD dwExStyle, UINT nID)
{
	this->wc = wc;
	m_hWndParent = hWndParent;
	m_hWndPrev = NULL;
	m_hWndNext = NULL;
	m_hWndChild = NULL;
	m_hWndCurChild = NULL;
	m_nID = nID;
	m_rc = rcPos;
	m_dwStyle = dwStyle;
	m_dwExStyle = dwExStyle;
	m_dwState = 0;
	m_UserData = 0;
	m_strText = szWindowName;

	m_pHScrollInfo = NULL;
	m_pVScrollInfo = NULL;
	m_pHScrollBarInfo = NULL;
	m_pVScrollBarInfo = NULL;
	if(m_dwStyle & WS_HSCROLL) {
		m_pHScrollInfo = new SCROLLINFO;
		memset(m_pHScrollInfo, 0, sizeof(SCROLLINFO));
		m_pHScrollInfo->cbSize = sizeof(SCROLLINFO);
		m_pHScrollBarInfo = new SCROLLBARINFO;
		memset(m_pHScrollBarInfo, 0, sizeof(SCROLLBARINFO));
		m_pHScrollBarInfo->cbSize = sizeof(SCROLLBARINFO);
	}
	if(m_dwStyle & WS_VSCROLL) {
		m_pVScrollInfo = new SCROLLINFO;
		memset(m_pVScrollInfo, 0, sizeof(SCROLLINFO));
		m_pVScrollInfo->cbSize = sizeof(SCROLLINFO);
		m_pVScrollBarInfo = new SCROLLBARINFO;
		memset(m_pVScrollBarInfo, 0, sizeof(SCROLLBARINFO));
		m_pVScrollBarInfo->cbSize = sizeof(SCROLLBARINFO);
	}

	m_hFont = NULL;

	m_hRgnInvalidate = NULL;
	//m_bInvalidate = FALSE;
	m_psRef = 0;
	memset(&m_ps, 0, sizeof(m_ps));
	m_memDC = NULL;

	m_dwThreadId = GetCurrentThreadId();
	//m_hChilds

	m_bAutoDelete = FALSE;
}

HUIWnd2::HUIWnd2(const HUIWnd2& hUIWnd)
{
	this->wc = hUIWnd.wc;
	m_hWndParent = hUIWnd.m_hWndParent;
	m_hWndPrev = hUIWnd.m_hWndPrev;
	m_hWndNext = hUIWnd.m_hWndNext;
	m_hWndChild = hUIWnd.m_hWndChild;
	m_hWndCurChild = hUIWnd.m_hWndCurChild;
	m_nID = hUIWnd.m_nID;
	m_rc = hUIWnd.m_rc;
	m_dwStyle = hUIWnd.m_dwStyle;
	m_dwExStyle = hUIWnd.m_dwExStyle;
	m_dwState = hUIWnd.m_dwState;
	m_UserData = hUIWnd.m_UserData;
	m_strText = hUIWnd.m_strText;

	m_pHScrollInfo = NULL;
	m_pVScrollInfo = NULL;
	m_pHScrollBarInfo = NULL;
	m_pVScrollBarInfo = NULL;
	if(hUIWnd.m_pHScrollInfo) {
		m_pHScrollInfo = new SCROLLINFO;
		memcpy(m_pHScrollInfo, hUIWnd.m_pHScrollInfo, sizeof(SCROLLINFO));
	}
	if(hUIWnd.m_pVScrollInfo) {
		m_pVScrollInfo = new SCROLLINFO;
		memcpy(m_pVScrollInfo, hUIWnd.m_pVScrollInfo, sizeof(SCROLLINFO));
	}
	if(hUIWnd.m_pHScrollBarInfo) {
		m_pHScrollBarInfo = new SCROLLBARINFO;
		memcpy(m_pHScrollBarInfo, hUIWnd.m_pHScrollBarInfo, sizeof(SCROLLBARINFO));
	}
	if(hUIWnd.m_pVScrollBarInfo) {
		m_pVScrollBarInfo = new SCROLLBARINFO;
		memcpy(m_pVScrollBarInfo, hUIWnd.m_pVScrollBarInfo, sizeof(SCROLLBARINFO));
	}

	m_hFont = NULL;

	m_hRgnInvalidate = NULL;
	if(hUIWnd.m_hRgnInvalidate) {
		CombineRgn(m_hRgnInvalidate,hUIWnd.m_hRgnInvalidate, 0, RGN_COPY);
	}
	//m_bInvalidate = hUIWnd.m_bInvalidate;
	m_psRef = hUIWnd.m_psRef;
	m_ps = hUIWnd.m_ps;
	m_memDC = hUIWnd.m_memDC;

	m_dwThreadId = hUIWnd.m_dwThreadId;
	//m_hChilds

	m_bAutoDelete = hUIWnd.m_bAutoDelete;
}

HUIWnd2::~HUIWnd2()
{
	ATLASSERT(m_memDC==NULL);
	if (m_hRgnInvalidate) {
		DeleteObject(m_hRgnInvalidate);
		m_hRgnInvalidate = NULL;
	}

	if(m_pHScrollInfo) {
		delete m_pHScrollInfo;
		m_pHScrollInfo = NULL;
	}
	if(m_pVScrollInfo) {
		delete m_pVScrollInfo;
		m_pVScrollInfo = NULL;
	}
	if(m_pHScrollBarInfo) {
		delete m_pHScrollBarInfo;
		m_pHScrollBarInfo = NULL;
	}
	if(m_pVScrollBarInfo) {
		delete m_pVScrollBarInfo;
		m_pVScrollBarInfo = NULL;
	}

	//m_hFont
}

//////////////////////////////////////////////////////////////////////////

UIWnd2Manager::UIWnd2Manager()
{
	ASSERT(!g_pUIWnd2Manager);
	g_pUIWnd2Manager = this;

	m_phUIWnd2Pool = NULL;
	m_hMaxWnd2 = (HWND)(-1)-1;
	m_hMinWnd2 = m_hMaxWnd2;
	m_hNextWnd2 = m_hMaxWnd2;

	m_hWndHover = NULL;
	m_hWndFocus = NULL;
	m_hWndTabStop = NULL;
	m_hWndCapture = NULL;
	
	m_hWndToolTip = NULL;
	memset(&m_ToolTip,0,sizeof(TOOLINFO));
}

UIWnd2Manager::~UIWnd2Manager()
{
	if (m_phUIWnd2Pool) {
		delete []m_phUIWnd2Pool;
		m_phUIWnd2Pool = NULL;
	}
	m_hMaxWnd2 = (HWND)(-1)-1;
	m_hMinWnd2 = m_hMaxWnd2;
	m_hNextWnd2 = m_hMaxWnd2;

	m_hWndHover = NULL;
	m_hWndFocus = NULL;
	m_hWndTabStop = NULL;
	m_hWndCapture = NULL;

	if( m_hWndToolTip != NULL ) {
		::DestroyWindow(m_hWndToolTip);
		m_hWndToolTip = NULL;
	}
	memset(&m_ToolTip,0,sizeof(TOOLINFO));

	ASSERT(g_pUIWnd2Manager);
	g_pUIWnd2Manager = NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2(HWND hWnd) const
{
	if (hWnd) {
		CComAutoCritSectionLock Lock(const_cast<CComAutoCriticalSection &>(m_Wnd2Section));
		if (hWnd>m_hMinWnd2 && hWnd <= m_hMaxWnd2) {
			return m_phUIWnd2Pool[m_hMaxWnd2-hWnd];
		} else {
			UIWnd2Pool::const_iterator it = m_hWnd2Pool.find(hWnd);
			if (it != m_hWnd2Pool.end()) {
				return it->second;
			}
		}
	}
	return NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2Parent(HWND hWnd) const
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return FindpHUIWnd2(phWnd2->m_hWndParent);
	}
	return NULL;
}

HWND UIWnd2Manager::FindhWnd2Parent(HWND hWnd) const
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_hWndParent;
	}
	return NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2Prev(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return FindpHUIWnd2(phWnd2->m_hWndPrev);
	}
	return NULL;
}

HWND UIWnd2Manager::FindhWnd2Prev(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_hWndPrev;
	}
	return NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2Next(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return FindpHUIWnd2(phWnd2->m_hWndNext);
	}
	return NULL;
}

HWND UIWnd2Manager::FindhWnd2Next(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_hWndNext;
	}
	return NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2FirstChild(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return FindpHUIWnd2(phWnd2->m_hWndChild);
	}
	return NULL;
}

HWND UIWnd2Manager::FindhWnd2FirstChild(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_hWndChild;
	}
	return NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2CurChild(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return FindpHUIWnd2(phWnd2->m_hWndCurChild);
	}
	return NULL;
}

HWND UIWnd2Manager::FindhWnd2CurChild(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_hWndCurChild;
	}
	return NULL;
}

HUIWnd2* UIWnd2Manager::FindpHUIWnd2LastChild(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		HUIWnd2* phWnd2Child = FindpHUIWnd2Next(phWnd2->m_hWndChild);
		while (phWnd2Child)
		{
			HUIWnd2* phWnd2ChildNext = FindpHUIWnd2Next(phWnd2Child->m_hWndNext);
			if (phWnd2ChildNext == NULL) {
				break;
			}
			phWnd2Child = phWnd2ChildNext;
		}
		return phWnd2Child;
	}
	return NULL;
}

HWND UIWnd2Manager::FindhWnd2LastChild(HWND hWnd) const 
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		HWND hWnd2Child = FindhWnd2Next(phWnd2->m_hWndChild);
		while (hWnd2Child)
		{
			HWND hWnd2ChildNext = FindhWnd2Next(hWnd2Child);
			if (hWnd2ChildNext == NULL) {
				break;
			}
			hWnd2Child = hWnd2ChildNext;
		}
		return hWnd2Child;
	}
	return NULL;
}

void UIWnd2Manager::AddPrevWnd2(HWND hWnd, HWND hPrevWnd, HUIWnd2* phWnd2Prev)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if(phWnd2->m_hWndPrev) {
			HUIWnd2* phWnd2NowPrev = FindpHUIWnd2(phWnd2->m_hWndPrev);
			if(phWnd2NowPrev) {
				phWnd2NowPrev->m_hWndNext = hPrevWnd;
			}
		}
		phWnd2Prev->m_hWndPrev = phWnd2->m_hWndPrev;
		phWnd2Prev->m_hWndNext = hWnd;
		phWnd2->m_hWndPrev = hPrevWnd;
	}
}

void UIWnd2Manager::AddNextWnd2(HWND hWnd, HWND hNextWnd, HUIWnd2* phWnd2Next)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if(phWnd2->m_hWndNext) {
			HUIWnd2* phWnd2NowNext = FindpHUIWnd2(phWnd2->m_hWndNext);
			if(phWnd2NowNext) {
				phWnd2NowNext->m_hWndPrev = hNextWnd;
			}
		}
		phWnd2Next->m_hWndPrev = hWnd;
		phWnd2Next->m_hWndNext = phWnd2->m_hWndNext;
		phWnd2->m_hWndNext = hNextWnd;
	}
}

void UIWnd2Manager::AddLastWnd2(HWND hWnd, HWND hLastWnd, HUIWnd2* phWnd2Last)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if(phWnd2->m_hWndNext) {
			AddLastWnd2(phWnd2->m_hWndNext, hLastWnd, phWnd2Last);
		} else {
			phWnd2Last->m_hWndPrev = hWnd;
			phWnd2Last->m_hWndNext = phWnd2->m_hWndNext;
			phWnd2->m_hWndNext = hLastWnd;
		}
	}
}

void UIWnd2Manager::SetWnd2Pos(HWND hWnd, HWND hWndInsertAfter, UINT nFlags)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (!phWnd2) {
		return ;
	}
	if (!(nFlags & SWP_NOZORDER)) {
		if (hWnd != hWndInsertAfter) {
			HUIWnd2* phWnd2InsertAfter = FindpHUIWnd2(hWndInsertAfter);
			if (phWnd2InsertAfter) {
				if (phWnd2InsertAfter->m_hWndNext != hWnd) {
					//
					HUIWnd2* phWnd2Prev = FindpHUIWnd2(phWnd2->m_hWndPrev);
					HUIWnd2* phWnd2Next = FindpHUIWnd2(phWnd2->m_hWndNext);
					phWnd2Prev->m_hWndNext = phWnd2->m_hWndNext;
					phWnd2Next->m_hWndPrev = phWnd2->m_hWndPrev;
					//
					phWnd2->m_hWndPrev = hWndInsertAfter;
					phWnd2->m_hWndNext = phWnd2InsertAfter->m_hWndNext;
					//
					HUIWnd2* phWnd2InsertAfterNext = FindpHUIWnd2(phWnd2InsertAfter->m_hWndNext);
					phWnd2InsertAfter->m_hWndNext = hWnd;
					phWnd2InsertAfterNext->m_hWndPrev = hWnd;
				}
			}
		}
	}
	if (!(nFlags & SWP_NOACTIVATE) || !(nFlags & SWP_NOOWNERZORDER) || !(nFlags & SWP_NOREPOSITION)) {
		HUIWnd2* phWnd2Parent = FindpHUIWnd2(GetParent(hWnd));
		if (phWnd2Parent) {
			phWnd2Parent->m_hWndCurChild = hWnd;
		}
	} 
}

//for create or initdialog
void UIWnd2Manager::SethWndParent(HWND hWndParent, DWORD dwThreadID)
{
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	m_ThreadWnd2Data[dwThreadID].hWndParent = hWndParent;
}
HWND UIWnd2Manager::GethWndParent(DWORD dwThreadID)
{
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	HWND hWndParent = NULL;
	ThreadID2HUIWnd2Data::iterator it = m_ThreadWnd2Data.find(dwThreadID);
	if (it != m_ThreadWnd2Data.end()) {
		hWndParent = it->second.hWndParent;
		it->second.hWndParent = NULL;
	}
	return hWndParent;
}

void UIWnd2Manager::PostWnd2Message(MSG & msg)
{
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	ATLASSERT(msg.hwnd);
	DWORD dwThreadID = GetWindowThreadID(msg.hwnd);
	m_ThreadWnd2Data[dwThreadID].msgQueue.push_back(msg);
}
BOOL UIWnd2Manager::GethWnd2Message(MSG & msg)
{
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	ThreadID2HUIWnd2Data::iterator it = m_ThreadWnd2Data.find(GetCurrentThreadId());
	if (it != m_ThreadWnd2Data.end()) {
		if (!it->second.msgQueue.empty()) {
			msg = it->second.msgQueue.front();
			it->second.msgQueue.pop_front();
			return TRUE;
		}
	}
	return FALSE;
}

//UIWnd2 Add
void UIWnd2Manager::AddWnd2(HWND hWnd, HUIWnd2* phWnd2)
{
	if (phWnd2==NULL) {
		phWnd2 = FindpHUIWnd2(hWnd);
	}

	ATLASSERT(phWnd2);

	HUIWnd2* phWnd2Parent = FindpHUIWnd2(phWnd2->m_hWndParent);
	if (phWnd2Parent) {
		if (phWnd2Parent->m_hWndChild) {
			AddLastWnd2(phWnd2Parent->m_hWndChild, hWnd, phWnd2);
		} else {
			phWnd2Parent->m_hWndChild = hWnd;
		}
	}
}

//标准窗口Add
void UIWnd2Manager::AddWnd2(HWND hWnd, HWND hWndParent)
{
	HUIWnd2* phWnd2 = new HUIWnd2(hWndParent);
	AddWnd2(hWnd, phWnd2);
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	m_hWnd2Pool[hWnd] = phWnd2;
	Lock.Unlock();
}

//统一移除
void UIWnd2Manager::RemoveWnd2(HWND hWnd, HUIWnd2* phWnd2)
{
	if (phWnd2==NULL) {
		phWnd2 = FindpHUIWnd2(hWnd);
	}
	if (phWnd2) {
		HUIWnd2* phWnd2Parent = FindpHUIWnd2(phWnd2->m_hWndParent);
		if (phWnd2Parent) {
			//移除前面的连接
			if (phWnd2Parent->m_hWndChild == hWnd) {
				phWnd2Parent->m_hWndChild = phWnd2->m_hWndNext;
			} else {
				HUIWnd2* phWnd2Prev = FindpHUIWnd2(phWnd2->m_hWndPrev);
				if (phWnd2Prev) {
					phWnd2Prev->m_hWndNext = phWnd2->m_hWndNext;
				}
			}
			//移除后面的连接
			HUIWnd2* phWnd2Next = FindpHUIWnd2(phWnd2->m_hWndNext);
			if (phWnd2Next) {
				phWnd2Next->m_hWndPrev = phWnd2->m_hWndPrev;
			}
			//清空自己
			phWnd2->m_hWndParent = NULL;
			phWnd2->m_hWndPrev = NULL;
			phWnd2->m_hWndNext = NULL;
		} 
		//Remove from HWND TO pWnd2 map
		CComAutoCritSectionLock Lock(m_Wnd2Section);
		if (hWnd>m_hMinWnd2 && hWnd <= m_hMaxWnd2) {
			m_phUIWnd2Pool[m_hMaxWnd2-hWnd] = NULL;
		}
		m_hWnd2Pool.erase(hWnd);
		Lock.Unlock();
		//统一从这里delete对象
		delete phWnd2;
	}
}

LRESULT UIWnd2Manager::DefWindowProc(
									 HWND hWnd, 
									 UINT Msg, 
									 WPARAM wParam, 
									 LPARAM lParam 
									 )
{
	switch(Msg)
	{
	case WM_NCCREATE:
	case WM_CREATE:
		return 1L;
		break;
	case WM_DESTROY:
	case WM_NCDESTROY:
		return 1L;
		break;
	case WM_MOVE:
		break;
	case WM_SIZE:
		break;
	case WM_SETTEXT:
		{
			HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
			if (phWnd2) {
				phWnd2->m_strText = (LPCTSTR)lParam;
				return phWnd2->m_strText.GetLength();
			}
		}
		break;
	case WM_GETTEXT:
		{
			HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
			if (phWnd2) {
				_tcsncpy((LPTSTR)lParam, phWnd2->m_strText, (UINT)wParam);
				return phWnd2->m_strText.GetLength();
			}
		}
		break;
	case WM_GETTEXTLENGTH:
		{
			HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
			if (phWnd2) {
				return phWnd2->m_strText.GetLength();
			}
		}
		break;
	case WM_ERASEBKGND:
		break;
	case WM_PAINT:
	case WM_PRINTCLIENT:
		break;
	case WM_MOUSEHOVER:
		{
			// Create tooltip information
			ZeroMemory(&m_ToolTip, sizeof(TOOLINFO));
			m_ToolTip.cbSize = sizeof(TOOLINFO);
			m_ToolTip.uFlags = TTF_IDISHWND;
			m_ToolTip.hwnd = GetSafeHwnd(hWnd);
			m_ToolTip.uId = (UINT_PTR)m_ToolTip.hwnd;
			//m_ToolTip.hinst = _Module.GetModuleInstance();
			//m_ToolTip.lpszText = ;
			//GetWindowRect(m_ToolTip.rect);
			if(SendMessage(hWnd, TTM_GETTOOLINFO, 0, (LPARAM) &m_ToolTip)) {
				if( m_hWndToolTip == NULL ) {
					m_hWndToolTip = ::CreateWindowEx(0, TOOLTIPS_CLASS, NULL, WS_POPUP | TTS_NOPREFIX | TTS_ALWAYSTIP, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, m_ToolTip.hwnd, NULL, m_ToolTip.hinst, NULL);
					::SendMessage(m_hWndToolTip, TTM_ADDTOOL, 0, (LPARAM) &m_ToolTip);
					//::SendMessage(m_hWndToolTip,TTM_SETMAXTIPWIDTH,0, );
				}
				if(!::IsWindowVisible(m_hWndToolTip)) {
					::SendMessage(m_hWndToolTip, TTM_SETTOOLINFO, 0, (LPARAM)&m_ToolTip);
					::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, TRUE, (LPARAM)&m_ToolTip);
				}
			}
		}
		break;
	case WM_MOUSELEAVE:
		{
			if(m_hWndToolTip != NULL) {
				::SendMessage(m_hWndToolTip, TTM_TRACKACTIVATE, FALSE, (LPARAM) &m_ToolTip);
			}
		}
		break;
	}
	return 0;
}

#ifndef _MAC
LRESULT
WINAPI
#else
LRESULT
CALLBACK
#endif
UIWnd2Manager::DefWindowProc2( 
							  HWND hWnd, 
							  UINT Msg, 
							  WPARAM wParam, 
							  LPARAM lParam 
							  )
{//用DefWindowProc2 是为了和::DefWindowProc区分开来
	return _pUIWnd2Manager->DefWindowProc(hWnd, Msg, wParam, lParam);
	return 0;
}

BOOL UIWnd2Manager::IsDirectUI(HWND hWnd) const
{
	return (hWnd > m_hMinWnd2 ? TRUE : FALSE);
}

BOOL UIWnd2Manager::IsUIWnd2(HWND hWnd) const
{
	CComAutoCritSectionLock Lock(const_cast<CComAutoCriticalSection &>(m_Wnd2Section));
	return m_hWnd2Pool.find(hWnd) != m_hWnd2Pool.end() ? TRUE : FALSE;
}

HWND UIWnd2Manager::Create(HINSTANCE hInstance, HWND hWndParent, RECT& rcPos, LPCTSTR szWindowName,
						   DWORD dwStyle, DWORD dwExStyle, UINT nID, ATOM atom, LPVOID lpCreateParam)
{
	HWND hWnd = NULL;
	WNDCLASSEX wcTemp = {0};
	if(::GetClassInfoEx(hInstance, (LPCTSTR)MAKELONG(atom, 0), &wcTemp)) {
		ASSERT(wcTemp.lpfnWndProc);
		//ClientToScreen(hWndParent, &rcPos);
		HUIWnd2* phUIWnd2 = new HUIWnd2(wcTemp, hWndParent, rcPos, szWindowName, dwStyle, dwExStyle, nID);
		if (phUIWnd2) {
			//Create from HWND TO pWnd2 map
			CComAutoCritSectionLock Lock(m_Wnd2Section);
			//
			const UINT uIncrementCount = 256;
			if (m_phUIWnd2Pool == NULL) {
				m_phUIWnd2Pool = new PHUIWnd2[uIncrementCount];
				memset(m_phUIWnd2Pool, 0, sizeof(PHUIWnd2)*uIncrementCount);
				ATLASSERT(m_phUIWnd2Pool);
				m_hMinWnd2 = m_hMaxWnd2 - uIncrementCount;

			} else if(m_hNextWnd2 <= m_hMinWnd2) {
				UINT uNowCount = m_hMaxWnd2-m_hMinWnd2;
				UINT uNewCount = uNowCount + uIncrementCount;
				PHUIWnd2* pNewphUIWnd2Pool = new PHUIWnd2[uNewCount];
				ATLASSERT(pNewphUIWnd2Pool);
				memset(m_phUIWnd2Pool, 0, sizeof(PHUIWnd2)*uNewCount);
				memcpy(pNewphUIWnd2Pool, m_phUIWnd2Pool, sizeof(PHUIWnd2)*uNowCount);
				delete []m_phUIWnd2Pool;
				m_phUIWnd2Pool = pNewphUIWnd2Pool;
				m_hMinWnd2 -= uIncrementCount;
			}
			hWnd = m_hNextWnd2;
			m_phUIWnd2Pool[m_hMaxWnd2-hWnd] = phUIWnd2;
			for (m_hNextWnd2 = m_hMaxWnd2; m_hNextWnd2 > m_hMinWnd2; m_hNextWnd2--)
			{
				if (m_phUIWnd2Pool[m_hMaxWnd2-m_hNextWnd2] == NULL) {
					break;
				}
			}
			//
			m_hWnd2Pool[hWnd] = phUIWnd2;
			Lock.Unlock();

			//WM_CREATE
			CREATESTRUCT cs = {0};
			cs.lpCreateParams = lpCreateParam;
			cs.hInstance = hInstance;
			cs.hMenu = (HMENU)nID;
			cs.hwndParent = hWndParent;
			cs.cy;
			cs.cx;
			cs.y;
			cs.x;
			cs.style = dwStyle;
			cs.lpszName = szWindowName;
			cs.lpszClass = (LPCTSTR)MAKELONG(atom, 0);
			cs.dwExStyle = dwExStyle;
			if(phUIWnd2->wc.lpfnWndProc(hWnd, WM_NCCREATE, 0, (LPARAM)&cs) 
				&& phUIWnd2->wc.lpfnWndProc(hWnd, WM_CREATE, 0, (LPARAM)&cs)
				) {
				//phUIWnd2->wc.lpfnWndProc(hWnd, WM_SIZE, 0, MAKELPARAM(phUIWnd2->m_rc.Width(),phUIWnd2->m_rc.Height()));
				//if (dwStyle & WS_VISIBLE) {
				//	phUIWnd2->wc.lpfnWndProc(hWnd, WM_SHOWWINDOW, SW_SHOWNORMAL, 0L);
				//}
			} else {
				RemoveWnd2(hWnd, phUIWnd2);
				hWnd = NULL;
			}
		}
	}
	return hWnd;
}

BOOL UIWnd2Manager::DestroyWindow(HWND hWnd)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		//Destroy Window
		if (IsDirectUI(hWnd)) {
			RECT rc = phWnd2->m_rc;
			HWND hWndParent = phWnd2->m_hWndParent;
			//WM_SHOWWINDOW
			//phWnd2->wc.lpfnWndProc(hWnd, WM_SHOWWINDOW, 0, 0L);
			//WM_DESTROY
			phWnd2->wc.lpfnWndProc(hWnd, WM_DESTROY, 0, 0L);
			phWnd2->wc.lpfnWndProc(hWnd, WM_NCDESTROY, 0, 0L);
			InvalidateRect(hWndParent,&rc);
		} else {
			::DestroyWindow(hWnd);
		}
		return TRUE;
	} else {
		//非Wnd2管理窗口
		::DestroyWindow(hWnd);
	}
	return FALSE;
}

BOOL UIWnd2Manager::EndDialog(HWND hWnd, int nRetCode)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		//Destroy Window
		if (IsDirectUI(hWnd)) {
			RECT rc = phWnd2->m_rc;
			HWND hWndParent = phWnd2->m_hWndParent;
			//WM_DESTROY
			phWnd2->wc.lpfnWndProc(hWnd, WM_DESTROY, 0, 0L);
			phWnd2->wc.lpfnWndProc(hWnd, WM_NCDESTROY, 0, 0L);
			InvalidateRect(hWndParent,&rc);
		} else {
			::EndDialog(hWnd, nRetCode);
		}
		return TRUE;
	} else {
		//非Wnd2管理窗口
		ATLASSERT(0);
	}
	return FALSE;
}

BOOL UIWnd2Manager::DestroyChildWindow(HWND hWnd)
{
	//Destroy Child Window
	HWND hChild = FindhWnd2FirstChild(hWnd);
	while(hChild) 
	{
		HWND hNextChild = FindhWnd2Next(hChild);
		DestroyWindow(hChild);
		hChild = hNextChild;
	}
	return TRUE;
}

BOOL UIWnd2Manager::IsAutoDelete(HWND hWnd)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_bAutoDelete;
	}
	return FALSE;
}

BOOL UIWnd2Manager::SetAutoDelete(HWND hWnd, BOOL bDelete)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		phWnd2->m_bAutoDelete = bDelete;
		return TRUE;
	}
	return FALSE;
}

DWORD UIWnd2Manager::GetStyle(HWND hWnd) const
{
	if (IsDirectUI(hWnd)) {
		return (DWORD)GetWindowLong(hWnd, GWL_STYLE);
	}
	return (DWORD)::GetWindowLong(hWnd, GWL_STYLE);
}

DWORD UIWnd2Manager::GetExStyle(HWND hWnd) const
{
	if (IsDirectUI(hWnd)) {
		return (DWORD)GetWindowLong(hWnd, GWL_EXSTYLE);
	}
	return (DWORD)::GetWindowLong(hWnd, GWL_EXSTYLE);
}

DWORD UIWnd2Manager::GetClassLongA( HWND hWnd, int nIndex)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phUIWnd2 = FindpHUIWnd2(hWnd);
		if (phUIWnd2) {
			switch(nIndex)
			{
			case GCW_ATOM:
				break;
			case GCL_CBCLSEXTRA:
				return (DWORD)phUIWnd2->wc.cbClsExtra;
				break;
			case GCL_CBWNDEXTRA:
				return (DWORD)phUIWnd2->wc.cbWndExtra;
				break;
			case GCL_HBRBACKGROUND:
				return (DWORD)phUIWnd2->wc.hbrBackground;
				break;
			case GCL_HCURSOR:
				return (DWORD)phUIWnd2->wc.hCursor;
				break;
			case GCL_HICON:
				return (DWORD)phUIWnd2->wc.hIcon;
				break;
			case GCL_HICONSM:
				return (DWORD)phUIWnd2->wc.hIconSm;
				break;
			case GCL_HMODULE:
				return (DWORD)phUIWnd2->wc.hInstance;
				break;
			case GCL_MENUNAME:
				return (DWORD)phUIWnd2->wc.lpszMenuName;
				break;
			case GCL_STYLE:
				return (DWORD)phUIWnd2->wc.style;
				break;
			case GCL_WNDPROC:
				return (DWORD)phUIWnd2->wc.lpfnWndProc;
				break;
			}
		}
	} else {
		return ::GetClassLong(hWnd, nIndex);
	}
	return 0;
}

DWORD UIWnd2Manager::GetClassLongW( HWND hWnd, int nIndex)
{
	return GetClassLongA(hWnd, nIndex);
}

int UIWnd2Manager::GetClassNameA(HWND hWnd, LPTSTR lpClassName, int nMaxCount)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phUIWnd2 = FindpHUIWnd2(hWnd);
		if (phUIWnd2) {
			int nClassNameLen = _tcslen(phUIWnd2->wc.lpszClassName);
			if (nClassNameLen > nMaxCount) {
				nClassNameLen = nMaxCount;
			}
			_tcsncpy(lpClassName, phUIWnd2->wc.lpszClassName, nClassNameLen);
			return nClassNameLen;
		}
	} else {
		return ::GetClassName(hWnd, lpClassName, nMaxCount);
	}
	return 0;
}

int UIWnd2Manager::GetClassNameW(HWND hWnd, LPTSTR lpClassName, int nMaxCount)
{
	return GetClassNameA(hWnd, lpClassName, nMaxCount);
}

LONG UIWnd2Manager::GetWindowLongA(HWND hWnd, int nIndex) const
{
	return GetWindowLongPtrA(hWnd, nIndex);
}

LONG UIWnd2Manager::GetWindowLongW(HWND hWnd, int nIndex) const
{
	return GetWindowLongPtrW(hWnd, nIndex);
}

LONG_PTR UIWnd2Manager::GetWindowLongPtrA(HWND hWnd, int nIndex) const
{
	return GetWindowLongPtrW(hWnd, nIndex);
}

LONG_PTR UIWnd2Manager::GetWindowLongPtrW(HWND hWnd, int nIndex) const
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (!phWnd2) {
		return 0L;
	}
	LONG_PTR lRes = 0L;
	switch(nIndex)
	{
	case GWL_WNDPROC:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->wc.lpfnWndProc;
			} else {
				ATLASSERT(0);
				::GetWindowLongPtrW(hWnd, nIndex);
			}
		}
		break;
	case GWL_HINSTANCE:
		{
			if (IsDirectUI(hWnd)) {
				HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
				if (!phWnd2) {
					lRes = (LONG_PTR)GetModuleHandle(NULL);
				}
				return (LONG_PTR)phWnd2->wc.hInstance;
			} else {
				ATLASSERT(0);
				::GetWindowLongPtrW(hWnd, nIndex);
			}
		}
		break;
	case GWL_HWNDPARENT:
		{
			lRes = (LONG_PTR)phWnd2->m_hWndParent;
		}
		break;
	case GWL_STYLE:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->m_dwStyle;
			} else {
				ATLASSERT(0);
				::GetWindowLongPtrW(hWnd, nIndex);
			}
		}
		break;
	case GWL_EXSTYLE:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->m_dwExStyle;
			} else {
				ATLASSERT(0);
				::GetWindowLongPtrW(hWnd, nIndex);
			}
		}
		break;
	case GWL_USERDATA:
		{
			if (IsDirectUI(hWnd)) {
				//lRes = 0;
			} else {
				ATLASSERT(0);
				::GetWindowLongPtrW(hWnd, nIndex);
			}
		}
		break;
	case GWL_ID:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->m_nID;
			} else {
				ATLASSERT(0);
				::GetWindowLongPtrW(hWnd, nIndex);
			}
		}
		break;
	default:
		ATLASSERT(0);
		break;
	}
	return lRes;
	return 0L;
}

LONG UIWnd2Manager::SetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
	return SetWindowLongPtrA(hWnd,nIndex,dwNewLong);
}

LONG UIWnd2Manager::SetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong)
{
	return SetWindowLongA(hWnd, nIndex, dwNewLong);
}

LONG_PTR UIWnd2Manager::SetWindowLongPtrA(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
	return SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
}

LONG_PTR UIWnd2Manager::SetWindowLongPtrW(HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (!phWnd2) {
		return 0L;
	}
	LONG_PTR lRes = 0L;
	BOOL bInvalidate = FALSE;
	switch(nIndex)
	{
	case GWL_WNDPROC:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->wc.lpfnWndProc;
				phWnd2->wc.lpfnWndProc = (WNDPROC)dwNewLong;
			} else {
				ATLASSERT(0);
				::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
			}
		}
		break;
	case GWL_HINSTANCE:
		{
			if (IsDirectUI(hWnd)) {
			} else {
				ATLASSERT(0);
				::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
			}
		}
		break;
	case GWL_HWNDPARENT:
		{
			if (phWnd2->m_hWndParent != (HWND)dwNewLong)
			{
				//这样处理不对
				lRes = (LONG)phWnd2->m_hWndParent;
				phWnd2->m_hWndParent = (HWND)dwNewLong;
			}
		}
		break;
	case GWL_STYLE:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->m_dwStyle;
				phWnd2->m_dwStyle = (DWORD)dwNewLong;
				if ((lRes&WS_VISIBLE) && !(dwNewLong&WS_VISIBLE)) {
					bInvalidate = TRUE;
					phWnd2->wc.lpfnWndProc(hWnd, WM_SHOWWINDOW, SW_HIDE, 0L);
				} else if (!(lRes&WS_VISIBLE) && (dwNewLong&WS_VISIBLE)) {
					bInvalidate = TRUE;
					phWnd2->wc.lpfnWndProc(hWnd, WM_SHOWWINDOW, SW_SHOWNORMAL, 0L);
				}
			} else {
				ATLASSERT(0);
				::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
			}
		}
		break;
	case GWL_EXSTYLE:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->m_dwExStyle;
				phWnd2->m_dwExStyle = (DWORD)dwNewLong;
			} else {
				ATLASSERT(0);
				::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
			}
		}
		break;
	case GWL_USERDATA:
		{
			if (IsDirectUI(hWnd)) {
				lRes = phWnd2->m_UserData;
				phWnd2->m_UserData = dwNewLong;
			} else {
				ATLASSERT(0);
				::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
			}
		}
		break;
	case GWL_ID:
		{
			if (IsDirectUI(hWnd)) {
				lRes = (LONG_PTR)phWnd2->m_nID;
				phWnd2->m_nID = (UINT)dwNewLong;
			} else {
				ATLASSERT(0);
				::SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
			}
		}
		break;
	default:
		break;
	}
	if (bInvalidate) {
		Invalidate(hWnd);
	}
	return lRes;
}

WORD UIWnd2Manager::GetWindowWord(HWND hWnd, int nIndex) const
{
	return 0;
}

WORD UIWnd2Manager::SetWindowWord(HWND hWnd, int nIndex, WORD wNewWord)
{
	return 0;
}

// Message Functions

LRESULT UIWnd2Manager::SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			return phWnd2->wc.lpfnWndProc(hWnd, message, wParam, lParam);
		}
	} else {
		return ::SendMessage(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL UIWnd2Manager::PostMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (IsDirectUI(hWnd)) {
		HWND hSafeWnd = GetSafeHwnd(hWnd);
		if (hSafeWnd) {
			MSG msg = { hWnd, message, wParam, lParam, 0, {0,0} };
			PostWnd2Message(msg);
			::PostMessage(hSafeWnd, WM_POSTDIRECTUIMSG, wParam, lParam);
		}
	} else {
		return ::PostMessage(hWnd, message, wParam, lParam);
	}
	return 0;
}

BOOL UIWnd2Manager::SendNotifyMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (IsDirectUI(hWnd)) {
		return SendMessage(hWnd, message, wParam, lParam);
	} else {
		::SendNotifyMessage(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Window Text Functions

BOOL UIWnd2Manager::SetWindowText(HWND hWnd, LPCTSTR lpszString)
{
	return SendMessage(hWnd, WM_SETTEXT, (WPARAM)0, (LPARAM)lpszString);
	return 0;
}

int UIWnd2Manager::GetWindowText(HWND hWnd, LPTSTR lpszStringBuf, int nMaxCount)
{
	return SendMessage(hWnd, WM_GETTEXT, (WPARAM)nMaxCount, (LPARAM)lpszStringBuf);
	return 0;
}

int UIWnd2Manager::GetWindowTextLength(HWND hWnd)
{
	return SendMessage(hWnd, WM_GETTEXTLENGTH);
	return 0;
}

// Font Functions

void UIWnd2Manager::SetFont(HWND hWnd, HFONT hFont, BOOL bRedraw)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			phWnd2->m_hFont = hFont;
			if (bRedraw) {
				Invalidate(hWnd);
			}
		}
	} else {
		::SendMessage(hWnd, WM_SETFONT, (WPARAM)hFont, MAKELPARAM(bRedraw, 0));
	}
}

HFONT UIWnd2Manager::GetFont(HWND hWnd) const
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			return phWnd2->m_hFont;
		}
	} else {
		return (HFONT)::SendMessage(hWnd, WM_GETFONT, 0, 0);
	}
	return 0;
}

// Menu Functions (non-child windows only)

HMENU UIWnd2Manager::GetMenu(HWND hWnd) const
{
	return 0;
}

BOOL UIWnd2Manager::SetMenu(HWND hWnd, HMENU hMenu)
{
	return 0;
}

BOOL UIWnd2Manager::DrawMenuBar(HWND hWnd)
{
	return 0;
}

HMENU UIWnd2Manager::GetSystemMenu(HWND hWnd, BOOL bRevert) const
{
	return 0;
}

BOOL UIWnd2Manager::HiliteMenuItem(HWND hWnd, HMENU hMenu, UINT uItemHilite, UINT uHilite)
{
	return 0;
}

// Window Size and Position Functions

BOOL UIWnd2Manager::IsIconic(HWND hWnd) const
{
	return 0;
}

BOOL UIWnd2Manager::IsZoomed(HWND hWnd) const
{
	return 0;
}

BOOL UIWnd2Manager::MoveWindow(HWND hWnd, int x, int y, int nWidth, int nHeight, BOOL bRepaint)
{
	return SetWindowPos(hWnd, NULL, x, y, nWidth, nHeight, 
		SWP_NOREPOSITION|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE|(bRepaint ? 0 : SWP_NOREDRAW));
	return 0;
}

BOOL UIWnd2Manager::MoveWindow(HWND hWnd, LPCRECT lpRect, BOOL bRepaint)
{
	if(lpRect) {
		return MoveWindow(hWnd, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, bRepaint);
	}
	return 0;
}

BOOL UIWnd2Manager::SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (!phWnd2) {
		return ::SetWindowPos(hWnd, hWndInsertAfter, x, y, cx, cy, nFlags);
	}
	if (IsDirectUI(hWnd)) {
		if (!(nFlags & SWP_NOSENDCHANGING)) {
			nFlags &= ~SWP_NOSENDCHANGING;
			WINDOWPOS wndpos = {0};
			wndpos.x = x;
			wndpos.y = y;
			wndpos.cx = cx;
			wndpos.cy = cy;
			wndpos.flags = nFlags;
			wndpos.hwnd = hWnd;
			wndpos.hwndInsertAfter = hWndInsertAfter;
			if(SendMessage(hWnd, WM_WINDOWPOSCHANGING, 0, (LPARAM)&wndpos)) {
				//hWnd = wndpos.hwnd;
				hWndInsertAfter = wndpos.hwndInsertAfter;
				nFlags = wndpos.flags;
				x = wndpos.x;
				y = wndpos.y;
				cx = wndpos.cx;
				cy = wndpos.cy;
			}
		}
		BOOL bMove = ((nFlags & SWP_NOMOVE) && (nFlags & SWP_NOSIZE)) ? FALSE : TRUE;
		BOOL bRedraw = nFlags & SWP_NOREDRAW ? FALSE : TRUE;
		BOOL bFrameChanged = FALSE;
		CRect rc = phWnd2->m_rc;
		/*if (bMove) {
		SendMessage(hWnd, WM_MOVING, 0, (LPARAM)&rc);
		}*/
		if (bMove) {
			int nOldWidth = rc.Width();
			int nOldHeight = rc.Height();
			if (!(nFlags & SWP_NOMOVE) && x != rc.left || y != rc.top) {
				int xOffset = x - rc.left;
				int yOffset = y - rc.top;
				/*HWND hWndChild = phWnd2->m_hWndChild;
				while (hWndChild) 
				{
				HUIWnd2* phWnd2Child = FindpHUIWnd2(hWndChild);
				if (IsDirectUI(hWndChild)) {
				phWnd2Child->m_rc.OffsetRect(xOffset, yOffset);
				} else {
				RECT rcWnd = {0};
				::GetWindowRect(hWndChild, &rcWnd);
				ScreenToClient(hWnd, &rcWnd);
				::OffsetRect(&rcWnd, xOffset, yOffset);
				::SetWindowPos(hWndChild, NULL, rcWnd.left, rcWnd.top, 0, 0, 
				SWP_NOSIZE|SWP_NOREPOSITION|SWP_NOZORDER|SWP_NOSENDCHANGING|SWP_NOACTIVATE);
				}
				hWndChild = phWnd2Child->m_hWndNext;
				}*/
				phWnd2->m_rc.OffsetRect(xOffset, yOffset);
				phWnd2->wc.lpfnWndProc(hWnd, WM_MOVE, 0, MAKELPARAM(x,y));
			}
			if (!(nFlags & SWP_NOSIZE) && (nOldWidth != cx || nOldHeight != cy)) {
				phWnd2->m_rc.right = x + cx;
				phWnd2->m_rc.bottom = y + cy;
				phWnd2->wc.lpfnWndProc(hWnd, WM_SIZE, 0, MAKELPARAM(cx,cy));
			}
		}
		if ((nFlags & SWP_SHOWWINDOW) && !(phWnd2->m_dwStyle & WS_VISIBLE)) {
			bRedraw = TRUE;
			phWnd2->m_dwStyle |= WS_VISIBLE;
		} 
		if ((nFlags & SWP_HIDEWINDOW) && (phWnd2->m_dwStyle & WS_VISIBLE)) {
			phWnd2->m_dwStyle &= ~WS_VISIBLE;
			InvalidateRect(phWnd2->m_hWndParent, &rc);
		} 
		SetWnd2Pos(hWnd, hWndInsertAfter, nFlags);
		if (nFlags & SWP_FRAMECHANGED) {
			bFrameChanged = TRUE;
		} 
		if (nFlags & SWP_NOCOPYBITS) {
		} 
		if (nFlags & SWP_DRAWFRAME) {
			bRedraw = TRUE;
		} 
#if(WINVER >= 0x0400)
		if (nFlags & SWP_DEFERERASE) {
		} 
		if (nFlags & SWP_ASYNCWINDOWPOS) {
		} 
#endif//
		if (bRedraw) {
			Invalidate(hWnd);
		}
		if (bFrameChanged) {
		}
		//if (bFrameChanged || bRedraw) 
		{
			WINDOWPOS wndpos = {0};
			wndpos.x = rc.left;
			wndpos.y = rc.top;
			wndpos.cx = rc.Width();
			wndpos.cy = rc.Height();
			wndpos.flags = nFlags;
			wndpos.hwnd = hWnd;
			wndpos.hwndInsertAfter = hWndInsertAfter;
			phWnd2->wc.lpfnWndProc(hWnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)&wndpos);
		}
	} else {
		ATLASSERT(::IsWindow(hWnd));
		if (!(nFlags & SWP_NOMOVE)) {
			HWND hRealWndParent = ::GetParent(hWnd);
			if(hRealWndParent) {
				//RECT rc = {0};
				//SIZE szOffset = {0};
				HWND hWndParent = GetParent(hWnd);
				/*while (hWndParent != hRealWndParent)
				{
					GetWindowRect(hWndParent, &rc);
					szOffset.cx += rc.left;
					szOffset.cx += rc.top;
					hWndParent = GetParent(hWndParent);
				}
				x += szOffset.cx;
				y += szOffset.cy;*/
				RECT rcRealParent;
				GetWindowRect(hRealWndParent, &rcRealParent);
				RECT rcParent;
				GetWindowRect(hWndParent, &rcParent);
				x += rcParent.left - rcRealParent.left;
				y += rcParent.top - rcRealParent.top;
			}
		}
		SetWnd2Pos(hWnd, hWndInsertAfter, nFlags);
		return ::SetWindowPos(hWnd, hWndInsertAfter, x, y, cx, cy, 
			nFlags | (SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOREPOSITION|SWP_NOZORDER));
	}
	return 0;
}

BOOL UIWnd2Manager::SetWindowPos(HWND hWnd, HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags)
{
	if (lpRect) {
		return SetWindowPos(hWnd, hWndInsertAfter
			, lpRect->left, lpRect->top, lpRect->right - lpRect->left, lpRect->bottom - lpRect->top, nFlags);
	} else {
		return SetWindowPos(hWnd, hWndInsertAfter, 0, 0, 0, 0, nFlags);
	}
	return 0;
}

UINT UIWnd2Manager::ArrangeIconicWindows(HWND hWnd)
{
	return 0;
}

BOOL UIWnd2Manager::BringWindowToTop(HWND hWnd)
{
	return 0;
}

BOOL UIWnd2Manager::GetWindowRect(HWND hWnd, LPRECT lpRect) const
{
	ATLASSERT(lpRect);
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if (GetWindowRect(phWnd2->m_hWndParent, lpRect)) {
				lpRect->left += phWnd2->m_rc.left;
				lpRect->top += phWnd2->m_rc.top;
				lpRect->right = lpRect->left + phWnd2->m_rc.Width();
				lpRect->bottom = lpRect->top + phWnd2->m_rc.Height();
				return TRUE;
			}
		}
	} else {
		/*ATLASSERT(::IsWindow(hWnd));
		SIZE szOffset = {0};
		HWND hRealWndParent = ::GetParent(hWnd);
		ATLASSERT(hRealWndParent);
		HWND hWndParent = GetParent(hWnd);
		while (hWndParent != hRealWndParent)
		{
		GetWindowRect(hWndParent, lpRect);
		szOffset.cx += lpRect->left;
		szOffset.cx += lpRect->top;
		hWndParent = FindhWnd2Parent(hWndParent);
		}
		::GetWindowRect(hWnd, lpRect);
		OffsetRect(lpRect, -szOffset.cx, -szOffset.cy);*/
		return ::GetWindowRect(hWnd, lpRect);
	}
	return 0;
}

BOOL UIWnd2Manager::GetClientRect(HWND hWnd, LPRECT lpRect) const
{
	ATLASSERT(lpRect);
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			lpRect->left = 0;
			lpRect->top = 0;
			lpRect->right = phWnd2->m_rc.Width();
			lpRect->bottom = phWnd2->m_rc.Height();
			if((phWnd2->m_dwStyle&WS_VSCROLL)&&!(phWnd2->m_pVScrollBarInfo->rgstate[0]&STATE_SYSTEM_INVISIBLE)) {
				lpRect->right -= (phWnd2->m_pVScrollBarInfo->rcScrollBar.right-phWnd2->m_pVScrollBarInfo->rcScrollBar.left);
			}
			if((phWnd2->m_dwStyle&WS_HSCROLL)&&!(phWnd2->m_pHScrollBarInfo->rgstate[0]&STATE_SYSTEM_INVISIBLE)) {
				lpRect->bottom -= (phWnd2->m_pHScrollBarInfo->rcScrollBar.bottom-phWnd2->m_pHScrollBarInfo->rcScrollBar.top);
			}
			return TRUE;
		}
	} else {
		::GetClientRect(hWnd, lpRect);
	}
	return 0;
}

BOOL UIWnd2Manager::GetWindowPlacement(HWND hWnd, WINDOWPLACEMENT FAR* lpwndpl) const
{
	return 0;
}

BOOL UIWnd2Manager::SetWindowPlacement(HWND hWnd, const WINDOWPLACEMENT FAR* lpwndpl)
{
	return 0;
}

// Coordinate Mapping Functions

BOOL UIWnd2Manager::ClientToScreen(HWND hWnd, LPPOINT lpPoint) const
{
	RECT rc = {0};
	if(GetWindowRect(hWnd, &rc)) {
		lpPoint->x += rc.left;
		lpPoint->y += rc.top;
		/*HWND hParent = GetParent(hWnd);
		if (IsDirectUI(hParent)) {
		return ClientToScreen(hParent, lpPoint);
		} else {
		return ::ClientToScreen(hParent, lpPoint);
		}*/
		return TRUE;
	}
	return 0;
}

BOOL UIWnd2Manager::ClientToScreen(HWND hWnd, LPRECT lpRect) const
{
	RECT rc = {0};
	if(GetWindowRect(hWnd, &rc)) {
		::OffsetRect(lpRect, rc.left, rc.top);
		/*HWND hParent = GetParent(hWnd);
		if (IsDirectUI(hParent)) {
		return ClientToScreen(hParent, lpRect);
		} else {
		if(!::ClientToScreen(hParent, (LPPOINT)lpRect))
		return FALSE;
		return ::ClientToScreen(hParent, ((LPPOINT)lpRect)+1);
		}*/
		return TRUE;
	}
	return 0;
}

BOOL UIWnd2Manager::ScreenToClient(HWND hWnd, LPPOINT lpPoint) const
{
	//HWND hParent = GetParent(hWnd);
	RECT rc = {0};
	if(GetWindowRect(hWnd, &rc)) {
		lpPoint->x -= rc.left;
		lpPoint->y -= rc.top;
		/*if (IsDirectUI(hParent)) {
		return ScreenToClient(hParent, lpPoint);
		} else {
		return ::ScreenToClient(hParent, lpPoint);
		}*/
		return TRUE;
	}
	return 0;
}

BOOL UIWnd2Manager::ScreenToClient(HWND hWnd, LPRECT lpRect) const
{
	//HWND hParent = GetParent(hWnd);
	RECT rc = {0};
	if(GetWindowRect(hWnd, &rc)) {
		::OffsetRect(lpRect, -rc.left, -rc.top);
		/*if (IsDirectUI(hParent)) {
		return ScreenToClient(hWnd, lpRect);
		} else {
		if(!::ScreenToClient(hParent, (LPPOINT)lpRect))
		return FALSE;
		return ::ScreenToClient(hParent, ((LPPOINT)lpRect)+1);
		}*/
		return TRUE;
	}
	return 0;
}

int UIWnd2Manager::MapWindowPoints(HWND hWnd, HWND hWndTo, LPPOINT lpPoint, UINT nCount) const
{
	if (IsDirectUI(hWnd)) {
		HWND hWndParent = GetParent(hWnd);
		int nRet = MapWindowPoints(hWndParent, hWndTo, lpPoint, nCount);
		RECT rc;
		GetWindowRect(hWnd, &rc);
		ScreenToClient(hWndParent, &rc);
		for (int i = 0; i < nCount; i++)
		{
			lpPoint[i].x += rc.left;
			lpPoint[i].y += rc.top;
		}
		return MAKEWPARAM(LOWORD(nRet)+rc.left, HIWORD(nRet)+rc.top);
	} 
	if (IsDirectUI(hWndTo)) {
		HWND hWndToParent = GetParent(hWndTo);
		int nRet = MapWindowPoints(hWnd, hWndToParent, lpPoint, nCount);
		RECT rc;
		GetWindowRect(hWndTo, &rc);
		ScreenToClient(hWndToParent, &rc);
		for (int i = 0; i < nCount; i++)
		{
			lpPoint[i].x -= rc.left;
			lpPoint[i].y -= rc.top;
		}
		return MAKEWPARAM(LOWORD(nRet)-rc.left, HIWORD(nRet)-rc.top);
	}
	return ::MapWindowPoints(hWnd, hWndTo, lpPoint, nCount);
	return 0;
}

int UIWnd2Manager::MapWindowPoints(HWND hWnd, HWND hWndTo, LPRECT lpRect) const
{
	return MapWindowPoints(hWnd, hWndTo, (LPPOINT)lpRect, 2);
}

// Update and Painting Functions

HDC UIWnd2Manager::BeginPaint(HWND hWnd, LPPAINTSTRUCT lpPaint)
{
	ATLASSERT(lpPaint);
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			if (!phWnd2->m_psRef) {
				HDC hdc = BeginPaint(phWnd2->m_hWndParent, &phWnd2->m_ps);
				ATLASSERT(hdc==phWnd2->m_ps.hdc);
				//phWnd2->m_psRef = SaveDC(hdc);
				::OffsetWindowOrgEx(hdc, -phWnd2->m_rc.left, -phWnd2->m_rc.top, NULL);
				GetRgnBox(phWnd2->m_hRgnInvalidate, &phWnd2->m_ps.rcPaint);
				SelectClipRgn(hdc, phWnd2->m_hRgnInvalidate);
				ValidateRgn(hWnd, NULL); //将无效区域重置
			}
			phWnd2->m_psRef++;
			if (lpPaint) {
				*lpPaint = phWnd2->m_ps;
			}
			return phWnd2->m_ps.hdc;
		} else {
			if (!phWnd2->m_psRef) {
				::BeginPaint(hWnd, &phWnd2->m_ps);
				ATLASSERT(phWnd2->m_ps.hdc);
				CDCHandle dc(phWnd2->m_ps.hdc);
				//ATLASSERT(!phWnd2->m_memDC);
				//phWnd2->m_memDC = new CMemDC(phWnd2->m_ps.hdc, NULL);
				::GetClientRect(hWnd, &phWnd2->m_rc);
				phWnd2->m_memDC.CreateCompatibleDC(dc, &phWnd2->m_rc);
				phWnd2->m_hFont = phWnd2->m_memDC.SelectFont(GetFont(hWnd));
				if (phWnd2->m_rc != phWnd2->m_ps.rcPaint) {
					CRgn rgn;
					if (rgn.CreateRectRgnIndirect(&phWnd2->m_ps.rcPaint)) {
						phWnd2->m_memDC.SelectClipRgn(rgn);
					}
				}
			} 
			phWnd2->m_psRef++;
			if (lpPaint) {
				*lpPaint = phWnd2->m_ps;
				lpPaint->hdc = phWnd2->m_memDC;
			}
			//return *phWnd2->m_memDC;
			return phWnd2->m_memDC;
			return phWnd2->m_ps.hdc;
		}
	} else {
		return ::BeginPaint(hWnd, lpPaint);
	}
	return 0;
}

void UIWnd2Manager::EndPaint(HWND hWnd, LPPAINTSTRUCT lpPaint)
{
	//ATLASSERT(lpPaint);
	HDC hdc = NULL;
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			if (phWnd2->m_psRef) {
				phWnd2->m_psRef--;
				if (!phWnd2->m_psRef) {
					::OffsetWindowOrgEx(hdc, phWnd2->m_rc.left, phWnd2->m_rc.top, NULL);
					//RestoreDC(lpPaint->hdc, phWnd2->m_psRef);
					//phWnd2->m_psRef = 0;
					EndPaint(phWnd2->m_hWndParent, &phWnd2->m_ps);
				}
			}
		} else {
			if (phWnd2->m_psRef) {
				phWnd2->m_psRef--;
				if (!phWnd2->m_psRef) {
					ATLASSERT(phWnd2->m_memDC);
					PAINTEFFECT PE = {0};
					PE.hWnd = hWnd;
					PE.hDstDC = phWnd2->m_ps.hdc;
					PE.hSrcDC = phWnd2->m_memDC;
					SendMessage(hWnd, WM_PAINTEFFECTMSG, (WPARAM)0, (LPARAM)&PE);
					//delete phWnd2->m_memDC;
					//phWnd2->m_memDC = NULL;
					::BitBlt(phWnd2->m_ps.hdc, phWnd2->m_rc.left, phWnd2->m_rc.top, phWnd2->m_rc.Width(), phWnd2->m_rc.Height(), phWnd2->m_memDC, 0, 0, SRCCOPY);
					phWnd2->m_hFont = phWnd2->m_memDC.SelectFont(phWnd2->m_hFont);
					phWnd2->m_memDC.DeleteDC();
					::EndPaint(hWnd, &phWnd2->m_ps);
				}
			}
		}
	} else {
		::EndPaint(hWnd, lpPaint);
	}
}

HDC UIWnd2Manager::GetDC(HWND hWnd)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			HDC hdc = GetDC(phWnd2->m_hWndParent);
			if (hdc) {
				::OffsetWindowOrgEx(hdc, -phWnd2->m_rc.left, -phWnd2->m_rc.top, NULL);
			}
			return hdc;
		} else {
			return ::GetDC(hWnd);
		}
	} else {
		 return ::GetDC(hWnd);
	}
	return 0;
}

HDC UIWnd2Manager::GetWindowDC(HWND hWnd)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			HDC hdc =  GetWindowDC(phWnd2->m_hWndParent);
			if (hdc) {
				::OffsetWindowOrgEx(hdc, -phWnd2->m_rc.left, -phWnd2->m_rc.top, NULL);
			}
			return hdc;
		} else {
			return ::GetWindowDC(hWnd);
		}
	} else {
		return ::GetWindowDC(hWnd);
	}
	return 0;
}

int UIWnd2Manager::ReleaseDC(HWND hWnd, HDC hDC)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			if (hDC) {
				::OffsetWindowOrgEx(hDC, phWnd2->m_rc.left, phWnd2->m_rc.top, NULL);
			}
			return ReleaseDC(phWnd2->m_hWndParent, hDC);
		} else {
			return ::ReleaseDC(hWnd, hDC);
		}
	} else {
		return ::ReleaseDC(hWnd, hDC);
	}
	return 0;
}

void UIWnd2Manager::Print(HWND hWnd, HDC hDC, DWORD dwFlags)
{
	SendMessage(hWnd, WM_PRINT, (WPARAM)hDC, (LPARAM)dwFlags);
}

void UIWnd2Manager::PrintClient(HWND hWnd, HDC hDC, DWORD dwFlags)
{
	SendMessage(hWnd, WM_PRINTCLIENT, (WPARAM)hDC, (LPARAM)dwFlags);
}

BOOL UIWnd2Manager::UpdateWindow(HWND hWnd)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			return UpdateWindow(phWnd2->m_hWndParent);
		} else {
			return ::UpdateWindow(hWnd);
		}
	} else {
		return ::UpdateWindow(hWnd);
	}
	return 0;
}

void UIWnd2Manager::SetRedraw(HWND hWnd, BOOL bRedraw)
{

}

BOOL UIWnd2Manager::GetUpdateRect(HWND hWnd, LPRECT lpRect, BOOL bErase)
{
	ATLASSERT(lpRect);
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if(phWnd2->m_hRgnInvalidate) {
				return GetRgnBox(phWnd2->m_hRgnInvalidate, lpRect);
			}
		}
	} else {
		return ::GetUpdateRect(hWnd, lpRect, bErase);
	}
	return 0;
}

int UIWnd2Manager::GetUpdateRgn(HWND hWnd, HRGN hRgn, BOOL bErase)
{
	ATLASSERT(hRgn);
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if(phWnd2->m_hRgnInvalidate) {
				CombineRgn(hRgn, phWnd2->m_hRgnInvalidate, 0, RGN_COPY);
				RECT rc;
				return GetRgnBox(hRgn, &rc);
			}
		}
	} else {
		return ::GetUpdateRgn(hWnd, hRgn, bErase);
	}
	return ERROR;
}

BOOL UIWnd2Manager::Invalidate(HWND hWnd, BOOL bErase)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			CRect rc = phWnd2->m_rc;
			//ScreenToClient(phWnd2->m_hWndParent, &rc);
			if(phWnd2->m_hRgnInvalidate == NULL) {
				phWnd2->m_hRgnInvalidate = CreateRectRgn(0, 0, rc.Width(), rc.Height());
			} else {
				SetRectRgn(phWnd2->m_hRgnInvalidate, 0, 0, rc.Width(), rc.Height());
			}
			return InvalidateRect(phWnd2->m_hWndParent, &rc, bErase);
		}
	} else {
		//RECT rc;
		//GetClientRect(hWnd, &rc);
		return ::InvalidateRect(hWnd, NULL, bErase);
	}
	return 0;
}

BOOL UIWnd2Manager::InvalidateRect(HWND hWnd, LPCRECT lpRect, BOOL bErase)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if (!(phWnd2->m_dwStyle&WS_VISIBLE)) {
				//SetLastError()
				return FALSE;
			}

			CRect rcClient(0,0,phWnd2->m_rc.Width(),phWnd2->m_rc.Height());
			if (!lpRect) {
				lpRect = &rcClient;
			}
			if(phWnd2->m_hRgnInvalidate == NULL) {
				phWnd2->m_hRgnInvalidate = CreateRectRgnIndirect(lpRect);
			} else {
				HRGN hRgn = CreateRectRgnIndirect(lpRect);
				CombineRgn(phWnd2->m_hRgnInvalidate, phWnd2->m_hRgnInvalidate, hRgn, RGN_OR);
				DeleteObject(hRgn);
			}
			RECT rcInvalidate = *lpRect;
			OffsetRect(&rcInvalidate, phWnd2->m_rc.left, phWnd2->m_rc.top);
			return InvalidateRect(phWnd2->m_hWndParent, &rcInvalidate, bErase);
			//InvalidateRgn(phWnd2->m_hWndParent, phWnd2->m_hRgnInvalidate, bErase);
		}
	} else {
		return ::InvalidateRect(hWnd, lpRect, bErase);
	}
	return 0;
}

BOOL UIWnd2Manager::ValidateRect(HWND hWnd, LPCRECT lpRect)
{
	if (IsDirectUI(hWnd)) {
		BOOL bValid = FALSE;
		if (lpRect) {
			HRGN hRgn = CreateRectRgnIndirect(lpRect);
			bValid = ValidateRgn(hWnd, hRgn);
			DeleteObject(hRgn);
		} else {
			bValid = ValidateRgn(hWnd, NULL);
		}
		return bValid;
	} else {
		return ::ValidateRect(hWnd, lpRect);
	}
	return 0;
}

BOOL UIWnd2Manager::InvalidateRgn(HWND hWnd, HRGN hRgn, BOOL bErase)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if (!(phWnd2->m_dwStyle&WS_VISIBLE)) {
				//SetLastError()
				return FALSE;
			}

			BOOL bOk = FALSE;
			if (!hRgn) {
				if(phWnd2->m_hRgnInvalidate == NULL) {
					phWnd2->m_hRgnInvalidate =  CreateRectRgn(0,0,phWnd2->m_rc.Width(),phWnd2->m_rc.Height());
				} 
				ATLASSERT(phWnd2->m_hRgnInvalidate);
			} else {
				if(phWnd2->m_hRgnInvalidate == NULL) {
					phWnd2->m_hRgnInvalidate =  CreateRectRgn(0,0,0,0);
				} 
				ATLASSERT(phWnd2->m_hRgnInvalidate);
				CombineRgn(phWnd2->m_hRgnInvalidate, phWnd2->m_hRgnInvalidate, hRgn, RGN_OR);
			}
			OffsetRgn(phWnd2->m_hRgnInvalidate, phWnd2->m_rc.left, phWnd2->m_rc.top);
			bOk = InvalidateRgn(phWnd2->m_hWndParent, phWnd2->m_hRgnInvalidate, bErase);
			OffsetRgn(phWnd2->m_hRgnInvalidate, -phWnd2->m_rc.left, -phWnd2->m_rc.top);
			return bOk;
		}
	} else {
		return ::InvalidateRgn(hWnd, hRgn, bErase);
	}
	return 0;
}

BOOL UIWnd2Manager::ValidateRgn(HWND hWnd, HRGN hRgn)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if(phWnd2->m_hRgnInvalidate) {
				if(hRgn) {
					CombineRgn(phWnd2->m_hRgnInvalidate, phWnd2->m_hRgnInvalidate, hRgn, RGN_DIFF);
				} else {
					DeleteObject(phWnd2->m_hRgnInvalidate);
					phWnd2->m_hRgnInvalidate = NULL;
				}
			}
			return TRUE;
		}
	} else {
		return ::ValidateRgn(hWnd, hRgn);
	}
	return FALSE;
}

BOOL UIWnd2Manager::ShowWindow(HWND hWnd, int nCmdShow)
{
	if (IsDirectUI(hWnd)) {
		DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
		if (nCmdShow && !(dwStyle&WS_VISIBLE)) {
			SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_VISIBLE);
		} else if(!nCmdShow && (dwStyle&WS_VISIBLE)) {
			SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_VISIBLE);
		}
		_ShowWindow(hWnd, nCmdShow);
		return nCmdShow;
	} else {
		return ::ShowWindow(hWnd, nCmdShow);
	}
	return 0;
}

BOOL UIWnd2Manager::_ShowWindow(HWND hWnd, int nCmdShow)
{
	HWND hWndChild = FindhWnd2FirstChild(hWnd);
	for (; hWndChild!=NULL; hWndChild = FindhWnd2Next(hWndChild))
	{
		HUIWnd2* phWnd2Child = FindpHUIWnd2(hWndChild);
		if (IsDirectUI(hWndChild)) {
			_ShowWindow(hWndChild, nCmdShow);
		} else {
			if (nCmdShow && (phWnd2Child->m_dwStyle&WS_VISIBLE)) {
				if (!::IsWindowVisible(hWndChild)) {
					::ShowWindow(hWndChild, SW_RESTORE);
				}
			} else if (!nCmdShow) {
				if (::IsWindowVisible(hWndChild)) {
					//记住之前状态
					phWnd2Child->m_dwStyle = ::GetWindowLong(hWndChild, GWL_STYLE); 
					phWnd2Child->m_dwExStyle = ::GetWindowLong(hWndChild, GWL_EXSTYLE);
					//隐藏窗口
					::ShowWindow(hWndChild, SW_HIDE);
				}
			}
		}
	}
	return TRUE;
}

/*BOOL UIWnd2Manager::IsWindowVisible(HWND hWnd) const
{

}*/

BOOL UIWnd2Manager::ShowOwnedPopups(HWND hWnd, BOOL bShow)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			return ShowOwnedPopups(phWnd2->m_hWndParent, bShow);
		} else {
			return ::ShowOwnedPopups(hWnd, bShow);
		}
	} else {
		return ::ShowOwnedPopups(hWnd, bShow);
	}
	return 0;
}

HDC UIWnd2Manager::GetDCEx(HWND hWnd, HRGN hRgnClip, DWORD flags)
{
	/*HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			return GetDCEx(phWnd2->m_hWndParent, hRgnClip, flags);
		} else {
			return ::GetDCEx(hWnd, hRgnClip, flags);
		}
	} else {
		return ::GetDCEx(hWnd, hRgnClip, flags);
	}*/
	return 0;
}

BOOL UIWnd2Manager::LockWindowUpdate(HWND hWnd, BOOL bLock)
{
	
	return 0;
}

BOOL UIWnd2Manager::RedrawWindow(HWND hWnd, LPCRECT lpRectUpdate, HRGN hRgnUpdate, UINT flags)
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		if (IsDirectUI(hWnd)) {
			::OffsetRect(const_cast<LPRECT>(lpRectUpdate), phWnd2->m_rc.left, phWnd2->m_rc.right);
			::OffsetRgn(hRgnUpdate, phWnd2->m_rc.left, phWnd2->m_rc.right);
			BOOL bRes = RedrawWindow(phWnd2->m_hWndParent, lpRectUpdate, hRgnUpdate, flags);
			::OffsetRect(const_cast<LPRECT>(lpRectUpdate), -phWnd2->m_rc.left, -phWnd2->m_rc.right);
			::OffsetRgn(hRgnUpdate, -phWnd2->m_rc.left, -phWnd2->m_rc.right);
			return bRes;
		} else {
			return ::RedrawWindow(hWnd, lpRectUpdate, hRgnUpdate, flags);
		}
	} else {
		return ::RedrawWindow(hWnd, lpRectUpdate, hRgnUpdate, flags);
	}
	return 0;
}

// Timer Functions

UINT UIWnd2Manager::SetTimer(HWND hWnd, UINT nIDEvent, UINT nElapse)
{
	if (IsDirectUI(hWnd)) {
		HWND hSafeWnd = GetSafeHwnd(hWnd);
		UINT nOldIDEvent = FindTimer(hWnd, nIDEvent);
		UINT nSafeIDEvent = ::SetTimer(hSafeWnd, nOldIDEvent, nElapse, NULL);
		if (nOldIDEvent==0) {
			if (nIDEvent==0) {
				nIDEvent = nSafeIDEvent;
			}
			CComAutoCritSectionLock Lock(m_Wnd2Section);
			DWORD dwThreadID = GetWindowThreadID(hSafeWnd);
			HUIWND2ThreadData& tWnd2Data = m_ThreadWnd2Data[dwThreadID];
			HUIWND2ThreadData::tagTimerInfo& tTimerInfo = tWnd2Data.nIDEvent2TimerInfo[nSafeIDEvent];
			tTimerInfo.hWnd = hWnd;
			tTimerInfo.nIDEvent = nIDEvent;
			Lock.Unlock();
		}
		return nIDEvent;
	} else {
		return ::SetTimer(hWnd, nIDEvent, nElapse, NULL);
	}
}

UINT UIWnd2Manager::FindTimer(HWND hWnd, UINT nIDEvent, BOOL bErase)
{
	ASSERT (IsDirectUI(hWnd));
	HWND hSafeWnd = GetSafeHwnd(hWnd);
	UINT nSafeIDEvent = 0;
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	DWORD dwThreadID = GetWindowThreadID(hSafeWnd);
	HUIWND2ThreadData& tWnd2Data = m_ThreadWnd2Data[dwThreadID];
	HUIWND2ThreadData::TimerID2TimerInfo::iterator it = tWnd2Data.nIDEvent2TimerInfo.begin();
	for (; it!=tWnd2Data.nIDEvent2TimerInfo.end(); ++it)
	{
		if (it->second.hWnd==hWnd && it->second.nIDEvent==nIDEvent) {
			nSafeIDEvent = it->first;
			if (bErase) {
				tWnd2Data.nIDEvent2TimerInfo.erase(it);
			}
			break;
		}
	}
	Lock.Unlock();
	if (nSafeIDEvent) {
		return nSafeIDEvent;
	}
	return FALSE;
}

BOOL UIWnd2Manager::PostTimer(UINT_PTR nSafeIDEvent)
{
	BOOL bFind = FALSE;
	HUIWND2ThreadData::tagTimerInfo tTimerInfo = {0};
	CComAutoCritSectionLock Lock(m_Wnd2Section);
	DWORD dwThreadID = GetCurrentThreadId();
	HUIWND2ThreadData& tWnd2Data = m_ThreadWnd2Data[dwThreadID];
	HUIWND2ThreadData::TimerID2TimerInfo::iterator it = tWnd2Data.nIDEvent2TimerInfo.find(nSafeIDEvent);
	if (it!=tWnd2Data.nIDEvent2TimerInfo.end()) {
		tTimerInfo = it->second;
		bFind = TRUE;
	}
	Lock.Unlock();
	if (bFind) {
		if (IsDirectUI(tTimerInfo.hWnd)) {
			SendMessage(tTimerInfo.hWnd, WM_TIMER, tTimerInfo.nIDEvent, NULL);
		}
		return TRUE;
	}
	return FALSE;
}

BOOL UIWnd2Manager::KillTimer(HWND hWnd, UINT nIDEvent)
{
	if (IsDirectUI(hWnd)) {
		HWND hSafeWnd = GetSafeHwnd(hWnd);
		UINT nSafeIDEvent = FindTimer(hWnd, nIDEvent, TRUE);
		if (nSafeIDEvent) {
			return ::KillTimer(hSafeWnd, nSafeIDEvent);
		}
		return FALSE;
	}
	return ::KillTimer(hWnd, nIDEvent);
}

// Window State Functions

BOOL UIWnd2Manager::IsWindowEnabled(HWND hWnd) const
{
	ATLASSERT(IsDirectUI(hWnd));
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	return dwStyle & WS_DISABLED ? FALSE : TRUE;
}

BOOL UIWnd2Manager::EnableWindow(HWND hWnd, BOOL bEnable)
{
	ATLASSERT(IsDirectUI(hWnd));
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	if (bEnable && (dwStyle&WS_DISABLED)) {
		SetWindowLong(hWnd, GWL_STYLE, dwStyle & ~WS_DISABLED);
	} else if(!bEnable && !(dwStyle&WS_DISABLED)) {
		SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_DISABLED);
	}
	return bEnable;
	return 0;
}

HWND UIWnd2Manager::SetActiveWindow(HWND hWnd)
{
	return 0;
}

HWND UIWnd2Manager::SetHover(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (hWnd == m_hWndHover) {
		return m_hWndHover;
	}
	HWND hWndOldHover = m_hWndHover;
	if (IsDirectUI(hWndOldHover)) {
		SendMessage(hWndOldHover, WM_MOUSELEAVE, wParam, lParam);
	}
	m_hWndHover = hWnd;
	if (m_hWndHover) {
		SendMessage(m_hWndHover, WM_MOUSEHOVER, wParam, lParam);
	}
	return hWndOldHover;
}

HWND UIWnd2Manager::GetHover()
{
	return m_hWndHover;
}

HWND UIWnd2Manager::SetCapture(HWND hWnd)
{
	m_hWndCapture = hWnd;
	while (hWnd && IsDirectUI(hWnd)) 
	{
		hWnd = GetParent(hWnd);
	}
	if (hWnd) {
		return ::SetCapture(hWnd);
	}
	return NULL;
}

HWND UIWnd2Manager::GetCapture(void)
{
	return m_hWndCapture;
}

BOOL UIWnd2Manager::ReleaseCapture()
{
	if (m_hWndCapture) {
		m_hWndCapture = NULL;
	}
	return ::ReleaseCapture();
}

HWND UIWnd2Manager::SetFocus(HWND hWnd, BOOL bKillFocus, BOOL bSetFocus)
{
	if (hWnd == m_hWndFocus) {
		return m_hWndFocus;
	}
	HWND hWndOldFocus = m_hWndFocus;
	if (hWndOldFocus && bKillFocus) {
		SendMessage(hWndOldFocus, WM_KILLFOCUS, (WPARAM)hWnd, (LPARAM)0);
	}
	m_hWndFocus = hWnd;
	if (GetStyle(hWnd) & WS_TABSTOP) {
		m_hWndTabStop = hWnd;
	}
	if (m_hWndFocus && bSetFocus) {
		SendMessage(m_hWndFocus, WM_SETFOCUS, (WPARAM)hWndOldFocus, (LPARAM)0);
	}
	return hWndOldFocus;
	return 0;
}

HWND UIWnd2Manager::SetFocus(HWND hWnd)
{
	if (IsDirectUI(hWnd)) {
		HWND hRealWnd = GetSafeHwnd(hWnd);
		if(hRealWnd != ::GetFocus()) {
			SetFocus(hRealWnd);
		}
		return SetFocus(hWnd, TRUE, TRUE);
	} else {
		if (IsDirectUI(m_hWndFocus)) {
			SetFocus(NULL, TRUE, FALSE);
		}
		m_hWndFocus = hWnd;
		return ::SetFocus(hWnd);
	}
}

HWND UIWnd2Manager::GetFocus() 
{
	return m_hWndFocus;
}

// Dialog-Box Item Functions

BOOL UIWnd2Manager::CheckDlgButton(HWND hWnd, int nIDButton, UINT nCheck)
{
	return (BOOL)SendDlgItemMessage(hWnd, nIDButton, BM_SETCHECK, nCheck, 0L);
}

BOOL UIWnd2Manager::CheckRadioButton(HWND hWnd, int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
{
	HWND hWndItem = GetDlgItem(hWnd, nIDCheckButton);
	if (hWndItem) {
		DWORD dwStyle = GetStyle(hWndItem);
		if (dwStyle & BS_RADIOBUTTON) {
			SendMessage(hWndItem, BM_SETCHECK, BST_CHECKED, 0L);
			//向前
			if(!(dwStyle & WS_GROUP)) {
				HWND hPrev = hWndItem;
				do 
				{
					hPrev = FindhWnd2Prev(hPrev);
					if (hPrev == NULL) {
						break;
					}
					SendMessage(hPrev, BM_SETCHECK, BST_UNCHECKED, 0L);
				} while (!(GetStyle(hPrev) & WS_GROUP));
			}
			//向后
			do 
			{
				hWndItem = FindhWnd2Next(hWndItem);
				if (hWndItem == NULL) {
					break;
				}
				SendMessage(hWndItem, BM_SETCHECK, BST_UNCHECKED, 0L);
			} while (!(GetStyle(hWndItem) & WS_GROUP));
			//
			return TRUE;
		}
	}
	return FALSE;
}

int UIWnd2Manager::DlgDirList(HWND hWnd, LPTSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT nFileType)
{
	return 0;
}

int UIWnd2Manager::DlgDirListComboBox(HWND hWnd, LPTSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT nFileType)
{
	return 0;
}

BOOL UIWnd2Manager::DlgDirSelect(HWND hWnd, LPTSTR lpString, int nCount, int nIDListBox)
{
	return 0;
}

BOOL UIWnd2Manager::DlgDirSelectComboBox(HWND hWnd, LPTSTR lpString, int nCount, int nIDComboBox)
{
	return 0;
}

UINT UIWnd2Manager::GetDlgItemInt(HWND hWnd, int nID, BOOL* lpTrans, BOOL bSigned)
{
	if (IsDirectUI(hWnd)) {
		CString strText;
		GetWindowText(hWnd, strText);
		if (bSigned) {
			return (UINT)_ttoi(strText);
		} else {
			return (UINT)_ttoi64(strText);
		}
	}
	return ::GetDlgItemInt(hWnd, nID, lpTrans, bSigned);
	return 0;
}

UINT UIWnd2Manager::GetDlgItemText(HWND hWnd, int nID, LPTSTR lpStr, int nMaxCount)
{
	HWND hWndItem = GetDlgItem(hWnd, nID);
	if (hWndItem) {
		return GetWindowText(hWndItem, lpStr, nMaxCount);
	}
	return 0;
}
BOOL UIWnd2Manager::GetDlgItemText(HWND hWnd, int nID, BSTR& bstrText)
{
	return 0;
}
HWND UIWnd2Manager::GetNextDlgGroupItem(HWND hWnd, HWND hWndCtl, BOOL bPrevious) const
{
	if (hWndCtl) {
		if (bPrevious) {
			DWORD dwStyle = GetStyle(hWndCtl);
			if (dwStyle & WS_GROUP) {
				return NULL;
			}
			HWND hWndPrev = FindhWnd2Prev(hWndCtl);
			if (hWndPrev) {
				dwStyle = GetStyle(hWndPrev);
				if (dwStyle & WS_GROUP) {
					return hWndPrev;
				} else {
					return GetNextDlgGroupItem(hWnd, hWndPrev, bPrevious);
				}
			}
		} else {
			HWND hWndNext = FindhWnd2Next(hWndCtl);
			if (hWndNext) {
				DWORD dwStyle = GetStyle(hWndNext);
				if (dwStyle & WS_GROUP) {
					return hWndNext;
				} else {
					return GetNextDlgGroupItem(hWnd, hWndNext, bPrevious);
				}
			}
		}
	}
	return 0;
}

HWND UIWnd2Manager::GetNextDlgTabItem(HWND hWnd, HWND hWndCtl, BOOL bPrevious) const
{
	if (hWndCtl) {
		if (bPrevious) {
			DWORD dwStyle = GetStyle(hWndCtl);
			if (dwStyle & WS_TABSTOP) {
				return NULL;
			}
			HWND hWndPrev = FindhWnd2Prev(hWndCtl);
			if (hWndPrev) {
				dwStyle = GetStyle(hWndPrev);
				if (dwStyle & WS_TABSTOP) {
					return hWndPrev;
				} else {
					return GetNextDlgGroupItem(hWnd, hWndPrev, bPrevious);
				}
			}
		} else {
			HWND hWndNext = FindhWnd2Next(hWndCtl);
			if (hWndNext) {
				DWORD dwStyle = GetStyle(hWndNext);
				if (dwStyle & WS_TABSTOP) {
					return hWndNext;
				} else {
					return GetNextDlgGroupItem(hWnd, hWndNext, bPrevious);
				}
			}
		}
	}
	return 0;
}

UINT UIWnd2Manager::IsDlgButtonChecked(HWND hWnd, int nIDButton) const
{
	if (IsDirectUI(hWnd)) {
		return GetState(hWnd) & BST_CHECKED ? TRUE : FALSE;
	}
	return ::IsDlgButtonChecked(hWnd, nIDButton);
	return 0;
}

LRESULT UIWnd2Manager::SendDlgItemMessage(HWND hWnd, int nID, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND hWndItem = GetDlgItem(hWnd, nID);
	if (hWndItem) {
		return SendMessage(hWndItem, message, wParam, lParam);
	}
	return 0L;
}

BOOL UIWnd2Manager::SetDlgItemInt(HWND hWnd, int nID, UINT nValue, BOOL bSigned)
{
	CString strText;
	if (bSigned) {
		strText.Format(_T("%d"), nValue);
	} else {
		strText.Format(_T("%u"), nValue);
	}
	return SetWindowText(hWnd, strText);
	return 0;
}

BOOL UIWnd2Manager::SetDlgItemText(HWND hWnd, int nID, LPCTSTR lpszString)
{
	HWND hWndItem = GetDlgItem(hWnd, nID);
	if (hWndItem) {
		return SetWindowText(hWndItem, lpszString);
	}
	return 0;
}

#ifndef _ATL_NO_HOSTING
HRESULT UIWnd2Manager::GetDlgControl(HWND hWnd, int nID, REFIID iid, void** ppUnk)
{
	return 0;
}
#endif //!_ATL_NO_HOSTING

// Scrolling Functions

int UIWnd2Manager::GetScrollPos(HWND hWnd, int nBar) const
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			switch(nBar)
			{
			case SB_HORZ:
				ASSERT(phWnd2->m_pHScrollInfo);
				if(phWnd2->m_pHScrollInfo) {
					return phWnd2->m_pHScrollInfo->nPos;
				}
				break;
			case SB_VERT:
				ASSERT(phWnd2->m_pVScrollInfo);
				if(phWnd2->m_pVScrollInfo) {
					return phWnd2->m_pVScrollInfo->nPos;
				}
				break;
			case SB_CTL:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_GETPOS, 0, 0);
				break;
			}
		}
	} else {
		return ::GetScrollPos(hWnd, nBar);
	}
	return 0;
}

BOOL UIWnd2Manager::GetScrollRange(HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos) const
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if(lpMinPos) {
				*lpMinPos = 0;
			}
			if(lpMaxPos) {
				*lpMaxPos = 0;
			}
			switch(nBar)
			{
			case SB_HORZ:
				ASSERT(phWnd2->m_pHScrollInfo);
				if(phWnd2->m_pHScrollInfo) {
					if(lpMinPos) {
						*lpMinPos = phWnd2->m_pHScrollInfo->nMin;
					}
					if(lpMaxPos) {
						*lpMaxPos = phWnd2->m_pHScrollInfo->nMax;
					}
				}
				break;
			case SB_VERT:
				ASSERT(phWnd2->m_pVScrollInfo);
				if(phWnd2->m_pVScrollInfo) {
					if(lpMinPos) {
						*lpMinPos = phWnd2->m_pVScrollInfo->nMin;
					}
					if(lpMaxPos) {
						*lpMaxPos = phWnd2->m_pVScrollInfo->nMax;
					}
				}
				break;
			case SB_CTL:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_GETRANGE, (WPARAM)lpMinPos, (LPARAM)lpMaxPos);
				break;
			}
			return TRUE;
		}
	} else {
		return ::GetScrollRange(hWnd, nBar, lpMinPos, lpMaxPos);
	}
	return 0;
}

BOOL UIWnd2Manager::ScrollWindow(HWND hWnd, int xAmount, int yAmount, LPCRECT lpRect, LPCRECT lpClipRect)
{
	return ScrollWindowEx(hWnd, xAmount, yAmount, lpRect, lpClipRect, NULL, NULL, SW_SCROLLCHILDREN|SW_ERASE|SW_INVALIDATE);
	return 0;
}

int UIWnd2Manager::ScrollWindowEx(HWND hWnd, int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate, UINT uFlags)
{
	if (IsDirectUI(hWnd)) {
		/*RECT rcScroll;
		if (lpRectScroll) {
			rcScroll = *lpRectScroll;
		} else {
			GetClientRect(hWnd, &rcScroll);
		}*/
		/*if(dx!=0) {
			HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
			if (phWnd2) {
				phWnd2->m_pHScrollBarInfo->
			}
		}*/
		if(uFlags&SW_SCROLLCHILDREN) {
			HWND hWndChild = FindhWnd2FirstChild(hWnd);
			for (; hWndChild!=NULL; hWndChild = FindhWnd2Next(hWndChild))
			{
				RECT rcWndChild;
				GetWindowRect(hWndChild, &rcWndChild);
				ScreenToClient(hWnd, &rcWndChild);
				::OffsetRect(&rcWndChild, dx, dy);
				MoveWindow(hWndChild, &rcWndChild);
			}
		}
		if (uFlags&(SW_ERASE|SW_INVALIDATE)) {
			Invalidate(hWnd, (uFlags&SW_ERASE)?TRUE:FALSE);
		}
	} else {
		return ::ScrollWindowEx(hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
	}
	return 0;
}

int UIWnd2Manager::ScrollWindowEx(HWND hWnd, int dx, int dy, UINT uFlags, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate)
{
	return ScrollWindowEx(hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
}

int UIWnd2Manager::SetScrollPos(HWND hWnd, int nBar, int nPos, BOOL bRedraw)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			int nOldPos = 0;
			switch(nBar)
			{
			case SB_HORZ:
				ASSERT(phWnd2->m_pHScrollInfo);
				if(phWnd2->m_pHScrollInfo) {
					nOldPos = phWnd2->m_pHScrollInfo->nPos;
					phWnd2->m_pHScrollInfo->nPos = nPos;
				}
				break;
			case SB_VERT:
				ASSERT(phWnd2->m_pVScrollInfo);
				if(phWnd2->m_pVScrollInfo) {
					nOldPos = phWnd2->m_pVScrollInfo->nPos;
					phWnd2->m_pVScrollInfo->nPos = nPos;
				}
				break;
			case SB_CTL:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_SETPOS, (WPARAM)nPos, (LPARAM)bRedraw);
				break;
			}
			return nOldPos;
		}
	} else {
		return ::SetScrollPos(hWnd, nBar, nPos, bRedraw);
	}
	return 0;
}

BOOL UIWnd2Manager::SetScrollRange(HWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			int nOldPos = 0;
			switch(nBar)
			{
			case SB_HORZ:
				ASSERT(phWnd2->m_pHScrollInfo);
				if(phWnd2->m_pHScrollInfo) {
					nOldPos = phWnd2->m_pHScrollInfo->nPos;
					phWnd2->m_pHScrollInfo->nMin = nMinPos;
					phWnd2->m_pHScrollInfo->nMax = nMaxPos;
				}
				break;
			case SB_VERT:
				ASSERT(phWnd2->m_pVScrollInfo);
				if(phWnd2->m_pVScrollInfo) {
					nOldPos = phWnd2->m_pVScrollInfo->nPos;
					phWnd2->m_pVScrollInfo->nMin = nMinPos;
					phWnd2->m_pVScrollInfo->nMax = nMaxPos;
				}
				break;
			case SB_CTL:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_SETRANGE, (WPARAM)nMinPos, (LPARAM)nMaxPos);
				break;
			}
			return nOldPos;
		}
	} else {
		return ::SetScrollRange(hWnd, nBar, nMinPos, nMaxPos, bRedraw);
	}
	return 0;
}

BOOL UIWnd2Manager::ShowScrollBar(HWND hWnd, UINT nBar, BOOL bShow)
{	
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if(nBar==SB_CTL) {
				if(phWnd2->m_dwStyle&SBS_VERT) {
					nBar = SB_VERT;
				} else {
					nBar = SB_HORZ;
				}
			}
			if(nBar==SB_BOTH || nBar==SB_HORZ) {
				ASSERT(phWnd2->m_pHScrollBarInfo);
				if(phWnd2->m_pHScrollBarInfo) {
					if(bShow) {
						phWnd2->m_pHScrollBarInfo->rgstate[0] &= ~STATE_SYSTEM_INVISIBLE;
					} else {
						phWnd2->m_pHScrollBarInfo->rgstate[0] |= STATE_SYSTEM_INVISIBLE;
					}
				}
			}
			if(nBar==SB_BOTH || nBar==SB_VERT) {
				ASSERT(phWnd2->m_pVScrollBarInfo);
				if(phWnd2->m_pVScrollBarInfo) {
					if(bShow) {
						phWnd2->m_pVScrollBarInfo->rgstate[0] &= ~STATE_SYSTEM_INVISIBLE;
					} else {
						phWnd2->m_pVScrollBarInfo->rgstate[0] |= STATE_SYSTEM_INVISIBLE;
					}
				}
			}
			return TRUE;
		}
	} else {
		return ::ShowScrollBar(hWnd, nBar, bShow);
	}
	return 0;
}

BOOL UIWnd2Manager::EnableScrollBar(HWND hWnd, UINT uSBFlags, UINT uArrowFlags)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			if(uSBFlags==SB_CTL) {
				if(phWnd2->m_dwStyle&SBS_VERT) {
					uSBFlags = SBS_VERT;
				} else {
					uSBFlags = SBS_HORZ;
				}
			}
			switch(uSBFlags)
			{
			case SB_HORZ:
				ASSERT(phWnd2->m_pHScrollBarInfo);
				if(phWnd2->m_pHScrollBarInfo) {
					if(uArrowFlags & ESB_DISABLE_LEFT) {
						phWnd2->m_pHScrollBarInfo->rgstate[5] |= STATE_SYSTEM_UNAVAILABLE;
					} else {
						phWnd2->m_pHScrollBarInfo->rgstate[5] &= ~STATE_SYSTEM_UNAVAILABLE;
					}
					if(uArrowFlags & ESB_DISABLE_RIGHT) {
						phWnd2->m_pHScrollBarInfo->rgstate[1] |= STATE_SYSTEM_UNAVAILABLE;
					} else {
						phWnd2->m_pHScrollBarInfo->rgstate[1] &= ~STATE_SYSTEM_UNAVAILABLE;
					}
					return TRUE;
				}
				break;
			case SB_VERT:
				ASSERT(phWnd2->m_pVScrollBarInfo);
				if(phWnd2->m_pVScrollBarInfo) {
					if(uArrowFlags & ESB_DISABLE_UP) {
						phWnd2->m_pVScrollBarInfo->rgstate[1] |= STATE_SYSTEM_UNAVAILABLE;
					} else {
						phWnd2->m_pVScrollBarInfo->rgstate[1] &= ~STATE_SYSTEM_UNAVAILABLE;
					}
					if(uArrowFlags & ESB_DISABLE_DOWN) {
						phWnd2->m_pVScrollBarInfo->rgstate[5] |= STATE_SYSTEM_UNAVAILABLE;
					} else {
						phWnd2->m_pVScrollBarInfo->rgstate[5] &= ~STATE_SYSTEM_UNAVAILABLE;
					}
					return TRUE;
				}
				break;
			case SB_CTL:
				//EnableWindow()
				//return phWnd2->wc.lpfnWndProc(hWnd, SBM_SETRANGE, (WPARAM)nMinPos, (LPARAM)nMaxPos);
				break;
			}
		}
	} else {
		return ::EnableScrollBar(hWnd, uSBFlags, uArrowFlags);
	}
	return 0;
}

// Window Access Functions

HWND UIWnd2Manager::ChildWindowFromPoint(HWND hWnd, POINT point) const
{
	return ChildWindowFromPointEx(hWnd, point, 0);
	return 0;
}

#define CWP_SKIPDIRECTUIWND		0X8000
#define CWP_SKIPNODIRECTUIWND	0X4000

HWND UIWnd2Manager::ChildWindowFromPointEx(HWND hWnd, POINT point, UINT uFlags) const
{
	HWND hChild = FindhWnd2FirstChild(hWnd);
	while(hChild) 
	{
		BOOL bContinue = FALSE;
		if (uFlags) {
			DWORD dwStyle = GetStyle(hChild);
			if (uFlags & CWP_SKIPINVISIBLE) {
				if (!(dwStyle & WS_VISIBLE)) {
					bContinue = TRUE;
				}
			}
			if (uFlags & CWP_SKIPDISABLED) {
				if (dwStyle & WS_DISABLED) {
					bContinue = TRUE;
				}
			}
			if (uFlags & CWP_SKIPTRANSPARENT) {
				if (GetExStyle(hChild) & WS_EX_TRANSPARENT) {
					bContinue = TRUE;
				}
			}
			if (uFlags & CWP_SKIPDIRECTUIWND) {
				if (IsDirectUI(hChild)) {
					bContinue = TRUE;
				}
			}
			if (uFlags & CWP_SKIPNODIRECTUIWND) {
				if (!IsDirectUI(hChild)) {
					bContinue = TRUE;
				}
			}
		}
		if (!bContinue) {
			RECT rcChild;
			GetWindowRect(hChild, &rcChild);
			ScreenToClient(hWnd, &rcChild);
			if (::PtInRect(&rcChild, point)) {
				break;
			}
		}
		hChild = FindhWnd2Next(hChild);
	}
	return hChild;
	return 0;
}

HWND UIWnd2Manager::GetTopWindow(HWND hWnd) const
{
	do
	{
		hWnd = GetParent(hWnd);
	}while (hWnd && !::IsWindow(hWnd));
	if (hWnd) {
		return ::GetTopWindow(hWnd);
	}
	return 0;
}

HWND UIWnd2Manager::GetWindow(HWND hWnd, UINT nCmd) const
{
	switch(nCmd)
	{
	case GW_HWNDFIRST:
		{
			return GetWindow(GetParent(hWnd),GW_CHILD);
		}
		break;
	case GW_HWNDLAST:
		{
			return FindhWnd2LastChild(GetParent(hWnd));
		}
		break;
	case GW_HWNDNEXT:
		{
			return FindhWnd2Next(hWnd);
		}
		break;
	case GW_HWNDPREV:
		{
			return FindhWnd2Prev(hWnd);
		}
		break;
	case GW_OWNER:
		{

		}
		break;
	case GW_CHILD:
		{
			return FindhWnd2FirstChild(hWnd);
		}
		break;
	}
	return 0;
}

HWND UIWnd2Manager::GetLastActivePopup(HWND hWnd) const
{
	return 0;
}

BOOL UIWnd2Manager::IsChild(HWND hWnd, HWND hWndChild) const
{
	HWND hChild = FindhWnd2FirstChild(hWnd);
	while(hChild) 
	{
		if (hWndChild == hChild) {
			break;
		}
		hChild = FindhWnd2Next(hChild);
	}
	return (BOOL)hChild;
	return 0;
}

HWND UIWnd2Manager::GetParent(HWND hWnd) const
{
	return (HWND)GetWindowLong(hWnd, GWL_HWNDPARENT);
}

HWND UIWnd2Manager::SetParent(HWND hWnd, HWND hWndNewParent)
{
	return (HWND)SetWindowLong(hWnd, GWL_HWNDPARENT, (LONG)hWndNewParent);
}

HWND UIWnd2Manager::GetSafeHwnd(HWND hWnd) const
{
	if (IsDirectUI(hWnd)) {
		do 
		{
			hWnd = GetParent(hWnd);
		} while (IsDirectUI(hWnd));
		return hWnd;
	}
	return hWnd;
}

// Window Tree Access

int UIWnd2Manager::GetDlgCtrlID(HWND hWnd) const
{
	return (int)GetWindowLong(hWnd, GWL_ID);
	return 0;
}

int UIWnd2Manager::SetDlgCtrlID(HWND hWnd, int nID)
{
	return (int)SetWindowLong(hWnd, GWL_ID, nID);
	return 0;
}

HWND UIWnd2Manager::GetDlgItem(HWND hWnd, int nID) const
{
	HWND hChild = FindhWnd2FirstChild(hWnd);
	while(hChild) 
	{
		if (nID == GetDlgCtrlID(hChild)) {
			break;
		}
		hChild = FindhWnd2Next(hChild);
	}
	return hChild;
	return 0;
}

// Alert Functions

BOOL UIWnd2Manager::FlashWindow(HWND hWnd, BOOL bInvert)
{
	return 0;
}

int UIWnd2Manager::MessageBox(HWND hWnd, LPCTSTR lpszText, LPCTSTR lpszCaption, UINT nType)
{
	return ::MessageBox(GetTopWindow(hWnd), lpszText, lpszCaption, nType);
	return 0;
}

// Clipboard Functions

BOOL UIWnd2Manager::ChangeClipboardChain(HWND hWnd, HWND hWndNewNext)
{
	return 0;
}

HWND UIWnd2Manager::SetClipboardViewer(HWND hWnd)
{
	return 0;
}

BOOL UIWnd2Manager::OpenClipboard(HWND hWnd)
{
	return 0;
}

// Caret Functions

BOOL UIWnd2Manager::CreateCaret(HWND hWnd, HBITMAP hBitmap)
{
	return 0;
}

BOOL UIWnd2Manager::CreateSolidCaret(HWND hWnd, int nWidth, int nHeight)
{
	return 0;
}

BOOL UIWnd2Manager::CreateGrayCaret(HWND hWnd, int nWidth, int nHeight)
{
	return 0;
}

BOOL UIWnd2Manager::HideCaret(HWND hWnd)
{
	return 0;
}

BOOL UIWnd2Manager::ShowCaret(HWND hWnd)
{
	return 0;
}

#ifdef _INC_SHELLAPI
// Drag-Drop Functions
void UIWnd2Manager::DragAcceptFiles(HWND hWnd, BOOL bAccept)
{

}
#endif

// Icon Functions

HICON UIWnd2Manager::SetIcon(HWND hWnd, HICON hIcon, BOOL bBigIcon)
{
	return 0;
}

HICON UIWnd2Manager::GetIcon(HWND hWnd, BOOL bBigIcon) const
{
	return 0;
}

// Help Functions

BOOL UIWnd2Manager::WinHelp(HWND hWnd, LPCTSTR lpszHelp, UINT nCmd, DWORD dwData)
{
	return 0;
}

BOOL UIWnd2Manager::SetWindowContextHelpId(HWND hWnd, DWORD dwContextHelpId)
{
	return 0;
}

DWORD UIWnd2Manager::GetWindowContextHelpId(HWND hWnd) const
{
	return 0;
}

// Hot Key Functions

int UIWnd2Manager::SetHotKey(HWND hWnd, WORD wVirtualKeyCode, WORD wModifiers)
{
	return 0;
}

DWORD UIWnd2Manager::GetHotKey(HWND hWnd) const
{
	return 0;
}

// Misc. Operations

//N new
BOOL UIWnd2Manager::GetScrollInfo(HWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			switch(nBar)
			{
			case SB_HORZ:
				if(phWnd2->m_pHScrollInfo) {
					*lpScrollInfo = *phWnd2->m_pHScrollInfo;
					return TRUE;
				}
				break;
			case SB_VERT:
				if(phWnd2->m_pVScrollInfo) {
					*lpScrollInfo = *phWnd2->m_pVScrollInfo;
					return TRUE;
				}
				break;
			case SB_CTL:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_GETSCROLLINFO, 0, (LPARAM)lpScrollInfo);
				break;
			}
		}
	} else {
		return ::GetScrollInfo(hWnd, nBar, lpScrollInfo);
	}
	return 0;
}
BOOL UIWnd2Manager::SetScrollInfo(HWND hWnd, int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			switch(nBar)
			{
			case SB_HORZ:
				ASSERT(phWnd2->m_pHScrollInfo);
				if(phWnd2->m_pHScrollInfo) {
					*phWnd2->m_pHScrollInfo = *lpScrollInfo;
					return TRUE;
				}
				break;
			case SB_VERT:
				ASSERT(phWnd2->m_pVScrollInfo);
				if(phWnd2->m_pVScrollInfo) {
					*phWnd2->m_pVScrollInfo = *lpScrollInfo;
					return TRUE;
				}
				break;
			case SB_CTL:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_SETSCROLLINFO, 0, (LPARAM)lpScrollInfo);
				break;
			}
		}
	} else {
		return ::SetScrollInfo(hWnd, nBar, lpScrollInfo, bRedraw);
	}
	return 0;
}

BOOL UIWnd2Manager::GetScrollBarInfo(HWND hWnd, LONG idObject, PSCROLLBARINFO pScrollBarInfo) const
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			switch(idObject)
			{
			case OBJID_HSCROLL:
				if(phWnd2->m_pHScrollBarInfo) {
					*pScrollBarInfo = *phWnd2->m_pHScrollBarInfo;
					return TRUE;
				}
				break;
			case OBJID_VSCROLL:
				if(phWnd2->m_pVScrollBarInfo) {
					*pScrollBarInfo = *phWnd2->m_pVScrollBarInfo;
					return TRUE;
				}
				break;
			case OBJID_CLIENT:
				return phWnd2->wc.lpfnWndProc(hWnd, SBM_GETSCROLLBARINFO, 0, (LPARAM)pScrollBarInfo);
				break;
			}
		}
	} else {
		return ::GetScrollBarInfo(hWnd, idObject, pScrollBarInfo);
	}
	return 0;
}

BOOL UIWnd2Manager::SetScrollBarInfo(HWND hWnd, LONG idObject, PSCROLLBARINFO pScrollBarInfo)
{
	if (IsDirectUI(hWnd)) {
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			switch(idObject)
			{
			case OBJID_HSCROLL:
				if(phWnd2->m_pHScrollBarInfo) {
					*phWnd2->m_pHScrollBarInfo = *pScrollBarInfo;
					return TRUE;
				}
				break;
			case OBJID_VSCROLL:
				if(phWnd2->m_pVScrollBarInfo) {
					*phWnd2->m_pVScrollBarInfo = *pScrollBarInfo;
					return TRUE;
				}
				break;
			case OBJID_CLIENT:
				//return phWnd2->wc.lpfnWndProc(hWnd, SBM_SETSCROLLBARINFO, 0, (LPARAM)pScrollBarInfo);
				break;
			}
		}
	} else {
		//return ::SetScrollBarInfo(hWnd, idObject, pScrollBarInfo);
	}
	return 0;
}

BOOL UIWnd2Manager::IsDialogMessage(HWND hWnd, LPMSG lpMsg)
{
	return 0;
}

void UIWnd2Manager::NextDlgCtrl(HWND hWnd) const
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		phWnd2->m_hWndCurChild = FindhWnd2Next(phWnd2->m_hWndCurChild);
	}
}
void UIWnd2Manager::PrevDlgCtrl(HWND hWnd) const
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		phWnd2->m_hWndCurChild = FindhWnd2Prev(phWnd2->m_hWndCurChild);
	}
}
void UIWnd2Manager::GotoDlgCtrl(HWND hWnd, HWND hWndCtrl) const
{
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		phWnd2->m_hWndCurChild = hWndCtrl;
	}
}

BOOL UIWnd2Manager::ResizeClient(HWND hWnd, int nWidth, int nHeight, BOOL bRedraw)
{
	return 0;
}

int UIWnd2Manager::GetWindowRgn(HWND hWnd, HRGN hRgn)
{
	return 0;
}
int UIWnd2Manager::SetWindowRgn(HWND hWnd, HRGN hRgn, BOOL bRedraw)
{
	return 0;
}
HDWP UIWnd2Manager::DeferWindowPos(HWND hWnd, HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
	return 0;
}
DWORD UIWnd2Manager::GetWindowThreadProcessId(HWND hWnd, LPDWORD lpdwProcessId)
{
	if (IsDirectUI(hWnd)) {
		if (lpdwProcessId) {
			*lpdwProcessId = ::GetCurrentProcessId();
		}
		HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
		if (phWnd2) {
			return phWnd2->m_dwThreadId;
		}
	} else {
		return ::GetWindowThreadProcessId(hWnd, lpdwProcessId);
	}
	return 0;
}
DWORD UIWnd2Manager::GetWindowThreadID(HWND hWnd)
{
	return GetWindowThreadProcessId(hWnd, NULL);
}
DWORD UIWnd2Manager::GetWindowProcessID(HWND hWnd)
{
	DWORD dwProcessID = 0;
	GetWindowThreadProcessId(hWnd, &dwProcessID);
	return dwProcessID;
}
BOOL UIWnd2Manager::IsWindow(HWND hWnd)
{
	if(IsUIWnd2(hWnd)) {
		return TRUE;
	} else {
		return ::IsWindow(hWnd);
	}
	return 0;
}
BOOL UIWnd2Manager::IsWindowUnicode(HWND hWnd)
{
#ifdef UNICODE
	return TRUE;
#else
	return FALSE;
#endif//
	return 0;
}
BOOL UIWnd2Manager::IsParentDialog(HWND hWnd)
{
	if (IsDirectUI(hWnd)) {
		return IsParentDialog(GetParent(hWnd));
	}
	ATLASSERT(::IsWindow(hWnd));
	TCHAR szBuf[8]; // "#32770" + NUL character
	if (GetClassName(GetParent(hWnd), szBuf, sizeof(szBuf)/sizeof(szBuf[0])) == 0)
		return FALSE;
	return lstrcmp(szBuf, _T("#32770")) == 0;
	return 0;
}
BOOL UIWnd2Manager::ShowWindowAsync(HWND hWnd, int nCmdShow)
{
	return 0;
}

HWND UIWnd2Manager::GetDescendantWindow(HWND hWnd, int nID) const
{
	return 0;
}

void UIWnd2Manager::SendMessageToDescendants(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, BOOL bDeep)
{
	HWND hChild = GetWindow(hWnd, GW_CHILD);
	while (hChild)
	{
		SendMessage(hChild, message, wParam, lParam);
		if (bDeep) {
			SendMessageToDescendants(hChild, message, wParam, lParam, bDeep);
		}
		hChild = GetWindow(hChild, GW_HWNDNEXT);
	}
}

BOOL UIWnd2Manager::CenterWindow(HWND hWnd, HWND hWndCenter)
{
	if (IsUIWnd2(hWnd)) {
		CRect rc;
		GetWindowRect(hWnd, &rc);
		CRect rcParent;
		GetClientRect(GetParent(hWnd), &rcParent);
		int x = 0, y = 0;
		x = rcParent.left + (rcParent.Width()-rc.Width())/2;
		y = rcParent.top + (rcParent.Height()-rc.Height())/2;
		return MoveWindow(hWnd, x, y, rc.Width(), rc.Height());
	} else {
		UIWnd Wnd(hWnd);
		return Wnd.CenterWindow(hWndCenter);
	}
	return 0;
}

BOOL UIWnd2Manager::ModifyStyle(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	ATLASSERT(IsDirectUI(hWnd));
	SetWindowLong(hWnd, GWL_STYLE, (GetStyle(hWnd) | dwAdd) & ~dwRemove);
	return TRUE;
	return 0;
}

BOOL UIWnd2Manager::ModifyStyleEx(HWND hWnd, DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	ATLASSERT(IsDirectUI(hWnd));
	SetWindowLong(hWnd, GWL_EXSTYLE, (GetStyle(hWnd) | dwAdd) & ~dwRemove);
	return TRUE;
	return 0;
}

BOOL UIWnd2Manager::ModifyState(HWND hWnd, DWORD dwRemove, DWORD dwAdd)
{
	ATLASSERT(IsDirectUI(hWnd));
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		phWnd2->m_dwState |= dwAdd;
		phWnd2->m_dwState &= ~dwRemove;
		return TRUE;
	}
	return FALSE;
}

BOOL UIWnd2Manager::SetState(HWND hWnd, DWORD dwState)
{
	ATLASSERT(IsDirectUI(hWnd));
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		phWnd2->m_dwState = dwState;
		return TRUE;
	}
	return FALSE;
}

DWORD UIWnd2Manager::GetState(HWND hWnd) const
{
	ATLASSERT(IsDirectUI(hWnd));
	HUIWnd2* phWnd2 = FindpHUIWnd2(hWnd);
	if (phWnd2) {
		return phWnd2->m_dwState;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////

BOOL UIWnd2Manager::IsWindowVisible(HWND hWnd)
{
	return GetStyle(hWnd) & WS_VISIBLE ? TRUE : FALSE;
	return 0;
}

BOOL UIWnd2Manager::IsWindowVisible(HWND hWnd, BOOL bDeep)
{
	if (bDeep) {
		do 
		{
			if (!IsWindowVisible(hWnd))
				return FALSE;
		} while(hWnd = GetParent(hWnd));
		return TRUE;
	}
	return IsWindowVisible(hWnd);
}

BOOL UIWnd2Manager::SetLayeredWindowAttributes(HWND hWnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	return 0;
}

BOOL UIWnd2Manager::GetLayeredWindowAttributes(HWND hWnd, COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags)
{
	return FALSE;
}

void UIWnd2Manager::SetAlpha(HWND hWnd, BYTE bAlpha)
{

}

void UIWnd2Manager::SetColorKey(HWND hWnd, COLORREF crKey)
{

}

void UIWnd2Manager::SetWindowZOrder(HWND hWnd, HWND hWndInsertAfter)
{

}

void UIWnd2Manager::GetWindowSize(HWND hWnd, LPSIZE lpSize)
{
	ATLASSERT(lpSize);
	RECT rcWnd;
	GetWindowRect(hWnd, &rcWnd);
	lpSize->cx = rcWnd.right - rcWnd.left;
	lpSize->cy = rcWnd.bottom - rcWnd.top;
}

SIZE UIWnd2Manager::GetWindowSize(HWND hWnd)
{
	SIZE sz = {0};
	GetWindowSize(hWnd, &sz);
	return sz;
}

void UIWnd2Manager::GetClientSize(HWND hWnd, LPSIZE lpSize)
{
	ATLASSERT(lpSize);
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);
	lpSize->cx = rcClient.right;
	lpSize->cy = rcClient.bottom;
}

SIZE UIWnd2Manager::GetClientSize(HWND hWnd)
{
	SIZE sz = {0};
	GetClientSize(hWnd, &sz);
	return sz;
}

void UIWnd2Manager::SetWindowRect(HWND hWnd, LPCRECT lpRect, BOOL bRedraw)
{
	MoveWindow(hWnd, lpRect, bRedraw);
}

void UIWnd2Manager::SetWindowSize(HWND hWnd, INT cx, INT cy)
{
	SetWindowPos(hWnd, NULL, 0, 0, cx, cy, SWP_NOMOVE);
}

void UIWnd2Manager::SetWindowSize(HWND hWnd, SIZE sz)
{
	SetWindowSize(hWnd, sz.cx, sz.cy);
}

void UIWnd2Manager::SetClientRect(HWND hWnd, LPCRECT lpRect, BOOL bRedraw)
{
	RECT rcClient;
	GetClientRect(hWnd, &rcClient);
	RECT rcNewClient = *lpRect;
	RECT rcWnd;
	GetWindowRect(hWnd, &rcWnd);
	rcWnd.left += rcNewClient.left - rcClient.left;
	rcWnd.top += rcNewClient.top - rcClient.top;
	rcWnd.right += rcNewClient.right - rcClient.right;
	rcWnd.bottom += rcNewClient.bottom - rcClient.bottom;
	SetWindowRect(hWnd, &rcWnd, bRedraw);
}

void UIWnd2Manager::SetClientSize(HWND hWnd, SIZE szNew)
{
	SetClientSize(hWnd, szNew.cx, szNew.cy);
}

void UIWnd2Manager::SetClientSize(HWND hWnd, int cxNew, int cyNew)
{
	SIZE szClient;
	GetClientSize(hWnd, &szClient);
	SIZE szWnd;
	GetWindowSize(hWnd, &szWnd);
	szWnd.cx += cxNew - szClient.cx;
	szWnd.cy += cyNew - szClient.cy;
	SetWindowSize(hWnd, szWnd);
}

int UIWnd2Manager::GetWindowText(HWND hWnd, CString& strText)
{
	int nLen = GetWindowTextLength(hWnd);
	GetWindowText(hWnd, strText.GetBufferSetLength(nLen), nLen + 1);
	strText.ReleaseBuffer();
	return nLen;
	return 0;
}

UINT UIWnd2Manager::GetDlgItemText(HWND hWnd, int nID, CString& strText)
{
	HWND hItem = GetDlgItem(hWnd, nID);
	if (hItem) {
#if 0
		int nLength;
		LPTSTR pszText;
		nLength = GetWindowTextLength(hItem);
		pszText = strText.GetBuffer(nLength + 1);
		nLength = GetWindowText(hItem, pszText, nLength + 1);
		strText.ReleaseBuffer(nLength);
		return nLength;
#else
		int nLen = GetWindowTextLength(hItem);
		GetWindowText(hItem, strText.GetBufferSetLength(nLen), nLen + 1);
		strText.ReleaseBuffer();
		return nLen;
#endif//
	}
	return 0;
}

LRESULT UIWnd2Manager::PostDlgItemMessage(HWND hWnd, int nID, UINT message, WPARAM wParam, LPARAM lParam) throw()
{
	HWND hDlgItem = GetDlgItem(hWnd, nID);
	if (hDlgItem) {
		return PostMessage(hDlgItem, message, wParam, lParam);
	}
	return 0L;
}

BOOL UIWnd2Manager::TrackMouseEvent(HWND hWnd, DWORD dwFalgs)
{
	if (IsDirectUI(hWnd)) {
	} else {
		TRACKMOUSEEVENT   tme = {0};     
		tme.cbSize = sizeof(TRACKMOUSEEVENT);     
		tme.dwFlags = dwFalgs;
		tme.hwndTrack = hWnd;  
		tme.dwHoverTime = m_hWndToolTip==NULL?400UL:(DWORD)::SendMessage(m_hWndToolTip, TTM_GETDELAYTIME, TTDT_INITIAL, 0L);
		return _TrackMouseEvent(&tme);
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////

UIWnd2::UIWnd2(HWND hWnd) : UIWnd(hWnd) 
{

}

void UIWnd2::Attach(HWND hWndNew) throw()
{
	ASSERT(m_hWnd == NULL);
	m_hWnd = hWndNew;
	/*if (_pUIWnd2Manager->IsDirectUI(hWndNew)) {
		ATLASSUME(m_hWnd == NULL);
		m_hWnd = hWndNew;
	} else {
		UIWnd::Attach(hWndNew);
	}*/
}

HWND UIWnd2::Detach()
{
	HWND hWnd = m_hWnd;
	m_hWnd = NULL;
	return hWnd;
}

UIWnd2* UIWnd2::FromHandle(HWND hWnd)
{
	return reinterpret_cast<UIWnd2*>(_pUIWnd2Manager->GetWindowLongPtr(hWnd, GWL_USERDATA));
}

BOOL UIWnd2::DestroyWindow()
{
	return _pUIWnd2Manager->DestroyWindow(m_hWnd);
}

BOOL UIWnd2::DestroyChildWindow()
{
	return _pUIWnd2Manager->DestroyChildWindow(m_hWnd);
}

BOOL UIWnd2::IsAutoDelete()
{
	return _pUIWnd2Manager->IsAutoDelete(m_hWnd);
}

DWORD UIWnd2::GetStyle() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetStyle(m_hWnd);
	} else {
		return UIWnd::GetStyle();
	}
}

DWORD UIWnd2::GetExStyle() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetExStyle(m_hWnd);
	} else {
		return UIWnd::GetExStyle();
	}
}

LONG UIWnd2::GetWindowLong(int nIndex) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowLong(m_hWnd, nIndex);
	} else {
		return UIWnd::GetWindowLong(nIndex);
	}
}

LONG_PTR UIWnd2::GetWindowLongPtr(int nIndex) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowLongPtr(m_hWnd, nIndex);
	} else {
		return UIWnd::GetWindowLongPtr(nIndex);
	}
}

LONG UIWnd2::SetWindowLong(int nIndex, LONG dwNewLong)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowLong(m_hWnd, nIndex, dwNewLong);
	} else {
		return UIWnd::SetWindowLong(nIndex, dwNewLong);
	}
}

LONG_PTR UIWnd2::SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowLongPtr(m_hWnd, nIndex, dwNewLong);
	} else {
		return UIWnd::SetWindowLongPtr(nIndex, dwNewLong);
	}
}

WORD UIWnd2::GetWindowWord(int nIndex) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowWord(m_hWnd, nIndex);
	} else {
		return UIWnd::GetWindowWord(nIndex);
	}
}

WORD UIWnd2::SetWindowWord(int nIndex, WORD wNewWord)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowWord(m_hWnd, nIndex, wNewWord);
	} else {
		return UIWnd::SetWindowWord(nIndex, wNewWord);
	}
}

// Message Functions

LRESULT UIWnd2::SendMessage(UINT message, WPARAM wParam, LPARAM lParam) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SendMessage(m_hWnd, message, wParam, lParam);
	} else {
		return UIWnd::SendMessage(message, wParam, lParam);
	}
}

/*LRESULT UIWnd2::SendMessageW(UINT message, WPARAM wParam = 0, LPARAM lParam = 0) const
{
if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
return _pUIWnd2Manager->SendMessage(m_hWnd, message, wParam, lParam);
} else {
return UIWnd::SendMessage(message, wParam, lParam);
}
}*/

BOOL UIWnd2::PostMessage(UINT message, WPARAM wParam, LPARAM lParam) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->PostMessage(m_hWnd, message, wParam, lParam);
	} else {
		return UIWnd::PostMessage(message, wParam, lParam);
	}
}

BOOL UIWnd2::SendNotifyMessage(UINT message, WPARAM wParam, LPARAM lParam) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SendNotifyMessage(m_hWnd, message, wParam, lParam);
	} else {
		return UIWnd::SendNotifyMessage(message, wParam, lParam);
	}
}

// support for C style macros
LRESULT UIWnd2::SendMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_pUIWnd2Manager->IsDirectUI(hWnd)) {
		return _pUIWnd2Manager->SendMessage(hWnd, message, wParam, lParam);
	} else {
		return UIWnd::SendMessage(hWnd, message, wParam, lParam);
	}
}

LRESULT UIWnd2::PostMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_pUIWnd2Manager->IsDirectUI(hWnd)) {
		return _pUIWnd2Manager->PostMessage(hWnd, message, wParam, lParam);
	} else {
		return UIWnd::PostMessage(hWnd, message, wParam, lParam);
	}
}

// Window Text Functions

BOOL UIWnd2::SetWindowText(LPCTSTR lpszString)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowText(m_hWnd, lpszString);
	} else {
		return UIWnd::SetWindowText(lpszString);
	}
}

int UIWnd2::GetWindowText(LPTSTR lpszStringBuf, int nMaxCount) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowText(m_hWnd, lpszStringBuf, nMaxCount);
	} else {
		return UIWnd::GetWindowText(lpszStringBuf, nMaxCount);
	}
}

int UIWnd2::GetWindowTextLength() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowTextLength(m_hWnd);
	} else {
		return UIWnd::GetWindowTextLength();
	}
}

// Font Functions

void UIWnd2::SetFont(HFONT hFont, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetFont(m_hWnd, hFont, bRedraw);
	} else {
		UIWnd::SetFont(hFont, bRedraw);
	}
}

HFONT UIWnd2::GetFont() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetFont(m_hWnd);
	} else {
		return UIWnd::GetFont();
	}
}

// Menu Functions (non-child windows only)

HMENU UIWnd2::GetMenu() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetMenu(m_hWnd);
	} else {
		return UIWnd::GetMenu();
	}
}

BOOL UIWnd2::SetMenu(HMENU hMenu)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetMenu(m_hWnd, hMenu);
	} else {
		return UIWnd::SetMenu(hMenu);
	}
}

BOOL UIWnd2::DrawMenuBar()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->DrawMenuBar(m_hWnd);
	} else {
		return UIWnd::DrawMenuBar();
	}
}

HMENU UIWnd2::GetSystemMenu(BOOL bRevert) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetSystemMenu(m_hWnd, bRevert);
	} else {
		return UIWnd::GetSystemMenu(bRevert);
	}
}

BOOL UIWnd2::HiliteMenuItem(HMENU hMenu, UINT uItemHilite, UINT uHilite)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->HiliteMenuItem(m_hWnd, hMenu, uItemHilite, uHilite);
	} else {
		return UIWnd::HiliteMenuItem(hMenu, uItemHilite, uHilite);
	}
}

// Window Size and Position Functions

BOOL UIWnd2::IsIconic() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsIconic(m_hWnd);
	} else {
		return UIWnd::IsIconic();
	}
}

BOOL UIWnd2::IsZoomed() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsZoomed(m_hWnd);
	} else {
		return UIWnd::IsZoomed();
	}
}

BOOL UIWnd2::MoveWindow(int x, int y, int nWidth, int nHeight, BOOL bRepaint)
{
	//if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->MoveWindow(m_hWnd, x, y, nWidth, nHeight, bRepaint);
	//} else {
	//	return UIWnd::MoveWindow(x, y, nWidth, nHeight, bRepaint);
	//}
}

BOOL UIWnd2::MoveWindow(LPCRECT lpRect, BOOL bRepaint)
{
	//if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->MoveWindow(m_hWnd, lpRect, bRepaint);
	//} else {
	//	return UIWnd::MoveWindow(lpRect, bRepaint);
	//}
}

BOOL UIWnd2::SetWindowPos(HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT nFlags)
{
	return _pUIWnd2Manager->SetWindowPos(m_hWnd, hWndInsertAfter, x, y, cx, cy, nFlags);
}

BOOL UIWnd2::SetWindowPos(HWND hWndInsertAfter, LPCRECT lpRect, UINT nFlags)
{
	return _pUIWnd2Manager->SetWindowPos(m_hWnd, hWndInsertAfter, lpRect, nFlags);
}

UINT UIWnd2::ArrangeIconicWindows()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ArrangeIconicWindows(m_hWnd);
	} else {
		return UIWnd::ArrangeIconicWindows();
	}
}

BOOL UIWnd2::BringWindowToTop()
{
	return _pUIWnd2Manager->BringWindowToTop(m_hWnd);
}

BOOL UIWnd2::GetWindowRect(LPRECT lpRect) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowRect(m_hWnd, lpRect);
	} else {
		return UIWnd::GetWindowRect(lpRect);
	}
}

BOOL UIWnd2::GetClientRect(LPRECT lpRect) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetClientRect(m_hWnd, lpRect);
	} else {
		return UIWnd::GetClientRect(lpRect);
	}
}

BOOL UIWnd2::GetWindowPlacement(WINDOWPLACEMENT FAR* lpwndpl) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowPlacement(m_hWnd, lpwndpl);
	} else {
		return UIWnd::GetWindowPlacement(lpwndpl);
	}
}

BOOL UIWnd2::SetWindowPlacement(const WINDOWPLACEMENT FAR* lpwndpl)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowPlacement(m_hWnd, lpwndpl);
	} else {
		return UIWnd::SetWindowPlacement(lpwndpl);
	}
}

// Coordinate Mapping Functions

BOOL UIWnd2::ClientToScreen(LPPOINT lpPoint) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ClientToScreen(m_hWnd, lpPoint);
	} else {
		return UIWnd::ClientToScreen(lpPoint);
	}
}

BOOL UIWnd2::ClientToScreen(LPRECT lpRect) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ClientToScreen(m_hWnd, lpRect);
	} else {
		return UIWnd::ClientToScreen(lpRect);
	}
}

BOOL UIWnd2::ScreenToClient(LPPOINT lpPoint) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ScreenToClient(m_hWnd, lpPoint);
	} else {
		return UIWnd::ScreenToClient(lpPoint);
	}
}

BOOL UIWnd2::ScreenToClient(LPRECT lpRect) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ScreenToClient(m_hWnd, lpRect);
	} else {
		return UIWnd::ScreenToClient(lpRect);
	}
}

int UIWnd2::MapWindowPoints(HWND hWndTo, LPPOINT lpPoint, UINT nCount) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->MapWindowPoints(m_hWnd, hWndTo, lpPoint, nCount);
	} else {
		return UIWnd::MapWindowPoints(hWndTo, lpPoint, nCount);
	}
}

int UIWnd2::MapWindowPoints(HWND hWndTo, LPRECT lpRect) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->MapWindowPoints(m_hWnd, hWndTo, lpRect);
	} else {
		return UIWnd::MapWindowPoints(hWndTo, lpRect);
	}
}

// Update and Painting Functions

HDC UIWnd2::BeginPaint(LPPAINTSTRUCT lpPaint)
{
	return _pUIWnd2Manager->BeginPaint(m_hWnd, lpPaint);
}

void UIWnd2::EndPaint(LPPAINTSTRUCT lpPaint)
{
	_pUIWnd2Manager->EndPaint(m_hWnd, lpPaint);
}

HDC UIWnd2::GetDC()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDC(m_hWnd);
	} else {
		return UIWnd::GetDC();
	}
}

HDC UIWnd2::GetWindowDC()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowDC(m_hWnd);
	} else {
		return UIWnd::GetWindowDC();
	}
}

int UIWnd2::ReleaseDC(HDC hDC)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ReleaseDC(m_hWnd, hDC);
	} else {
		return UIWnd::ReleaseDC(hDC);
	}
}

void UIWnd2::Print(HDC hDC, DWORD dwFlags) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->Print(m_hWnd, hDC, dwFlags);
	} else {
		UIWnd::Print(hDC, dwFlags);
	}
}

void UIWnd2::PrintClient(HDC hDC, DWORD dwFlags) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->PrintClient(m_hWnd, hDC, dwFlags);
	} else {
		UIWnd::PrintClient(hDC, dwFlags);
	}
}

BOOL UIWnd2::UpdateWindow()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->UpdateWindow(m_hWnd);
	} else {
		return UIWnd::UpdateWindow();
	}
}

void UIWnd2::SetRedraw(BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetRedraw(m_hWnd, bRedraw);
	} else {
		UIWnd::SetRedraw(bRedraw);
	}
}

BOOL UIWnd2::GetUpdateRect(LPRECT lpRect, BOOL bErase)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetUpdateRect(m_hWnd, lpRect, bErase);
	} else {
		return UIWnd::GetUpdateRect(lpRect, bErase);
	}
}

int UIWnd2::GetUpdateRgn(HRGN hRgn, BOOL bErase)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetUpdateRgn(m_hWnd, hRgn, bErase);
	} else {
		return UIWnd::GetUpdateRgn(hRgn, bErase);
	}
}

BOOL UIWnd2::Invalidate(BOOL bErase)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->Invalidate(m_hWnd, bErase);
	} else {
		return UIWnd::Invalidate(bErase);
	}
}

BOOL UIWnd2::InvalidateRect(LPCRECT lpRect, BOOL bErase)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->InvalidateRect(m_hWnd, lpRect, bErase);
	} else {
		return UIWnd::InvalidateRect(lpRect, bErase);
	}
}

BOOL UIWnd2::ValidateRect(LPCRECT lpRect)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ValidateRect(m_hWnd, lpRect);
	} else {
		return UIWnd::ValidateRect(lpRect);
	}
}

void UIWnd2::InvalidateRgn(HRGN hRgn, BOOL bErase)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->InvalidateRgn(m_hWnd, hRgn, bErase);
	} else {
		UIWnd::InvalidateRgn(hRgn, bErase);
	}
}

BOOL UIWnd2::ValidateRgn(HRGN hRgn)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ValidateRgn(m_hWnd, hRgn);
	} else {
		return UIWnd::ValidateRgn(hRgn);
	}
}

BOOL UIWnd2::ShowWindow(int nCmdShow)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ShowWindow(m_hWnd, nCmdShow);
	} else {
		return UIWnd::ShowWindow(nCmdShow);
	}
}

/*BOOL UIWnd2::IsWindowVisible() const
{
if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
return _pUIWnd2Manager->IsWindowVisible(m_hWnd);
} else {
return UIWnd::IsWindowVisible();
}
}*/

BOOL UIWnd2::ShowOwnedPopups(BOOL bShow)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ShowOwnedPopups(m_hWnd, bShow);
	} else {
		return UIWnd::ShowOwnedPopups(bShow);
	}
}

HDC UIWnd2::GetDCEx(HRGN hRgnClip, DWORD flags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDCEx(m_hWnd, hRgnClip, flags);
	} else {
		return UIWnd::GetDCEx(hRgnClip, flags);
	}
}

BOOL UIWnd2::LockWindowUpdate(BOOL bLock)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->LockWindowUpdate(m_hWnd, bLock);
	} else {
		return UIWnd::LockWindowUpdate(bLock);
	}
}

BOOL UIWnd2::RedrawWindow(LPCRECT lpRectUpdate, HRGN hRgnUpdate, UINT flags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->RedrawWindow(m_hWnd, lpRectUpdate, hRgnUpdate, flags);
	} else {
		return UIWnd::RedrawWindow(lpRectUpdate, hRgnUpdate, flags);
	}
}

// Timer Functions

UINT UIWnd2::SetTimer(UINT nIDEvent, UINT nElapse)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetTimer(m_hWnd, nIDEvent, nElapse);
	} else {
		return UIWnd::SetTimer(nIDEvent, nElapse);
	}
}

BOOL UIWnd2::KillTimer(UINT nIDEvent)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->KillTimer(m_hWnd, nIDEvent);
	} else {
		return UIWnd::KillTimer(nIDEvent);
	}
}

// Window State Functions

BOOL UIWnd2::IsWindowEnabled() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsWindowEnabled(m_hWnd);
	} else {
		return UIWnd::IsWindowEnabled();
	}
}

BOOL UIWnd2::EnableWindow(BOOL bEnable)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->EnableWindow(m_hWnd, bEnable);
	} else {
		return UIWnd::EnableWindow(bEnable);
	}
}

HWND UIWnd2::SetActiveWindow()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetActiveWindow(m_hWnd);
	} else {
		return UIWnd::SetActiveWindow();
	}
}

HWND UIWnd2::GetHover()
{
	return _pUIWnd2Manager->GetHover();
}

HWND UIWnd2::SetCapture()
{
	return _pUIWnd2Manager->SetCapture(m_hWnd);
}

HWND UIWnd2::GetCapture()
{
	return _pUIWnd2Manager->GetCapture();
}

BOOL UIWnd2::ReleaseCapture()
{
	return _pUIWnd2Manager->ReleaseCapture();
}

HWND UIWnd2::SetFocus(HWND hWnd)
{
	return _pUIWnd2Manager->SetFocus(hWnd);
}

HWND UIWnd2::SetFocus()
{
	return SetFocus(m_hWnd);
}

/*HWND UIWnd2::GetFocus() 
{
return _pUIWnd2Manager->GetFocus();
}*/

// Dialog-Box Item Functions

BOOL UIWnd2::CheckDlgButton(int nIDButton, UINT nCheck)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->CheckDlgButton(m_hWnd, nIDButton, nCheck);
	} else {
		return UIWnd::CheckDlgButton(nIDButton, nCheck);
	}
}

BOOL UIWnd2::CheckRadioButton(int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->CheckRadioButton(m_hWnd, nIDFirstButton, nIDLastButton, nIDCheckButton);
	} else {
		return UIWnd::CheckRadioButton(nIDFirstButton, nIDLastButton, nIDCheckButton);
	}
}

int UIWnd2::DlgDirList(LPTSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT nFileType)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->DlgDirList(m_hWnd, lpPathSpec, nIDListBox, nIDStaticPath, nFileType);
	} else {
		return UIWnd::DlgDirList(lpPathSpec, nIDListBox, nIDStaticPath, nFileType);
	}
}

int UIWnd2::DlgDirListComboBox(LPTSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT nFileType)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->DlgDirListComboBox(m_hWnd, lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);
	} else {
		return UIWnd::DlgDirListComboBox(lpPathSpec, nIDComboBox, nIDStaticPath, nFileType);
	}
}

BOOL UIWnd2::DlgDirSelect(LPTSTR lpString, int nCount, int nIDListBox)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->DlgDirSelect(m_hWnd, lpString, nCount, nIDListBox);
	} else {
		return UIWnd::DlgDirSelect(lpString, nCount, nIDListBox);
	}
}

BOOL UIWnd2::DlgDirSelectComboBox(LPTSTR lpString, int nCount, int nIDComboBox)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->DlgDirSelectComboBox(m_hWnd, lpString, nCount, nIDComboBox);
	} else {
		return UIWnd::DlgDirSelectComboBox(lpString, nCount, nIDComboBox);
	}
}

UINT UIWnd2::GetDlgItemInt(int nID, BOOL* lpTrans, BOOL bSigned) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDlgItemInt(m_hWnd, nID, lpTrans, bSigned);
	} else {
		return UIWnd::GetDlgItemInt(nID, lpTrans, bSigned);
	}
}

UINT UIWnd2::GetDlgItemText(int nID, LPTSTR lpStr, int nMaxCount) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDlgItemText(m_hWnd, nID, lpStr, nMaxCount);
	} else {
		return UIWnd::GetDlgItemText(nID, lpStr, nMaxCount);
	}
}
BOOL UIWnd2::GetDlgItemText(int nID, BSTR& bstrText) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDlgItemText(m_hWnd, nID, bstrText);
	} else {
		return UIWnd::GetDlgItemText(nID, bstrText);
	}
}
HWND UIWnd2::GetNextDlgGroupItem(HWND hWndCtl, BOOL bPrevious) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetNextDlgGroupItem(m_hWnd, hWndCtl, bPrevious);
	} else {
		return UIWnd::GetNextDlgGroupItem(hWndCtl, bPrevious);
	}
}

HWND UIWnd2::GetNextDlgTabItem(HWND hWndCtl, BOOL bPrevious) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetNextDlgTabItem(m_hWnd, hWndCtl, bPrevious);
	} else {
		return UIWnd::GetNextDlgTabItem(hWndCtl, bPrevious);
	}
}

UINT UIWnd2::IsDlgButtonChecked(int nIDButton) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsDlgButtonChecked(m_hWnd, nIDButton);
	} else {
		return UIWnd::IsDlgButtonChecked(nIDButton);
	}
}

LRESULT UIWnd2::SendDlgItemMessage(int nID, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SendDlgItemMessage(m_hWnd, nID, message, wParam, lParam);
	} else {
		return UIWnd::SendDlgItemMessage(nID, message, wParam, lParam);
	}
}

BOOL UIWnd2::SetDlgItemInt(int nID, UINT nValue, BOOL bSigned)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetDlgItemInt(m_hWnd, nID, nValue, bSigned);
	} else {
		return UIWnd::SetDlgItemInt(nID, nValue, bSigned);
	}
}

BOOL UIWnd2::SetDlgItemText(int nID, LPCTSTR lpszString)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetDlgItemText(m_hWnd, nID, lpszString);
	} else {
		return UIWnd::SetDlgItemText(nID, lpszString);
	}
}

#ifndef _ATL_NO_HOSTING
HRESULT UIWnd2::GetDlgControl(int nID, REFIID iid, void** ppUnk)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDlgControl(m_hWnd, nID, iid, ppUnk);
	} else {
		return UIWnd::GetDlgControl(nID, iid, ppUnk);
	}
}
#endif //!_ATL_NO_HOSTING

// Scrolling Functions

int UIWnd2::GetScrollPos(int nBar) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetScrollPos(m_hWnd, nBar);
	} else {
		return UIWnd::GetScrollPos(nBar);
	}
}

BOOL UIWnd2::GetScrollRange(int nBar, LPINT lpMinPos, LPINT lpMaxPos) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetScrollRange(m_hWnd, nBar, lpMinPos, lpMaxPos);
	} else {
		return UIWnd::GetScrollRange(nBar, lpMinPos, lpMaxPos);
	}
}

BOOL UIWnd2::ScrollWindow(int xAmount, int yAmount, LPCRECT lpRect, LPCRECT lpClipRect)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ScrollWindow(m_hWnd, xAmount, yAmount, lpRect, lpClipRect);
	} else {
		return UIWnd::ScrollWindow(xAmount, yAmount, lpRect, lpClipRect);
	}
}

int UIWnd2::ScrollWindowEx(int dx, int dy, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate, UINT uFlags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ScrollWindowEx(m_hWnd, dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
	} else {
		return UIWnd::ScrollWindowEx(dx, dy, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate, uFlags);
	}
}

int UIWnd2::ScrollWindowEx(int dx, int dy, UINT uFlags, LPCRECT lpRectScroll, LPCRECT lpRectClip, HRGN hRgnUpdate, LPRECT lpRectUpdate)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ScrollWindowEx(m_hWnd, dx, dy, uFlags, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate);
	} else {
		return UIWnd::ScrollWindowEx(dx, dy, uFlags, lpRectScroll, lpRectClip, hRgnUpdate, lpRectUpdate);
	}
}

int UIWnd2::SetScrollPos(int nBar, int nPos, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetScrollPos(m_hWnd, nBar, nPos, bRedraw);
	} else {
		return UIWnd::SetScrollPos(nBar, nPos, bRedraw);
	}
}

BOOL UIWnd2::SetScrollRange(int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetScrollRange(m_hWnd, nBar, nMinPos, nMaxPos, bRedraw);
	} else {
		return UIWnd::SetScrollRange(nBar, nMinPos, nMaxPos, bRedraw);
	}
}

BOOL UIWnd2::ShowScrollBar(UINT nBar, BOOL bShow)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ShowScrollBar(m_hWnd, nBar, bShow);
	} else {
		return UIWnd::ShowScrollBar(nBar, bShow);
	}
}

BOOL UIWnd2::EnableScrollBar(UINT uSBFlags, UINT uArrowFlags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->EnableScrollBar(m_hWnd, uSBFlags, uArrowFlags);
	} else {
		return UIWnd::EnableScrollBar(uSBFlags, uArrowFlags);
	}
}

// Window Access Functions

HWND UIWnd2::ChildWindowFromPoint(POINT point) const
{
	return _pUIWnd2Manager->ChildWindowFromPoint(m_hWnd, point);
}

HWND UIWnd2::ChildWindowFromPointEx(POINT point, UINT uFlags) const
{
	return _pUIWnd2Manager->ChildWindowFromPointEx(m_hWnd, point, uFlags);
}

HWND UIWnd2::GetTopWindow() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		UIWnd wnd = GetSafeHwnd();
		return wnd.GetTopWindow();
	} else {
		return UIWnd::GetTopWindow();
	}
}

HWND UIWnd2::GetTopLevelParent() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		UIWnd wnd = GetSafeHwnd();
		return wnd.GetTopLevelParent();
	} else {
		return UIWnd::GetTopLevelParent();
	}
}

HWND UIWnd2::GetTopLevelWindow() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		UIWnd wnd = GetSafeHwnd();
		return wnd.GetTopLevelWindow();
	} else {
		return UIWnd::GetTopLevelWindow();
	}
}

HWND UIWnd2::GetWindow(UINT nCmd) const
{
	return _pUIWnd2Manager->GetWindow(m_hWnd, nCmd);
}

HWND UIWnd2::GetWindow(HWND hWnd, UINT nCmd) const
{
	return _pUIWnd2Manager->GetWindow(hWnd, nCmd);
}

HWND UIWnd2::GetLastActivePopup() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetLastActivePopup(m_hWnd);
	} else {
		return UIWnd::GetLastActivePopup();
	}
}

BOOL UIWnd2::IsChild(HWND hWnd) const
{
	return _pUIWnd2Manager->IsChild(m_hWnd, hWnd);
}

HWND UIWnd2::GetParent() const
{
	return _pUIWnd2Manager->GetParent(m_hWnd);
}

HWND UIWnd2::SetParent(HWND hWndNewParent)
{
	return _pUIWnd2Manager->SetParent(m_hWnd, hWndNewParent);
}

HWND UIWnd2::GetSafeHwnd() const 
{
	return _pUIWnd2Manager->GetSafeHwnd(m_hWnd);
}

// Window Tree Access

int UIWnd2::GetDlgCtrlID() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDlgCtrlID(m_hWnd);
	} else {
		return UIWnd::GetDlgCtrlID();
	}
}

int UIWnd2::SetDlgCtrlID(int nID)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetDlgCtrlID(m_hWnd, nID);
	} else {
		return UIWnd::SetDlgCtrlID(nID);
	}
}

HWND UIWnd2::GetDlgItem(int nID) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDlgItem(m_hWnd, nID);
	} else {
		return UIWnd::GetDlgItem(nID);
	}
}

// Alert Functions

BOOL UIWnd2::FlashWindow(BOOL bInvert)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->FlashWindow(m_hWnd, bInvert);
	} else {
		return UIWnd::FlashWindow(bInvert);
	}
}

int UIWnd2::MessageBox(LPCTSTR lpszText, LPCTSTR lpszCaption, UINT nType)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->MessageBox(m_hWnd, lpszText, lpszCaption, nType);
	} else {
		return UIWnd::MessageBox(lpszText, lpszCaption, nType);
	}
}

// Clipboard Functions

BOOL UIWnd2::ChangeClipboardChain(HWND hWndNewNext)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ChangeClipboardChain(m_hWnd, hWndNewNext);
	} else {
		return UIWnd::ChangeClipboardChain(hWndNewNext);
	}
}

HWND UIWnd2::SetClipboardViewer()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetClipboardViewer(m_hWnd);
	} else {
		return UIWnd::SetClipboardViewer();
	}
}

BOOL UIWnd2::OpenClipboard()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->OpenClipboard(m_hWnd);
	} else {
		return UIWnd::OpenClipboard();
	}
}

// Caret Functions

BOOL UIWnd2::CreateCaret(HBITMAP hBitmap)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->CreateCaret(m_hWnd, hBitmap);
	} else {
		return UIWnd::CreateCaret(hBitmap);
	}
}

BOOL UIWnd2::CreateSolidCaret(int nWidth, int nHeight)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->CreateSolidCaret(m_hWnd, nWidth, nHeight);
	} else {
		return UIWnd::CreateSolidCaret(nWidth, nHeight);
	}
}

BOOL UIWnd2::CreateGrayCaret(int nWidth, int nHeight)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->CreateGrayCaret(m_hWnd, nWidth, nHeight);
	} else {
		return UIWnd::CreateGrayCaret(nWidth, nHeight);
	}
}

BOOL UIWnd2::HideCaret()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->HideCaret(m_hWnd);
	} else {
		return UIWnd::HideCaret();
	}
}

BOOL UIWnd2::ShowCaret()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ShowCaret(m_hWnd);
	} else {
		return UIWnd::ShowCaret();
	}
}

#ifdef _INC_SHELLAPI
// Drag-Drop Functions
void UIWnd2::DragAcceptFiles(BOOL bAccept)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->DragAcceptFiles(m_hWnd, bAccept);
	} else {
		UIWnd::DragAcceptFiles(bAccept);
	}
}
#endif

// Icon Functions

HICON UIWnd2::SetIcon(HICON hIcon, BOOL bBigIcon)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetIcon(m_hWnd, hIcon, bBigIcon);
	} else {
		return UIWnd::SetIcon(hIcon, bBigIcon);
	}
}

HICON UIWnd2::GetIcon(BOOL bBigIcon) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetIcon(m_hWnd, bBigIcon);
	} else {
		return UIWnd::GetIcon(bBigIcon);
	}
}

// Help Functions

BOOL UIWnd2::WinHelp(LPCTSTR lpszHelp, UINT nCmd, DWORD dwData)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->WinHelp(m_hWnd, lpszHelp, nCmd, dwData);
	} else {
		return UIWnd::WinHelp(lpszHelp, nCmd, dwData);
	}
}

BOOL UIWnd2::SetWindowContextHelpId(DWORD dwContextHelpId)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowContextHelpId(m_hWnd, dwContextHelpId);
	} else {
		return UIWnd::SetWindowContextHelpId(dwContextHelpId);
	}
}

DWORD UIWnd2::GetWindowContextHelpId() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowContextHelpId(m_hWnd);
	} else {
		return UIWnd::GetWindowContextHelpId();
	}
}

// Hot Key Functions

int UIWnd2::SetHotKey(WORD wVirtualKeyCode, WORD wModifiers)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetHotKey(m_hWnd, wVirtualKeyCode, wModifiers);
	} else {
		return UIWnd::SetHotKey(wVirtualKeyCode, wModifiers);
	}
}

DWORD UIWnd2::GetHotKey() const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetHotKey(m_hWnd);
	} else {
		return UIWnd::GetHotKey();
	}
}

// Misc. Operations

//N new
BOOL UIWnd2::GetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetScrollInfo(m_hWnd, nBar, lpScrollInfo);
	} else {
		return UIWnd::GetScrollInfo(nBar, lpScrollInfo);
	}
}
BOOL UIWnd2::SetScrollInfo(int nBar, LPSCROLLINFO lpScrollInfo, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetScrollInfo(m_hWnd, nBar, lpScrollInfo, bRedraw);
	} else {
		return UIWnd::SetScrollInfo(nBar, lpScrollInfo, bRedraw);
	}
}
BOOL UIWnd2::GetScrollBarInfo(LONG idObject, PSCROLLBARINFO pScrollBarInfo) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetScrollBarInfo(m_hWnd, idObject, pScrollBarInfo);
	} else {
		return UIWnd::GetScrollBarInfo(idObject, pScrollBarInfo);
	}
}
BOOL UIWnd2::SetScrollBarInfo(LONG idObject, PSCROLLBARINFO pScrollBarInfo)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetScrollBarInfo(m_hWnd, idObject, pScrollBarInfo);
	} else {
		return FALSE;
	}
}
BOOL UIWnd2::IsDialogMessage(LPMSG lpMsg)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsDialogMessage(m_hWnd, lpMsg);
	} else {
		return UIWnd::IsDialogMessage(lpMsg);
	}
}

void UIWnd2::NextDlgCtrl() const
{
	_pUIWnd2Manager->NextDlgCtrl(m_hWnd);
}
void UIWnd2::PrevDlgCtrl() const
{
	_pUIWnd2Manager->PrevDlgCtrl(m_hWnd);
}
void UIWnd2::GotoDlgCtrl(HWND hWndCtrl) const
{
	_pUIWnd2Manager->GotoDlgCtrl(m_hWnd, hWndCtrl);
}

BOOL UIWnd2::ResizeClient(int nWidth, int nHeight, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ResizeClient(m_hWnd, nWidth, nHeight, bRedraw);
	} else {
		return UIWnd::ResizeClient(nWidth, nHeight, bRedraw);
	}
}

int UIWnd2::GetWindowRgn(HRGN hRgn)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowRgn(m_hWnd, hRgn);
	} else {
		return UIWnd::GetWindowRgn(hRgn);
	}
}
int UIWnd2::SetWindowRgn(HRGN hRgn, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetWindowRgn(m_hWnd, hRgn, bRedraw);
	} else {
		return UIWnd::SetWindowRgn(hRgn, bRedraw);
	}
}
HDWP UIWnd2::DeferWindowPos(HDWP hWinPosInfo, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
	return _pUIWnd2Manager->DeferWindowPos(m_hWnd, hWinPosInfo, hWndInsertAfter, x, y, cx, cy, uFlags);
}
DWORD UIWnd2::GetWindowThreadID()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowThreadID(m_hWnd);
	} else {
		return UIWnd::GetWindowThreadID();
	}
}
DWORD UIWnd2::GetWindowProcessID()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowProcessID(m_hWnd);
	} else {
		return UIWnd::GetWindowProcessID();
	}
}
BOOL UIWnd2::IsDirectUI()
{
	return _pUIWnd2Manager->IsDirectUI(m_hWnd);
}
BOOL UIWnd2::IsWindow()
{
	if (_pUIWnd2Manager->IsWindow(m_hWnd)) {
		return TRUE;
	} else {
		return UIWnd::IsWindow();
	}
}
BOOL UIWnd2::IsWindowUnicode()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsWindowUnicode(m_hWnd);
	} else {
		return UIWnd::IsWindowUnicode();
	}
}
BOOL UIWnd2::IsParentDialog()
{
	return _pUIWnd2Manager->IsParentDialog(m_hWnd);
}
BOOL UIWnd2::ShowWindowAsync(int nCmdShow)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ShowWindowAsync(m_hWnd, nCmdShow);
	} else {
		return UIWnd::ShowWindowAsync(nCmdShow);
	}
}

HWND UIWnd2::GetDescendantWindow(int nID) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetDescendantWindow(m_hWnd, nID);
	} else {
		return UIWnd::GetDescendantWindow(nID);
	}
}

void UIWnd2::SendMessageToDescendants(UINT message, WPARAM wParam, LPARAM lParam, BOOL bDeep)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SendMessageToDescendants(m_hWnd, message, wParam, lParam, bDeep);
	} else {
		UIWnd::SendMessageToDescendants(message, wParam, lParam, bDeep);
	}
}

BOOL UIWnd2::CenterWindow(HWND hWndCenter)
{
	return _pUIWnd2Manager->CenterWindow(m_hWnd, hWndCenter);
}

BOOL UIWnd2::ModifyStyle(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ModifyStyle(m_hWnd, dwRemove, dwAdd, nFlags);
	} else {
		return UIWnd::ModifyStyle(dwRemove, dwAdd, nFlags);
	}
}

BOOL UIWnd2::ModifyStyleEx(DWORD dwRemove, DWORD dwAdd, UINT nFlags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->ModifyStyleEx(m_hWnd, dwRemove, dwAdd, nFlags);
	} else {
		return UIWnd::ModifyStyleEx(dwRemove, dwAdd, nFlags);
	}
}

/*BOOL UIWnd2::ModifyState(DWORD dwRemove, DWORD dwAdd)
{
if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
return _pUIWnd2Manager->ModifyState(m_hWnd, dwRemove, dwAdd);
} else {
//return UIWnd::ModifyState(dwRemove, dwAdd, nFlags);
}
return FALSE;
}

BOOL UIWnd2::SetState(DWORD dwState)
{
if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
return _pUIWnd2Manager->SetState(m_hWnd, dwState);
} else {
//return UIWnd::SetState(dwRemove, dwAdd, nFlags);
}
return FALSE;
}

DWORD UIWnd2::GetState() const
{
if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
return _pUIWnd2Manager->GetState(m_hWnd);
} else {
//return UIWnd::SetState(dwRemove, dwAdd, nFlags);
}
return 0;
}*/

//////////////////////////////////////////////////////////////////////////

BOOL UIWnd2::IsWindowVisible(BOOL bDeep)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->IsWindowVisible(m_hWnd, bDeep);
	} else {
		return UIWnd::IsWindowVisible(bDeep);
	}
}

BOOL UIWnd2::SetLayeredWindowAttributes(COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->SetLayeredWindowAttributes(m_hWnd, crKey, bAlpha, dwFlags);
	} else {
		return UIWnd::SetLayeredWindowAttributes(crKey, bAlpha, dwFlags);
	}
}

BOOL UIWnd2::GetLayeredWindowAttributes(COLORREF *pcrKey, BYTE *pbAlpha, DWORD *pdwFlags)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetLayeredWindowAttributes(m_hWnd, pcrKey, pbAlpha, pdwFlags);
	} else {
		return UIWnd::GetLayeredWindowAttributes(pcrKey, pbAlpha, pdwFlags);
	}
}

void UIWnd2::SetAlpha(BYTE bAlpha)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetAlpha(m_hWnd, bAlpha);
	} else {
		UIWnd::SetAlpha(bAlpha);
	}
}

void UIWnd2::SetColorKey(COLORREF crKey)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetColorKey(m_hWnd, crKey);
	} else {
		UIWnd::SetColorKey(crKey);
	}
}

void UIWnd2::SetWindowZOrder(HWND hWndInsertAfter)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetWindowZOrder(m_hWnd, hWndInsertAfter);
	} else {
		UIWnd::SetWindowZOrder(hWndInsertAfter);
	}
}

void UIWnd2::GetWindowSize(LPSIZE lpSize)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->GetWindowSize(m_hWnd, lpSize);
	} else {
		UIWnd::GetWindowSize(lpSize);
	}
}

SIZE UIWnd2::GetWindowSize()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowSize(m_hWnd);
	} else {
		return UIWnd::GetWindowSize();
	}
}

void UIWnd2::GetClientSize(LPSIZE lpSize)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->GetClientSize(m_hWnd, lpSize);
	} else {
		UIWnd::GetClientSize(lpSize);
	}
}

SIZE UIWnd2::GetClientSize()
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetClientSize(m_hWnd);
	} else {
		return UIWnd::GetClientSize();
	}
}

void UIWnd2::SetWindowRect(LPCRECT lpRect, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetWindowRect(m_hWnd, lpRect, bRedraw);
	} else {
		UIWnd::SetWindowRect(lpRect, bRedraw);
	}
}

void UIWnd2::SetWindowSize(INT cx, INT cy)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetWindowSize(m_hWnd, cx, cy);
	} else {
		UIWnd::SetWindowSize(cx, cy);
	}
}

void UIWnd2::SetWindowSize(SIZE sz)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetWindowSize(m_hWnd, sz);
	} else {
		UIWnd::SetWindowSize(sz);
	}
}

void UIWnd2::SetClientRect(LPCRECT lpRect, BOOL bRedraw)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetClientRect(m_hWnd, lpRect, bRedraw);
	} else {
		UIWnd::SetClientRect(lpRect, bRedraw);
	}
}

void UIWnd2::SetClientSize(SIZE szNew)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetClientSize(m_hWnd, szNew);
	} else {
		UIWnd::SetClientSize(szNew);
	}
}

void UIWnd2::SetClientSize(int cxNew, int cyNew)
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		_pUIWnd2Manager->SetClientSize(m_hWnd, cxNew, cyNew);
	} else {
		UIWnd::SetClientSize(cxNew, cyNew);
	}
}

int UIWnd2::GetWindowText(CString& strText) const
{
	if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->GetWindowText(m_hWnd, strText);
	} else {
		return UIWnd::GetWindowText(strText);
	}
}

UINT UIWnd2::GetDlgItemText(int nID, CString& strText) const
{
	return _pUIWnd2Manager->GetDlgItemText(m_hWnd, nID, strText);
}

LRESULT UIWnd2::PostDlgItemMessage(int nID, UINT message, WPARAM wParam, LPARAM lParam) throw()
{
	return _pUIWnd2Manager->PostDlgItemMessage(m_hWnd, nID, message, wParam, lParam);
}

BOOL UIWnd2::TrackMouseEvent(DWORD dwFalgs)
{
	//if (_pUIWnd2Manager->IsDirectUI(m_hWnd)) {
		return _pUIWnd2Manager->TrackMouseEvent(m_hWnd, dwFalgs);
	//} else {
	//	return UIWnd::TrackMouseEvent(dwFalgs);
	//}
}

