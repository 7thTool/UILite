
#pragma once

#ifndef _H_UICMMCTRL2_H_
#define _H_UICMMCTRL2_H_

#include "UIWnd2.h"
#include "UISkin2.h"

//////////////////////////////////////////////////////////////////////////

#define DEFINE_CMMCTRL2_CLASS(classname,basename) \
	template<class TBase = UIWnd2> \
	class classname##T : public basename##T<TBase> \
	{ \
		typedef classname##T<TBase> This; \
		typedef basename##T<TBase> Base; \
	public: \
		classname##T(HWND hWnd = NULL) : Base(hWnd) { } \
		This & operator =(HWND hWnd) { m_hWnd = hWnd; return *this; } \
	}; \
	typedef classname##T<UIWnd2> classname;

//DEFINE_CMMCTRL2_CLASS(UIStatic2,UIStatic)
template <class TBase = UIWnd2>
class UIStatic2T : public TBase
{
	typedef UIStatic2T<TBase> This;
	typedef TBase Base;
public:
	// Constructors
	UIStatic2T(HWND hWnd = NULL) : TBase(hWnd)
	{ }
	
	This& operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}
	
	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}
	
	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return _T("STATIC");
	}
	
#ifndef _WIN32_WCE
	HICON GetIcon() const
	{
		return (HICON)SendMessage(STM_GETICON, 0, 0L);
	}
	
	HICON SetIcon(HICON hIcon)
	{
		return (HICON)SendMessage(STM_SETICON, (WPARAM)hIcon, 0L);
	}
	
	HENHMETAFILE GetEnhMetaFile() const
	{
		return (HENHMETAFILE)SendMessage(STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);
	}
	
	HENHMETAFILE SetEnhMetaFile(HENHMETAFILE hMetaFile)
	{
		return (HENHMETAFILE)SendMessage(STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);
	}
#else // CE specific
	HICON GetIcon() const
	{
		return (HICON)SendMessage(STM_GETIMAGE, IMAGE_ICON, 0L);
	}
	
	HICON SetIcon(HICON hIcon)
	{
		return (HICON)SendMessage(STM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	}
#endif // _WIN32_WCE
	
	CBitmapHandle GetBitmap() const
	{
		return CBitmapHandle((HBITMAP)SendMessage(STM_GETIMAGE, IMAGE_BITMAP, 0L));
	}
	
	CBitmapHandle SetBitmap(HBITMAP hBitmap)
	{
		return CBitmapHandle((HBITMAP)SendMessage(STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap));
	}
	
	HCURSOR GetCursor() const
	{
		return (HCURSOR)SendMessage(STM_GETIMAGE, IMAGE_CURSOR, 0L);
	}
	
	HCURSOR SetCursor(HCURSOR hCursor)
	{
		return (HCURSOR)SendMessage(STM_SETIMAGE, IMAGE_CURSOR, (LPARAM)hCursor);
	}
};
typedef UIStatic2T<UIWnd2> UIStatic2;
DEFINE_CMMCTRL2_CLASS(UIListBox2,UIListBox)
DEFINE_CMMCTRL2_CLASS(UIComboBox2,UIComboBox)
//DEFINE_CMMCTRL2_CLASS(UIEdit2,UIEdit)
template <class TBase = UIWnd2>
class UIEdit2T : public TBase
{
	typedef UIEdit2T<TBase> This;
	typedef TBase Base;
public:
// Constructors
	UIEdit2T(HWND hWnd = NULL) : TBase(hWnd)
	{ }

	This& operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

// Attributes
	static LPCTSTR GetWndClassName()
	{
		return _T("EDIT");
	}

	BOOL CanUndo() const
	{
		return (BOOL)SendMessage(EM_CANUNDO, 0, 0L);
	}

	int GetLineCount() const
	{
		return (int)SendMessage(EM_GETLINECOUNT, 0, 0L);
	}

	BOOL GetModify() const
	{
		return (BOOL)SendMessage(EM_GETMODIFY, 0, 0L);
	}

	void SetModify(BOOL bModified = TRUE)
	{
		SendMessage(EM_SETMODIFY, bModified, 0L);
	}

	void GetRect(LPRECT lpRect) const
	{
		SendMessage(EM_GETRECT, 0, (LPARAM)lpRect);
	}

	DWORD GetSel() const
	{
		return (DWORD)SendMessage(EM_GETSEL, 0, 0L);
	}

	void GetSel(int& nStartChar, int& nEndChar) const
	{
		SendMessage(EM_GETSEL, (WPARAM)&nStartChar, (LPARAM)&nEndChar);
	}

#ifndef _WIN32_WCE
	HLOCAL GetHandle() const
	{
		return (HLOCAL)SendMessage(EM_GETHANDLE, 0, 0L);
	}

	void SetHandle(HLOCAL hBuffer)
	{
		SendMessage(EM_SETHANDLE, (WPARAM)hBuffer, 0L);
	}
#endif // !_WIN32_WCE

	DWORD GetMargins() const
	{
		return (DWORD)SendMessage(EM_GETMARGINS, 0, 0L);
	}

	void SetMargins(UINT nLeft, UINT nRight)
	{
		SendMessage(EM_SETMARGINS, EC_LEFTMARGIN|EC_RIGHTMARGIN, MAKELONG(nLeft, nRight));
	}

	UINT GetLimitText() const
	{
		return (UINT)SendMessage(EM_GETLIMITTEXT, 0, 0L);
	}

	void SetLimitText(UINT nMax)
	{
		SendMessage(EM_SETLIMITTEXT, nMax, 0L);
	}

	POINT PosFromChar(UINT nChar) const
	{
		DWORD dwRet = (DWORD)SendMessage(EM_POSFROMCHAR, nChar, 0);
		POINT point = { GET_X_LPARAM(dwRet), GET_Y_LPARAM(dwRet) };
		return point;
	}

	int CharFromPos(POINT pt, int* pLine = NULL) const
	{
		DWORD dwRet = (DWORD)SendMessage(EM_CHARFROMPOS, 0, MAKELPARAM(pt.x, pt.y));
		if(pLine != NULL)
			*pLine = (int)(short)HIWORD(dwRet);
		return (int)(short)LOWORD(dwRet);
	}

	// NOTE: first word in lpszBuffer must contain the size of the buffer!
	int GetLine(int nIndex, LPTSTR lpszBuffer) const
	{
		return (int)SendMessage(EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	int GetLine(int nIndex, LPTSTR lpszBuffer, int nMaxLength) const
	{
		*(LPWORD)lpszBuffer = (WORD)nMaxLength;
		return (int)SendMessage(EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	TCHAR GetPasswordChar() const
	{
		return (TCHAR)SendMessage(EM_GETPASSWORDCHAR, 0, 0L);
	}

	void SetPasswordChar(TCHAR ch)
	{
		SendMessage(EM_SETPASSWORDCHAR, ch, 0L);
	}

#ifndef _WIN32_WCE
	EDITWORDBREAKPROC GetWordBreakProc() const
	{
		return (EDITWORDBREAKPROC)SendMessage(EM_GETWORDBREAKPROC, 0, 0L);
	}

	void SetWordBreakProc(EDITWORDBREAKPROC ewbprc)
	{
		SendMessage(EM_SETWORDBREAKPROC, 0, (LPARAM)ewbprc);
	}
#endif // !_WIN32_WCE

	int GetFirstVisibleLine() const
	{
		return (int)SendMessage(EM_GETFIRSTVISIBLELINE, 0, 0L);
	}

#ifndef _WIN32_WCE
	int GetThumb() const
	{
		ATLASSERT((GetStyle() & ES_MULTILINE) != 0);
		return (int)SendMessage(EM_GETTHUMB, 0, 0L);
	}
#endif // !_WIN32_WCE

	BOOL SetReadOnly(BOOL bReadOnly = TRUE)
	{
		return (BOOL)SendMessage(EM_SETREADONLY, bReadOnly, 0L);
	}

#if (WINVER >= 0x0500) && !defined(_WIN32_WCE)
	UINT GetImeStatus(UINT uStatus) const
	{
		return (UINT)SendMessage(EM_GETIMESTATUS, uStatus, 0L);
	}

	UINT SetImeStatus(UINT uStatus, UINT uData)
	{
		return (UINT)SendMessage(EM_SETIMESTATUS, uStatus, uData);
	}
#endif // (WINVER >= 0x0500) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0501)
	BOOL GetCueBannerText(LPCWSTR lpstrText, int cchText) const
	{
		return (BOOL)SendMessage(EM_GETCUEBANNER, (WPARAM)lpstrText, cchText);
	}

	// bKeepWithFocus - Vista only
	BOOL SetCueBannerText(LPCWSTR lpstrText, BOOL bKeepWithFocus = FALSE)
	{
		return (BOOL)SendMessage(EM_SETCUEBANNER, (WPARAM)bKeepWithFocus, (LPARAM)(lpstrText));
	}
#endif // (_WIN32_WINNT >= 0x0501)

// Operations
	void EmptyUndoBuffer()
	{
		SendMessage(EM_EMPTYUNDOBUFFER, 0, 0L);
	}

	BOOL FmtLines(BOOL bAddEOL)
	{
		return (BOOL)SendMessage(EM_FMTLINES, bAddEOL, 0L);
	}

	void LimitText(int nChars = 0)
	{
		SendMessage(EM_LIMITTEXT, nChars, 0L);
	}

	int LineFromChar(int nIndex = -1) const
	{
		return (int)SendMessage(EM_LINEFROMCHAR, nIndex, 0L);
	}

	int LineIndex(int nLine = -1) const
	{
		return (int)SendMessage(EM_LINEINDEX, nLine, 0L);
	}

	int LineLength(int nLine = -1) const
	{
		return (int)SendMessage(EM_LINELENGTH, nLine, 0L);
	}

	void LineScroll(int nLines, int nChars = 0)
	{
		SendMessage(EM_LINESCROLL, nChars, nLines);
	}

	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE)
	{
		SendMessage(EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
	}

	void SetRect(LPCRECT lpRect)
	{
		SendMessage(EM_SETRECT, 0, (LPARAM)lpRect);
	}

	void SetRectNP(LPCRECT lpRect)
	{
		SendMessage(EM_SETRECTNP, 0, (LPARAM)lpRect);
	}

	void SetSel(DWORD dwSelection, BOOL bNoScroll = FALSE)
	{
		SendMessage(EM_SETSEL, LOWORD(dwSelection), HIWORD(dwSelection));
		if(!bNoScroll)
			SendMessage(EM_SCROLLCARET, 0, 0L);
	}

	void SetSel(int nStartChar, int nEndChar, BOOL bNoScroll = FALSE)
	{
		SendMessage(EM_SETSEL, nStartChar, nEndChar);
		if(!bNoScroll)
			SendMessage(EM_SCROLLCARET, 0, 0L);
	}

	void SetSelAll(BOOL bNoScroll = FALSE)
	{
		SetSel(0, -1, bNoScroll);
	}

	void SetSelNone(BOOL bNoScroll = FALSE)
	{
		SetSel(-1, 0, bNoScroll);
	}

	BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
	{
		return (BOOL)SendMessage(EM_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
	}

	BOOL SetTabStops()
	{
		return (BOOL)SendMessage(EM_SETTABSTOPS, 0, 0L);
	}

	BOOL SetTabStops(const int& cxEachStop)    // takes an 'int'
	{
		return (BOOL)SendMessage(EM_SETTABSTOPS, 1, (LPARAM)(LPINT)&cxEachStop);
	}

	void ScrollCaret()
	{
		SendMessage(EM_SCROLLCARET, 0, 0L);
	}

	int Scroll(int nScrollAction)
	{
		ATLASSERT((GetStyle() & ES_MULTILINE) != 0);
		LRESULT lRet = SendMessage(EM_SCROLL, nScrollAction, 0L);
		if(!(BOOL)HIWORD(lRet))
			return -1;   // failed
		return (int)(short)LOWORD(lRet);
		
	}

	void InsertText(int nInsertAfterChar, LPCTSTR lpstrText, BOOL bNoScroll = FALSE, BOOL bCanUndo = FALSE)
	{
		SetSel(nInsertAfterChar, nInsertAfterChar, bNoScroll);
		ReplaceSel(lpstrText, bCanUndo);
	}

	void AppendText(LPCTSTR lpstrText, BOOL bNoScroll = FALSE, BOOL bCanUndo = FALSE)
	{
		InsertText(GetWindowTextLength(), lpstrText, bNoScroll, bCanUndo);
	}

#if (_WIN32_WINNT >= 0x0501)
	BOOL ShowBalloonTip(PEDITBALLOONTIP pEditBaloonTip)
	{
		return (BOOL)SendMessage(EM_SHOWBALLOONTIP, 0, (LPARAM)pEditBaloonTip);
	}

	BOOL HideBalloonTip()
	{
		return (BOOL)SendMessage(EM_HIDEBALLOONTIP, 0, 0L);
	}
#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)
	DWORD GetHilite() const
	{
		return (DWORD)SendMessage(EM_GETHILITE, 0, 0L);
	}

	void GetHilite(int& nStartChar, int& nEndChar) const
	{
		DWORD dwRet = (DWORD)SendMessage(EM_GETHILITE, 0, 0L);
		nStartChar = (int)(short)LOWORD(dwRet);
		nEndChar = (int)(short)HIWORD(dwRet);
	}

	void SetHilite(int nStartChar, int nEndChar)
	{
		SendMessage(EM_SETHILITE, nStartChar, nEndChar);
	}
#endif // (_WIN32_WINNT >= 0x0600)

	// Clipboard operations
	BOOL Undo()
	{
		return (BOOL)SendMessage(EM_UNDO, 0, 0L);
	}

	void Clear()
	{
		SendMessage(WM_CLEAR, 0, 0L);
	}

	void Copy()
	{
		SendMessage(WM_COPY, 0, 0L);
	}

	void Cut()
	{
		SendMessage(WM_CUT, 0, 0L);
	}

	void Paste()
	{
		SendMessage(WM_PASTE, 0, 0L);
	}

#ifdef WIN32_PLATFORM_WFSP   // SmartPhone only messages
	DWORD GetExtendedStyle()
	{
		return SendMessage(EM_GETEXTENDEDSTYLE);
	}

	DWORD SetExtendedStyle(DWORD dwMask, DWORD dwExStyle)
	{
		return SendMessage(EM_SETEXTENDEDSTYLE, (WPARAM)dwMask, (LPARAM)dwExStyle);
	}

	DWORD GetInputMode(BOOL bCurrentMode = TRUE)
	{
		return SendMessage(EM_GETINPUTMODE, 0, (LPARAM)bCurrentMode);
	}

	BOOL SetInputMode(DWORD dwMode)
	{
		return SendMessage(EM_SETINPUTMODE, 0, (LPARAM)dwMode);
	}

	BOOL SetSymbols(LPCTSTR szSymbols)
	{
		return SendMessage(EM_SETSYMBOLS, 0, (LPARAM)szSymbols);
	}

	BOOL ResetSymbols()
	{
		return SendMessage(EM_SETSYMBOLS);
	}
#endif // WIN32_PLATFORM_WFSP
};
typedef UIEdit2T<UIWnd2> UIEdit2;
//DEFINE_CMMCTRL2_CLASS(UIScrollBar2,UIScrollBar)
template <class TBase = UIWnd2>
class UIScrollBar2T : public TBase
{
	typedef UIScrollBar2T This;
	typedef TBase Base;
public:
	// Constructors
	UIScrollBar2T(HWND hWnd = NULL) : Base(hWnd)
	{ }

	This& operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return _T("SCROLLBAR");
	}

#ifndef _WIN32_WCE
	int GetScrollPos() const
	{
		return Base::GetScrollPos(SB_CTL);
	}
#endif // !_WIN32_WCE

	int SetScrollPos(int nPos, BOOL bRedraw = TRUE)
	{
		return Base::SetScrollPos(SB_CTL, nPos, bRedraw);
	}

#ifndef _WIN32_WCE
	void GetScrollRange(LPINT lpMinPos, LPINT lpMaxPos) const
	{
		Base::GetScrollRange(SB_CTL, lpMinPos, lpMaxPos);
	}
#endif // !_WIN32_WCE

	void SetScrollRange(int nMinPos, int nMaxPos, BOOL bRedraw = TRUE)
	{
		Base::SetScrollRange(SB_CTL, nMinPos, nMaxPos, bRedraw);
	}

	BOOL GetScrollInfo(LPSCROLLINFO lpScrollInfo)// const
	{
		return Base::GetScrollInfo(SB_CTL, lpScrollInfo);
	}

	int SetScrollInfo(LPSCROLLINFO lpScrollInfo, BOOL bRedraw = TRUE)
	{
		return Base::SetScrollInfo(SB_CTL, lpScrollInfo, bRedraw);
	}

#ifndef _WIN32_WCE
	int GetScrollLimit() const
	{
		int nMin = 0, nMax = 0;
		Base::GetScrollRange(SB_CTL, &nMin, &nMax);
		SCROLLINFO info = { 0 };
		info.cbSize = sizeof(SCROLLINFO);
		info.fMask = SIF_PAGE;
		if(Base::GetScrollInfo(SB_CTL, &info))
			nMax -= ((info.nPage - 1) > 0) ? (info.nPage - 1) : 0;

		return nMax;
	}

#if (WINVER >= 0x0500)
	BOOL GetScrollBarInfo(PSCROLLBARINFO pScrollBarInfo) const
	{
#if (_WIN32_WINNT >= 0x0501)
		return (BOOL)SendMessage(SBM_GETSCROLLBARINFO, 0, (LPARAM)pScrollBarInfo);
#else // !(_WIN32_WINNT >= 0x0501)
		return Base::GetScrollBarInfo(OBJID_CLIENT, pScrollBarInfo);
#endif // !(_WIN32_WINNT >= 0x0501)
	}
#endif // (WINVER >= 0x0500)

	// Operations
	void ShowScrollBar(BOOL bShow = TRUE)
	{
		Base::ShowScrollBar(SB_CTL, bShow);
	}

	BOOL EnableScrollBar(UINT nArrowFlags = ESB_ENABLE_BOTH)
	{
		Base::EnableScrollBar(SB_CTL, nArrowFlags);
	}
#endif // !_WIN32_WCE
};
typedef UIScrollBar2T<UIWnd2>   UIScrollBar2;
//DEFINE_CMMCTRL2_CLASS(UIButton2,UIButton)
template<class TBase = UIWnd2>
class UIButton2T : public TBase
{
	typedef UIButton2T<TBase> This;
	typedef TBase Base;
public:
	// Constructors
	UIButton2T(HWND hWnd = NULL) : Base(hWnd)
	{ }
	
	Base & operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}
	
	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return _T("BUTTON");
	}

	UINT GetState() const
	{
		return (UINT)SendMessage(BM_GETSTATE, 0, 0L);
	}

	void SetState(BOOL bHighlight)
	{
		SendMessage(BM_SETSTATE, bHighlight, 0L);
	}

	int GetCheck() const
	{
		return (int)SendMessage(BM_GETCHECK, 0, 0L);
	}

	void SetCheck(int nCheck)
	{
		SendMessage(BM_SETCHECK, nCheck, 0L);
	}

	UINT GetButtonStyle() const
	{
		return (UINT)GetWindowLong(GWL_STYLE) & 0xFFFF;
	}

	void SetButtonStyle(UINT nStyle, BOOL bRedraw = TRUE)
	{
		SendMessage(BM_SETSTYLE, nStyle, (LPARAM)bRedraw);
	}

#ifndef _WIN32_WCE
	HICON GetIcon() const
	{
		return (HICON)SendMessage(BM_GETIMAGE, IMAGE_ICON, 0L);
	}

	HICON SetIcon(HICON hIcon)
	{
		return (HICON)SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)hIcon);
	}

	CBitmapHandle GetBitmap() const
	{
		return CBitmapHandle((HBITMAP)SendMessage(BM_GETIMAGE, IMAGE_BITMAP, 0L));
	}

	CBitmapHandle SetBitmap(HBITMAP hBitmap)
	{
		return CBitmapHandle((HBITMAP)SendMessage(BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap));
	}
#endif // !_WIN32_WCE

#if (_WIN32_WINNT >= 0x0501)
	BOOL GetIdealSize(LPSIZE lpSize) const
	{
		return (BOOL)SendMessage(BCM_GETIDEALSIZE, 0, (LPARAM)lpSize);
	}

	BOOL GetImageList(PBUTTON_IMAGELIST pButtonImagelist) const
	{
		return (BOOL)SendMessage(BCM_GETIMAGELIST, 0, (LPARAM)pButtonImagelist);
	}

	BOOL SetImageList(PBUTTON_IMAGELIST pButtonImagelist)
	{
		return (BOOL)SendMessage(BCM_SETIMAGELIST, 0, (LPARAM)pButtonImagelist);
	}

	BOOL GetTextMargin(LPRECT lpRect) const
	{
		return (BOOL)SendMessage(BCM_GETTEXTMARGIN, 0, (LPARAM)lpRect);
	}

	BOOL SetTextMargin(LPRECT lpRect)
	{
		return (BOOL)SendMessage(BCM_SETTEXTMARGIN, 0, (LPARAM)lpRect);
	}
#endif // (_WIN32_WINNT >= 0x0501)

#if (WINVER >= 0x0600)
	void SetDontClick(BOOL bDontClick)
	{
		SendMessage(BM_SETDONTCLICK, (WPARAM)bDontClick, 0L);
	}
#endif // (WINVER >= 0x0600)

#if (_WIN32_WINNT >= 0x0600)
	BOOL SetDropDownState(BOOL bDropDown)
	{
		ATLASSERT((GetStyle() & (BS_SPLITBUTTON | BS_DEFSPLITBUTTON)) != 0);
		return (BOOL)SendMessage(BCM_SETDROPDOWNSTATE, (WPARAM)bDropDown, 0L);
	}

	BOOL GetSplitInfo(PBUTTON_SPLITINFO pSplitInfo) const
	{
		ATLASSERT((GetStyle() & (BS_SPLITBUTTON | BS_DEFSPLITBUTTON)) != 0);
		return (BOOL)SendMessage(BCM_GETSPLITINFO, 0, (LPARAM)pSplitInfo);
	}

	BOOL SetSplitInfo(PBUTTON_SPLITINFO pSplitInfo)
	{
		ATLASSERT((GetStyle() & (BS_SPLITBUTTON | BS_DEFSPLITBUTTON)) != 0);
		return (BOOL)SendMessage(BCM_SETSPLITINFO, 0, (LPARAM)pSplitInfo);
	}

	int GetNoteLength() const
	{
		ATLASSERT((GetStyle() & (BS_COMMANDLINK | BS_DEFCOMMANDLINK)) != 0);
		return (int)SendMessage(BCM_GETNOTELENGTH, 0, 0L);
	}

	BOOL GetNote(LPWSTR lpstrNoteText, int cchNoteText) const
	{
		ATLASSERT((GetStyle() & (BS_COMMANDLINK | BS_DEFCOMMANDLINK)) != 0);
		return (BOOL)SendMessage(BCM_GETNOTE, cchNoteText, (LPARAM)lpstrNoteText);
	}

	BOOL SetNote(LPCWSTR lpstrNoteText)
	{
		ATLASSERT((GetStyle() & (BS_COMMANDLINK | BS_DEFCOMMANDLINK)) != 0);
		return (BOOL)SendMessage(BCM_SETNOTE, 0, (LPARAM)lpstrNoteText);
	}

	LRESULT SetElevationRequiredState(BOOL bSet)
	{
		return SendMessage(BCM_SETSHIELD, 0, (LPARAM)bSet);
	}
#endif // (_WIN32_WINNT >= 0x0600)

// Operations
	void Click()
	{
		SendMessage(BM_CLICK, 0, 0L);
	}
};
typedef UIButton2T<UIWnd2> UIButton2;
//DEFINE_CMMCTRL2_CLASS(UIListCtrl2,UIListCtrl)
template <class TBase = UIWnd2>
class UIListCtrl2T : public TBase
{
	typedef UIListCtrl2T<TBase> This;
	typedef TBase Base;
public:
	// Constructors
	UIListCtrl2T(HWND hWnd = NULL) : Base(hWnd)
	{ }

	This & operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return WC_LISTVIEW;
	}

	COLORREF GetBkColor() const
	{
		return (COLORREF)SendMessage(LVM_GETBKCOLOR, 0, 0L);
	}

	BOOL SetBkColor(COLORREF cr)
	{
		return (BOOL)SendMessage(LVM_SETBKCOLOR, 0, cr);
	}

	CImageList GetImageList(int nImageListType) const
	{
		return CImageList((HIMAGELIST)SendMessage(LVM_GETIMAGELIST, nImageListType, 0L));
	}

	CImageList SetImageList(HIMAGELIST hImageList, int nImageList)
	{
		return CImageList((HIMAGELIST)SendMessage(LVM_SETIMAGELIST, nImageList, (LPARAM)hImageList));
	}

	int GetItemCount() const
	{
		return (int)SendMessage(LVM_GETITEMCOUNT, 0, 0L);
	}

	BOOL SetItemCount(int nItems)
	{
		return (BOOL)SendMessage(LVM_SETITEMCOUNT, nItems, 0L);
	}

	BOOL GetItem(LPLVITEM pItem) const
	{
		return (BOOL)SendMessage(LVM_GETITEM, 0, (LPARAM)pItem);
	}

	BOOL SetItem(const LVITEM* pItem)
	{
		return (BOOL)SendMessage(LVM_SETITEM, 0, (LPARAM)pItem);
	}

	BOOL SetItem(int nItem, int nSubItem, UINT nMask, LPCTSTR lpszItem,
		int nImage, UINT nState, UINT nStateMask, LPARAM lParam)
	{
		LVITEM lvi = { 0 };
		lvi.mask = nMask;
		lvi.iItem = nItem;
		lvi.iSubItem = nSubItem;
		lvi.stateMask = nStateMask;
		lvi.state = nState;
		lvi.pszText = (LPTSTR) lpszItem;
		lvi.iImage = nImage;
		lvi.lParam = lParam;
		return (BOOL)SendMessage(LVM_SETITEM, 0, (LPARAM)&lvi);
	}

	UINT GetItemState(int nItem, UINT nMask) const
	{
		return (UINT)SendMessage(LVM_GETITEMSTATE, nItem, nMask);
	}

	BOOL SetItemState(int nItem, UINT nState, UINT nStateMask)
	{
		LVITEM lvi = { 0 };
		lvi.state = nState;
		lvi.stateMask = nStateMask;
		return (BOOL)SendMessage(LVM_SETITEMSTATE, nItem, (LPARAM)&lvi);
	}

	BOOL SetItemState(int nItem, LPLVITEM pItem)
	{
		return (BOOL)SendMessage(LVM_SETITEMSTATE, nItem, (LPARAM)pItem);
	}

#ifndef _ATL_NO_COM
	BOOL GetItemText(int nItem, int nSubItem, BSTR& bstrText) const
	{
		USES_CONVERSION;
		ATLASSERT(bstrText == NULL);
		LVITEM lvi = { 0 };
		lvi.iSubItem = nSubItem;

		LPTSTR lpstrText = NULL;
		int nRes = 0;
		for(int nLen = 256; ; nLen *= 2)
		{
			ATLTRY(lpstrText = new TCHAR[nLen]);
			if(lpstrText == NULL)
				break;
			lpstrText[0] = NULL;
			lvi.cchTextMax = nLen;
			lvi.pszText = lpstrText;
			nRes  = (int)SendMessage(LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
			if(nRes < nLen - 1)
				break;
			delete [] lpstrText;
			lpstrText = NULL;
		}

		if(lpstrText != NULL)
		{
			if(nRes != 0)
				bstrText = ::SysAllocString(T2OLE(lpstrText));
			delete [] lpstrText;
		}

		return (bstrText != NULL) ? TRUE : FALSE;
	}
#endif // !_ATL_NO_COM

#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)
	int GetItemText(int nItem, int nSubItem, _CSTRING_NS::CString& strText) const
	{
		LVITEM lvi = { 0 };
		lvi.iSubItem = nSubItem;

		strText.Empty();
		int nRes = 0;
		for(int nLen = 256; ; nLen *= 2)
		{
			lvi.cchTextMax = nLen;
			lvi.pszText = strText.GetBufferSetLength(nLen);
			if(lvi.pszText == NULL)
			{
				nRes = 0;
				break;
			}
			nRes  = (int)SendMessage(LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
			if(nRes < nLen - 1)
				break;
		}
		strText.ReleaseBuffer();
		return nRes;
	}
#endif // defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)

	int GetItemText(int nItem, int nSubItem, LPTSTR lpszText, int nLen) const
	{
		LVITEM lvi = { 0 };
		lvi.iSubItem = nSubItem;
		lvi.cchTextMax = nLen;
		lvi.pszText = lpszText;
		return (int)SendMessage(LVM_GETITEMTEXT, (WPARAM)nItem, (LPARAM)&lvi);
	}

	BOOL SetItemText(int nItem, int nSubItem, LPCTSTR lpszText)
	{
		return SetItem(nItem, nSubItem, LVIF_TEXT, lpszText, 0, 0, 0, 0);
	}

	DWORD_PTR GetItemData(int nItem) const
	{
		LVITEM lvi = { 0 };
		lvi.iItem = nItem;
		lvi.mask = LVIF_PARAM;
		BOOL bRet = (BOOL)SendMessage(LVM_GETITEM, 0, (LPARAM)&lvi);
		return (DWORD_PTR)(bRet ? lvi.lParam : NULL);
	}

	BOOL SetItemData(int nItem, DWORD_PTR dwData)
	{
		return SetItem(nItem, 0, LVIF_PARAM, NULL, 0, 0, 0, (LPARAM)dwData);
	}

	UINT GetCallbackMask() const
	{
		return (UINT)SendMessage(LVM_GETCALLBACKMASK, 0, 0L);
	}

	BOOL SetCallbackMask(UINT nMask)
	{
		return (BOOL)SendMessage(LVM_SETCALLBACKMASK, nMask, 0L);
	}

	BOOL GetItemPosition(int nItem, LPPOINT lpPoint) const
	{
		return (BOOL)SendMessage(LVM_GETITEMPOSITION, nItem, (LPARAM)lpPoint);
	}

	BOOL SetItemPosition(int nItem, POINT pt)
	{
		ATLASSERT(((GetStyle() & LVS_TYPEMASK) == LVS_ICON) || ((GetStyle() & LVS_TYPEMASK) == LVS_SMALLICON));
		return (BOOL)SendMessage(LVM_SETITEMPOSITION32, nItem, (LPARAM)&pt);
	}

	BOOL SetItemPosition(int nItem, int x, int y)
	{
		ATLASSERT(((GetStyle() & LVS_TYPEMASK) == LVS_ICON) || ((GetStyle() & LVS_TYPEMASK) == LVS_SMALLICON));
		POINT pt = { x, y };
		return (BOOL)SendMessage(LVM_SETITEMPOSITION32, nItem, (LPARAM)&pt);
	}

	int GetStringWidth(LPCTSTR lpsz) const
	{
		return (int)SendMessage(LVM_GETSTRINGWIDTH, 0, (LPARAM)lpsz);
	}

	CEdit GetEditControl() const
	{
		return CEdit((HWND)SendMessage(LVM_GETEDITCONTROL, 0, 0L));
	}

	BOOL GetColumn(int nCol, LVCOLUMN* pColumn) const
	{
		return (BOOL)SendMessage(LVM_GETCOLUMN, nCol, (LPARAM)pColumn);
	}

	BOOL SetColumn(int nCol, const LVCOLUMN* pColumn)
	{
		return (BOOL)SendMessage(LVM_SETCOLUMN, nCol, (LPARAM)pColumn);
	}

	int GetColumnWidth(int nCol) const
	{
		return (int)SendMessage(LVM_GETCOLUMNWIDTH, nCol, 0L);
	}

	BOOL SetColumnWidth(int nCol, int cx)
	{
		return (BOOL)SendMessage(LVM_SETCOLUMNWIDTH, nCol, MAKELPARAM(cx, 0));
	}

	BOOL GetViewRect(LPRECT lpRect) const
	{
		return (BOOL)SendMessage(LVM_GETVIEWRECT, 0, (LPARAM)lpRect);
	}

	COLORREF GetTextColor() const
	{
		return (COLORREF)SendMessage(LVM_GETTEXTCOLOR, 0, 0L);
	}

	BOOL SetTextColor(COLORREF cr)
	{
		return (BOOL)SendMessage(LVM_SETTEXTCOLOR, 0, cr);
	}

	COLORREF GetTextBkColor() const
	{
		return (COLORREF)SendMessage(LVM_GETTEXTBKCOLOR, 0, 0L);
	}

	BOOL SetTextBkColor(COLORREF cr)
	{
		return (BOOL)SendMessage(LVM_SETTEXTBKCOLOR, 0, cr);
	}

	int GetTopIndex() const
	{
		return (int)SendMessage(LVM_GETTOPINDEX, 0, 0L);
	}

	int GetCountPerPage() const
	{
		return (int)SendMessage(LVM_GETCOUNTPERPAGE, 0, 0L);
	}

	BOOL GetOrigin(LPPOINT lpPoint) const
	{
		return (BOOL)SendMessage(LVM_GETORIGIN, 0, (LPARAM)lpPoint);
	}

	UINT GetSelectedCount() const
	{
		return (UINT)SendMessage(LVM_GETSELECTEDCOUNT, 0, 0L);
	}

	BOOL GetItemRect(int nItem, LPRECT lpRect, UINT nCode) const
	{
		lpRect->left = nCode;
		return (BOOL)SendMessage(LVM_GETITEMRECT, (WPARAM)nItem, (LPARAM)lpRect);
	}

#ifndef _WIN32_WCE
	HCURSOR GetHotCursor() const
	{
		return (HCURSOR)SendMessage(LVM_GETHOTCURSOR, 0, 0L);
	}

	HCURSOR SetHotCursor(HCURSOR hHotCursor)
	{
		return (HCURSOR)SendMessage(LVM_SETHOTCURSOR, 0, (LPARAM)hHotCursor);
	}

	int GetHotItem() const
	{
		return (int)SendMessage(LVM_GETHOTITEM, 0, 0L);
	}

	int SetHotItem(int nIndex)
	{
		return (int)SendMessage(LVM_SETHOTITEM, nIndex, 0L);
	}
#endif // !_WIN32_WCE

	BOOL GetColumnOrderArray(int nCount, int* lpnArray) const
	{
		return (BOOL)SendMessage(LVM_GETCOLUMNORDERARRAY, nCount, (LPARAM)lpnArray);
	}

	BOOL SetColumnOrderArray(int nCount, int* lpnArray)
	{
		return (BOOL)SendMessage(LVM_SETCOLUMNORDERARRAY, nCount, (LPARAM)lpnArray);
	}

	HWND GetHeader() const
	{
		return (HWND)SendMessage(LVM_GETHEADER, 0, 0L);
	}

	BOOL GetSubItemRect(int nItem, int nSubItem, int nFlag, LPRECT lpRect) const
	{
		ATLASSERT((GetStyle() & LVS_TYPEMASK) == LVS_REPORT);
		ATLASSERT(lpRect != NULL);
		lpRect->top = nSubItem;
		lpRect->left = nFlag;
		return (BOOL)SendMessage(LVM_GETSUBITEMRECT, nItem, (LPARAM)lpRect);
	}

	DWORD SetIconSpacing(int cx, int cy)
	{
		ATLASSERT((GetStyle() & LVS_TYPEMASK) == LVS_ICON);
		return (DWORD)SendMessage(LVM_SETICONSPACING, 0, MAKELPARAM(cx, cy));
	}

	int GetISearchString(LPTSTR lpstr) const
	{
		return (int)SendMessage(LVM_GETISEARCHSTRING, 0, (LPARAM)lpstr);
	}

	void GetItemSpacing(SIZE& sizeSpacing, BOOL bSmallIconView = FALSE) const
	{
		DWORD dwRet = (DWORD)SendMessage(LVM_GETITEMSPACING, bSmallIconView, 0L);
		sizeSpacing.cx = GET_X_LPARAM(dwRet);
		sizeSpacing.cy = GET_Y_LPARAM(dwRet);
	}

#if (_WIN32_WCE >= 410)
	void SetItemSpacing(INT cySpacing)
	{
		ListView_SetItemSpacing(m_hWnd, cySpacing);
	}
#endif // (_WIN32_WCE >= 410)

	// single-selection only
	int GetSelectedIndex() const
	{
		ATLASSERT((GetStyle() & LVS_SINGLESEL) != 0);
		return (int)SendMessage(LVM_GETNEXTITEM, (WPARAM)-1, MAKELPARAM(LVNI_ALL | LVNI_SELECTED, 0));
	}

	BOOL GetSelectedItem(LPLVITEM pItem) const
	{
		ATLASSERT((GetStyle() & LVS_SINGLESEL) != 0);
		ATLASSERT(pItem != NULL);
		pItem->iItem = (int)SendMessage(LVM_GETNEXTITEM, (WPARAM)-1, MAKELPARAM(LVNI_ALL | LVNI_SELECTED, 0));
		if(pItem->iItem == -1)
			return FALSE;
		return (BOOL)SendMessage(LVM_GETITEM, 0, (LPARAM)pItem);
	}

	// extended list view styles
	DWORD GetExtendedListViewStyle() const
	{
		return (DWORD)SendMessage(LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0L);
	}

	// dwExMask = 0 means all styles
	DWORD SetExtendedListViewStyle(DWORD dwExStyle, DWORD dwExMask = 0)
	{
		return (DWORD)SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, dwExMask, dwExStyle);
	}

	// checkboxes only
	BOOL GetCheckState(int nIndex) const
	{
		ATLASSERT((GetExtendedListViewStyle() & LVS_EX_CHECKBOXES) != 0);
		UINT uRet = GetItemState(nIndex, LVIS_STATEIMAGEMASK);
		return (uRet >> 12) - 1;
	}

	BOOL SetCheckState(int nItem, BOOL bCheck)
	{
		int nCheck = bCheck ? 2 : 1;   // one based index
		return SetItemState(nItem, INDEXTOSTATEIMAGEMASK(nCheck), LVIS_STATEIMAGEMASK);
	}

	// view type
	DWORD GetViewType() const
	{
		return (GetStyle() & LVS_TYPEMASK);
	}

	DWORD SetViewType(DWORD dwType)
	{
		ATLASSERT(dwType == LVS_ICON || dwType == LVS_SMALLICON || dwType == LVS_LIST || dwType == LVS_REPORT);
		DWORD dwOldType = GetViewType();
		if(dwType != dwOldType)
			ModifyStyle(LVS_TYPEMASK, (dwType & LVS_TYPEMASK));
		return dwOldType;
	}

#if (_WIN32_IE >= 0x0400)
#ifndef _WIN32_WCE
	BOOL GetBkImage(LPLVBKIMAGE plvbki) const
	{
		return (BOOL)SendMessage(LVM_GETBKIMAGE, 0, (LPARAM)plvbki);
	}

	BOOL SetBkImage(LPLVBKIMAGE plvbki)
	{
		return (BOOL)SendMessage(LVM_SETBKIMAGE, 0, (LPARAM)plvbki);
	}
#endif // !_WIN32_WCE

	int GetSelectionMark() const
	{
		return (int)SendMessage(LVM_GETSELECTIONMARK, 0, 0L);
	}

	int SetSelectionMark(int nIndex)
	{
		return (int)SendMessage(LVM_SETSELECTIONMARK, 0, nIndex);
	}

#ifndef _WIN32_WCE
	BOOL GetWorkAreas(int nWorkAreas, LPRECT lpRect) const
	{
		return (BOOL)SendMessage(LVM_GETWORKAREAS, nWorkAreas, (LPARAM)lpRect);
	}

	BOOL SetWorkAreas(int nWorkAreas, LPRECT lpRect)
	{
		return (BOOL)SendMessage(LVM_SETWORKAREAS, nWorkAreas, (LPARAM)lpRect);
	}

	DWORD GetHoverTime() const
	{
		ATLASSERT((GetExtendedListViewStyle() & (LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TWOCLICKACTIVATE)) != 0);
		return (DWORD)SendMessage(LVM_GETHOVERTIME, 0, 0L);
	}

	DWORD SetHoverTime(DWORD dwHoverTime)
	{
		ATLASSERT((GetExtendedListViewStyle() & (LVS_EX_TRACKSELECT | LVS_EX_ONECLICKACTIVATE | LVS_EX_TWOCLICKACTIVATE)) != 0);
		return (DWORD)SendMessage(LVM_SETHOVERTIME, 0, dwHoverTime);
	}

	BOOL GetNumberOfWorkAreas(int* pnWorkAreas) const
	{
		return (BOOL)SendMessage(LVM_GETNUMBEROFWORKAREAS, 0, (LPARAM)pnWorkAreas);
	}
#endif // !_WIN32_WCE

	BOOL SetItemCountEx(int nItems, DWORD dwFlags)
	{
		ATLASSERT(((GetStyle() & LVS_OWNERDATA) != 0) && (((GetStyle() & LVS_TYPEMASK) == LVS_REPORT) || ((GetStyle() & LVS_TYPEMASK) == LVS_LIST)));
		return (BOOL)SendMessage(LVM_SETITEMCOUNT, nItems, dwFlags);
	}

#ifndef _WIN32_WCE
	CToolTipCtrl GetToolTips() const
	{
		return CToolTipCtrl((HWND)SendMessage(LVM_GETTOOLTIPS, 0, 0L));
	}

	CToolTipCtrl SetToolTips(HWND hWndTT)
	{
		return CToolTipCtrl((HWND)SendMessage(LVM_SETTOOLTIPS, (WPARAM)hWndTT, 0L));
	}

	BOOL GetUnicodeFormat() const
	{
		return (BOOL)SendMessage(LVM_GETUNICODEFORMAT, 0, 0L);
	}

	BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
	{
		return (BOOL)SendMessage(LVM_SETUNICODEFORMAT, bUnicode, 0L);
	}
#endif // !_WIN32_WCE
#endif // (_WIN32_IE >= 0x0400)

#if (_WIN32_WINNT >= 0x0501)
	int GetSelectedColumn() const
	{
		return (int)SendMessage(LVM_GETSELECTEDCOLUMN, 0, 0L);
	}

	void SetSelectedColumn(int nColumn)
	{
		SendMessage(LVM_SETSELECTEDCOLUMN, nColumn, 0L);
	}

	DWORD GetView() const
	{
		return (DWORD)SendMessage(LVM_GETVIEW, 0, 0L);
	}

	int SetView(DWORD dwView)
	{
		return (int)SendMessage(LVM_SETVIEW, dwView, 0L);
	}

	BOOL IsGroupViewEnabled() const
	{
		return (BOOL)SendMessage(LVM_ISGROUPVIEWENABLED, 0, 0L);
	}

	int GetGroupInfo(int nGroupID, PLVGROUP pGroup) const
	{
		return (int)SendMessage(LVM_GETGROUPINFO, nGroupID, (LPARAM)pGroup);
	}

	int SetGroupInfo(int nGroupID, PLVGROUP pGroup)
	{
		return (int)SendMessage(LVM_SETGROUPINFO, nGroupID, (LPARAM)pGroup);
	}

	void GetGroupMetrics(PLVGROUPMETRICS pGroupMetrics) const
	{
		SendMessage(LVM_GETGROUPMETRICS, 0, (LPARAM)pGroupMetrics);
	}

	void SetGroupMetrics(PLVGROUPMETRICS pGroupMetrics)
	{
		SendMessage(LVM_SETGROUPMETRICS, 0, (LPARAM)pGroupMetrics);
	}

	void GetTileViewInfo(PLVTILEVIEWINFO pTileViewInfo) const
	{
		SendMessage(LVM_GETTILEVIEWINFO, 0, (LPARAM)pTileViewInfo);
	}

	BOOL SetTileViewInfo(PLVTILEVIEWINFO pTileViewInfo)
	{
		return (BOOL)SendMessage(LVM_SETTILEVIEWINFO, 0, (LPARAM)pTileViewInfo);
	}

	void GetTileInfo(PLVTILEINFO pTileInfo) const
	{
		SendMessage(LVM_GETTILEINFO, 0, (LPARAM)pTileInfo);
	}

	BOOL SetTileInfo(PLVTILEINFO pTileInfo)
	{
		return (BOOL)SendMessage(LVM_SETTILEINFO, 0, (LPARAM)pTileInfo);
	}

	BOOL GetInsertMark(LPLVINSERTMARK pInsertMark) const
	{
		return (BOOL)SendMessage(LVM_GETINSERTMARK, 0, (LPARAM)pInsertMark);
	}

	BOOL SetInsertMark(LPLVINSERTMARK pInsertMark)
	{
		return (BOOL)SendMessage(LVM_SETINSERTMARK, 0, (LPARAM)pInsertMark);
	}

	int GetInsertMarkRect(LPRECT lpRect) const
	{
		return (int)SendMessage(LVM_GETINSERTMARKRECT, 0, (LPARAM)lpRect);
	}

	COLORREF GetInsertMarkColor() const
	{
		return (COLORREF)SendMessage(LVM_GETINSERTMARKCOLOR, 0, 0L);
	}

	COLORREF SetInsertMarkColor(COLORREF cr)
	{
		return (COLORREF)SendMessage(LVM_SETINSERTMARKCOLOR, 0, cr);
	}

	COLORREF GetOutlineColor() const
	{
		return (COLORREF)SendMessage(LVM_GETOUTLINECOLOR, 0, 0L);
	}

	COLORREF SetOutlineColor(COLORREF cr)
	{
		return (COLORREF)SendMessage(LVM_SETOUTLINECOLOR, 0, cr);
	}
#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)
	int GetGroupCount() const
	{
		return (int)SendMessage(LVM_GETGROUPCOUNT, 0, 0L);
	}

	BOOL GetGroupInfoByIndex(int nIndex, PLVGROUP pGroup) const
	{
		return (BOOL)SendMessage(LVM_GETGROUPINFOBYINDEX, nIndex, (LPARAM)pGroup);
	}

	BOOL GetGroupRect(int nGroupID, int nType, LPRECT lpRect) const
	{
		ATLASSERT(lpRect != NULL);
		if(lpRect != NULL)
			lpRect->top = nType;
		return (BOOL)SendMessage(LVM_GETGROUPRECT, nGroupID, (LPARAM)lpRect);
	}

	UINT GetGroupState(int nGroupID, UINT uMask) const
	{
		return (UINT)SendMessage(LVM_GETGROUPSTATE, nGroupID, (LPARAM)uMask);
	}

	int GetFocusedGroup() const
	{
		return (int)SendMessage(LVM_GETFOCUSEDGROUP, 0, 0L);
	}

	BOOL GetEmptyText(LPWSTR lpstrText, int cchText) const
	{
		return (BOOL)SendMessage(LVM_GETEMPTYTEXT, cchText, (LPARAM)lpstrText);
	}

	BOOL GetFooterRect(LPRECT lpRect) const
	{
		return (BOOL)SendMessage(LVM_GETFOOTERRECT, 0, (LPARAM)lpRect);
	}

	BOOL GetFooterInfo(LPLVFOOTERINFO lpFooterInfo) const
	{
		return (BOOL)SendMessage(LVM_GETFOOTERINFO, 0, (LPARAM)lpFooterInfo);
	}

	BOOL GetFooterItemRect(int nItem, LPRECT lpRect) const
	{
		return (BOOL)SendMessage(LVM_GETFOOTERITEMRECT, nItem, (LPARAM)lpRect);
	}

	BOOL GetFooterItem(int nItem, LPLVFOOTERITEM lpFooterItem) const
	{
		return (BOOL)SendMessage(LVM_GETFOOTERITEM, nItem, (LPARAM)lpFooterItem);
	}

	BOOL GetItemIndexRect(PLVITEMINDEX pItemIndex, int nSubItem, int nType, LPRECT lpRect) const
	{
		ATLASSERT(pItemIndex != NULL);
		ATLASSERT(lpRect != NULL);
		if(lpRect != NULL)
		{
			lpRect->top = nSubItem;
			lpRect->left = nType;
		}
		return (BOOL)SendMessage(LVM_GETITEMINDEXRECT, (WPARAM)pItemIndex, (LPARAM)lpRect);
	}

	BOOL SetItemIndexState(PLVITEMINDEX pItemIndex, UINT uState, UINT dwMask)
	{
		LVITEM lvi = { 0 };
		lvi.state = uState;
		lvi.stateMask = dwMask;
		return (BOOL)SendMessage(LVM_SETITEMINDEXSTATE, (WPARAM)pItemIndex, (LPARAM)&lvi);
	}

	BOOL GetNextItemIndex(PLVITEMINDEX pItemIndex, WORD wFlags) const
	{
		return (BOOL)SendMessage(LVM_GETNEXTITEMINDEX, (WPARAM)pItemIndex, MAKELPARAM(wFlags, 0));
	}
#endif // (_WIN32_WINNT >= 0x0600)

	// Operations
	int InsertColumn(int nCol, const LVCOLUMN* pColumn)
	{
		return (int)SendMessage(LVM_INSERTCOLUMN, nCol, (LPARAM)pColumn);
	}

	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat = LVCFMT_LEFT, 
		int nWidth = -1, int nSubItem = -1, int iImage = -1, int iOrder = -1)
	{
		LVCOLUMN column = { 0 };
		column.mask = LVCF_TEXT|LVCF_FMT;
		column.pszText = (LPTSTR)lpszColumnHeading;
		column.fmt = nFormat;
		if (nWidth != -1)
		{
			column.mask |= LVCF_WIDTH;
			column.cx = nWidth;
		}
		if (nSubItem != -1)
		{
			column.mask |= LVCF_SUBITEM;
			column.iSubItem = nSubItem;
		}
		if (iImage != -1)
		{
			column.mask |= LVCF_IMAGE;
			column.iImage = iImage;
		}
		if (iOrder != -1)
		{
			column.mask |= LVCF_ORDER;
			column.iOrder = iOrder;
		}
		return InsertColumn(nCol, &column);
	}

	BOOL DeleteColumn(int nCol)
	{
		return (BOOL)SendMessage(LVM_DELETECOLUMN, nCol, 0L);
	}

	int InsertItem(UINT nMask, int nItem, LPCTSTR lpszItem, UINT nState, UINT nStateMask, int nImage, LPARAM lParam)
	{
		LVITEM item = { 0 };
		item.mask = nMask;
		item.iItem = nItem;
		item.iSubItem = 0;
		item.pszText = (LPTSTR)lpszItem;
		item.state = nState;
		item.stateMask = nStateMask;
		item.iImage = nImage;
		item.lParam = lParam;
		return InsertItem(&item);
	}

	int InsertItem(const LVITEM* pItem)
	{
		return (int)SendMessage(LVM_INSERTITEM, 0, (LPARAM)pItem);
	}

	int InsertItem(int nItem, LPCTSTR lpszItem)
	{
		return InsertItem(LVIF_TEXT, nItem, lpszItem, 0, 0, 0, 0);
	}

	int InsertItem(int nItem, LPCTSTR lpszItem, int nImage)
	{
		return InsertItem(LVIF_TEXT|LVIF_IMAGE, nItem, lpszItem, 0, 0, nImage, 0);
	}

	int GetNextItem(int nItem, int nFlags) const
	{
		return (int)SendMessage(LVM_GETNEXTITEM, nItem, MAKELPARAM(nFlags, 0));
	}

	BOOL DeleteItem(int nItem)
	{
		return (BOOL)SendMessage(LVM_DELETEITEM, nItem, 0L);
	}

	BOOL DeleteAllItems()
	{
		return (BOOL)SendMessage(LVM_DELETEALLITEMS, 0, 0L);
	}

	int FindItem(LVFINDINFO* pFindInfo, int nStart) const
	{
		return (int)SendMessage(LVM_FINDITEM, nStart, (LPARAM)pFindInfo);
	}

	int HitTest(LVHITTESTINFO* pHitTestInfo) const
	{
		return (int)SendMessage(LVM_HITTEST, 0, (LPARAM)pHitTestInfo);
	}

	int HitTest(POINT pt, UINT* pFlags) const
	{
		LVHITTESTINFO hti = { 0 };
		hti.pt = pt;
		int nRes = (int)SendMessage(LVM_HITTEST, 0, (LPARAM)&hti);
		if (pFlags != NULL)
			*pFlags = hti.flags;
		return nRes;
	}

	BOOL EnsureVisible(int nItem, BOOL bPartialOK)
	{
		return (BOOL)SendMessage(LVM_ENSUREVISIBLE, nItem, MAKELPARAM(bPartialOK, 0));
	}

	BOOL Scroll(SIZE size)
	{
		return (BOOL)SendMessage(LVM_SCROLL, size.cx, size.cy);
	}

	BOOL RedrawItems(int nFirst, int nLast)
	{
		return (BOOL)SendMessage(LVM_REDRAWITEMS, nFirst, nLast);
	}

	BOOL Arrange(UINT nCode)
	{
		return (BOOL)SendMessage(LVM_ARRANGE, nCode, 0L);
	}

	CEdit EditLabel(int nItem)
	{
		return CEdit((HWND)SendMessage(LVM_EDITLABEL, nItem, 0L));
	}

	BOOL Update(int nItem)
	{
		return (BOOL)SendMessage(LVM_UPDATE, nItem, 0L);
	}

	BOOL SortItems(PFNLVCOMPARE pfnCompare, LPARAM lParamSort)
	{
		return (BOOL)SendMessage(LVM_SORTITEMS, (WPARAM)lParamSort, (LPARAM)pfnCompare);
	}

	CImageList RemoveImageList(int nImageList)
	{
		return CImageList((HIMAGELIST)SendMessage(LVM_SETIMAGELIST, (WPARAM)nImageList, NULL));
	}

	CImageList CreateDragImage(int nItem, LPPOINT lpPoint)
	{
		return CImageList((HIMAGELIST)SendMessage(LVM_CREATEDRAGIMAGE, nItem, (LPARAM)lpPoint));
	}

	DWORD ApproximateViewRect(int cx = -1, int cy = -1, int nCount = -1)
	{
		return (DWORD)SendMessage(LVM_APPROXIMATEVIEWRECT, nCount, MAKELPARAM(cx, cy));
	}

	int SubItemHitTest(LPLVHITTESTINFO lpInfo) const
	{
		return (int)SendMessage(LVM_SUBITEMHITTEST, 0, (LPARAM)lpInfo);
	}

	int AddColumn(LPCTSTR strItem, int nItem, int nSubItem = -1,
		int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
		int nFmt = LVCFMT_LEFT)
	{
		const int cxOffset = 15;
		LVCOLUMN lvc = { 0 };
		lvc.mask = nMask;
		lvc.fmt = nFmt;
		lvc.pszText = (LPTSTR)strItem;
		lvc.cx = GetStringWidth(lvc.pszText) + cxOffset;
		if(nMask & LVCF_SUBITEM)
			lvc.iSubItem = (nSubItem != -1) ? nSubItem : nItem;
		return InsertColumn(nItem, &lvc);
	}

	int AddItem(int nItem, int nSubItem, LPCTSTR strItem, int nImageIndex = -1)
	{
		LVITEM lvItem = { 0 };
		lvItem.mask = LVIF_TEXT;
		lvItem.iItem = nItem;
		lvItem.iSubItem = nSubItem;
		lvItem.pszText = (LPTSTR)strItem;
		if(nImageIndex != -1)
		{
			lvItem.mask |= LVIF_IMAGE;
			lvItem.iImage = nImageIndex;
		}
		if(nSubItem == 0)
			return InsertItem(&lvItem);
		return SetItem(&lvItem) ? nItem : -1;
	}

#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	BOOL SortItemsEx(PFNLVCOMPARE pfnCompare, LPARAM lParamSort)
	{
		return (BOOL)SendMessage(LVM_SORTITEMSEX, (WPARAM)lParamSort, (LPARAM)pfnCompare);
	}
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0501)
	int InsertGroup(int nItem, PLVGROUP pGroup)
	{
		return (int)SendMessage(LVM_INSERTGROUP, nItem, (LPARAM)pGroup);
	}

	int AddGroup(PLVGROUP pGroup)
	{
		return InsertGroup(-1, pGroup);
	}

	int RemoveGroup(int nGroupID)
	{
		return (int)SendMessage(LVM_REMOVEGROUP, nGroupID, 0L);
	}

	void MoveGroup(int nGroupID, int nItem)
	{
		SendMessage(LVM_MOVEGROUP, nGroupID, nItem);
	}

	void MoveItemToGroup(int nItem, int nGroupID)
	{
		SendMessage(LVM_MOVEITEMTOGROUP, nItem, nGroupID);
	}

	int EnableGroupView(BOOL bEnable)
	{
		return (int)SendMessage(LVM_ENABLEGROUPVIEW, bEnable, 0L);
	}

	int SortGroups(PFNLVGROUPCOMPARE pCompareFunc, LPVOID lpVoid = NULL)
	{
		return (int)SendMessage(LVM_SORTGROUPS, (WPARAM)pCompareFunc, (LPARAM)lpVoid);
	}

	void InsertGroupSorted(PLVINSERTGROUPSORTED pInsertGroupSorted)
	{
		SendMessage(LVM_INSERTGROUPSORTED, (WPARAM)pInsertGroupSorted, 0L);
	}

	void RemoveAllGroups()
	{
		SendMessage(LVM_REMOVEALLGROUPS, 0, 0L);
	}

	BOOL HasGroup(int nGroupID)
	{
		return (BOOL)SendMessage(LVM_HASGROUP, nGroupID, 0L);
	}

	BOOL InsertMarkHitTest(LPPOINT lpPoint, LPLVINSERTMARK pInsertMark) const
	{
		return (BOOL)SendMessage(LVM_INSERTMARKHITTEST, (WPARAM)lpPoint, (LPARAM)pInsertMark);
	}

	BOOL SetInfoTip(PLVSETINFOTIP pSetInfoTip)
	{
		return (BOOL)SendMessage(LVM_SETINFOTIP, 0, (LPARAM)pSetInfoTip);
	}

	void CancelEditLabel()
	{
		SendMessage(LVM_CANCELEDITLABEL, 0, 0L);
	}

	UINT MapIndexToID(int nIndex) const
	{
		return (UINT)SendMessage(LVM_MAPINDEXTOID, nIndex, 0L);
	}

	int MapIDToIndex(UINT uID) const
	{
		return (int)SendMessage(LVM_MAPIDTOINDEX, uID, 0L);
	}
#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)
	int HitTestEx(LPLVHITTESTINFO lpHitTestInfo) const
	{
		return (int)SendMessage(LVM_HITTEST, (WPARAM)-1, (LPARAM)lpHitTestInfo);
	}

	int HitTestEx(POINT pt, UINT* pFlags) const
	{
		LVHITTESTINFO hti = { 0 };
		hti.pt = pt;
		int nRes = (int)SendMessage(LVM_HITTEST, (WPARAM)-1, (LPARAM)&hti);
		if (pFlags != NULL)
			*pFlags = hti.flags;
		return nRes;
	}

	int SubItemHitTestEx(LPLVHITTESTINFO lpHitTestInfo) const
	{
		return (int)SendMessage(LVM_SUBITEMHITTEST, (WPARAM)-1, (LPARAM)lpHitTestInfo);
	}
#endif // (_WIN32_WINNT >= 0x0600)

	// Note: selects only one item
	BOOL SelectItem(int nIndex)
	{
		// multi-selection only: de-select all items
		if((GetStyle() & LVS_SINGLESEL) == 0)
			SetItemState(-1, 0, LVIS_SELECTED);

		BOOL bRet = SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
		if(bRet)
			bRet = EnsureVisible(nIndex, FALSE);

		return bRet;
	}

	// Gets first item selected in the control and prepares for
	// finding other selected items (if the control has the multiple
	// selection style).
	POSITION GetFirstSelectedItemPosition() const
	{
		ATLASSERT(::IsWindow(m_hWnd)); 
		return (POSITION)(DWORD_PTR)(1+GetNextItem(-1, LVIS_SELECTED));
	}
	// Finds the next selected item, after a previous call
	// to GetFirstSelectedItemPosition().
	int GetNextSelectedItem(_Inout_ POSITION& pos) const
	{ 
		ASSERT(::IsWindow(m_hWnd)); 
		DWORD_PTR nOldPos = (DWORD_PTR)pos-1; 
		pos = (POSITION)(DWORD_PTR)(1+GetNextItem((UINT)nOldPos, LVIS_SELECTED)); return (UINT)nOldPos;
	}
};
typedef UIListCtrl2T<UIWnd2>   UIListCtrl2;
DEFINE_CMMCTRL2_CLASS(UITreeCtrl2,UITreeCtrl)
//DEFINE_CMMCTRL2_CLASS(UIHeaderCtrl2,UIHeaderCtrl)
///////////////////////////////////////////////////////////////////////////////
// UIHeaderCtrl2

template <class TBase = UIWnd2>
class UIHeaderCtrl2T : public TBase
{
	typedef UIHeaderCtrl2T<TBase> This;
	typedef TBase Base;
public:
	// Constructors
	UIHeaderCtrl2T(HWND hWnd = NULL) : TBase(hWnd)
	{ }

	This & operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return WC_HEADER;
	}

	int GetItemCount() const
	{
		return (int)SendMessage(HDM_GETITEMCOUNT, 0, 0L);
	}

	BOOL GetItem(int nIndex, LPHDITEM pHeaderItem) const
	{
		return (BOOL)SendMessage(HDM_GETITEM, nIndex, (LPARAM)pHeaderItem);
	}

	BOOL SetItem(int nIndex, LPHDITEM pHeaderItem)
	{
		return (BOOL)SendMessage(HDM_SETITEM, nIndex, (LPARAM)pHeaderItem);
	}

	CImageList GetImageList() const
	{
		return CImageList((HIMAGELIST)SendMessage(HDM_GETIMAGELIST, 0, 0L));
	}

	CImageList SetImageList(HIMAGELIST hImageList)
	{
		return CImageList((HIMAGELIST)SendMessage(HDM_SETIMAGELIST, 0, (LPARAM)hImageList));
	}

	BOOL GetOrderArray(int nSize, int* lpnArray) const
	{
		return (BOOL)SendMessage(HDM_GETORDERARRAY, nSize, (LPARAM)lpnArray);
	}

	BOOL SetOrderArray(int nSize, int* lpnArray)
	{
		return (BOOL)SendMessage(HDM_SETORDERARRAY, nSize, (LPARAM)lpnArray);
	}

	BOOL GetItemRect(int nIndex, LPRECT lpItemRect) const
	{
		return (BOOL)SendMessage(HDM_GETITEMRECT, nIndex, (LPARAM)lpItemRect);
	}

	int SetHotDivider(BOOL bPos, DWORD dwInputValue)
	{
		return (int)SendMessage(HDM_SETHOTDIVIDER, bPos, dwInputValue);
	}

#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
	BOOL GetUnicodeFormat() const
	{
		return (BOOL)SendMessage(HDM_GETUNICODEFORMAT, 0, 0L);
	}

	BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
	{
		return (BOOL)SendMessage(HDM_SETUNICODEFORMAT, bUnicode, 0L);
	}
#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	int GetBitmapMargin() const
	{
		return (int)SendMessage(HDM_GETBITMAPMARGIN, 0, 0L);
	}

	int SetBitmapMargin(int nWidth)
	{
		return (int)SendMessage(HDM_SETBITMAPMARGIN, nWidth, 0L);
	}

	int SetFilterChangeTimeout(DWORD dwTimeOut)
	{
		return (int)SendMessage(HDM_SETFILTERCHANGETIMEOUT, 0, dwTimeOut);
	}
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0600)
	BOOL GetItemDropDownRect(int nIndex, LPRECT lpRect) const
	{
		return (BOOL)SendMessage(HDM_GETITEMDROPDOWNRECT, nIndex, (LPARAM)lpRect);
	}

	BOOL GetOverflowRect(LPRECT lpRect) const
	{
		return (BOOL)SendMessage(HDM_GETOVERFLOWRECT, 0, (LPARAM)lpRect);
	}

	int GetFocusedItem() const
	{
		return (int)SendMessage(HDM_GETFOCUSEDITEM, 0, 0L);
	}

	BOOL SetFocusedItem(int nIndex)
	{
		return (BOOL)SendMessage(HDM_SETFOCUSEDITEM, 0, nIndex);
	}
#endif // (_WIN32_WINNT >= 0x0600)

	// Operations
	int InsertItem(int nIndex, LPHDITEM phdi)
	{
		return (int)SendMessage(HDM_INSERTITEM, nIndex, (LPARAM)phdi);
	}

	int AddItem(LPHDITEM phdi)
	{
		return InsertItem(GetItemCount(), phdi);
	}

	BOOL DeleteItem(int nIndex)
	{
		return (BOOL)SendMessage(HDM_DELETEITEM, nIndex, 0L);
	}

	BOOL Layout(HD_LAYOUT* pHeaderLayout)
	{
		return (BOOL)SendMessage(HDM_LAYOUT, 0, (LPARAM)pHeaderLayout);
	}

	int HitTest(LPHDHITTESTINFO lpHitTestInfo) const
	{
		return (int)SendMessage(HDM_HITTEST, 0, (LPARAM)lpHitTestInfo);
	}

	int OrderToIndex(int nOrder)
	{
		return (int)SendMessage(HDM_ORDERTOINDEX, nOrder, 0L);
	}

	CImageList CreateDragImage(int nIndex)
	{
		return CImageList((HIMAGELIST)SendMessage(HDM_CREATEDRAGIMAGE, nIndex, 0L));
	}

#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	int EditFilter(int nColumn, BOOL bDiscardChanges)
	{
		return (int)SendMessage(HDM_EDITFILTER, nColumn, MAKELPARAM(bDiscardChanges, 0));
	}

	int ClearFilter(int nColumn)
	{
		return (int)SendMessage(HDM_CLEARFILTER, nColumn, 0L);
	}

	int ClearAllFilters()
	{
		return (int)SendMessage(HDM_CLEARFILTER, (WPARAM)-1, 0L);
	}
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
};

typedef UIHeaderCtrl2T<UIWnd2>   UIHeaderCtrl2;
DEFINE_CMMCTRL2_CLASS(UIToolBarCtrl2,UIToolBarCtrl)
DEFINE_CMMCTRL2_CLASS(UIStatusBarCtrl2,UIStatusBarCtrl)
//DEFINE_CMMCTRL2_CLASS(UITabCtrl2,UITabCtrl)
///////////////////////////////////////////////////////////////////////////////
// UITabCtrl2

template <class TBase = UIWnd2>
class UITabCtrl2T : public TBase
{
	typedef UITabCtrl2T<TBase> This;
	typedef TBase Base;
public:
	// Constructors
	UITabCtrl2T(HWND hWnd = NULL) : TBase(hWnd)
	{ }

	Base& operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return WC_TABCONTROL;
	}

	CImageList GetImageList() const
	{
		return CImageList((HIMAGELIST)SendMessage(TCM_GETIMAGELIST, 0, 0L));
	}

	CImageList SetImageList(HIMAGELIST hImageList)
	{
		return CImageList((HIMAGELIST)SendMessage(TCM_SETIMAGELIST, 0, (LPARAM)hImageList));
	}

	int GetItemCount() const
	{
		return (int)SendMessage(TCM_GETITEMCOUNT, 0, 0L);
	}

	BOOL GetItem(int nItem, LPTCITEM pTabCtrlItem) const
	{
		return (BOOL)SendMessage(TCM_GETITEM, nItem, (LPARAM)pTabCtrlItem);
	}

	BOOL SetItem(int nItem, LPTCITEM pTabCtrlItem)
	{
		return (BOOL)SendMessage(TCM_SETITEM, nItem, (LPARAM)pTabCtrlItem);
	}

	int SetItem(int nItem, UINT mask, LPCTSTR lpszItem, DWORD dwState, DWORD dwStateMask, int iImage, LPARAM lParam)
	{
		TCITEM tci = { 0 };
		tci.mask = mask;
		tci.pszText = (LPTSTR) lpszItem;
		tci.dwState = dwState;
		tci.dwStateMask = dwStateMask;
		tci.iImage = iImage;
		tci.lParam = lParam;
		return (int)SendMessage(TCM_SETITEM, nItem, (LPARAM)&tci);
	}

	BOOL GetItemRect(int nItem, LPRECT lpRect) const
	{
		return (BOOL)SendMessage(TCM_GETITEMRECT, nItem, (LPARAM)lpRect);
	}

	int GetCurSel() const
	{
		return (int)SendMessage(TCM_GETCURSEL, 0, 0L);
	}

	int SetCurSel(int nItem)
	{
		
		return (int)SendMessage(TCM_SETCURSEL, nItem, 0L);
	}

	SIZE SetItemSize(SIZE size)
	{
		
		DWORD dwSize = (DWORD)SendMessage(TCM_SETITEMSIZE, 0, MAKELPARAM(size.cx, size.cy));
		SIZE sizeRet = { GET_X_LPARAM(dwSize), GET_Y_LPARAM(dwSize) };
		return sizeRet;
	}

	void SetItemSize(int cx, int cy)
	{
		
		SendMessage(TCM_SETITEMSIZE, 0, MAKELPARAM(cx, cy));
	}

	void SetPadding(SIZE size)
	{
		
		SendMessage(TCM_SETPADDING, 0, MAKELPARAM(size.cx, size.cy));
	}

	int GetRowCount() const
	{
		
		return (int)SendMessage(TCM_GETROWCOUNT, 0, 0L);
	}

#ifndef _WIN32_WCE
	CToolTipCtrl GetTooltips() const
	{
		
		return CToolTipCtrl((HWND)SendMessage(TCM_GETTOOLTIPS, 0, 0L));
	}

	void SetTooltips(HWND hWndToolTip)
	{
		
		SendMessage(TCM_SETTOOLTIPS, (WPARAM)hWndToolTip, 0L);
	}
#endif // !_WIN32_WCE

	int GetCurFocus() const
	{
		
		return (int)SendMessage(TCM_GETCURFOCUS, 0, 0L);
	}

	void SetCurFocus(int nItem)
	{
		
		SendMessage(TCM_SETCURFOCUS, nItem, 0L);
	}

	BOOL SetItemExtra(int cbExtra)
	{
		
		ATLASSERT(GetItemCount() == 0);   // must be empty
		return (BOOL)SendMessage(TCM_SETITEMEXTRA, cbExtra, 0L);
	}

	int SetMinTabWidth(int nWidth = -1)
	{
		
		return (int)SendMessage(TCM_SETMINTABWIDTH, 0, nWidth);
	}

#if (_WIN32_IE >= 0x0400)
	DWORD GetExtendedStyle() const
	{
		
		return (DWORD)SendMessage(TCM_GETEXTENDEDSTYLE, 0, 0L);
	}

	DWORD SetExtendedStyle(DWORD dwExMask, DWORD dwExStyle)
	{
		
		return (DWORD)SendMessage(TCM_SETEXTENDEDSTYLE, dwExMask, dwExStyle);
	}

#ifndef _WIN32_WCE
	BOOL GetUnicodeFormat() const
	{
		
		return (BOOL)SendMessage(TCM_GETUNICODEFORMAT, 0, 0L);
	}

	BOOL SetUnicodeFormat(BOOL bUnicode = TRUE)
	{
		
		return (BOOL)SendMessage(TCM_SETUNICODEFORMAT, bUnicode, 0L);
	}
#endif // !_WIN32_WCE
#endif // (_WIN32_IE >= 0x0400)

	// Operations
	int InsertItem(int nItem, LPTCITEM pTabCtrlItem)
	{
		
		return (int)SendMessage(TCM_INSERTITEM, nItem, (LPARAM)pTabCtrlItem);
	}

	int InsertItem(int nItem, UINT mask, LPCTSTR lpszItem, int iImage, LPARAM lParam)
	{
		
		TCITEM tci = { 0 };
		tci.mask = mask;
		tci.pszText = (LPTSTR) lpszItem;
		tci.iImage = iImage;
		tci.lParam = lParam;
		return (int)SendMessage(TCM_INSERTITEM, nItem, (LPARAM)&tci);
	}

	int InsertItem(int nItem, LPCTSTR lpszItem)
	{
		
		TCITEM tci = { 0 };
		tci.mask = TCIF_TEXT;
		tci.pszText = (LPTSTR) lpszItem;
		return (int)SendMessage(TCM_INSERTITEM, nItem, (LPARAM)&tci);
	}

	int AddItem(LPTCITEM pTabCtrlItem)
	{
		return InsertItem(GetItemCount(), pTabCtrlItem);
	}

	int AddItem(UINT mask, LPCTSTR lpszItem, int iImage, LPARAM lParam)
	{
		return InsertItem(GetItemCount(), mask, lpszItem, iImage, lParam);
	}

	int AddItem(LPCTSTR lpszItem)
	{
		return InsertItem(GetItemCount(), lpszItem);
	}

	BOOL DeleteItem(int nItem)
	{
		
		return (BOOL)SendMessage(TCM_DELETEITEM, nItem, 0L);
	}

	BOOL DeleteAllItems()
	{
		
		return (BOOL)SendMessage(TCM_DELETEALLITEMS, 0, 0L);
	}

	void AdjustRect(BOOL bLarger, LPRECT lpRect)
	{
		
		SendMessage(TCM_ADJUSTRECT, bLarger, (LPARAM)lpRect);
	}

	void RemoveImage(int nImage)
	{
		
		SendMessage(TCM_REMOVEIMAGE, nImage, 0L);
	}

	int HitTest(TC_HITTESTINFO* pHitTestInfo) const
	{
		
		return (int)SendMessage(TCM_HITTEST, 0, (LPARAM)pHitTestInfo);
	}

	void DeselectAll(BOOL bExcludeFocus = TRUE)
	{
		
		SendMessage(TCM_DESELECTALL, bExcludeFocus, 0L);
	}

#if (_WIN32_IE >= 0x0400)
	BOOL HighlightItem(int nIndex, BOOL bHighlight = TRUE)
	{
		
		return (BOOL)SendMessage(TCM_HIGHLIGHTITEM, nIndex, MAKELPARAM(bHighlight, 0));
	}
#endif // (_WIN32_IE >= 0x0400)
};

typedef UITabCtrl2T<UIWnd2>   UITabCtrl2;
DEFINE_CMMCTRL2_CLASS(UIToolTipCtrl2,UIToolTipCtrl)
DEFINE_CMMCTRL2_CLASS(UITrackBarCtrl2,UITrackBarCtrl)
DEFINE_CMMCTRL2_CLASS(UIUpDownCtrl2,UIUpDownCtrl)
//DEFINE_CMMCTRL2_CLASS(UIProgressBarCtrl2,UIProgressBarCtrl)
///////////////////////////////////////////////////////////////////////////////
// UIProgressBarCtrl2

template <class TBase = UIWnd2>
class UIProgressBarCtrl2T : public TBase
{
	typedef UIProgressBarCtrl2T<TBase> This;
public:
// Constructors
	UIProgressBarCtrl2T(HWND hWnd = NULL) : TBase(hWnd)
	{ }

	This& operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
			DWORD dwStyle = 0, DWORD dwExStyle = 0,
			ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

// Attributes
	static LPCTSTR GetWndClassName()
	{
		return PROGRESS_CLASS;
	}

	DWORD SetRange(int nLower, int nUpper)
	{
		return (DWORD)SendMessage(PBM_SETRANGE, 0, MAKELPARAM(nLower, nUpper));
	}

	int SetPos(int nPos)
	{
		return (int)(short)LOWORD(SendMessage(PBM_SETPOS, nPos, 0L));
	}

	int OffsetPos(int nPos)
	{
		return (int)(short)LOWORD(SendMessage(PBM_DELTAPOS, nPos, 0L));
	}

	int SetStep(int nStep)
	{
		return (int)(short)LOWORD(SendMessage(PBM_SETSTEP, nStep, 0L));
	}

	UINT GetPos() const
	{
		return (UINT)SendMessage(PBM_GETPOS, 0, 0L);
	}

	void GetRange(PPBRANGE pPBRange) const
	{
		ATLASSERT(pPBRange != NULL);
		SendMessage(PBM_GETRANGE, TRUE, (LPARAM)pPBRange);
	}

	void GetRange(int& nLower, int& nUpper) const
	{
		PBRANGE range = { 0 };
		SendMessage(PBM_GETRANGE, TRUE, (LPARAM)&range);
		nLower = range.iLow;
		nUpper = range.iHigh;
	}

	int GetRangeLimit(BOOL bLowLimit) const
	{
		return (int)SendMessage(PBM_GETRANGE, bLowLimit, (LPARAM)NULL);
	}

	DWORD SetRange32(int nMin, int nMax)
	{
		return (DWORD)SendMessage(PBM_SETRANGE32, nMin, nMax);
	}

#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
	COLORREF SetBarColor(COLORREF cr)
	{
		return (COLORREF)SendMessage(PBM_SETBARCOLOR, 0, (LPARAM)cr);
	}

	COLORREF SetBkColor(COLORREF cr)
	{
		return (COLORREF)SendMessage(PBM_SETBKCOLOR, 0, (LPARAM)cr);
	}
#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0501) && defined(PBM_SETMARQUEE)
	BOOL SetMarquee(BOOL bMarquee, UINT uUpdateTime = 0U)
	{
		return (BOOL)SendMessage(PBM_SETMARQUEE, (WPARAM)bMarquee, (LPARAM)uUpdateTime);
	}
#endif // (_WIN32_WINNT >= 0x0501) && defined(PBM_SETMARQUEE)

#if (_WIN32_WINNT >= 0x0600)
	int GetStep() const
	{
		return (int)SendMessage(PBM_GETSTEP, 0, 0L);
	}

	COLORREF GetBkColor() const
	{
		return (COLORREF)SendMessage(PBM_GETBKCOLOR, 0, 0L);
	}

	COLORREF GetBarColor() const
	{
		return (COLORREF)SendMessage(PBM_GETBARCOLOR, 0, 0L);
	}

	int GetState() const
	{
		return (int)SendMessage(PBM_GETSTATE, 0, 0L);
	}

	int SetState(int nState)
	{
		return (int)SendMessage(PBM_SETSTATE, nState, 0L);
	}
#endif // (_WIN32_WINNT >= 0x0600)

// Operations
	int StepIt()
	{
		return (int)(short)LOWORD(SendMessage(PBM_STEPIT, 0, 0L));
	}
};

typedef UIProgressBarCtrl2T<UIWnd2>   UIProgressBarCtrl2;
DEFINE_CMMCTRL2_CLASS(UIHotKeyCtrl2,UIHotKeyCtrl)
DEFINE_CMMCTRL2_CLASS(UIAnimateCtrl2,UIAnimateCtrl)
//DEFINE_CMMCTRL2_CLASS(UIRichEditCtrl2,UIRichEditCtrl)
///////////////////////////////////////////////////////////////////////////////
// UIRichEditCtrl2

template <class TBase = UIWnd2>
class UIRichEditCtrl2T : public TBase
{
	typedef UIRichEditCtrl2T<TBase> This;
public:
	// Constructors
	UIRichEditCtrl2T(HWND hWnd = NULL) : TBase(hWnd)
	{ }

	This& operator =(HWND hWnd)
	{
		m_hWnd = hWnd;
		return *this;
	}

	HWND Create(HWND hWndParent, ATL::_U_RECT rect = NULL, LPCTSTR szWindowName = NULL,
		DWORD dwStyle = 0, DWORD dwExStyle = 0,
		ATL::_U_MENUorID MenuOrID = 0U, LPVOID lpCreateParam = NULL)
	{
		return Base::Create(GetWndClassName(), hWndParent, rect.m_lpRect, szWindowName, dwStyle, dwExStyle, MenuOrID.m_hMenu, lpCreateParam);
	}

	// Attributes
	static LPCTSTR GetWndClassName()
	{
		return RICHEDIT_CLASS;
	}

	static LPCTSTR GetLibraryName()
	{
#if (_RICHEDIT_VER >= 0x0200)
		return _T("RICHED20.DLL");
#else
		return _T("RICHED32.DLL");
#endif
	}

	int GetLineCount() const
	{
		return (int)SendMessage(EM_GETLINECOUNT, 0, 0L);
	}

	BOOL GetModify() const
	{
		return (BOOL)SendMessage(EM_GETMODIFY, 0, 0L);
	}

	void SetModify(BOOL bModified = TRUE)
	{
		SendMessage(EM_SETMODIFY, bModified, 0L);
	}

	void GetRect(LPRECT lpRect) const
	{
		SendMessage(EM_GETRECT, 0, (LPARAM)lpRect);
	}

	DWORD GetOptions() const
	{
		return (DWORD)SendMessage(EM_GETOPTIONS, 0, 0L);
	}

	DWORD SetOptions(WORD wOperation, DWORD dwOptions)
	{
		return (DWORD)SendMessage(EM_SETOPTIONS, wOperation, dwOptions);
	}

	// NOTE: first word in lpszBuffer must contain the size of the buffer!
	int GetLine(int nIndex, LPTSTR lpszBuffer) const
	{
		return (int)SendMessage(EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	int GetLine(int nIndex, LPTSTR lpszBuffer, int nMaxLength) const
	{
		*(LPWORD)lpszBuffer = (WORD)nMaxLength;
		return (int)SendMessage(EM_GETLINE, nIndex, (LPARAM)lpszBuffer);
	}

	BOOL CanUndo() const
	{
		return (BOOL)SendMessage(EM_CANUNDO, 0, 0L);
	}

	BOOL CanPaste(UINT nFormat = 0) const
	{
		return (BOOL)SendMessage(EM_CANPASTE, nFormat, 0L);
	}

	void GetSel(LONG& nStartChar, LONG& nEndChar) const
	{
		CHARRANGE cr = { 0, 0 };
		SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);
		nStartChar = cr.cpMin;
		nEndChar = cr.cpMax;
	}

	void GetSel(CHARRANGE &cr) const
	{
		SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);
	}

	int SetSel(LONG nStartChar, LONG nEndChar)
	{
		CHARRANGE cr = { nStartChar, nEndChar };
		return (int)SendMessage(EM_EXSETSEL, 0, (LPARAM)&cr);
	}

	int SetSel(CHARRANGE &cr)
	{
		return (int)SendMessage(EM_EXSETSEL, 0, (LPARAM)&cr);
	}

	int SetSelAll()
	{
		return SetSel(0, -1);
	}

	int SetSelNone()
	{
		return SetSel(-1, 0);
	}

	DWORD GetDefaultCharFormat(CHARFORMAT& cf) const
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (DWORD)SendMessage(EM_GETCHARFORMAT, 0, (LPARAM)&cf);
	}

	DWORD GetSelectionCharFormat(CHARFORMAT& cf) const
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (DWORD)SendMessage(EM_GETCHARFORMAT, 1, (LPARAM)&cf);
	}

	DWORD GetEventMask() const
	{
		return (DWORD)SendMessage(EM_GETEVENTMASK, 0, 0L);
	}

	LONG GetLimitText() const
	{
		return (LONG)SendMessage(EM_GETLIMITTEXT, 0, 0L);
	}

	DWORD GetParaFormat(PARAFORMAT& pf) const
	{
		pf.cbSize = sizeof(PARAFORMAT);
		return (DWORD)SendMessage(EM_GETPARAFORMAT, 0, (LPARAM)&pf);
	}

#if (_RICHEDIT_VER >= 0x0200)
	LONG GetSelText(LPTSTR lpstrBuff) const
	{
		return (LONG)SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpstrBuff);
	}
#else // !(_RICHEDIT_VER >= 0x0200)
	// RichEdit 1.0 EM_GETSELTEXT is ANSI only
	LONG GetSelText(LPSTR lpstrBuff) const
	{
		return (LONG)SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpstrBuff);
	}
#endif // !(_RICHEDIT_VER >= 0x0200)

#ifndef _ATL_NO_COM
	BOOL GetSelTextBSTR(BSTR& bstrText) const
	{
		USES_CONVERSION;
		ATLASSERT(bstrText == NULL);

		CHARRANGE cr = { 0, 0 };
		SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);

#if (_RICHEDIT_VER >= 0x0200)
		CTempBuffer<TCHAR, _WTL_STACK_ALLOC_THRESHOLD> buff;
		LPTSTR lpstrText = buff.Allocate(cr.cpMax - cr.cpMin + 1);
		if(lpstrText == NULL)
			return FALSE;
		if(SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpstrText) == 0)
			return FALSE;

		bstrText = ::SysAllocString(T2W(lpstrText));
#else // !(_RICHEDIT_VER >= 0x0200)
		CTempBuffer<char, _WTL_STACK_ALLOC_THRESHOLD> buff;
		LPSTR lpstrText = buff.Allocate(cr.cpMax - cr.cpMin + 1);
		if(lpstrText == NULL)
			return FALSE;
		if(SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpstrText) == 0)
			return FALSE;

		bstrText = ::SysAllocString(A2W(lpstrText));
#endif // !(_RICHEDIT_VER >= 0x0200)

		return (bstrText != NULL) ? TRUE : FALSE;
	}
#endif // !_ATL_NO_COM

#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)
	LONG GetSelText(_CSTRING_NS::CString& strText) const
	{
		
		CHARRANGE cr = { 0, 0 };
		SendMessage(EM_EXGETSEL, 0, (LPARAM)&cr);

#if (_RICHEDIT_VER >= 0x0200)
		LONG lLen = 0;
		LPTSTR lpstrText = strText.GetBufferSetLength(cr.cpMax - cr.cpMin);
		if(lpstrText != NULL)
		{
			lLen = (LONG)SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpstrText);
			strText.ReleaseBuffer();
		}
#else // !(_RICHEDIT_VER >= 0x0200)
		CTempBuffer<char, _WTL_STACK_ALLOC_THRESHOLD> buff;
		LPSTR lpstrText = buff.Allocate(cr.cpMax - cr.cpMin + 1);
		if(lpstrText == NULL)
			return 0;
		LONG lLen = (LONG)SendMessage(EM_GETSELTEXT, 0, (LPARAM)lpstrText);
		if(lLen == 0)
			return 0;

		USES_CONVERSION;
		strText = A2T(lpstrText);
#endif // !(_RICHEDIT_VER >= 0x0200)

		return lLen;
	}
#endif // defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)

	WORD GetSelectionType() const
	{
		return (WORD)SendMessage(EM_SELECTIONTYPE, 0, 0L);
	}

	COLORREF SetBackgroundColor(COLORREF cr)
	{
		return (COLORREF)SendMessage(EM_SETBKGNDCOLOR, 0, cr);
	}

	COLORREF SetBackgroundColor()   // sets to system background
	{
		return (COLORREF)SendMessage(EM_SETBKGNDCOLOR, 1, 0);
	}

	BOOL SetCharFormat(CHARFORMAT& cf, WORD wFlags)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, (WPARAM)wFlags, (LPARAM)&cf);
	}

	BOOL SetDefaultCharFormat(CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}

	BOOL SetSelectionCharFormat(CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	BOOL SetWordCharFormat(CHARFORMAT& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
	}

	DWORD SetEventMask(DWORD dwEventMask)
	{
		return (DWORD)SendMessage(EM_SETEVENTMASK, 0, dwEventMask);
	}

	BOOL SetParaFormat(PARAFORMAT& pf)
	{
		pf.cbSize = sizeof(PARAFORMAT);
		return (BOOL)SendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&pf);
	}

	BOOL SetTargetDevice(HDC hDC, int cxLineWidth)
	{
		return (BOOL)SendMessage(EM_SETTARGETDEVICE, (WPARAM)hDC, cxLineWidth);
	}

	int GetTextLength() const
	{
		return (int)SendMessage(WM_GETTEXTLENGTH, 0, 0L);
	}

	BOOL SetReadOnly(BOOL bReadOnly = TRUE)
	{
		return (BOOL)SendMessage(EM_SETREADONLY, bReadOnly, 0L);
	}

	int GetFirstVisibleLine() const
	{
		return (int)SendMessage(EM_GETFIRSTVISIBLELINE, 0, 0L);
	}

	EDITWORDBREAKPROCEX GetWordBreakProcEx() const
	{
		return (EDITWORDBREAKPROCEX)SendMessage(EM_GETWORDBREAKPROCEX, 0, 0L);
	}

	EDITWORDBREAKPROCEX SetWordBreakProcEx(EDITWORDBREAKPROCEX pfnEditWordBreakProcEx)
	{
		return (EDITWORDBREAKPROCEX)SendMessage(EM_SETWORDBREAKPROCEX, 0, (LPARAM)pfnEditWordBreakProcEx);
	}

	int GetTextRange(TEXTRANGE* pTextRange) const
	{
		return (int)SendMessage(EM_GETTEXTRANGE, 0, (LPARAM)pTextRange);
	}

#if (_RICHEDIT_VER >= 0x0200)
	int GetTextRange(LONG nStartChar, LONG nEndChar, LPTSTR lpstrText) const
	{
		TEXTRANGE tr = { 0 };
		tr.chrg.cpMin = nStartChar;
		tr.chrg.cpMax = nEndChar;
		tr.lpstrText = lpstrText;
		return (int)SendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&tr);
	}
#else // !(_RICHEDIT_VER >= 0x0200)

	int GetTextRange(LONG nStartChar, LONG nEndChar, LPSTR lpstrText) const
	{
		TEXTRANGE tr = { 0 };
		tr.chrg.cpMin = nStartChar;
		tr.chrg.cpMax = nEndChar;
		tr.lpstrText = lpstrText;
		return (int)SendMessage(EM_GETTEXTRANGE, 0, (LPARAM)&tr);
	}
#endif // !(_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0200)
	DWORD GetDefaultCharFormat(CHARFORMAT2& cf) const
	{
		cf.cbSize = sizeof(CHARFORMAT2);
		return (DWORD)SendMessage(EM_GETCHARFORMAT, 0, (LPARAM)&cf);
	}

	BOOL SetCharFormat(CHARFORMAT2& cf, WORD wFlags)
	{
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, (WPARAM)wFlags, (LPARAM)&cf);
	}

	BOOL SetDefaultCharFormat(CHARFORMAT2& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, 0, (LPARAM)&cf);
	}

	DWORD GetSelectionCharFormat(CHARFORMAT2& cf) const
	{
		cf.cbSize = sizeof(CHARFORMAT2);
		return (DWORD)SendMessage(EM_GETCHARFORMAT, 1, (LPARAM)&cf);
	}

	BOOL SetSelectionCharFormat(CHARFORMAT2& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&cf);
	}

	BOOL SetWordCharFormat(CHARFORMAT2& cf)
	{
		cf.cbSize = sizeof(CHARFORMAT2);
		return (BOOL)SendMessage(EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
	}

	DWORD GetParaFormat(PARAFORMAT2& pf) const
	{
		pf.cbSize = sizeof(PARAFORMAT2);
		return (DWORD)SendMessage(EM_GETPARAFORMAT, 0, (LPARAM)&pf);
	}

	BOOL SetParaFormat(PARAFORMAT2& pf)
	{
		pf.cbSize = sizeof(PARAFORMAT2);
		return (BOOL)SendMessage(EM_SETPARAFORMAT, 0, (LPARAM)&pf);
	}

	TEXTMODE GetTextMode() const
	{
		return (TEXTMODE)SendMessage(EM_GETTEXTMODE, 0, 0L);
	}

	BOOL SetTextMode(TEXTMODE enumTextMode)
	{
		return !(BOOL)SendMessage(EM_SETTEXTMODE, enumTextMode, 0L);
	}

	UNDONAMEID GetUndoName() const
	{
		return (UNDONAMEID)SendMessage(EM_GETUNDONAME, 0, 0L);
	}

	UNDONAMEID GetRedoName() const
	{
		return (UNDONAMEID)SendMessage(EM_GETREDONAME, 0, 0L);
	}

	BOOL CanRedo() const
	{
		return (BOOL)SendMessage(EM_CANREDO, 0, 0L);
	}

	BOOL GetAutoURLDetect() const
	{
		return (BOOL)SendMessage(EM_GETAUTOURLDETECT, 0, 0L);
	}

	BOOL SetAutoURLDetect(BOOL bAutoDetect = TRUE)
	{
		return !(BOOL)SendMessage(EM_AUTOURLDETECT, bAutoDetect, 0L);
	}

	// this method is deprecated, please use SetAutoURLDetect
	BOOL EnableAutoURLDetect(BOOL bEnable = TRUE) { return SetAutoURLDetect(bEnable); }

	UINT SetUndoLimit(UINT uUndoLimit)
	{
		return (UINT)SendMessage(EM_SETUNDOLIMIT, uUndoLimit, 0L);
	}

	void SetPalette(HPALETTE hPalette)
	{
		SendMessage(EM_SETPALETTE, (WPARAM)hPalette, 0L);
	}

	int GetTextEx(GETTEXTEX* pGetTextEx, LPTSTR lpstrText) const
	{
		return (int)SendMessage(EM_GETTEXTEX, (WPARAM)pGetTextEx, (LPARAM)lpstrText);
	}

	int GetTextEx(LPTSTR lpstrText, int nTextLen, DWORD dwFlags = GT_DEFAULT, UINT uCodePage = CP_ACP, LPCSTR lpDefaultChar = NULL, LPBOOL lpUsedDefChar = NULL) const
	{
		GETTEXTEX gte = { 0 };
		gte.cb = nTextLen * sizeof(TCHAR);
		gte.codepage = uCodePage;
		gte.flags = dwFlags;
		gte.lpDefaultChar = lpDefaultChar;
		gte.lpUsedDefChar = lpUsedDefChar;
		return (int)SendMessage(EM_GETTEXTEX, (WPARAM)&gte, (LPARAM)lpstrText);
	}

	int GetTextLengthEx(GETTEXTLENGTHEX* pGetTextLengthEx) const
	{
		return (int)SendMessage(EM_GETTEXTLENGTHEX, (WPARAM)pGetTextLengthEx, 0L);
	}

	int GetTextLengthEx(DWORD dwFlags = GTL_DEFAULT, UINT uCodePage = CP_ACP) const
	{
		GETTEXTLENGTHEX gtle = { 0 };
		gtle.codepage = uCodePage;
		gtle.flags = dwFlags;
		return (int)SendMessage(EM_GETTEXTLENGTHEX, (WPARAM)&gtle, 0L);
	}
#endif // (_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0300)
	int SetTextEx(SETTEXTEX* pSetTextEx, LPCTSTR lpstrText)
	{
		return (int)SendMessage(EM_SETTEXTEX, (WPARAM)pSetTextEx, (LPARAM)lpstrText);
	}

	int SetTextEx(LPCTSTR lpstrText, DWORD dwFlags = ST_DEFAULT, UINT uCodePage = CP_ACP)
	{
		SETTEXTEX ste = { 0 };
		ste.flags = dwFlags;
		ste.codepage = uCodePage;
		return (int)SendMessage(EM_SETTEXTEX, (WPARAM)&ste, (LPARAM)lpstrText);
	}

	int GetEditStyle() const
	{
		return (int)SendMessage(EM_GETEDITSTYLE, 0, 0L);
	}

	int SetEditStyle(int nStyle, int nMask = -1)
	{
		if(nMask == -1)
			nMask = nStyle;   // set everything specified
		return (int)SendMessage(EM_SETEDITSTYLE, nStyle, nMask);
	}

	BOOL SetFontSize(int nFontSizeDelta)
	{
		ATLASSERT(nFontSizeDelta >= -1637 && nFontSizeDelta <= 1638);
		return (BOOL)SendMessage(EM_SETFONTSIZE, nFontSizeDelta, 0L);
	}

	void GetScrollPos(LPPOINT lpPoint) const
	{
		ATLASSERT(lpPoint != NULL);
		SendMessage(EM_GETSCROLLPOS, 0, (LPARAM)lpPoint);
	}

	void SetScrollPos(LPPOINT lpPoint)
	{
		ATLASSERT(lpPoint != NULL);
		SendMessage(EM_SETSCROLLPOS, 0, (LPARAM)lpPoint);
	}

	BOOL GetZoom(int& nNum, int& nDen) const
	{
		return (BOOL)SendMessage(EM_GETZOOM, (WPARAM)&nNum, (LPARAM)&nDen);
	}

	BOOL SetZoom(int nNum, int nDen)
	{
		ATLASSERT(nNum >= 0 && nNum <= 64);
		ATLASSERT(nDen >= 0 && nDen <= 64);
		return (BOOL)SendMessage(EM_SETZOOM, nNum, nDen);
	}

	BOOL SetZoomOff()
	{
		return (BOOL)SendMessage(EM_SETZOOM, 0, 0L);
	}
#endif // (_RICHEDIT_VER >= 0x0300)

	// Operations
	void LimitText(LONG nChars = 0)
	{
		SendMessage(EM_EXLIMITTEXT, 0, nChars);
	}

	int LineFromChar(LONG nIndex) const
	{
		return (int)SendMessage(EM_EXLINEFROMCHAR, 0, nIndex);
	}

	POINT PosFromChar(LONG nChar) const
	{
		POINT point = { 0, 0 };
		SendMessage(EM_POSFROMCHAR, (WPARAM)&point, nChar);
		return point;
	}

	int CharFromPos(POINT pt) const
	{
		POINTL ptl = { pt.x, pt.y };
		return (int)SendMessage(EM_CHARFROMPOS, 0, (LPARAM)&ptl);
	}

	void EmptyUndoBuffer()
	{
		SendMessage(EM_EMPTYUNDOBUFFER, 0, 0L);
	}

	int LineIndex(int nLine = -1) const
	{
		return (int)SendMessage(EM_LINEINDEX, nLine, 0L);
	}

	int LineLength(int nLine = -1) const
	{
		return (int)SendMessage(EM_LINELENGTH, nLine, 0L);
	}

	BOOL LineScroll(int nLines, int nChars = 0)
	{
		return (BOOL)SendMessage(EM_LINESCROLL, nChars, nLines);
	}

	void ReplaceSel(LPCTSTR lpszNewText, BOOL bCanUndo = FALSE)
	{
		SendMessage(EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
	}

	void SetRect(LPCRECT lpRect)
	{
		SendMessage(EM_SETRECT, 0, (LPARAM)lpRect);
	}

	BOOL DisplayBand(LPRECT pDisplayRect)
	{
		return (BOOL)SendMessage(EM_DISPLAYBAND, 0, (LPARAM)pDisplayRect);
	}

	LONG FindText(DWORD dwFlags, FINDTEXT& ft) const
	{
#if (_RICHEDIT_VER >= 0x0200) && defined(_UNICODE)
		return (LONG)SendMessage(EM_FINDTEXTW, dwFlags, (LPARAM)&ft);
#else
		return (LONG)SendMessage(EM_FINDTEXT, dwFlags, (LPARAM)&ft);
#endif
	}

	LONG FindText(DWORD dwFlags, FINDTEXTEX& ft) const
	{
#if (_RICHEDIT_VER >= 0x0200) && defined(_UNICODE)
		return (LONG)SendMessage(EM_FINDTEXTEXW, dwFlags, (LPARAM)&ft);
#else
		return (LONG)SendMessage(EM_FINDTEXTEX, dwFlags, (LPARAM)&ft);
#endif
	}

	LONG FormatRange(FORMATRANGE& fr, BOOL bDisplay = TRUE)
	{
		return (LONG)SendMessage(EM_FORMATRANGE, bDisplay, (LPARAM)&fr);
	}

	LONG FormatRange(FORMATRANGE* pFormatRange, BOOL bDisplay = TRUE)
	{
		return (LONG)SendMessage(EM_FORMATRANGE, bDisplay, (LPARAM)pFormatRange);
	}

	void HideSelection(BOOL bHide = TRUE, BOOL bChangeStyle = FALSE)
	{
		SendMessage(EM_HIDESELECTION, bHide, bChangeStyle);
	}

	void PasteSpecial(UINT uClipFormat, DWORD dwAspect = 0, HMETAFILE hMF = 0)
	{
		REPASTESPECIAL reps = { dwAspect, (DWORD_PTR)hMF };
		SendMessage(EM_PASTESPECIAL, uClipFormat, (LPARAM)&reps);
	}

	void RequestResize()
	{
		SendMessage(EM_REQUESTRESIZE, 0, 0L);
	}

	LONG StreamIn(UINT uFormat, EDITSTREAM& es)
	{
		return (LONG)SendMessage(EM_STREAMIN, uFormat, (LPARAM)&es);
	}

	LONG StreamOut(UINT uFormat, EDITSTREAM& es)
	{
		return (LONG)SendMessage(EM_STREAMOUT, uFormat, (LPARAM)&es);
	}

	DWORD FindWordBreak(int nCode, LONG nStartChar)
	{
		return (DWORD)SendMessage(EM_FINDWORDBREAK, nCode, nStartChar);
	}

	// Additional operations
	void ScrollCaret()
	{
		SendMessage(EM_SCROLLCARET, 0, 0L);
	}

	int InsertText(long nInsertAfterChar, LPCTSTR lpstrText, BOOL bCanUndo = FALSE)
	{
		int nRet = SetSel(nInsertAfterChar, nInsertAfterChar);
		ReplaceSel(lpstrText, bCanUndo);
		return nRet;
	}

	int AppendText(LPCTSTR lpstrText, BOOL bCanUndo = FALSE)
	{
		return InsertText(GetWindowTextLength(), lpstrText, bCanUndo);
	}

	// Clipboard operations
	BOOL Undo()
	{
		return (BOOL)SendMessage(EM_UNDO, 0, 0L);
	}

	void Clear()
	{
		SendMessage(WM_CLEAR, 0, 0L);
	}

	void Copy()
	{
		SendMessage(WM_COPY, 0, 0L);
	}

	void Cut()
	{
		SendMessage(WM_CUT, 0, 0L);
	}

	void Paste()
	{
		SendMessage(WM_PASTE, 0, 0L);
	}

	// OLE support
	IRichEditOle* GetOleInterface() const
	{
		IRichEditOle *pRichEditOle = NULL;
		SendMessage(EM_GETOLEINTERFACE, 0, (LPARAM)&pRichEditOle);
		return pRichEditOle;
	}

	BOOL SetOleCallback(IRichEditOleCallback* pCallback)
	{
		return (BOOL)SendMessage(EM_SETOLECALLBACK, 0, (LPARAM)pCallback);
	}

#if (_RICHEDIT_VER >= 0x0200)
	BOOL Redo()
	{
		return (BOOL)SendMessage(EM_REDO, 0, 0L);
	}

	void StopGroupTyping()
	{
		SendMessage(EM_STOPGROUPTYPING, 0, 0L);
	}

	void ShowScrollBar(int nBarType, BOOL bVisible = TRUE)
	{
		SendMessage(EM_SHOWSCROLLBAR, nBarType, bVisible);
	}
#endif // (_RICHEDIT_VER >= 0x0200)

#if (_RICHEDIT_VER >= 0x0300)
	BOOL SetTabStops(int nTabStops, LPINT rgTabStops)
	{
		return (BOOL)SendMessage(EM_SETTABSTOPS, nTabStops, (LPARAM)rgTabStops);
	}

	BOOL SetTabStops()
	{
		return (BOOL)SendMessage(EM_SETTABSTOPS, 0, 0L);
	}

	BOOL SetTabStops(const int& cxEachStop)    // takes an 'int'
	{
		return (BOOL)SendMessage(EM_SETTABSTOPS, 1, (LPARAM)(LPINT)&cxEachStop);
	}
#endif // (_RICHEDIT_VER >= 0x0300)
};
typedef UIRichEditCtrl2T<UIWnd2>   UIRichEditCtrl2;
DEFINE_CMMCTRL2_CLASS(UIDragListBox2,UIDragListBox)
DEFINE_CMMCTRL2_CLASS(UIReBarCtrl2,UIReBarCtrl)
DEFINE_CMMCTRL2_CLASS(UIComboBoxEx2,UIComboBoxEx)
DEFINE_CMMCTRL2_CLASS(UIDateTimePickerCtrl2,UIDateTimePickerCtrl)
DEFINE_CMMCTRL2_CLASS(UIMonthCalendarCtrl2,UIMonthCalendarCtrl)
DEFINE_CMMCTRL2_CLASS(UIFlatScrollBar2,UIFlatScrollBar)
DEFINE_CMMCTRL2_CLASS(UIIPAddressCtrl2,UIIPAddressCtrl)
DEFINE_CMMCTRL2_CLASS(UIPagerCtrl2,UIPagerCtrl)
DEFINE_CMMCTRL2_CLASS(UILinkCtrl2,UILinkCtrl)
//DEFINE_CMMCTRL2_CLASS(UICECommandBarCtrl2,UICECommandBarCtrl)
//DEFINE_CMMCTRL2_CLASS(UICECommandBandsCtrl2,UICECommandBandsCtrl)

//////////////////////////////////////////////////////////////////////////
//标准控件的功能 Windows已经支持

//////////////////////////////////////////////////////////////////////////
//DirectUI 控件功能实现
enum
{
	UCN_DISABLED = 1,
	UCN_PUSHED,
	UCN_UNPUSHED,
	UCN_CLICKED,
	UCN_DBCLICKED,
	//UCN_SETFOCUS,
	//UCN_KILLFOCUS,
};

enum
{
	UCST_NORMAL		= 0,
	UCST_HOVER		= 0X01,
	UCST_PRESSED	= 0X02,
};

template<class T>
class UICtrl2Map
{
	typedef UICtrl2Map<T> This;
public:
	BOOL IsNotify() { return FALSE; }

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDBClick)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		//MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		//MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
	END_MSG_MAP()

	LRESULT OnLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->NotifyCommand(pT->GetParent(), UCN_DBCLICKED);
		}
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->SetCapture();

			_pUIWnd2Manager->ModifyState(*pT, 0, UCST_PRESSED);
			pT->Invalidate();

			pT->NotifyCommand(pT->GetParent(), UCN_PUSHED);
		}
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			if(pT->GetCapture() == *pT) {
				pT->ReleaseCapture();

				_pUIWnd2Manager->ModifyState(*pT, UCST_PRESSED, 0);
				pT->Invalidate();

				pT->NotifyCommand(pT->GetParent(), UCN_DBCLICKED);

				POINT pt;
				POINTSTOPOINT(pt, lParam);
				RECT rcClient;
				pT->GetClientRect(&rcClient);
				if (::PtInRect(&rcClient, pt)) {
					pT->NotifyCommand(pT->GetParent(), UCN_CLICKED);
				}
			}
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (!(_pUIWnd2Manager->GetState(*pT) & UCST_HOVER)) {
			_pUIWnd2Manager->ModifyState(*pT, 0, UCST_HOVER);
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		_pUIWnd2Manager->ModifyState(*pT, UCST_HOVER, 0);
		pT->Invalidate();
		return bHandled;
	}

	/*LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->NotifyCommand(pT->GetParent(), UCN_SETFOCUS);
		}
		return bHandled;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (pT->IsNotify()) {
			pT->NotifyCommand(pT->GetParent(), UCN_KILLFOCUS);
		}
		return bHandled;
	}*/
};

template<class T>
class UIStatic2Map
{
	typedef UIStatic2Map<T> This;
public:
	BEGIN_MSG_MAP(This)
		
	END_MSG_MAP()
};

template<class T>
class UIHypeLink2Map
{
	typedef UIHypeLink2Map<T> This;
protected:
	CString m_strHypeLink;
public:

	void SetHypeLink(LPCTSTR lpszHypeLink)
	{
		m_strHypeLink = lpszHypeLink;
	}

	DWORD GetState()
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->GetState(*pT);
	}

	BOOL IsCommandButton() const
	{
		return TRUE;
	}

	BOOL IsNotifyButton() const
	{
		return FALSE;
	}

	BOOL Navigate()
	{
		T* pT = static_cast<T*>(this);
		BOOL bRet = TRUE;
		if(IsNotifyButton()) {
			NMHDR nmhdr = { *pT, pT->GetDlgCtrlID(), NM_CLICK };
			bRet = T::SendMessage(pT->GetParent(), WM_NOTIFY, pT->GetDlgCtrlID(), (LPARAM)&nmhdr);
		} else if(IsCommandButton()) {
			bRet = T::SendMessage(pT->GetParent(), WM_COMMAND, MAKEWPARAM(pT->GetDlgCtrlID(), BN_CLICKED), (LPARAM)(HWND)(*pT));
		} 
		if (!bRet && !m_strHypeLink.IsEmpty()) {
#ifndef _WIN32_WCE
			DWORD_PTR dwRet = (DWORD_PTR)::ShellExecute(0, _T("open"), m_strHypeLink, 0, 0, SW_SHOWNORMAL);
			bRet = (dwRet > 32);
#else // CE specific
			SHELLEXECUTEINFO shExeInfo = { sizeof(SHELLEXECUTEINFO), 0, 0, L"open", m_strHypeLink, 0, 0, SW_SHOWNORMAL, 0, 0, 0, 0, 0, 0, 0 };
			::ShellExecuteEx(&shExeInfo);
			DWORD_PTR dwRet = (DWORD_PTR)shExeInfo.hInstApp;
			bRet = (dwRet == 0) || (dwRet > 32);
#endif // _WIN32_WCE
		}
		return bRet;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	END_MSG_MAP()

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (1) {
			pT->SetCapture();
		}
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (1) {
			if(pT->GetCapture() == *pT) {
				pT->ReleaseCapture();

				POINT pt;
				POINTSTOPOINT(pt, lParam);
				RECT rcClient;
				pT->GetClientRect(&rcClient);
				if (::PtInRect(&rcClient, pt)) {
					pT->Navigate();
				}
			}
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (!(_pUIWnd2Manager->GetState(*pT) & UCST_HOVER)) {
			_pUIWnd2Manager->ModifyState(*pT, 0, UCST_HOVER);
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		_pUIWnd2Manager->ModifyState(*pT, UCST_HOVER, 0);
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//ATLTRACE(_T("HypeLink[%d] SetCursor\n"), wParam);
		SetCursor(::LoadCursor(NULL, IDC_HAND));
		return bHandled;
	}
};

template<class T>
class UIEdit2Map
{
	typedef UIEdit2Map<T> This;
public:
	class UIInnerEdit : public UIWnd2Impl<UIInnerEdit,UIEdit2>
	{
		typedef UIInnerEdit InnerThis;
		typedef UIWnd2Impl<UIInnerEdit,UIEdit2> InnerBase;
	protected:
		T* m_pT;
	public:
		UIInnerEdit()
		{
			m_pT = NULL;
		}

		BEGIN_MSG_MAP(InnerThis)
			MESSAGE_HANDLER(WM_CREATE, OnCreate)
			MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
			//MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
			MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
			CHAIN_MSG_MAP(InnerBase)
		END_MSG_MAP()

		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
		{
			bHandled = FALSE;

			LPCREATESTRUCT lpCreateStruct = (LPCREATESTRUCT)lParam;
			m_pT = (T*)lpCreateStruct->lpCreateParams;
			ATLASSERT(m_pT);
			/*CString strText;
			m_pT->GetWindowText(strText);
			SetWindowText(strText);
			SetFocus();
			SetSel(0, -1);

			SetFont(m_pT->GetHFONT(EP_EDITTEXT,0));*/

			return bHandled;
		}

		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
		{
			bHandled = FALSE;

			ATLASSERT(m_pT);
			CString strText;
			GetWindowText(strText);
			m_pT->SetWindowText(strText);
			m_pT->SetSel(GetSel());

			m_pT = NULL;

			return bHandled;
		}

		LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
		{
			bHandled = FALSE;
			return bHandled;
		}
		
		LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
		{
			DestroyWindow();
			return bHandled;
		}

		virtual void OnFinalMessage(HWND hWnd)
		{
			InnerBase::OnFinalMessage(hWnd);
		} 
	};

	UIEdit2Map()
		:m_bCanUndo(FALSE)
		,m_nLineCount(0)
		,m_bModified(FALSE)
		,m_nStartSel(-1)
		,m_nEndSel(-1)
#ifndef _WIN32_WCE
		,m_WordBreakProc(NULL)
#endif // !_WIN32_WCE
		,m_nFirstVisibleLine(0)
#ifndef _WIN32_WCE
		,m_nThumb(0)
#endif // !_WIN32_WCE
#if (WINVER >= 0x0500) && !defined(_WIN32_WCE)
		,m_nImeStatus(0)
#endif // (WINVER >= 0x0500) && !defined(_WIN32_WCE)
#if (_WIN32_WINNT >= 0x0501)
		//,m_strCueBannerText()
#endif // (_WIN32_WINNT >= 0x0501)
		,m_bScrollCaret(FALSE)
#if (_WIN32_WINNT >= 0x0501)
		,m_pEditBaloonTip(NULL)
#endif // (_WIN32_WINNT >= 0x0501)
#if (_WIN32_WINNT >= 0x0600)
		,m_nStartHilite(0)
		,m_nEndHilite(0)
#endif // (_WIN32_WINNT >= 0x0600)
#ifdef WIN32_PLATFORM_WFSP   // SmartPhone only messages
		,m_dwExtendedStyle(0)
		,m_dwInputMode(0)
		//,m_strSymbols()
#endif // WIN32_PLATFORM_WFSP
	{
		T* pT = static_cast<T*>(this);
		m_rcRect.SetRectEmpty();
		m_cPasswordChar = pT->GetContentPasswordChar();
	}

protected:
	UIInnerEdit m_InnerEdit;
	BOOL m_bCanUndo;
	int m_nLineCount;
	BOOL m_bModified;
	CRect m_rcRect;
	int m_nStartSel,m_nEndSel;
#ifndef _WIN32_WCE
	HLOCAL m_hHandle;
#endif // !_WIN32_WCE
	DWORD m_dwMargins;
	UINT m_nLimitText;
	TCHAR m_cPasswordChar;
#ifndef _WIN32_WCE
	EDITWORDBREAKPROC m_WordBreakProc;
#endif // !_WIN32_WCE
	int m_nFirstVisibleLine;
#ifndef _WIN32_WCE
	int m_nThumb;
#endif // !_WIN32_WCE
#if (WINVER >= 0x0500) && !defined(_WIN32_WCE)
	UINT m_nImeStatus;
#endif // (WINVER >= 0x0500) && !defined(_WIN32_WCE)
#if (_WIN32_WINNT >= 0x0501)
	CString m_strCueBannerText;
#endif // (_WIN32_WINNT >= 0x0501)
	BOOL m_bScrollCaret;
#if (_WIN32_WINNT >= 0x0501)
	PEDITBALLOONTIP m_pEditBaloonTip;
#endif // (_WIN32_WINNT >= 0x0501)
#if (_WIN32_WINNT >= 0x0600)
	int m_nStartHilite,m_nEndHilite;
#endif // (_WIN32_WINNT >= 0x0600)
#ifdef WIN32_PLATFORM_WFSP   // SmartPhone only messages
	DWORD m_dwExtendedStyle;
	DWORD m_dwInputMode;
	CString m_strSymbols;
#endif // WIN32_PLATFORM_WFSP

	void ShowEdit()
	{
		T* pT = static_cast<T*>(this);
		if (!m_InnerEdit) {
			RECT rcRect;
			pT->GetRect(&rcRect);
			RECT rcMargin;
			pT->GetContentMargin(EP_EDITTEXT, 0, &rcMargin);
			rcRect.left += rcMargin.left;
			rcRect.top += rcMargin.top;
			rcRect.right -= rcMargin.right;
			rcRect.bottom -= rcMargin.bottom;
			CString strText;
			pT->GetWindowText(strText);
			m_InnerEdit.Create(*pT, rcRect, strText, pT->GetStyle()|WS_VISIBLE, pT->GetExStyle(), pT->GetDlgCtrlID(), (LPVOID)pT);
			m_InnerEdit.SetFont(pT->GetHFONT(EP_EDITTEXT,0),TRUE);
			if (m_InnerEdit.GetStyle()&ES_PASSWORD) {
				m_InnerEdit.SetPasswordChar(pT->GetPasswordChar());
			}
			m_InnerEdit.SetModify(FALSE);
			m_InnerEdit.SetMargins(0,0);
		}
		if (!m_InnerEdit.IsWindowVisible()) {
			m_InnerEdit.ShowWindow(SW_SHOWNOACTIVATE);
		}
		m_InnerEdit.SetSel(0, -1);
		m_InnerEdit.SetFocus();
	}

	void HideEdit()
	{
		if (m_InnerEdit) {
			m_InnerEdit.ShowWindow(SW_HIDE);
			m_InnerEdit.DestroyWindow();
		}
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		MESSAGE_HANDLER(WM_SETFOCUS, OnSetFocus)
		//MESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		//MESSAGE_RANGE_HANDLER(EM_GETSEL, EM_GETIMESTATUS, OnEM)
		MESSAGE_HANDLER(EM_CANUNDO, OnCanUndo)
		MESSAGE_HANDLER(EM_GETLINECOUNT, OnGetLineCount)
		MESSAGE_HANDLER(EM_GETMODIFY, OnGetModify)
		MESSAGE_HANDLER(EM_SETMODIFY, OnSetModify)
		MESSAGE_HANDLER(EM_GETRECT, OnGetRect)
		MESSAGE_HANDLER(EM_GETSEL, OnGetSel)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(EM_GETHANDLE, OnGetHandle)
		MESSAGE_HANDLER(EM_SETHANDLE, OnSetHandle)
#endif // !_WIN32_WCE
		MESSAGE_HANDLER(EM_GETMARGINS, OnGetMargins)
		MESSAGE_HANDLER(EM_SETMARGINS, OnSetMargins)
		MESSAGE_HANDLER(EM_GETLIMITTEXT, OnGetLimitText)
		MESSAGE_HANDLER(EM_SETLIMITTEXT, OnSetLimitText)
		MESSAGE_HANDLER(EM_POSFROMCHAR, OnPosFromChar)
		MESSAGE_HANDLER(EM_CHARFROMPOS, OnCharFromPos)
		MESSAGE_HANDLER(EM_GETLINE, OnGetLine)
		MESSAGE_HANDLER(EM_GETPASSWORDCHAR, OnGetPasswordChar)
		MESSAGE_HANDLER(EM_SETPASSWORDCHAR, OnSetPasswordChar)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(EM_GETWORDBREAKPROC, OnGetWordBreakProc)
		MESSAGE_HANDLER(EM_SETWORDBREAKPROC, OnSetWordBreakProc)
#endif // !_WIN32_WCE
		MESSAGE_HANDLER(EM_GETFIRSTVISIBLELINE, OnGetFirstVisibleLine)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(EM_GETTHUMB, OnGetThumb)
#endif // !_WIN32_WCE
		MESSAGE_HANDLER(EM_SETREADONLY, OnSetReadOnly)
#if (WINVER >= 0x0500) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(EM_GETIMESTATUS, OnGetImeStatus)
		MESSAGE_HANDLER(EM_SETIMESTATUS, OnSetImeStatus)
#endif // (WINVER >= 0x0500) && !defined(_WIN32_WCE)
#if (_WIN32_WINNT >= 0x0501)
		MESSAGE_HANDLER(EM_GETCUEBANNER, OnGetCueBannerText)
		MESSAGE_HANDLER(EM_SETCUEBANNER, OnSetCueBannerText)
#endif // (_WIN32_WINNT >= 0x0501)
		MESSAGE_HANDLER(EM_EMPTYUNDOBUFFER, OnEmptyUndoBuffer)
		MESSAGE_HANDLER(EM_FMTLINES, OnFmtLines)
		MESSAGE_HANDLER(EM_LIMITTEXT, OnLimitText)
		MESSAGE_HANDLER(EM_LINEFROMCHAR, OnLineFromChar)
		MESSAGE_HANDLER(EM_LINEINDEX, OnLineIndex)
		MESSAGE_HANDLER(EM_LINELENGTH, OnLineLength)
		MESSAGE_HANDLER(EM_LINESCROLL, OnLineScroll)
		MESSAGE_HANDLER(EM_REPLACESEL, OnReplaceSel)
		MESSAGE_HANDLER(EM_SETRECT, OnSetRect)
		MESSAGE_HANDLER(EM_SETRECTNP, OnSetRectNP)
		MESSAGE_HANDLER(EM_SETSEL, OnSetSel)
		MESSAGE_HANDLER(EM_SETTABSTOPS, OnSetTabStops)
		MESSAGE_HANDLER(EM_SETTABSTOPS, OnSetTabStops)
		MESSAGE_HANDLER(EM_SETTABSTOPS, OnSetTabStops)
		MESSAGE_HANDLER(EM_SCROLLCARET, OnScrollCaret)
		MESSAGE_HANDLER(EM_SCROLL, OnScroll)
#if (_WIN32_WINNT >= 0x0501)
		MESSAGE_HANDLER(EM_SHOWBALLOONTIP, OnShowBalloonTip)
		MESSAGE_HANDLER(EM_HIDEBALLOONTIP, OnHideBalloonTip)
#endif // (_WIN32_WINNT >= 0x0501)
#if (_WIN32_WINNT >= 0x0600)
		MESSAGE_HANDLER(EM_GETHILITE, OnGetHilite)
		MESSAGE_HANDLER(EM_SETHILITE, OnSetHilite)
#endif // (_WIN32_WINNT >= 0x0600)
		MESSAGE_HANDLER(EM_UNDO, OnUndo)
		MESSAGE_HANDLER(WM_CLEAR, OnClear)
		MESSAGE_HANDLER(WM_COPY, OnCopy)
		MESSAGE_HANDLER(WM_CUT, OnCut)
		MESSAGE_HANDLER(WM_PASTE, OnPaste)
#ifdef WIN32_PLATFORM_WFSP   // SmartPhone only messages
		MESSAGE_HANDLER(EM_GETEXTENDEDSTYLE, OnGetExtendedStyle)
		MESSAGE_HANDLER(EM_SETEXTENDEDSTYLE, OnSetExtendedStyle)
		MESSAGE_HANDLER(EM_GETINPUTMODE, OnGetInputMode)
		MESSAGE_HANDLER(EM_SETINPUTMODE, OnSetInputMode)
		MESSAGE_HANDLER(EM_SETSYMBOLS, OnSetSymbols)
		MESSAGE_HANDLER(EM_SETSYMBOLS, OnResetSymbols)
#endif // WIN32_PLATFORM_WFSP
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		T* pT = static_cast<T*>(this);
		pT->GetClientRect(&m_rcRect);

		return bHandled;
	}

	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		HideEdit();

		return bHandled;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//POINT pt;
		//POINTSTOPOINT(pt, lParam);
		pT->ShowEdit();
		return bHandled;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//POINT pt;
		//POINTSTOPOINT(pt, lParam);
		pT->HideEdit();
		return bHandled;
	}

	/*LRESULT OnEM(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = TRUE;
		if (m_InnerEdit) {
			switch()
			{
			case EM_GETRECT:
				break;
			case EM_SETRECT:
				break;
			case EM_SETRECTNP:
				break;
			case EM_SETMARGINS:
				break;
			case EM_GETMARGINS
			default:
				m_InnerEdit.SendMessage(uMsg,wParam,lParam);
				break;
			}
		}
		return 0L;
	}*/

	LRESULT OnCanUndo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_bCanUndo;
	}

	LRESULT OnGetLineCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nLineCount;
	}

	LRESULT OnGetModify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_bModified;
	}

	LRESULT OnSetModify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bModified = (BOOL)wParam;
		m_bModified = bModified;
		return 0L;
	}

	LRESULT OnGetRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LPRECT lpRect = (LPRECT)lParam;
		*lpRect = m_rcRect;
		return 0L;
	}

	LRESULT OnGetSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (wParam && lParam) {
			*(int*)wParam = m_nStartSel;
			*(int*)lParam = m_nEndSel;
		}
		return MAKEWPARAM(m_nStartSel,m_nEndSel);
	}

#ifndef _WIN32_WCE
	LRESULT OnGetHandle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return (LRESULT)m_hHandle;
	}

	LRESULT OnSetHandle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_hHandle = (HLOCAL)wParam;
		return 0L;
	}
#endif // !_WIN32_WCE

	LRESULT OnGetMargins(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_dwMargins;
	}

	LRESULT OnSetMargins(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_dwMargins = lParam;
		return 0L;
	}

	LRESULT OnGetLimitText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nLimitText;
	}

	LRESULT OnSetLimitText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nLimitText = wParam;
		return 0L;
	}

	LRESULT OnPosFromChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int nChar = wParam;
		return 0L;
	}

	LRESULT OnCharFromPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		POINT pt = {0};
		POINTSTOPOINT(pt,lParam);
		return 0L;
	}

	// NOTE: first word in lpszBuffer must contain the size of the buffer!
	LRESULT OnGetLine(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int nIndex = wParam;
		LPBYTE lpszBuffer = (LPBYTE)lParam;
		DWORD nMaxLength = *(LPWORD)lpszBuffer;
		LPTSTR lpszString = (LPTSTR)(lpszBuffer + sizeof(DWORD));
		return 0L;
	}

	LRESULT OnGetPasswordChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_cPasswordChar;
	}

	LRESULT OnSetPasswordChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_cPasswordChar = (TCHAR)wParam;
		return 0L;
	}

#ifndef _WIN32_WCE
	LRESULT OnGetWordBreakProc(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return (LRESULT)m_WordBreakProc;
	}

	LRESULT OnSetWordBreakProc(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_WordBreakProc = (EDITWORDBREAKPROC)lParam;
		return 0L;
	}
#endif // !_WIN32_WCE

	LRESULT OnGetFirstVisibleLine(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nFirstVisibleLine;
	}

#ifndef _WIN32_WCE
	LRESULT OnGetThumb(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nThumb;
	}
#endif // !_WIN32_WCE

	LRESULT OnSetReadOnly(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (wParam) {
			return pT->ModifyStyle(0,ES_READONLY);
		} else {
			return pT->ModifyStyle(ES_READONLY,0);
		}
		return 0L;
	}

#if (WINVER >= 0x0500) && !defined(_WIN32_WCE)
	LRESULT OnGetImeStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nImeStatus;
	}

	LRESULT OnSetImeStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nImeStatus = wParam;
		//uData = lParam;
		return m_nImeStatus;
	}
#endif // (WINVER >= 0x0500) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0501)
	LRESULT OnGetCueBannerText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int cchText = wParam;
		LPWSTR lpstrText = (LPWSTR)lParam;
		wcscpy_s(lpstrText,cchText,(LPCWSTR)m_strCueBannerText);
		return TRUE;
	}

	// bKeepWithFocus - Vista only
	LRESULT OnSetCueBannerText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bKeepWithFocus = wParam;
		m_strCueBannerText = (LPCTSTR)lParam;
		if (bKeepWithFocus) {
		}
		return TRUE;
	}
#endif // (_WIN32_WINNT >= 0x0501)

	// Operations
	LRESULT OnEmptyUndoBuffer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnFmtLines(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnLimitText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nLimitText = wParam;
		return 0L;
	}

	LRESULT OnLineFromChar(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnLineIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnLineLength(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnLineScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//SendMessage(EM_LINESCROLL, nChars, nLines);
		return 0L;
	}

	LRESULT OnReplaceSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//SendMessage(EM_REPLACESEL, (WPARAM) bCanUndo, (LPARAM)lpszNewText);
		return 0L;
	}

	LRESULT OnSetRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_rcRect = *(LPRECT)lParam;
		pT->Invalidate();
		return 0L;
	}

	LRESULT OnSetRectNP(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_rcRect = *(LPRECT)lParam;
		return 0L;
	}

	LRESULT OnSetSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nStartSel = LOWORD(wParam);
		m_nEndSel = HIWORD(wParam);
		return 0L;
	}

	LRESULT OnSetTabStops(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnScrollCaret(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		//LRESULT lRet = SendMessage(EM_SCROLL, nScrollAction, 0L);
		//if(!(BOOL)HIWORD(lRet))
		//	return -1;   // failed
		//return (int)(short)LOWORD(lRet);
		return 0L;
	}

#if (_WIN32_WINNT >= 0x0501)
	LRESULT OnShowBalloonTip(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pEditBaloonTip = (PEDITBALLOONTIP)lParam;
		return TRUE;
	}

	LRESULT OnHideBalloonTip(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_pEditBaloonTip = NULL;
		return TRUE;
	}
#endif // (_WIN32_WINNT >= 0x0501)

#if (_WIN32_WINNT >= 0x0600)
	LRESULT OnGetHilite(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return MAKELONG(m_nStartHilite,m_nEndHilite);
	}

	LRESULT OnSetHilite(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nStartHilite = wParam;
		m_nEndHilite = lParam;
		return 0L;
	}
#endif // (_WIN32_WINNT >= 0x0600)

	// Clipboard operations
	LRESULT OnUndo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnClear(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnCopy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnCut(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnPaste(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

#ifdef WIN32_PLATFORM_WFSP   // SmartPhone only messages
	LRESULT OnGetExtendedStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_dwExtendedStyle;
	}

	LRESULT OnSetExtendedStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		DWORD dwMask = wParam;
		DWORD dwExStyle = lParam;
		m_dwExtendedStyle = dwExStyle;
		return m_dwExtendedStyle;
	}

	LRESULT OnGetInputMode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bCurrentMode = lParam;
		return m_dwInputMode;
	}

	LRESULT OnSetInputMode(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_dwInputMode = lParam;
		return TRUE;
	}

	LRESULT OnSetSymbols(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_strSymbols = (LPCTSTR)lParam;
		return TRUE;
	}
#endif // WIN32_PLATFORM_WFSP
};


template<class T>
class UIScrollBar2Map : public UIScrollWnd2Map<T>
{
	typedef UIScrollBar2Map<T> This;
	typedef UIScrollWnd2Map<T> Base;
protected:
	SCROLLINFO m_ScrollInfo;
	SCROLLBARINFO m_ScrollBarInfo;

public:
	UIScrollBar2Map()
	{
		memset(&m_ScrollInfo, 0, sizeof(m_ScrollInfo));
		memset(&m_ScrollBarInfo, 0, sizeof(m_ScrollBarInfo));
	}

	//BOOL IsScrollOk()
	//{
	//	SCROLLINFO& SInfo = m_ScrollInfo;
	//	SCROLLBARINFO& SBInfo = m_ScrollBarInfo;
	//	/*SCROLLINFO SInfo;
	//	pT->GetScrollInfo(&SInfo);

	//	SCROLLBARINFO SBInfo = {0};
	//	pT->GetScrollBarInfo(&SBInfo);*/
	//	if (SInfo.nMin>=SInfo.nMax || SInfo.nPage<=0) {
	//		return FALSE;
	//	}
	//	if (SBInfo.xyThumbTop>=SBInfo.xyThumbBottom || SBInfo.dxyLineButton<=0) {
	//		return FALSE;
	//	}
	//	return TRUE;
	//}

	//void CalcLayout()
	//{
	//	//
	//	//nPage是一页 即一个客户区尺寸
	//	//nLine是一行 即滚动一行，行不好计算，需要特殊需求特殊设计，默认滚动一个像素
	//	//所以滚动条nPage决定了一共多少页，即nMaxRange/nPage
	//	//nTrackPos是拖动滚动按钮的及时位置
	//	//滚动条一像素滚动范围是nMaxRange/nShowRange
	//	//
	//	T* pT = static_cast<T*>(this);

	//	DWORD dwStyle = pT->GetStyle();

	//	//nMin		Specifies the minimum scrolling position. 
	//	//nMax		Specifies the maximum scrolling position. 
	//	//nPage		Specifies the page size. A scroll bar uses this value to determine the appropriate size of the proportional scroll box. 
	//	//nPos		Specifies the position of the scroll box. 
	//	//nTrackPos Specifies the immediate position of a scroll box that the user is dragging. 
	//	//			An application can retrieve this value while processing the SB_THUMBTRACK request code.
	//	//			An application cannot set the immediate scroll position; the SetScrollInfo function ignores this member. 
	//	SCROLLINFO& SInfo = m_ScrollInfo;
	//	//int   dxyLineButton;//按钮宽度（水平），或按钮高度（垂直）
	//	//int   xyThumbTop;//滑块左边位置（水平），滑块顶部位置（垂直），这个位置是相对于滚动条的。
	//	//int   xyThumbBottom;//滑块右边位置（水平），滑块底部位置（垂直）。相对于滚动条
	//	SCROLLBARINFO& SBInfo = m_ScrollBarInfo;

	//	CRect rcScrollBar;
	//	pT->GetClientRect(&rcScrollBar);
	//	SBInfo.rcScrollBar = rcScrollBar;

	//	HDC hdc = pT->GetDC();
	//	if(dwStyle&SBS_VERT) {
	//		SBInfo.dxyLineButton = rcScrollBar.Width();
	//		pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_UPNORMAL,TMT_HEIGHT,&SBInfo.dxyLineButton);
	//		int xyLineButton2 = rcScrollBar.Width();
	//		pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_UPNORMAL,TMT_WIDTH,&xyLineButton2);
	//		SBInfo.rcScrollBar.left = SBInfo.rcScrollBar.right-xyLineButton2;
	//		rcScrollBar = SBInfo.rcScrollBar;
	//	} else {
	//		SBInfo.dxyLineButton = rcScrollBar.Height();
	//		pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_LEFTNORMAL,TMT_WIDTH,&SBInfo.dxyLineButton);
	//		int xyLineButton2 = rcScrollBar.Height();
	//		pT->GetThemeMetric(hdc,SBP_ARROWBTN,ABS_LEFTNORMAL,TMT_HEIGHT,&xyLineButton2);
	//		SBInfo.rcScrollBar.top = SBInfo.rcScrollBar.bottom-xyLineButton2;
	//		rcScrollBar = SBInfo.rcScrollBar;
	//	}
	//	pT->ReleaseDC(hdc);
	//	
	//	int nMaxRange = SInfo.nMax-SInfo.nMin; //最大逻辑范围
	//	int nPos = SInfo.nPos-SInfo.nMin; //当前逻辑位置
	//	int nPage = SInfo.nPage; //一页逻辑范围
	//	
	//	int dxyTrackBar = (dwStyle&SBS_VERT?rcScrollBar.Height():rcScrollBar.Width())-SBInfo.dxyLineButton-SBInfo.dxyLineButton;

	//	if (nMaxRange<=0 || nPage<=0 || dxyTrackBar<=0) {
	//		SBInfo.xyThumbTop = 0;
	//		SBInfo.xyThumbBottom = 0;
	//	} else {
	//		//校验数据
	//		if (nMaxRange%nPage) {
	//			SInfo.nMax = SInfo.nMin+(nMaxRange+nPage-1)/nPage*nPage;
	//			nMaxRange = SInfo.nMax-SInfo.nMin;
	//		}
	//		if(nPos>(SInfo.nMax-SInfo.nPage)) {
	//			SInfo.nPos = (SInfo.nMax-SInfo.nPage);
	//			nPos = SInfo.nPos;
	//		}
	//		//ASSERT(nMaxRange%nPage!=0);
	//		ASSERT(nPos<=(SInfo.nMax-SInfo.nPage));
	//		int nPageNum = nMaxRange/nPage; //一共多少页
	//		double dxyThumbButton = dxyTrackBar/nPageNum*1.;
	//		if (SInfo.nPos>=(SInfo.nMax-SInfo.nPage)) {
	//			SBInfo.xyThumbTop = SBInfo.dxyLineButton+dxyTrackBar-(int)dxyThumbButton;
	//			SBInfo.xyThumbBottom = SBInfo.xyThumbTop+(int)dxyThumbButton;
	//		} else {
	//			//拖动范围只有dxyTrackBar-dxyThumbButton，逻辑范围也是nMaxRange-nPage
	//			double dRangePerPixel = (nMaxRange-nPage)/(dxyTrackBar-dxyThumbButton)*1.;
	//			SBInfo.xyThumbTop = SBInfo.dxyLineButton+(int)(nPos/dRangePerPixel);
	//			SBInfo.xyThumbBottom = SBInfo.xyThumbTop+(int)dxyThumbButton;
	//		}
	//	}
	//}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSEWHEEL, OnMouseWheel)
		MESSAGE_HANDLER(WM_MOUSEHOVER, OnMouseHover)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(SBM_SETPOS, OnSetPos)
		MESSAGE_HANDLER(SBM_GETPOS, OnGetPos)
		MESSAGE_HANDLER(SBM_SETRANGE, OnSetRange)
		MESSAGE_HANDLER(SBM_SETRANGEREDRAW, OnSetRangeRedraw)
		MESSAGE_HANDLER(SBM_GETRANGE, OnGetRange)
		MESSAGE_HANDLER(SBM_ENABLE_ARROWS, OnEnableArrows)
		MESSAGE_HANDLER(SBM_SETSCROLLINFO, OnSetScrollInfo)
		MESSAGE_HANDLER(SBM_GETSCROLLINFO, OnGetScrollInfo)
		MESSAGE_HANDLER(SBM_GETSCROLLBARINFO, OnGetScrollBarInfo)
	END_MSG_MAP()

	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;

		DWORD dwStyle = pT->GetStyle();
		pT->CalcScrollBar(dwStyle&SBS_VERT?SB_VERT:SB_HORZ,&m_ScrollInfo,&m_ScrollBarInfo);

		return bHandled;
	}

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			DWORD dwStyle = pT->GetStyle();
			pT->CalcScrollBar(dwStyle&SBS_VERT?SB_VERT:SB_HORZ,&m_ScrollInfo,&m_ScrollBarInfo);
		}
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		POINT pt;
		POINTSTOPOINT(pt, lParam); 

		DWORD dwStyle = pT->GetStyle();

		SCROLLINFO& SInfo = m_ScrollInfo;
		SCROLLBARINFO& SBInfo = m_ScrollBarInfo;
		/*SCROLLINFO SInfo;
		pT->GetScrollInfo(&SInfo);

		SCROLLBARINFO SBInfo = {0};
		pT->GetScrollBarInfo(&SBInfo);*/
		if (SInfo.nMin>=SInfo.nMax || SInfo.nPage<=0) {
			return bHandled;
		}
		if (SBInfo.xyThumbTop>=SBInfo.xyThumbBottom || SBInfo.dxyLineButton<=0) {
			return bHandled;
		}

		CRect rcScrollBar = SBInfo.rcScrollBar;

		int nSBCode = 0;
		int nPos = 0;
		if (dwStyle&SBS_VERT) {
			if(pt.y<(rcScrollBar.top+SBInfo.dxyLineButton)) {
				nSBCode = SB_LINEUP;
				nPos = SInfo.nPos-1;
			} else if (pt.y>=(rcScrollBar.bottom-SBInfo.dxyLineButton)) {
				nSBCode = SB_LINEDOWN;
				nPos = SInfo.nPos+1;
			} else {
				RECT rcThumb = rcScrollBar;
				rcThumb.top = rcScrollBar.top+SBInfo.xyThumbTop;
				rcThumb.bottom = rcScrollBar.top+SBInfo.xyThumbBottom;
				if(pt.y<rcThumb.top) {
					nSBCode = SB_PAGEUP;
					nPos = SInfo.nPos-SInfo.nPage;
				} else if(pt.y>=rcThumb.bottom) {
					nSBCode = SB_PAGEDOWN;
					nPos = SInfo.nPos+SInfo.nPage;
				} else {
					nSBCode = SB_THUMBTRACK;
					nPos = SInfo.nPos;
					SInfo.nTrackPos =(pt.y-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Height()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
					pT->SetCapture();
				}
			}
			if (nPos<SInfo.nMin) {
				nPos = SInfo.nMin;
			} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
				nPos = (SInfo.nMax-SInfo.nPage);
			}
			if (SInfo.nPos!=nPos) {
				SInfo.nPos = nPos;
				pT->SendMessage(pT->GetParent(), WM_VSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
				pT->CalcScrollBar(SB_VERT,&SInfo,&SBInfo);
				pT->Invalidate();
			}
		} else {
			if(pt.x<(rcScrollBar.left+SBInfo.dxyLineButton)) {
				nSBCode = SB_LINELEFT;
				nPos = SInfo.nPos-1;
			} else if (pt.x>=(rcScrollBar.right-SBInfo.dxyLineButton)) {
				nSBCode = SB_LINERIGHT;
				nPos = SInfo.nPos+1;
			} else {
				RECT rcThumb = rcScrollBar;
				rcThumb.left = rcScrollBar.left+SBInfo.xyThumbTop;
				rcThumb.right = rcScrollBar.left+SBInfo.xyThumbBottom;
				if(pt.x<rcThumb.left) {
					nSBCode = SB_PAGELEFT;
					nPos = SInfo.nPos-SInfo.nPage;
				} else if(pt.x>=rcThumb.right) {
					nSBCode = SB_PAGERIGHT;
					nPos = SInfo.nPos+SInfo.nPage;
				} else {
					nSBCode = SB_THUMBTRACK;
					nPos = SInfo.nPos;
					SInfo.nTrackPos = (pt.x-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Width()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
					pT->SetCapture();
				}
			}
			if (nPos<SInfo.nMin) {
				nPos = SInfo.nMin;
			} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
				nPos = (SInfo.nMax-SInfo.nPage);
			}
			if (SInfo.nPos!=nPos) {
				SInfo.nPos = nPos;
				pT->SendMessage(pT->GetParent(), WM_HSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
				pT->CalcScrollBar(SB_HORZ,&SInfo,&SBInfo);
				pT->Invalidate();
			}
		}
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(pT->GetCapture() == *pT) {
			pT->ReleaseCapture();
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(pT->GetCapture() == *pT) {
			POINT pt;
			POINTSTOPOINT(pt, lParam);

			DWORD dwStyle = pT->GetStyle();

			SCROLLINFO& SInfo = m_ScrollInfo;
			SCROLLBARINFO& SBInfo = m_ScrollBarInfo;
			/*SCROLLINFO SInfo;
			pT->GetScrollInfo(&SInfo);

			SCROLLBARINFO SBInfo = {0};
			pT->GetScrollBarInfo(&SBInfo);*/
			CRect rcScrollBar = SBInfo.rcScrollBar;

			int nSBCode = 0;
			int nPos = 0;
			int nPosOff = 0;
			if (dwStyle&SBS_VERT) {	
				nSBCode = SB_THUMBTRACK;
				nPos = (pt.y-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Height()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
				nPosOff = nPos-SInfo.nTrackPos;
				SInfo.nTrackPos = nPos;
				nPos = SInfo.nPos+nPosOff;

				if (nPos<SInfo.nMin) {
					nPos = SInfo.nMin;
				} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
					nPos = (SInfo.nMax-SInfo.nPage);
				}
				if (SInfo.nPos!=nPos) {
					SInfo.nPos = nPos;
					pT->SendMessage(pT->GetParent(), WM_VSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
					pT->CalcScrollBar(SB_VERT,&SInfo,&SBInfo);
					pT->Invalidate();
				}
			} else {
				nSBCode = SB_THUMBTRACK;
				nPos = (pt.x-SBInfo.dxyLineButton)*(SInfo.nMax-SInfo.nMin)/(rcScrollBar.Width()-SBInfo.dxyLineButton-SBInfo.dxyLineButton);
				nPosOff = nPos-SInfo.nTrackPos;
				SInfo.nTrackPos = nPos;
				nPos = SInfo.nPos+nPosOff;

				if (nPos<SInfo.nMin) {
					nPos = SInfo.nMin;
				} else if (nPos>(SInfo.nMax-SInfo.nPage)) {
					nPos = (SInfo.nMax-SInfo.nPage);
				}
				if (SInfo.nPos!=nPos) {
					SInfo.nPos = nPos;
					pT->SendMessage(pT->GetParent(), WM_HSCROLL, (WPARAM)(MAKELONG(nSBCode,(WORD)nPos)),(LPARAM)(HWND)(*pT));
					pT->CalcScrollBar(SB_HORZ,&SInfo,&SBInfo);
					pT->Invalidate();
				}
			}
		}
		return bHandled;
	}

	LRESULT OnMouseWheel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);

		bHandled = FALSE;

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

	LRESULT OnSetPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nOldPos = m_ScrollInfo.nPos;
		m_ScrollInfo.nPos = wParam;
		DWORD dwStyle = pT->GetStyle();
		pT->CalcScrollBar(dwStyle&SBS_VERT?SB_VERT:SB_HORZ,&m_ScrollInfo,&m_ScrollBarInfo);
		pT->Invalidate();
		return nOldPos;
		//return pT->SetScrollPos(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ, wParam);
		return bHandled;
	}

	LRESULT OnGetPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_ScrollInfo.nPos;
		//return pT->GetScrollPos(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ);
		return bHandled;
	}

	LRESULT OnSetRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nOldPos = m_ScrollInfo.nPos;
		m_ScrollInfo.nMin = wParam;
		m_ScrollInfo.nMax = lParam;
		DWORD dwStyle = pT->GetStyle();
		pT->CalcScrollBar(dwStyle&SBS_VERT?SB_VERT:SB_HORZ,&m_ScrollInfo,&m_ScrollBarInfo);
		return nOldPos;
		//return pT->SetScrollRange(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ, (INT)wParam, (INT)lParam, FALSE);
		return bHandled;
	}

	LRESULT OnSetRangeRedraw(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT lRes = OnSetRange(SBM_SETRANGE, wParam, lParam, bHandled);
		pT->Invalidate();
		return lRes;
		//pT->SetScrollRange(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ, (INT)wParam, (INT)lParam, TRUE);
		return bHandled;
	}

	LRESULT OnGetRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		(*(LPINT)wParam) = m_ScrollInfo.nMin;
		(*(LPINT)lParam) = m_ScrollInfo.nMax;
		//return pT->GetScrollRange(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ, (LPINT)wParam, (LPINT)lParam);
		return bHandled;
	}

	LRESULT OnEnableArrows(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(wParam & ESB_DISABLE_LEFT) {
			m_ScrollBarInfo.rgstate[5] |= STATE_SYSTEM_UNAVAILABLE;
		} else {
			m_ScrollBarInfo.rgstate[5] &= ~STATE_SYSTEM_UNAVAILABLE;
		}
		if(wParam & ESB_DISABLE_RIGHT) {
			m_ScrollBarInfo.rgstate[1] |= STATE_SYSTEM_UNAVAILABLE;
		} else {
			m_ScrollBarInfo.rgstate[1] &= ~STATE_SYSTEM_UNAVAILABLE;
		}
		pT->Invalidate();
		return TRUE;
		//return pT->EnableScrollBar(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ,wParam);
		return bHandled;
	}

	LRESULT OnSetScrollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_ScrollInfo = *(LPSCROLLINFO)lParam;
		DWORD dwStyle = pT->GetStyle();
		pT->CalcScrollBar(dwStyle&SBS_VERT?SB_VERT:SB_HORZ,&m_ScrollInfo,&m_ScrollBarInfo);
		pT->Invalidate();
		return TRUE;
		//return pT->SetScrollInfo(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ, (int)wParam, (LPSCROLLINFO)lParam);
		return bHandled;
	}

	LRESULT OnGetScrollInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		*(LPSCROLLINFO)lParam = m_ScrollInfo;
		return TRUE;
		//return pT->GetScrollInfo(pT->GetStyle()&SBS_VERT?SB_VERT:SB_HORZ, (int)wParam, (LPSCROLLINFO)lParam);
		return bHandled;
	}

	LRESULT OnGetScrollBarInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		*(LPSCROLLBARINFO)lParam = m_ScrollBarInfo;
		return TRUE;
		//return pT->GetScrollBarInfo(pT->GetStyle()&SBS_VERT?OBJID_VSCROLL:OBJID_HSCROLL, (LPSCROLLBARINFO)lParam);
		return bHandled;
	}
};

template<class T>
class UIButton2Map
{
	typedef UIButton2Map<T> This;
public:
	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDBLCLK,OnLButtonDBClick)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(BM_SETSTATE, OnSetState)
		MESSAGE_HANDLER(BM_GETSTATE, OnGetState)
		MESSAGE_HANDLER(BM_SETCHECK, OnSetCheck)
		MESSAGE_HANDLER(BM_GETCHECK, OnGetCheck)
		MESSAGE_HANDLER(BM_SETSTYLE, OnSetStyle)
		MESSAGE_HANDLER(BM_CLICK, OnClick)
	END_MSG_MAP()

	LRESULT OnLButtonDBClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//POINT pt;
		//POINTSTOPOINT(pt, lParam);
		pT->SendMessage(pT->GetParent(), WM_COMMAND, MAKEWPARAM(pT->GetDlgCtrlID(),BN_DBLCLK), (LPARAM)(HWND)(*pT));
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//POINT pt;
		//POINTSTOPOINT(pt, lParam);
		pT->SetCapture();
		_pUIWnd2Manager->ModifyState(*pT, 0, BST_PUSHED);
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(pT->GetCapture() == *pT) {
			pT->ReleaseCapture();

			POINT pt;
			POINTSTOPOINT(pt, lParam);
			RECT rcClient;
			pT->GetClientRect(&rcClient);
			if (::PtInRect(&rcClient,pt)) {
				DWORD dwStyle = pT->GetStyle() & BS_TYPEMASK;
				DWORD dwState = _pUIWnd2Manager->GetState(*pT);
				if (dwStyle==BS_AUTOCHECKBOX) {
					if (dwState & BST_INDETERMINATE) {
						dwState &= ~BST_INDETERMINATE;
						dwState |= BST_UNCHECKED;
					} else if (dwState & BST_CHECKED) {
						dwState &= ~BST_CHECKED;
						dwState |= BST_UNCHECKED;
					} else {
						dwState |= BST_CHECKED;
					}
				} else if (dwStyle==BS_AUTO3STATE) {
					if (dwState & BST_INDETERMINATE) {
						dwState &= ~BST_INDETERMINATE;
						dwState |= BST_UNCHECKED;
					} else if (dwState & BST_CHECKED) {
						dwState &= ~BST_CHECKED;
						dwState |= BST_INDETERMINATE;
					} else {
						dwState |= BST_CHECKED;
					}
				} else if (dwStyle==BS_AUTORADIOBUTTON) {
					if (dwState & BST_INDETERMINATE) {
						dwState &= ~BST_INDETERMINATE;
						dwState |= BST_UNCHECKED;
					} else if (dwState & BST_CHECKED) {
						dwState &= ~BST_CHECKED;
						dwState |= BST_UNCHECKED;
					} else {
						dwState |= BST_CHECKED;
					}
				}
				dwState &= ~BST_PUSHED;
				_pUIWnd2Manager->SetState(*pT, dwState);
				pT->Invalidate();
				pT->SendMessage(pT->GetParent(), WM_COMMAND, MAKEWPARAM(pT->GetDlgCtrlID(),BN_CLICKED), (LPARAM)(HWND)(*pT));
			}
			pT->SetState(FALSE);
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (!(pT->GetState() & BST_FOCUS)) {
			_pUIWnd2Manager->ModifyState(*pT, 0, BST_FOCUS);
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		_pUIWnd2Manager->ModifyState(*pT, BST_FOCUS, 0);
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnSetState(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		_pUIWnd2Manager->ModifyState(*pT, wParam ? 0 : BST_PUSHED, wParam ? BST_PUSHED : 0);
		pT->Invalidate();
		return 0;
	}
	
	LRESULT OnGetState(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return _pUIWnd2Manager->GetState(*pT);
		return bHandled;
	}

	LRESULT OnSetCheck(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		const DWORD dwState = BST_CHECKED|BST_INDETERMINATE|BST_UNCHECKED;
		_pUIWnd2Manager->ModifyState(*pT, ~wParam & dwState, wParam);
		pT->Invalidate();
		return 0;
	}
	
	LRESULT OnGetCheck(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		const DWORD dwState = BST_CHECKED|BST_INDETERMINATE|BST_UNCHECKED;
		return _pUIWnd2Manager->GetState(*pT) & dwState;
		return bHandled;
	}

	LRESULT OnSetStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->ModifyStyle(0, wParam);
		if (LOWORD(lParam)) {
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnClick(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		CPoint pt;
		CRect rc;
		RECT rcClient;
		pT->GetClientRect(&rcClient);
		pt = rc.CenterPoint();
		LPARAM lpt = (LPARAM)POINTTOPOINTS(pt);
		pT->SendMessage(WM_LBUTTONDOWN, 0, lpt);
		pT->SendMessage(WM_LBUTTONUP, 0, lpt);
		return bHandled;
	}
};

template<class T>
class UISysButton2Map : public UIButton2Map<T>
{
	typedef UISysButton2Map<T> This;
	typedef UIButton2Map<T> Base;
public:
	UINT GetSysCommand(LPCTSTR lpszPart)
	{
		T* pT = static_cast<T*>(this);
		UINT uSysCommand = 0;
		switch(pT->GetPartID(lpszPart))
		{
		case SBP_MIN:
			uSysCommand = SC_MINIMIZE;
			break;
		case SBP_MAX:
			uSysCommand = SC_MAXIMIZE;
			break;
		case SBP_CLOSE:
			uSysCommand = SC_CLOSE;
			break;
		case SBP_RESTORE:
			uSysCommand = SC_RESTORE;
			break;
		case SBP_HELP:
			uSysCommand = SC_CONTEXTHELP;
			break;
		}
		return uSysCommand;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		POINT pt;
		POINTSTOPOINT(pt, lParam);
		RECT rcClient;
		pT->GetClientRect(&rcClient);
		if (::PtInRect(&rcClient,pt)) {
			CString strText;
			pT->GetWindowText(strText);
			UINT uSysCommand = pT->GetSysCommand(strText);
#ifndef _AFX
			pT->PostMessage(pT->GetParent(), WM_SYSCOMMAND, uSysCommand, 0L);
#else
			pT->GetParent()->PostMessage(WM_SYSCOMMAND, uSysCommand, 0L);
#endif//
			switch (uSysCommand)
			{
			case SC_MAXIMIZE:
				pT->SetWindowText(_T("RESTORE"));
				break;
			case SC_RESTORE:
				pT->SetWindowText(_T("MAX"));
				break;
			}
			pT->Invalidate();
		}
		return bHandled;
	}
};

template<class T>
class UIListBox2Map
{
	typedef UIListBox2Map<T> This;
protected:
	class LBITEM
	{
	public:
		CString strText;
		DWORD data;
	};
	typedef LBITEM *PLBITEM;
	//std::vector<PLBITEM> m_Items;
public:
	
	BEGIN_MSG_MAP(This)
		//CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

template<class T, class TEdit = UIEdit2, class TButton = UIButton2, class TListBox = UIListBox2>
class UIComboBox2Map
{
	typedef UIComboBox2Map<T> This;
protected:
	TEdit m_edInput;
	TButton m_btnDropDwon;
	TListBox m_ListBox;
public:
	
	BEGIN_MSG_MAP(This)
		//CHAIN_MSG_MAP(Base)
	END_MSG_MAP()
};

template<class T>
class UITabCtrl2Map
{
	typedef UITabCtrl2Map<T> This;
protected:
	HIMAGELIST m_hImageList;
	std::vector<TCITEM> m_aryItem;
	std::vector<CString> m_aryText;
	std::vector<CRect> m_aryRect;
	int m_nCurSel;
	int m_nCurFocus;
	SIZE m_szItem;
	SIZE m_szPadding;
	int m_nRowCount;
	UIToolTipCtrl2 m_tooltip;
	int m_nItemExtra;
	int m_nMinTabWidth;
public:
	UITabCtrl2Map()
	{
		m_hImageList = NULL;
		//m_aryItem;
		//m_aryText;
		//m_aryRect;
		m_nCurSel = -1;
		m_nCurFocus = -1;
		//memset(&m_szItem, 0, sizeof(m_szItem));
		m_szItem.cx = 18;
		m_szItem.cy = 18;
		memset(&m_szPadding, 0, sizeof(m_szPadding));
		m_szPadding.cx = 1;
		m_szPadding.cy = 1;
		m_nRowCount = 1;
		//m_tooltip;
		m_nItemExtra = 0;
		m_nMinTabWidth = 0;
	}

	void CalcLayout(int nOffset = 0)
	{
		if (nOffset<0 || nOffset >= m_aryItem.size()) {
			return;
		}

		T* pT = static_cast<T*>(this);

		int i,j;

		DWORD dwStyle = pT->GetStyle();

		CRect rcClient;
		pT->GetClientRect(&rcClient);

		//TCS_FORCEICONLEFT | TCS_FORCEICONLEFT 会改变ICON和LABLE顺序
		//对于水平布局m_szItem.cy对应Tab高度，m_szItem.cx对应Tab一个字的宽度
		//对于水平布局paddingex对应m_szPadding.cy, padding对应m_szPadding.cx
		//|			-p--------------------------| 
		//|paddingex+icon+padding+text+paddingex|...
		//|----------p						    |

		CPoint ptOffset;
		if (nOffset == 0) {
			ptOffset = rcClient.TopLeft();
		} else {
			ptOffset = m_aryRect[nOffset-1].BottomRight();
		}

		int nIconWidth = 0,nIconHeight = 0;
		if (m_hImageList) {
			ImageList_GetIconSize(m_hImageList, &nIconWidth, &nIconHeight);
		} else {
			
		}

		if (dwStyle & TCS_FIXEDWIDTH) {
			if (dwStyle & TCS_VERTICAL) {
				for (i=nOffset,j=m_aryItem.size(); i<j; i++)
				{
					m_aryRect[i].left = rcClient.left;
					m_aryRect[i].top = ptOffset.y;
					m_aryRect[i].right = m_aryRect[i].left + m_szItem.cx;
					m_aryRect[i].bottom = m_aryRect[i].top + m_szItem.cy;
					ptOffset.y = m_aryRect[i].bottom;
				}
			} else {
				for (i=nOffset,j=m_aryItem.size(); i<j; i++)
				{
					m_aryRect[i].left = ptOffset.x;
					m_aryRect[i].top = rcClient.top;
					m_aryRect[i].right = m_aryRect[i].left + m_szItem.cx;
					m_aryRect[i].bottom = m_aryRect[i].top + m_szItem.cy;
					ptOffset.x = m_aryRect[i].right;
				}
			}
		} else {
			if (dwStyle & TCS_VERTICAL) {
				for (i=nOffset,j=m_aryItem.size(); i<j; i++)
				{
					m_aryRect[i].left = rcClient.left;
					m_aryRect[i].top = ptOffset.y;
					m_aryRect[i].right = m_aryRect[i].left + m_szItem.cx;
					if (m_hImageList && m_aryItem[i].iImage>=0) {
						m_aryRect[i].bottom = m_aryRect[i].top + m_szPadding.cx + nIconHeight + m_szPadding.cy + m_szItem.cy*m_aryItem[i].cchTextMax + m_szPadding.cy*(m_aryItem[i].cchTextMax-1) + m_szPadding.cx;
					} else {
						m_aryRect[i].bottom = m_aryRect[i].top + m_szPadding.cx + m_szItem.cy*m_aryItem[i].cchTextMax + m_szPadding.cy*(m_aryItem[i].cchTextMax-1) + m_szPadding.cx;
					}
					ptOffset.y = m_aryRect[i].bottom;
				}
			} else {
				for (i=nOffset,j=m_aryItem.size(); i<j; i++)
				{
					m_aryRect[i].left = ptOffset.x;
					m_aryRect[i].top = rcClient.top;
					if (m_hImageList && m_aryItem[i].iImage>=0) {
						m_aryRect[i].right = m_aryRect[i].left + m_szPadding.cy + nIconWidth + m_szPadding.cx + m_szItem.cx*m_aryItem[i].cchTextMax + m_szPadding.cy;
					} else {
						m_aryRect[i].right = m_aryRect[i].left + m_szPadding.cy + m_szItem.cx*m_aryItem[i].cchTextMax + m_szPadding.cy;
					}
					m_aryRect[i].bottom = m_aryRect[i].top + m_szItem.cy;
					ptOffset.x = m_aryRect[i].right;
				}
			}
		}
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_SIZE, OnSize)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(TCM_GETIMAGELIST, OnGetImageList)
		MESSAGE_HANDLER(TCM_SETIMAGELIST, OnSetImageList)
		MESSAGE_HANDLER(TCM_GETITEMCOUNT, OnGetItemCount)
		MESSAGE_HANDLER(TCM_GETITEM, OnGetItem)
		MESSAGE_HANDLER(TCM_SETITEM, OnSetItem)
		MESSAGE_HANDLER(TCM_GETITEMRECT, OnGetItemRect)
		MESSAGE_HANDLER(TCM_GETCURSEL, OnGetCurSel)
		MESSAGE_HANDLER(TCM_SETCURSEL, OnSetCurSel)
		MESSAGE_HANDLER(TCM_SETITEMSIZE, OnSetItemSize)
		MESSAGE_HANDLER(TCM_SETPADDING, OnSetPadding)
		MESSAGE_HANDLER(TCM_GETROWCOUNT, OnGetRowCount)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(TCM_GETTOOLTIPS, OnGetToolTips)
		MESSAGE_HANDLER(TCM_SETTOOLTIPS, OnSetToolTips)
#endif // !_WIN32_WCE
		MESSAGE_HANDLER(TCM_GETCURFOCUS, OnGetFocus)
		MESSAGE_HANDLER(TCM_SETCURFOCUS, OnSetFocus)
		MESSAGE_HANDLER(TCM_SETITEMEXTRA, OnSetItemExtra)
		MESSAGE_HANDLER(TCM_SETMINTABWIDTH, OnSetMinTabWidth)
#if (_WIN32_IE >= 0x0400)
		MESSAGE_HANDLER(TCM_GETEXTENDEDSTYLE, OnGetExtendedStyle)
		MESSAGE_HANDLER(TCM_SETEXTENDEDSTYLE, OnSetExtendedStyle)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(TCM_GETUNICODEFORMAT, OnGetUnicodeFormat)
		MESSAGE_HANDLER(TCM_SETUNICODEFORMAT, OnSetUnicodeFormat)
#endif // !_WIN32_WCE
#endif // (_WIN32_IE >= 0x0400)
		MESSAGE_HANDLER(TCM_INSERTITEM, OnInsertItem)
		MESSAGE_HANDLER(TCM_DELETEITEM, OnDeleteItem)
		MESSAGE_HANDLER(TCM_DELETEALLITEMS, OnDeleteAllItems)
		MESSAGE_HANDLER(TCM_ADJUSTRECT, OnAdjustRect)
		MESSAGE_HANDLER(TCM_REMOVEIMAGE, OnRemoveImage)
		MESSAGE_HANDLER(TCM_HITTEST, OnHitTest)
		MESSAGE_HANDLER(TCM_DESELECTALL, OnDeselectAll)
#if (_WIN32_IE >= 0x0400)
		MESSAGE_HANDLER(TCM_HIGHLIGHTITEM, OnHighlightItem)
#endif // (_WIN32_IE >= 0x0400)
	END_MSG_MAP()

	LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		if (wParam != SIZE_MINIMIZED && lParam != 0) {
			pT->CalcLayout();
		}
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		POINT pt;
		POINTSTOPOINT(pt, lParam);
		TCHITTESTINFO htinfo = {0};
		htinfo.pt = pt;
		int nItem = pT->HitTest(&htinfo);
		if (nItem>=0 && nItem!=m_nCurSel) {
			if(!(m_aryItem[nItem].dwState&TCIS_BUTTONPRESSED)) {
				NMHDR nmhdr = {0};
				nmhdr.hwndFrom = *pT;
				nmhdr.idFrom = pT->GetDlgCtrlID();
				nmhdr.code = TCN_SELCHANGING;
				if(!T::SendMessage(pT->GetParent(), WM_NOTIFY, (WPARAM)nmhdr.code, (LPARAM)&nmhdr)) {
					if (m_nCurSel >= 0) {
						if (!(pT->GetStyle()&TCS_MULTISELECT)) {
							m_aryItem[m_nCurSel].dwState &= ~TCIS_BUTTONPRESSED;
						}
					}
					m_aryItem[nItem].dwState &= ~TCIS_BUTTONPRESSED;
					m_nCurSel = nItem;
					nmhdr.code = TCN_SELCHANGE;
					T::SendMessage(pT->GetParent(), WM_NOTIFY, (WPARAM)nmhdr.code, (LPARAM)&nmhdr);
					pT->Invalidate();
				}
			}
		}
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		POINT pt;
		POINTSTOPOINT(pt, lParam);
		TCHITTESTINFO htinfo = {0};
		htinfo.pt = pt;
		int nItem = pT->HitTest(&htinfo);
		if (nItem >= 0) {
			if (m_nCurFocus != nItem) {
				m_nCurFocus = nItem;
				NMHDR nmhdr = {0};
				nmhdr.hwndFrom = *pT;
				nmhdr.idFrom = pT->GetDlgCtrlID();
				nmhdr.code = TCN_FOCUSCHANGE;
				T::SendMessage(pT->GetParent(), WM_NOTIFY, (WPARAM)nmhdr.code, (LPARAM)&nmhdr);
				pT->Invalidate();
			}
		}
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCurFocus = pT->GetCurFocus();
		if (nCurFocus >= 0) {
			m_nCurFocus = -1;
			NMHDR nmhdr = {0};
			nmhdr.hwndFrom = *pT;
			nmhdr.idFrom = pT->GetDlgCtrlID();
			nmhdr.code = TCN_FOCUSCHANGE;
			T::SendMessage(pT->GetParent(), WM_NOTIFY, (WPARAM)nmhdr.code, (LPARAM)&nmhdr);
			pT->Invalidate();
		}
		return bHandled;
	}

	LRESULT OnGetImageList(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return (LRESULT)m_hImageList;
	}

	LRESULT OnSetImageList(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = (LRESULT)m_hImageList;
		m_hImageList = (HIMAGELIST)lParam;
		pT->Invalidate();
		return Res;
	}

	LRESULT OnGetItemCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_aryItem.size();
	}

	LRESULT OnGetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLASSERT(lParam);
		if (wParam < m_aryItem.size()) {
			TCITEM* pItem = (TCITEM*)lParam;
			if (pItem->mask & TCIF_TEXT) {
				_tcsncpy(pItem->pszText, m_aryItem[wParam].pszText, pItem->cchTextMax-1);
			}
			if (pItem->mask & TCIF_IMAGE) {
				pItem->iImage = m_aryItem[wParam].iImage;
			}
			if (pItem->mask & TCIF_PARAM) {
				pItem->lParam = m_aryItem[wParam].lParam;
			}
#if (_WIN32_IE >= 0x0300)
			if (pItem->mask & TCIF_STATE) {
				pItem->dwState = m_aryItem[wParam].dwState;
				pItem->dwStateMask = m_aryItem[wParam].dwStateMask;
			}
#endif//
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnSetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		ATLASSERT(lParam);
		if (wParam < m_aryItem.size()) {
			TCITEM* pItem = (TCITEM*)lParam;
			if (pItem->mask & TCIF_TEXT) {
				m_aryText[wParam] = pItem->pszText;
				m_aryItem[wParam].pszText = (LPTSTR)(LPCTSTR)m_aryText[wParam];
				m_aryItem[wParam].cchTextMax = m_aryText[wParam].GetLength();
			}
			if (pItem->mask & TCIF_IMAGE) {
				m_aryItem[wParam].iImage = pItem->iImage;
			}
			if (pItem->mask & TCIF_PARAM) {
				m_aryItem[wParam].lParam = pItem->lParam;
			}
#if (_WIN32_IE >= 0x0300)
			if (pItem->mask & TCIF_STATE) {
				m_aryItem[wParam].dwState = pItem->dwState;
				m_aryItem[wParam].dwStateMask = pItem->dwStateMask;
			}
#endif//
			pT->CalcLayout(wParam);
			pT->Invalidate();
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnGetItemRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		ATLASSERT(lParam);
		if (wParam < m_aryItem.size()) {
			LPRECT lpRect = (LPRECT)lParam;
			*lpRect = m_aryRect[wParam];
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnGetCurSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nCurSel;
	}

	LRESULT OnSetCurSel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCurSel = (int)wParam;
		if(nCurSel >= m_aryItem.size()) {
			nCurSel = -1;
		}
		if(m_nCurSel != nCurSel) {
			m_nCurSel = nCurSel;
			pT->Invalidate();
			return TRUE;
		}
		return TRUE;
	}

	LRESULT OnSetItemSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_szItem.cx = GET_X_LPARAM(lParam);
		m_szItem.cy = GET_Y_LPARAM(lParam);
		if (pT->GetStyle()&TCS_FIXEDWIDTH) {
			pT->CalcLayout();
		}
		pT->Invalidate();
		return TRUE;
	}

	LRESULT OnSetPadding(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_szPadding.cx = GET_X_LPARAM(lParam);
		m_szPadding.cy = GET_Y_LPARAM(lParam);
		pT->CalcLayout();
		pT->Invalidate();
		return FALSE;
	}

	LRESULT OnGetRowCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nRowCount;
	}
#ifndef _WIN32_WCE
	LRESULT OnGetToolTips(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return (LRESULT)(HWND)m_tooltip;
	}

	LRESULT OnSetToolTips(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_tooltip = (HWND)wParam;
		return TRUE;
	}
#endif // !_WIN32_WCE
	LRESULT OnGetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nCurFocus;
	}

	LRESULT OnSetFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCurFocus = (int)wParam;
		if(nCurFocus>=m_aryItem.size()) {
			nCurFocus = -1;
		}
		if (m_nCurFocus != nCurFocus) {
			m_nCurFocus = nCurFocus;
			pT->Invalidate();
			return TRUE;
		}
		return TRUE;
	}

	LRESULT OnSetItemExtra(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		m_nItemExtra = wParam;
		return TRUE;
	}

	LRESULT OnSetMinTabWidth(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = m_nMinTabWidth;
		m_nMinTabWidth = wParam;
		pT->CalcLayout();
		pT->Invalidate();
		return Res;
	}
#if (_WIN32_IE >= 0x0400)
	LRESULT OnGetExtendedStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return pT->GetWindowLong(GWL_EXSTYLE);
	}

	LRESULT OnSetExtendedStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		pT->SetWindowLong(GWL_EXSTYLE, lParam);
		pT->Invalidate();
		return TRUE;
	}
#ifndef _WIN32_WCE
	LRESULT OnGetUnicodeFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return FALSE;
	}

	LRESULT OnSetUnicodeFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return FALSE;
	}
#endif // !_WIN32_WCE
#endif // (_WIN32_IE >= 0x0400)

	LRESULT OnInsertItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCount = m_aryItem.size();
		if (wParam > nCount) {
			wParam = nCount;
		}
		TCITEM item = *(TCITEM*)lParam;
		CRect rcItem;
		m_aryRect.insert(m_aryRect.begin()+wParam, rcItem);
		m_aryText.insert(m_aryText.begin()+wParam, item.pszText);
		item.pszText = (LPTSTR)(LPCTSTR)m_aryText[wParam];
		item.cchTextMax = m_aryText[wParam].GetLength();
		m_aryItem.insert(m_aryItem.begin()+wParam, item);
		pT->CalcLayout(wParam);
		pT->Invalidate();
		return TRUE;
	}

	LRESULT OnDeleteItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (wParam < m_aryItem.size()) {
			m_aryRect.erase(m_aryRect.begin()+wParam);
			m_aryText.erase(m_aryText.begin()+wParam);
			m_aryItem.erase(m_aryItem.begin()+wParam);
			pT->CalcLayout(wParam);
			pT->Invalidate();
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnDeleteAllItems(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (!m_aryItem.empty()) {
			m_aryRect.clear();
			m_aryText.clear();
			m_aryItem.clear();
			pT->CalcLayout(0);
			pT->Invalidate();
		}
		return TRUE;
	}

	LRESULT OnAdjustRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		BOOL bLarger = wParam;
		LPRECT lpRect = (LPRECT)lParam;
		if (!lpRect) {
			return FALSE;
		}

		if (bLarger) {
			lpRect->left -= m_szPadding.cx;
			lpRect->top -= m_szPadding.cy;
			lpRect->right += m_szPadding.cx;
			lpRect->bottom += m_szPadding.cy;
		} else {
			lpRect->left += m_szPadding.cx;
			lpRect->top += m_szPadding.cy;
			lpRect->right -= m_szPadding.cx;
			lpRect->bottom -= m_szPadding.cy;
		}
		
		return TRUE;
	}

	LRESULT OnRemoveImage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if (m_hImageList) {
			return ImageList_Remove(m_hImageList, wParam);
		}
		return FALSE;
	}

	LRESULT OnHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		TCHITTESTINFO* pHitInfo = (TCHITTESTINFO*)lParam;
		if (pHitInfo) {
			int i,j;
			DWORD dwStyle = pT->GetStyle();
			pHitInfo->flags = TCHT_NOWHERE;
			for (i=0,j=m_aryItem.size(); i<j; i++)
			{ 
				if(PtInRect(&m_aryRect[i],pHitInfo->pt)) {
					pHitInfo->flags = TCHT_ONITEM;
					CRect rc = m_aryRect[i];
					if (dwStyle&TCS_VERTICAL) {
						if (dwStyle&TCS_FORCEICONLEFT) {
							rc.top += m_szPadding.cx;
							rc.bottom = rc.top + (m_szItem.cy*m_aryItem[i].cchTextMax + m_szPadding.cy*(m_aryItem[i].cchTextMax-1));
							if (PtInRect(&rc,pHitInfo->pt)) {
								pHitInfo->flags = TCHT_ONITEMLABEL;
							} else {
								if (m_hImageList && m_aryItem[i].iImage>=0) {
									rc.top = rc.bottom + m_szPadding.cy;
									rc.bottom = m_aryRect[i].bottom - m_szPadding.cx;
									if (PtInRect(&rc, pHitInfo->pt)) {
										pHitInfo->flags = TCHT_ONITEMICON;
									}
								}
							}
						} else {
							rc.bottom -= m_szPadding.cx;
							rc.top = rc.bottom - (m_szItem.cy*m_aryItem[i].cchTextMax + m_szPadding.cy*(m_aryItem[i].cchTextMax-1));
							if (PtInRect(&rc,pHitInfo->pt)) {
								pHitInfo->flags = TCHT_ONITEMLABEL;
							} else {
								if (m_hImageList && m_aryItem[i].iImage>=0) {
									rc.bottom = rc.top - m_szPadding.cy;
									rc.top = m_aryRect[i].top + m_szPadding.cx;
									if (PtInRect(&rc, pHitInfo->pt)) {
										pHitInfo->flags = TCHT_ONITEMICON;
									}
								}
							}
						}
					} else {
						if (dwStyle&TCS_FORCEICONLEFT) {
							rc.left += m_szPadding.cy;
							rc.right = rc.left + m_szItem.cx*m_aryItem[i].cchTextMax;
							if (PtInRect(&rc, pHitInfo->pt)) {
								pHitInfo->flags = TCHT_ONITEMLABEL;
							} else {
								if (m_hImageList && m_aryItem[i].iImage>=0) {
									rc.left = rc.right + m_szPadding.cx;
									rc.right = m_aryRect[i].right - m_szPadding.cy;
									if (PtInRect(&rc, pHitInfo->pt)) {
										pHitInfo->flags = TCHT_ONITEMICON;
									}
								}
							}
						} else {
							rc.right -= m_szPadding.cy;
							rc.left = rc.right - m_szItem.cx*m_aryItem[i].cchTextMax;
							if (PtInRect(&rc, pHitInfo->pt)) {
								pHitInfo->flags = TCHT_ONITEMLABEL;
							} else {
								if (m_hImageList && m_aryItem[i].iImage>=0) {
									rc.right = rc.left - m_szPadding.cx;
									rc.left = m_aryRect[i].left + m_szPadding.cy;
									if (PtInRect(&rc, pHitInfo->pt)) {
										pHitInfo->flags = TCHT_ONITEMICON;
									}
								}
							}
						}
					}
					return i;
					break;
				}
			}
		}
		return -1;
	}

	LRESULT OnDeselectAll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return FALSE;
	}

#if (_WIN32_IE >= 0x0400)
	LRESULT OnHighlightItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		BOOL bHighlight = LOWORD(lParam);
		if (bHighlight) {
			pT->SetCurFocus(wParam);
		} else {
			pT->SetCurFocus(-1);
		}
		return TRUE;
	}
#endif // (_WIN32_IE >= 0x0400)
};

template<class T>
class UIProgressBarCtrl2Map
{
	typedef UIProgressBarCtrl2Map<T> This;
protected:
	int m_nMinRange;
	int m_nMaxRange;
	int m_nCurPos;
	int m_nStepInc;

#define VERIFYPOS(pos) \
		if (pos < m_nMinRange) { \
			pos = m_nMinRange; \
		} else if(pos >= m_nMaxRange) { \
			pos = m_nMaxRange; \
		}

public:	
	UIProgressBarCtrl2Map()
	{
		m_nMinRange = 0;
		m_nMaxRange = 0;
		m_nCurPos = 0;
		m_nStepInc = 0;
	}

	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(PBM_SETRANGE, OnSetRange)
		MESSAGE_HANDLER(PBM_SETPOS, OnSetPos)
		MESSAGE_HANDLER(PBM_DELTAPOS, OnDeltaPos)
		MESSAGE_HANDLER(PBM_SETSTEP, OnSetStep)
		MESSAGE_HANDLER(PBM_STEPIT, OnStepit)
		MESSAGE_HANDLER(PBM_SETRANGE32, OnSetRange32)
		MESSAGE_HANDLER(PBM_GETRANGE, OnGetRange)
		MESSAGE_HANDLER(PBM_GETPOS, OnGetPos)
		//MESSAGE_HANDLER(PBM_SETBARCOLOR, OnSetRange)
		//MESSAGE_HANDLER(PBM_SETBKCOLOR, OnSetRange)
		//CHAIN_MSG_MAP(Base)
	END_MSG_MAP()

	LRESULT OnSetRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = MAKELPARAM(m_nMinRange, m_nMaxRange);
		m_nMinRange = LOWORD(lParam);
		m_nMaxRange = HIWORD(lParam);
		return Res;
	}

	LRESULT OnSetPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = m_nCurPos;
		m_nCurPos = (int)wParam;
		VERIFYPOS(m_nCurPos);
		return Res;
	}

	LRESULT OnDeltaPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = m_nCurPos;
		m_nCurPos += (int)wParam;
		VERIFYPOS(m_nCurPos);
		return Res;
	}

	LRESULT OnSetStep(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = m_nStepInc;
		m_nStepInc = wParam;
		return Res;
	}

	LRESULT OnStepit(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = m_nCurPos;
		m_nCurPos += m_nStepInc;
		VERIFYPOS(m_nCurPos);
		return Res;
	}

	LRESULT OnSetRange32(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = MAKELPARAM(m_nMinRange,m_nMaxRange);
		m_nMinRange = (int)wParam;
		m_nMaxRange = (int)lParam;
		return Res;
	}

	LRESULT OnGetRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LRESULT Res = wParam ? m_nMinRange : m_nMaxRange;
		if (lParam) {
			PBRANGE* pRange = (PBRANGE* )lParam;
			pRange->iLow = m_nMinRange;
			pRange->iHigh = m_nMaxRange;
		}
		return Res;
	}

	LRESULT OnGetPos(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_nCurPos;
	}

	//LRESULT OnSetRange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	//{
	//	T* pT = static_cast<T*>(this);
	//	//
	//	return bHandled;
	//}
};

template<class T>
class UIHeaderCtrl2Map
{
	typedef UIHeaderCtrl2Map<T> This;
protected:
	std::vector<HDITEM> m_aryItem;
	HIMAGELIST m_hImageList;
	UINT m_nBitmapMargin;
	int m_nFocusItem;
public:
	UIHeaderCtrl2Map()
	{
		//m_aryItem;
		m_hImageList = NULL;
		m_nBitmapMargin = NULL;
		m_nFocusItem = -1;
	}

protected:
	
	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(HDM_GETITEMCOUNT, OnGetItemCount)
		MESSAGE_HANDLER(HDM_GETITEM, OnGetItem)
		MESSAGE_HANDLER(HDM_SETITEM, OnSetItem)
		MESSAGE_HANDLER(HDM_GETIMAGELIST, OnGetImageList)
		MESSAGE_HANDLER(HDM_SETIMAGELIST, OnSetImageList)
		MESSAGE_HANDLER(HDM_GETORDERARRAY, OnGetOrderArray)
		MESSAGE_HANDLER(HDM_SETORDERARRAY, OnSetOrderArray)
		MESSAGE_HANDLER(HDM_GETITEMRECT, OnGetItemRect)
		MESSAGE_HANDLER(HDM_SETHOTDIVIDER, OnSetHotDivider)
#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(HDM_GETUNICODEFORMAT, OnGetUnicodeFormat)
		MESSAGE_HANDLER(HDM_SETUNICODEFORMAT, OnSetUnicodeFormat)
#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(HDM_GETBITMAPMARGIN, OnGetBitmapMargin)
		MESSAGE_HANDLER(HDM_SETBITMAPMARGIN, OnSetBitmapMargin)
		MESSAGE_HANDLER(HDM_SETFILTERCHANGETIMEOUT, OnSetFilterChangeTimeout)
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
#if (_WIN32_WINNT >= 0x0600)
		MESSAGE_HANDLER(HDM_GETITEMDROPDOWNRECT, OnGetItemDropDownRect)
		MESSAGE_HANDLER(HDM_GETOVERFLOWRECT, OnGetOverflowRect)
		MESSAGE_HANDLER(HDM_GETFOCUSEDITEM, OnGetFocusedItem)
		MESSAGE_HANDLER(HDM_SETFOCUSEDITEM, OnSetFocusedItem)
#endif // (_WIN32_WINNT >= 0x0600)
		MESSAGE_HANDLER(HDM_INSERTITEM, OnInsertItem)
		MESSAGE_HANDLER(HDM_DELETEITEM, OnDeleteItem)
		MESSAGE_HANDLER(HDM_LAYOUT, OnLayout)
		MESSAGE_HANDLER(HDM_HITTEST, OnHitTest)
		MESSAGE_HANDLER(HDM_ORDERTOINDEX, OnOrderToIndex)
		MESSAGE_HANDLER(HDM_CREATEDRAGIMAGE, OnCreateDragImage)
#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(HDM_EDITFILTER, OnEditFilter)
		MESSAGE_HANDLER(HDM_CLEARFILTER, OnClearFilter)
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	END_MSG_MAP()

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//POINT pt;
		//POINTSTOPOINT(pt, lParam);
		pT->SetCapture();
		
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if(pT->GetCapture() == *pT) {
			pT->ReleaseCapture();

			POINT pt;
			POINTSTOPOINT(pt, lParam);
			RECT rcClient;
			pT->GetClientRect(&rcClient);
			if (::PtInRect(&rcClient,pt)) {
				
			}
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnGetItemCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_aryItem.size();
	}

	LRESULT OnGetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int nIndex = wParam;
		HDITEM* pHeaderItem = (HDITEM*)lParam;
		ASSERT(pHeaderItem);
		if (nIndex<0 || nIndex>=m_aryItem.size()) {
			return FALSE;
		}
		*pHeaderItem = m_aryItem[nIndex];
		return TRUE;
	}

	LRESULT OnSetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		HDITEM* pHeaderItem = (HDITEM*)lParam;
		ASSERT(pHeaderItem);
		if (nIndex<0 || nIndex>=m_aryItem.size()) {
			return FALSE;
		}
		m_aryItem[nIndex] = *pHeaderItem;
		pT->Invalidate();
		return TRUE;
	}

	LRESULT OnGetImageList(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return (LRESULT)m_hImageList;
	}

	LRESULT OnSetImageList(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		HIMAGELIST hImageList = (HIMAGELIST)lParam;
		HIMAGELIST hOldImageList = m_hImageList;
		m_hImageList = hImageList;
		pT->Invalidate();
		return (LRESULT)hOldImageList;
	}

	LRESULT OnGetOrderArray(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		int nSize = wParam;
		LPINT lpnArray = (LPINT)lParam;
		if (nSize && lpnArray) {
			int i,j;
			for (i=0,j=m_aryItem.size(); i<j&&i<nSize; i++)
			{
				lpnArray[i] = m_aryItem[i].iOrder;
			}
		}
		return 0L;
	}

	LRESULT OnSetOrderArray(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nSize = wParam;
		LPINT lpnArray = (LPINT)lParam;
		if (nSize && lpnArray) {
			int i,j;
			for (i=0,j=m_aryItem.size(); i<j&&i<nSize; i++)
			{
				m_aryItem[i].iOrder = lpnArray[i];
			}
		}
		pT->Invalidate();
		return 0L;
	}

	LRESULT OnGetItemRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		LPRECT lpItemRect = (LPRECT)lParam; 
		if (nIndex>=0 && nIndex<m_aryItem.size()) {
			int i,j;
			pT->GetClientRect(lpItemRect);
			for (i=0,j=m_aryItem.size(); i<j; i++)
			{
				if (i==nIndex) {
					lpItemRect->right = lpItemRect->left + m_aryItem[i].cxy;
					break;
				} else {
					::OffsetRect(lpItemRect, m_aryItem[i].cxy, 0);
				}
			}
			return TRUE;
		}
		return 0L;
	}

	LRESULT OnSetHotDivider(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

#if (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)
	LRESULT OnGetUnicodeFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnSetUnicodeFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}
#endif // (_WIN32_IE >= 0x0400) && !defined(_WIN32_WCE)

#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	LRESULT OnGetBitmapMargin(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nBitmapMargin;
	}

	LRESULT OnSetBitmapMargin(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nWidth = wParam;
		m_nBitmapMargin = nWidth;
		pT->Invalidate();
		return m_nBitmapMargin;
	}

	LRESULT OnSetFilterChangeTimeout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)

#if (_WIN32_WINNT >= 0x0600)
	LRESULT OnGetItemDropDownRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnGetOverflowRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnGetFocusedItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return m_nFocusItem;
	}

	LRESULT OnSetFocusedItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		if (m_nFocusItem>=0 && m_nFocusItem<m_aryItem.size()) {
			m_aryItem[m_nFocusItem].state &= ~HDIS_FOCUSED;
		}
		m_nFocusItem = nIndex;
		if (m_nFocusItem>=0 && m_nFocusItem<m_aryItem.size()) {
			m_aryItem[m_nFocusItem].state |= HDIS_FOCUSED;
		}
		pT->Invalidate();
		return TRUE;
	}
#endif // (_WIN32_WINNT >= 0x0600)

	// Operations
	LRESULT OnInsertItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		HDITEM* phdi = (HDITEM*)lParam;
		if (nIndex < 0) {
			nIndex = m_aryItem.size();
		}
		m_aryItem.insert(m_aryItem.begin()+nIndex, *phdi);
		pT->Invalidate();
		return nIndex;
	}

	LRESULT OnDeleteItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		if (nIndex>=0 && nIndex<m_aryItem.size()) {
			m_aryItem.erase(m_aryItem.begin()+nIndex);
			pT->Invalidate();
			return TRUE;
		}
		return 0L;
	}

	LRESULT OnLayout(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LPHDHITTESTINFO lpHitTestInfo = (LPHDHITTESTINFO)lParam;
		if (lpHitTestInfo) {
			int i,j;
			lpHitTestInfo->flags = HHT_NOWHERE;
			RECT rc;
			pT->GetClientRect(&rc);
			if (PtInRect(&rc, lpHitTestInfo->pt)) {
				lpHitTestInfo->flags = HHT_ONHEADER;
				for (i=0,j=m_aryItem.size(); i<j; i++)
				{
					rc.right = rc.left + m_aryItem[i].cxy;
					if(PtInRect(&rc,lpHitTestInfo->pt)) {
						//lpHitTestInfo->flags |= HHT_ABOVE;
						return i;
						break;
					}
					::OffsetRect(&rc, m_aryItem[i].cxy, 0);
				}
			}
		}
		return -1;
	}

	LRESULT OnOrderToIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnCreateDragImage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	LRESULT OnEditFilter(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}

	LRESULT OnClearFilter(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		return 0L;
	}
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
};

template<class T>
class UIListCtrl2Map
{
	typedef UIListCtrl2Map<T> This;
protected:
	std::vector<LVITEM> m_aryItem;
	std::vector<std::vector<CString>> m_aryText;
	std::vector<LVCOLUMN> m_aryColumn;
	std::vector<CString> m_aryColumnText;
	UIHeaderCtrl2 m_wndHeader;
	UINT m_uCallbackMask;
	COLORREF m_crBackgnd;
	HIMAGELIST m_hImageList;
	COLORREF m_crText;
	COLORREF m_crTextBackgnd;
	UIEdit m_wndEdit;
	int m_nTopIndex;
	int m_nCountPerPage;
	SIZE m_xyIconSpacing;
	SIZE m_xyItemSpacing;
	SIZE m_xyItem;
	UIToolTipCtrl m_wndToolTip;
	HCURSOR m_hHotCursor;
	int m_nHotItem;

public:
	UIListCtrl2Map()
	{
		//m_aryItem;
		//m_aryText;
		//m_aryColumn;
		//m_aryColumnText;
		//m_wndHeader;
		m_crBackgnd = cr_INVALID;
		m_hImageList = NULL;
		m_crText = cr_INVALID;
		m_crTextBackgnd = cr_INVALID;
		//m_wndEdit;
		m_nTopIndex = -1;
		m_nCountPerPage = 0;
		memset(&m_xyIconSpacing, 0, sizeof(m_xyIconSpacing));
		memset(&m_xyItemSpacing, 0, sizeof(m_xyItemSpacing));
		memset(&m_xyItem, 0, sizeof(m_xyItem));
		//m_wndToolTip;
		m_hHotCursor = NULL;
		m_nHotItem = -1;
	}
	
	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(LVM_GETBKCOLOR, OnGetBkColor)
		MESSAGE_HANDLER(LVM_SETBKCOLOR, OnSetBkColor)
		MESSAGE_HANDLER(LVM_GETIMAGELIST, OnGetImageList)
		MESSAGE_HANDLER(LVM_SETIMAGELIST, OnSetImageList)
		MESSAGE_HANDLER(LVM_GETITEMCOUNT, OnGetItemCount)
		MESSAGE_HANDLER(LVM_SETITEMCOUNT, OnSetItemCount)
		MESSAGE_HANDLER(LVM_GETITEM, OnGetItem)
		MESSAGE_HANDLER(LVM_GETNEXTITEM, OnGetNextItem)
		MESSAGE_HANDLER(LVM_SETITEM, OnSetItem)
		MESSAGE_HANDLER(LVM_GETITEMSTATE, OnGetItemState)
		MESSAGE_HANDLER(LVM_SETITEMSTATE, OnSetItemState)
#ifndef _ATL_NO_COM
#endif // !_ATL_NO_COM
#if defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)
#endif // defined(_WTL_USE_CSTRING) || defined(__ATLSTR_H__)
		MESSAGE_HANDLER(LVM_GETITEMTEXT, OnGetItemText)
		MESSAGE_HANDLER(LVM_GETCALLBACKMASK, OnGetCallbackMask)
		MESSAGE_HANDLER(LVM_SETCALLBACKMASK, OnSetCallbackMask)
		MESSAGE_HANDLER(LVM_GETITEMPOSITION, OnGetItemPosition)
		MESSAGE_HANDLER(LVM_SETITEMPOSITION32, OnSetItemPosition)
		MESSAGE_HANDLER(LVM_GETSTRINGWIDTH, OnGetStringWidth)
		MESSAGE_HANDLER(LVM_GETEDITCONTROL, OnGetEditControl)
		MESSAGE_HANDLER(LVM_GETCOLUMN, OnGetColumn)
		MESSAGE_HANDLER(LVM_SETCOLUMN, OnSetColumn)
		MESSAGE_HANDLER(LVM_GETCOLUMNWIDTH, OnGetColumnWidth)
		MESSAGE_HANDLER(LVM_SETCOLUMNWIDTH, OnSetColumnWidth)
		MESSAGE_HANDLER(LVM_GETVIEWRECT, OnGetViewRect)
		MESSAGE_HANDLER(LVM_GETTEXTCOLOR, OnGetTextColor)
		MESSAGE_HANDLER(LVM_SETTEXTCOLOR, OnSetTextColor)
		MESSAGE_HANDLER(LVM_GETTEXTBKCOLOR, OnGetTextBkColor)
		MESSAGE_HANDLER(LVM_SETTEXTBKCOLOR, OnSetTextBkColor)
		MESSAGE_HANDLER(LVM_GETTOPINDEX, OnGetTopIndex)
		MESSAGE_HANDLER(LVM_GETCOUNTPERPAGE, OnGetCountPerPage)
		MESSAGE_HANDLER(LVM_GETORIGIN, OnGetOrigin)
		MESSAGE_HANDLER(LVM_GETSELECTEDCOUNT, OnGetSelectedCount)
		MESSAGE_HANDLER(LVM_GETITEMRECT, OnGetItemRect)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(LVM_GETHOTCURSOR, OnGetHotCursor)
		MESSAGE_HANDLER(LVM_SETHOTCURSOR, OnSetHotCursor)
		MESSAGE_HANDLER(LVM_GETHOTITEM, OnGetHotItem)
		MESSAGE_HANDLER(LVM_SETHOTITEM, OnSetHotItem)
#endif // !_WIN32_WCE
		MESSAGE_HANDLER(LVM_GETCOLUMNORDERARRAY, OnGetColumnOrderArray)
		MESSAGE_HANDLER(LVM_SETCOLUMNORDERARRAY, OnSetColumnOrderArray)
		MESSAGE_HANDLER(LVM_GETHEADER, OnGetHeader)
		MESSAGE_HANDLER(LVM_GETSUBITEMRECT, OnGetSubItemRect)
		MESSAGE_HANDLER(LVM_SETICONSPACING, OnSetIconSpacing)
		MESSAGE_HANDLER(LVM_GETISEARCHSTRING, OnGetISearchString)
		MESSAGE_HANDLER(LVM_GETITEMSPACING, OnGetItemSpacing)
#if (_WIN32_WCE >= 410)
		//ListView_SetItemSpacing(m_hWnd, cySpacing);
#endif // (_WIN32_WCE >= 410)
		MESSAGE_HANDLER(LVM_GETEXTENDEDLISTVIEWSTYLE, OnGetExtendedListViewStyle)
		MESSAGE_HANDLER(LVM_SETEXTENDEDLISTVIEWSTYLE, OnSetExtendedListViewStyle)
#if (_WIN32_IE >= 0x0400)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(LVM_GETBKIMAGE, OnGetBkImage)
		MESSAGE_HANDLER(LVM_SETBKIMAGE, OnSetBkImage)
#endif // !_WIN32_WCE
		MESSAGE_HANDLER(LVM_GETSELECTIONMARK, OnGetSelectionMark)
		MESSAGE_HANDLER(LVM_SETSELECTIONMARK, OnSetSelectionMark)
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(LVM_GETWORKAREAS, OnGetWorkAreas)
		MESSAGE_HANDLER(LVM_SETWORKAREAS, OnSetWorkAreas)
		MESSAGE_HANDLER(LVM_GETHOVERTIME, OnGetHoverTime)
		MESSAGE_HANDLER(LVM_SETHOVERTIME, OnSetHoverTime)
		MESSAGE_HANDLER(LVM_GETNUMBEROFWORKAREAS, OnGetNumberOfWorkAreas)
#endif // !_WIN32_WCE
#ifndef _WIN32_WCE
		MESSAGE_HANDLER(LVM_GETTOOLTIPS, OnGetToolTips)
		MESSAGE_HANDLER(LVM_SETTOOLTIPS, OnSetToolTips)
		MESSAGE_HANDLER(LVM_GETUNICODEFORMAT, OnGetUnicodeFormat)
		MESSAGE_HANDLER(LVM_SETUNICODEFORMAT, OnSetUnicodeFormat)
#endif // !_WIN32_WCE
#endif // (_WIN32_IE >= 0x0400)
#if (_WIN32_WINNT >= 0x0501)
		MESSAGE_HANDLER(LVM_GETSELECTEDCOLUMN, OnGetSelectedColumn)
		MESSAGE_HANDLER(LVM_SETSELECTEDCOLUMN, OnSetSelectedColumn)
		MESSAGE_HANDLER(LVM_GETVIEW, OnGetView)
		MESSAGE_HANDLER(LVM_SETVIEW, OnSetView)
		MESSAGE_HANDLER(LVM_ISGROUPVIEWENABLED, OnIsGroupViewEnabled)
		MESSAGE_HANDLER(LVM_GETGROUPINFO, OnGetGroupInfo)
		MESSAGE_HANDLER(LVM_SETGROUPINFO, OnSetGroupInfo)
		MESSAGE_HANDLER(LVM_GETGROUPMETRICS, OnGetGroupMetrics)
		MESSAGE_HANDLER(LVM_SETGROUPMETRICS, OnSetGroupMetrics)
		MESSAGE_HANDLER(LVM_GETTILEVIEWINFO, OnGetTileViewInfo)
		MESSAGE_HANDLER(LVM_SETTILEVIEWINFO, OnSetTileViewInfo)
		MESSAGE_HANDLER(LVM_GETTILEINFO, OnGetTileInfo)
		MESSAGE_HANDLER(LVM_SETTILEINFO, OnSetTileInfo)
		MESSAGE_HANDLER(LVM_GETINSERTMARK, OnGetInsertMark)
		MESSAGE_HANDLER(LVM_SETINSERTMARK, OnSetInsertMark)
		MESSAGE_HANDLER(LVM_GETINSERTMARKRECT, OnGetInsertMarkRect)
		MESSAGE_HANDLER(LVM_GETINSERTMARKCOLOR, OnGetInsertMarkColor)
		MESSAGE_HANDLER(LVM_SETINSERTMARKCOLOR, OnSetInsertMarkColor)
		MESSAGE_HANDLER(LVM_GETOUTLINECOLOR, OnGetOutlineColor)
		MESSAGE_HANDLER(LVM_SETOUTLINECOLOR, OnSetOutlineColor)
#endif // (_WIN32_WINNT >= 0x0501)
#if (_WIN32_WINNT >= 0x0600)
		MESSAGE_HANDLER(LVM_GETGROUPCOUNT, OnGetGroupCount)
		MESSAGE_HANDLER(LVM_GETGROUPINFOBYINDEX, OnGetGroupInfoByIndex)
		MESSAGE_HANDLER(LVM_GETGROUPRECT, OnGetGroupRect)
		MESSAGE_HANDLER(LVM_GETGROUPSTATE, OnGetGroupState)
		MESSAGE_HANDLER(LVM_GETFOCUSEDGROUP, OnGetFocusedGroup)
		MESSAGE_HANDLER(LVM_GETEMPTYTEXT, OnGetEmptyText)
		MESSAGE_HANDLER(LVM_GETFOOTERRECT, OnGetFooterRect)
		MESSAGE_HANDLER(LVM_GETFOOTERINFO, OnGetFooterInfo)
		MESSAGE_HANDLER(LVM_GETFOOTERITEMRECT, OnGetFooterItemRect)
		MESSAGE_HANDLER(LVM_GETFOOTERITEM, OnGetFooterItem)
		MESSAGE_HANDLER(LVM_GETITEMINDEXRECT, OnGetItemIndexRect)
		MESSAGE_HANDLER(LVM_SETITEMINDEXSTATE, OnSetItemIndexState)
		MESSAGE_HANDLER(LVM_GETNEXTITEMINDEX, OnGetNextItemIndex)
#endif // (_WIN32_WINNT >= 0x0600)
		MESSAGE_HANDLER(LVM_INSERTCOLUMN, OnInsertColumn)
		MESSAGE_HANDLER(LVM_DELETECOLUMN, OnDeleteColumn)
		MESSAGE_HANDLER(LVM_INSERTITEM, OnInsertItem)
		MESSAGE_HANDLER(LVM_DELETEITEM, OnDeleteItem)
		MESSAGE_HANDLER(LVM_DELETEALLITEMS, OnDeleteAllItems)
		MESSAGE_HANDLER(LVM_FINDITEM, OnFindItem)
		MESSAGE_HANDLER(LVM_HITTEST, OnHitTest)
		MESSAGE_HANDLER(LVM_ENSUREVISIBLE, OnEnsureVisible)
		MESSAGE_HANDLER(LVM_SCROLL, OnScroll)
		MESSAGE_HANDLER(LVM_REDRAWITEMS, OnRedrawItems)
		MESSAGE_HANDLER(LVM_ARRANGE, OnArrange)
		MESSAGE_HANDLER(LVM_EDITLABEL, OnEditLabel)
		MESSAGE_HANDLER(LVM_UPDATE, OnUpdate)
		MESSAGE_HANDLER(LVM_SORTITEMS, OnSortItems)
		MESSAGE_HANDLER(LVM_CREATEDRAGIMAGE, OnCreateDragImage)
		MESSAGE_HANDLER(LVM_APPROXIMATEVIEWRECT, OnApproximateViewRect)
		MESSAGE_HANDLER(LVM_SUBITEMHITTEST, OnSubItemHitTest)
#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
		MESSAGE_HANDLER(LVM_SORTITEMSEX, OnSortItemsEx)
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
#if (_WIN32_WINNT >= 0x0501)
		MESSAGE_HANDLER(LVM_INSERTGROUP, OnInsertGroup)
		MESSAGE_HANDLER(LVM_REMOVEGROUP, OnRemoveGroup)
		MESSAGE_HANDLER(LVM_MOVEGROUP, OnMoveGroup)
		MESSAGE_HANDLER(LVM_MOVEITEMTOGROUP, OnMoveItemToGroup)
		MESSAGE_HANDLER(LVM_ENABLEGROUPVIEW, OnEnableGroupView)
		MESSAGE_HANDLER(LVM_SORTGROUPS, OnSortGroups)
		MESSAGE_HANDLER(LVM_INSERTGROUPSORTED, OnInsertGroupSorted)
		MESSAGE_HANDLER(LVM_REMOVEALLGROUPS, OnRemoveAllGroups)
		MESSAGE_HANDLER(LVM_HASGROUP, OnHasGroup)
		MESSAGE_HANDLER(LVM_INSERTMARKHITTEST, OnInsertMarkHitTest)
		MESSAGE_HANDLER(LVM_SETINFOTIP, OnSetInfoTip)
		MESSAGE_HANDLER(LVM_CANCELEDITLABEL, OnCancelEditLabel)
		MESSAGE_HANDLER(LVM_MAPINDEXTOID, OnMapIndexToID)
		MESSAGE_HANDLER(LVM_MAPIDTOINDEX, OnMapIDToIndex)
#endif // (_WIN32_WINNT >= 0x0501)
#if (_WIN32_WINNT >= 0x0600)
#endif // (_WIN32_WINNT >= 0x0600)
	END_MSG_MAP()

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		//POINT pt;
		//POINTSTOPOINT(pt, lParam);
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		/*if(pT->GetCapture() == *pT) {
			pT->ReleaseCapture();

			POINT pt;
			POINTSTOPOINT(pt, lParam);
			RECT rcClient;
			pT->GetClientRect(&rcClient);
			if (::PtInRect(&rcClient,pt)) {
				pT->Click();
			}
			pT->SetState(FALSE);
		}*/
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetBkColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_crBackgnd;
	}

	LRESULT OnSetBkColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_crBackgnd = (COLORREF)lParam;
		return TRUE;
	}

	LRESULT OnGetImageList(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return (LRESULT)m_hImageList;
	}

	LRESULT OnSetImageList(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		HIMAGELIST hOldImageList = m_hImageList;
		m_hImageList = (HIMAGELIST)lParam;
		return (LRESULT)hOldImageList;
	}

	LRESULT OnGetItemCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_aryItem.size();
	}

	LRESULT OnSetItemCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		LVITEM item = {0};
		m_aryItem.resize(wParam, item);
		return FALSE;
	}


	LRESULT OnGetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = 0;
		LVITEM* pItem = (LVITEM*)lParam; 
		ASSERT(pItem);
		nIndex = pItem->iItem;
		if (nIndex>=0 && nIndex<m_aryItem.size()) {
			if(pT->GetStyle()&LVS_OWNERDATA) {
				if (!(m_aryItem[nIndex].mask & LVIF_DI_SETITEM) || pItem->iSubItem != 0) {
					NMLVDISPINFO nmhdr = {0};
					nmhdr.hdr.hwndFrom = *pT;
					nmhdr.hdr.code = LVN_GETDISPINFO;
					nmhdr.hdr.idFrom = pT->GetDlgCtrlID();
					nmhdr.item = *pItem;
					pT->SendMessage(pT->GetParent(), WM_NOTIFY, (WPARAM)LVN_GETDISPINFO, (LPARAM)&nmhdr);
					*pItem = nmhdr.item;
					if (pItem->mask & LVIF_DI_SETITEM) {
						pT->SetItem(pItem);
					}
					return TRUE;
				}
			}
			//pItem->mask = m_aryItem[nIndex].mask;
			//pItem->iItem = m_aryItem[nIndex].iItem;
			//pItem->iSubItem = m_aryItem[nIndex].iSubItem;
			if (pItem->mask & LVIF_STATE) {
				pItem->state = m_aryItem[nIndex].state;
				pItem->stateMask = m_aryItem[nIndex].stateMask;
			}
			if (pItem->mask & LVIF_TEXT) {
				_tcsncpy(pItem->pszText, (LPCTSTR)m_aryText[nIndex][pItem->iSubItem], pItem->cchTextMax);
			}
			if (pItem->mask & LVIF_IMAGE) {
				pItem->iImage = m_aryItem[nIndex].iImage;
			}
			if (pItem->mask & LVIF_PARAM) {
				pItem->lParam = m_aryItem[nIndex].lParam;
			}
#if (_WIN32_IE >= 0x0300)
			if (pItem->mask & LVIF_INDENT) {
				pItem->iIndent = m_aryItem[nIndex].iIndent;
			}
#endif
/*#if (_WIN32_WINNT >= 0x0501)
			if (pItem->mask & LVIF_GROUPID) {
				pItem->iGroupId = m_aryItem[nIndex].iGroupId;
			}
			if (pItem->mask & LVIF_COLUMNS) {
				memcpy(pItem->puColumns, m_aryItem[nIndex].puColumns, min(pItem->cColumns,m_aryItem[nIndex].cColumns)*sizeof(UINT));
			}
#endif
#if _WIN32_WINNT >= 0x0600 // Will be unused downlevel, but sizeof(LVITEMA) must be equal to sizeof(LVITEMW)
			if (pItem->mask & LVIF_COLFMT) {
				memcpy(pItem->piColFmt, m_aryItem[nIndex].piColFmt, min(pItem->cColumns,m_aryItem[nIndex].cColumns)*sizeof(int));
			}
			if (pItem->mask & LVIF_GROUPID) {
				pItem->iGroup = m_aryItem[nIndex].iGroup; // readonly. only valid for owner data.
			}
#endif*/
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnGetNextItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		int flags = lParam;
		if (LVNI_ABOVE & flags) {
			nIndex--;
			if (nIndex>=0) {
				int stateflags = LVNI_STATEMASK & flags;
				if (stateflags) {
					for (; nIndex>=0; nIndex--)
					{
						if(m_aryItem[nIndex].state & stateflags) {
							break;
						}
					}
				}
				return nIndex;
			}
		} else {
			nIndex++;
			if (nIndex<m_aryItem.size()) {
				int stateflags = LVNI_STATEMASK & flags;
				if (stateflags) {
					for (; nIndex<m_aryItem.size(); nIndex++)
					{
						if(m_aryItem[nIndex].state & stateflags) {
							break;
						}
					}
				}
				return nIndex;
			}
		}

		return -1;
	}

	LRESULT OnSetItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = 0;
		LVITEM* pItem = (LVITEM*)lParam; 
		ASSERT(pItem);
		nIndex = pItem->iItem;
		if (nIndex>=0 && nIndex<m_aryItem.size()) {
			if (pItem->mask & LVIF_STATE) {
				m_aryItem[nIndex].state = pItem->state;
				m_aryItem[nIndex].stateMask = pItem->stateMask;
			}
			if (pItem->mask & LVIF_TEXT) {
				m_aryText[nIndex][pItem->iSubItem] = pItem->pszText;
			}
			if (pItem->mask & LVIF_IMAGE) {
				m_aryItem[nIndex].iImage = pItem->iImage;
			}
			if (pItem->mask & LVIF_PARAM) {
				m_aryItem[nIndex].lParam = pItem->lParam;
			}
#if (_WIN32_IE >= 0x0300)
			if (pItem->mask & LVIF_INDENT) {
				m_aryItem[nIndex].iIndent = pItem->iIndent;
			}
#endif
			if (pItem->mask & LVIF_DI_SETITEM) {
				m_aryItem[nIndex].mask |= LVIF_DI_SETITEM;
			}
			return TRUE;
		}
		return bHandled;
	}

	LRESULT OnGetItemState(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		LVITEM* pItem = (LVITEM*)lParam;
		ASSERT(pItem);
		if (nIndex<0 || nIndex>=m_aryItem.size()) {
			nIndex = pItem->iItem;
		}
		if (nIndex>0 && nIndex<m_aryItem.size()) {
			UINT state = 0;
			return m_aryItem[nIndex].state;
		}
		return 0;
	}

	LRESULT OnSetItemState(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		LVITEM* pItem = (LVITEM*)lParam;
		ASSERT(pItem);
		if (nIndex<0 || nIndex>=m_aryItem.size()) {
			nIndex = pItem->iItem;
		}
		if (nIndex>0 && nIndex<m_aryItem.size()) {
			m_aryItem[nIndex].state = pItem->state;
		}
		return 0;
	}
		
	LRESULT OnGetItemText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		int nSubItem = 0;
		LVITEM* pItem = (LVITEM*)lParam;
		ASSERT(pItem);
		if (nIndex<0 || nIndex>=m_aryItem.size()) {
			nIndex = pItem->iItem;
		}
		nSubItem = pItem->iSubItem;
		if (nIndex>0 && nIndex<m_aryItem.size()) {
			int nTextLen = min(m_aryText[nIndex][pItem->iSubItem].GetLength(), pItem->cchTextMax);
			_tcsncpy(pItem->pszText, (LPCTSTR)m_aryText[nIndex][pItem->iSubItem], nTextLen);
			return nTextLen;
		}
		return 0;
	}

	LRESULT OnGetCallbackMask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_uCallbackMask;
	}

	LRESULT OnSetCallbackMask(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		UINT uOldCallbackMask = m_uCallbackMask;
		m_uCallbackMask = wParam;
		return uOldCallbackMask;
	}

	LRESULT OnGetItemPosition(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetItemPosition(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetStringWidth(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetEditControl(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return (LRESULT)(HWND)m_wndEdit;
	}

	LRESULT OnGetColumn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCol = wParam;
		LVCOLUMN* pCol = (LVCOLUMN*)lParam;
		ASSERT(pCol);
		if (nCol>=0 && nCol<m_aryColumn.size()) {
			if(pCol->mask & LVCF_WIDTH) {
				pCol->cx = m_aryColumn[nCol].cx;
			}
			if(pCol->mask & LVCF_TEXT) {
				int nTextLen = min(m_aryColumnText[nCol].GetLength(),pCol->cchTextMax);
				_tcsncpy(pCol->pszText, (LPCTSTR)m_aryColumnText[nCol], nTextLen);
			}
			if(pCol->mask & LVCF_FMT) {
				pCol->fmt = m_aryColumn[nCol].fmt;
			}
			if(pCol->mask & LVCF_SUBITEM) {
				pCol->iSubItem = m_aryColumn[nCol].iSubItem;
			}
#if (_WIN32_IE >= 0x0300)
			if(pCol->mask & LVCF_IMAGE) {
				pCol->iImage = m_aryColumn[nCol].iImage;
			}
			if(pCol->mask & LVCF_ORDER) {
				pCol->iOrder = m_aryColumn[nCol].iOrder;
			}
#endif
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnSetColumn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCol = wParam;
		LVCOLUMN* pCol = (LVCOLUMN*)lParam;
		ASSERT(pCol);
		HDITEM hdItem = {0};
		if(pCol->mask & LVCF_WIDTH) {
			m_aryColumn[nCol].cx = pCol->cx;
			hdItem.mask |= HDI_WIDTH;
			hdItem.cxy = pCol->cx;
		}
		if(pCol->mask & LVCF_TEXT) {
			m_aryColumnText[nCol] = pCol->pszText;
			hdItem.mask |= HDI_TEXT;
			hdItem.pszText = pCol->pszText;
			//IMAGEINFO imageinfo;
			//ImageList_GetImageInfo(m_hImageList, pCol->iImage, &imageinfo);
			//hdItem.hbm = imageinfo.hbmImage;
			hdItem.cchTextMax = pCol->cchTextMax;
		}
		if(pCol->mask & LVCF_FMT) {
			m_aryColumn[nCol].fmt = pCol->fmt;
			hdItem.mask |= HDI_FORMAT;
			hdItem.fmt = pCol->fmt;
		}
		if(pCol->mask & LVCF_SUBITEM) {
			m_aryColumn[nCol].iSubItem = pCol->iSubItem;
			hdItem.mask |= HDI_LPARAM;
			hdItem.lParam = pCol->iSubItem;
		}
#if (_WIN32_IE >= 0x0300)
		if(pCol->mask & LVCF_IMAGE) {
			m_aryColumn[nCol].iImage = pCol->iImage;
			hdItem.mask |= HDI_IMAGE;
			hdItem.iImage = pCol->iImage;         // index of bitmap in ImageList
		}
		if(pCol->mask & LVCF_ORDER) {
			m_aryColumn[nCol].iOrder = pCol->iOrder;
			hdItem.mask |= HDI_ORDER;
			hdItem.iOrder = pCol->iOrder;
		}
#endif
		if (m_wndHeader) {
			m_wndHeader.SetItem(nCol, &hdItem);
		}
		return TRUE;
		return FALSE;
	}

	LRESULT OnGetColumnWidth(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCol = wParam;
		if (nCol>=0 && nCol<m_aryColumn.size()) {
			return m_aryColumn[nCol].cx;
		}
		return 0;
	}

	LRESULT OnSetColumnWidth(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCol = wParam;
		int nWidth = lParam;
		if (nCol>=0 && nCol<m_aryColumn.size()) {
			m_aryColumn[nCol].cx = nWidth;
			HDITEM hdItem = {0};
			hdItem.mask = HDI_WIDTH;
			hdItem.cxy = nWidth;
			if (m_wndHeader) {
				m_wndHeader.SetItem(nCol, &hdItem);
			}
			return TRUE;
		}
		return 0;
	}
		
	LRESULT OnGetViewRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetTextColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_crText;
	}
	
	LRESULT OnSetTextColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_crText = (COLORREF)lParam;
		return TRUE;
	}

	LRESULT OnGetTextBkColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_crTextBackgnd;
	}

	LRESULT OnSetTextBkColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_crTextBackgnd = (COLORREF)lParam;
		return TRUE;
	}
	
	LRESULT OnGetTopIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_nTopIndex;
	}

	LRESULT OnGetCountPerPage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_nCountPerPage;
	}

	LRESULT OnGetOrigin(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetSelectedCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int i,j;
		for (i=0,j=0; i<m_aryItem.size(); i++)
		{
			if (m_aryItem[i].state & LVIS_SELECTED) {
				j++;
			}
		}
		return j;
	}

	LRESULT OnGetItemRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		LPRECT lpRect = (LPRECT)lParam;
		int nCode = lpRect->left;

		RECT rcClient;
		pT->GetClientRect(&rcClient);

		SCROLLINFO HSCInfo;
		pT->GetScrollInfo(SB_HORZ, &HSCInfo);

		SCROLLINFO VSCInfo;
		pT->GetScrollInfo(SB_HORZ, &VSCInfo);

		//*lpRect = rcClient;
		lpRect->left = rcClient.left;
		lpRect->right = rcClient.right;
		lpRect->top = (nIndex-m_nTopIndex)*m_xyItem.cy;
		lpRect->bottom = lpRect->top + m_xyItem.cy;

		return TRUE;
	}
#ifndef _WIN32_WCE
	LRESULT OnGetHotCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return (LRESULT)m_hHotCursor;
	}

	LRESULT OnSetHotCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		HCURSOR hOldCursor = m_hHotCursor;
		m_hHotCursor = (HCURSOR)lParam;
		return (LRESULT)hOldCursor;
	}

	LRESULT OnGetHotItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_nHotItem;
	}

	LRESULT OnSetHotItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nOldHotItem = m_nHotItem;
		m_nHotItem = wParam;
		return nOldHotItem;
	}
#endif // !_WIN32_WCE

	LRESULT OnGetColumnOrderArray(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_wndHeader.GetOrderArray((int)wParam, (LPINT)lParam);
		return bHandled;
	}

	LRESULT OnSetColumnOrderArray(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return m_wndHeader.SetOrderArray((int)wParam, (LPINT)lParam);
		return bHandled;
	}

	LRESULT OnGetHeader(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return (LRESULT)(HWND)m_wndHeader;
	}

	LRESULT OnGetSubItemRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int i;
		int nIndex = wParam;
		LPRECT lpRect = (LPRECT)lParam;
		int nSubItem = lpRect->top;
		int nCode = lpRect->left;
		pT->GetItemRect(nIndex, lpRect, LVIR_BOUNDS);
		for (i=0; i<nSubItem; i++)
		{
			int nWidth = pT->GetColumnWidth(i);
			::OffsetRect(lpRect, nWidth, 0);
		}
		lpRect->right = lpRect->left + pT->GetColumnWidth(i);
		return TRUE;
	}

	LRESULT OnSetIconSpacing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return FALSE;
	}

	LRESULT OnGetISearchString(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetItemSpacing(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		BOOL bSmallIconView = wParam;
		return MAKELPARAM(m_szItemSpacing.cx,m_szItemSpacing.cy);
	}
	
#if (_WIN32_WCE >= 410)
		//ListView_SetItemSpacing(m_hWnd, cySpacing);
#endif // (_WIN32_WCE >= 410)
	LRESULT OnGetExtendedListViewStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetExtendedListViewStyle(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
		
#if (_WIN32_IE >= 0x0400)
#ifndef _WIN32_WCE
	LRESULT OnGetBkImage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetBkImage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // !_WIN32_WCE
	LRESULT OnGetSelectionMark(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetSelectionMark(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#ifndef _WIN32_WCE
	LRESULT OnGetWorkAreas(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetWorkAreas(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetHoverTime(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetHoverTime(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetNumberOfWorkAreas(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // !_WIN32_WCE

#ifndef _WIN32_WCE
	LRESULT OnGetToolTips(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return (LRESULT)(HWND)m_wndToolTip;
	}

	LRESULT OnSetToolTips(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		UIToolTipCtrl wndOldToopTip = m_wndToolTip;
		m_wndToolTip = (HWND)lParam;
		return (LRESULT)(HWND)wndOldToopTip;
	}

	LRESULT OnGetUnicodeFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetUnicodeFormat(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // !_WIN32_WCE
#endif // (_WIN32_IE >= 0x0400)
#if (_WIN32_WINNT >= 0x0501)
	LRESULT OnGetSelectedColumn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		/*int i,j;
		for (i=0,j=0; i<m_aryColumn.size(); i++)
		{
			if (m_aryColumn[i].cchTextMax)
			{
			}
		}*/
		return 0;
	}

	LRESULT OnSetSelectedColumn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetView(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetView(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnIsGroupViewEnabled(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetGroupInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetGroupInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetGroupMetrics(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetGroupMetrics(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetTileViewInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetTileViewInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetTileInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetTileInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetInsertMark(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
	
	LRESULT OnSetInsertMark(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetInsertMarkRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetInsertMarkColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetInsertMarkColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetOutlineColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetOutlineColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // (_WIN32_WINNT >= 0x0501)
#if (_WIN32_WINNT >= 0x0600)
	LRESULT OnGetGroupCount(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetGroupInfoByIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetGroupRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetGroupState(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetFocusedGroup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetEmptyText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetFooterRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetFooterInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetFooterItemRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetFooterItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetItemIndexRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetItemIndexState(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnGetNextItemIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // (_WIN32_WINNT >= 0x0600)
	LRESULT OnInsertColumn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCol = wParam;
		LVCOLUMN* pCol = (LVCOLUMN*)lParam;
		ASSERT(pCol);
		if (nCol<0) {
			nCol = m_aryColumn.size();
			m_aryColumn.push_back(*pCol);
			return nCol;
		} else {
			if (nCol>=0 && nCol<m_aryColumn.size()) {
				m_aryColumn.insert(m_aryColumn.begin()+nCol, *pCol);
				return nCol;
			}
		}
		return -1;
	}

	LRESULT OnDeleteColumn(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nCol = wParam;
		if (nCol>=0 && nCol<m_aryColumn.size()) {
			m_aryColumn.erase(m_aryColumn.begin()+nCol);
			return nCol;
		}
		return bHandled;
	}

	LRESULT OnInsertItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		LVITEM* pItem = (LVITEM*)lParam;
		ASSERT(pItem);
		if (nIndex<0) {
			nIndex = m_aryItem.size();
			m_aryItem.push_back(*pItem);
			return nIndex;
		} else {
			if (nIndex>=0 && nIndex<m_aryItem.size()) {
				m_aryItem.insert(m_aryItem.begin()+nIndex, *pItem);
				return nIndex;
			}
		}
		return bHandled;
	}

	LRESULT OnDeleteItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		int nIndex = wParam;
		if (nIndex>=0 && nIndex<m_aryItem.size()) {
			m_aryItem.erase(m_aryItem.begin()+nIndex);
			return TRUE;
		}
		return FALSE;
	}

	LRESULT OnDeleteAllItems(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_aryItem.clear();
		m_nHotItem = -1;
		return bHandled;
	}

	LRESULT OnFindItem(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnEnsureVisible(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnScroll(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnRedrawItems(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnArrange(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnEditLabel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnUpdate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSortItems(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnCreateDragImage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnApproximateViewRect(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSubItemHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#if (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
	LRESULT OnSortItemsEx(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // (_WIN32_IE >= 0x0500) && !defined(_WIN32_WCE)
#if (_WIN32_WINNT >= 0x0501)
	LRESULT OnInsertGroup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnRemoveGroup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnMoveGroup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnMoveItemToGroup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnEnableGroupView(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSortGroups(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnInsertGroupSorted(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnRemoveAllGroups(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnHasGroup(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnInsertMarkHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnSetInfoTip(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnCancelEditLabel(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnMapIndexToID(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}

	LRESULT OnMapIDToIndex(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		return bHandled;
	}
#endif // (_WIN32_WINNT >= 0x0501)
};
	
template<class T>
class UIRichText2Map
{
	typedef UIRichText2Map<T> This;
protected:
    BOOL m_bParsed;
	enum
	{
		ELEMENT_TYPE_UNKNOWN = 0,
		ELEMENT_TYPE_TEXT,
		ELEMENT_TYPE_HYPELINK,
		ELEMENT_TYPE_IMAGE,
	};
	class _ElementInfo
	{
	public:
		UINT		type;
		CString		strText;
		RECT		rc;
        UINT		uCmdID;
	};
	class _TextInfo : public _ElementInfo
    {
    public:
		BOOL		bBold;
		BOOL		bItalic;
		BOOL		bUnderLine;
		COLORREF	crText;
    };
	class _LinkInfo : public _TextInfo
    {
	public:
		CString		strHref;
	};
	class _ImageInfo : public _ElementInfo
    {
	public:
		Image*		pImage;
	};
	typedef std::vector<_ElementInfo*> ElementArray;
	ElementArray m_Elements;
    _ElementInfo* m_pHoverElement;
    _ElementInfo* m_pClickElement;
    
public:
	UIRichText2Map()
	{
		m_bParsed = FALSE;
		m_pHoverElement = NULL;
		m_pClickElement = NULL;
	}

protected:
	void Clear()
	{
		ElementArray::iterator it = m_Elements.begin();
		for (; it != m_Elements.end(); ++it)
		{
			delete *it;
		}
		m_Elements.clear();
		m_pHoverElement = NULL;
		m_pClickElement = NULL;
		m_bParsed = FALSE;
	}
	
	void Parse(LPCTSTR lpszText)
	{
	}

public:
	BEGIN_MSG_MAP(This)
		MESSAGE_HANDLER(WM_SETTEXT, OnSetText)
		MESSAGE_HANDLER(WM_LBUTTONDOWN, OnLButtonDown)
		MESSAGE_HANDLER(WM_LBUTTONUP, OnLButtonUp)
		MESSAGE_HANDLER(WM_MOUSEMOVE, OnMouseMove)
		MESSAGE_HANDLER(WM_MOUSELEAVE, OnMouseLeave)
		MESSAGE_HANDLER(WM_SETCURSOR, OnSetCursor)
	END_MSG_MAP()

	LRESULT OnSetText(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		bHandled = FALSE;
		pT->Clear();
		pT->Invalidate();
		return bHandled;
	}

	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_pClickElement = m_pHoverElement;
		return bHandled;
	}

	LRESULT OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		if (m_pClickElement == m_pHoverElement) {
			//
		}
		return bHandled;
	}

	LRESULT OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		POINT pt;
		POINTSTOPOINT(pt, lParam);
		ElementArray::iterator it = m_Elements.begin();
		for (; it != m_Elements.end(); ++it)
		{
			_ElementInfo* & pElement = (*it);
			if (::PtInRect(&pElement->rc, pt)) {
				m_pHoverElement = pElement;
			}
		}
		return bHandled;
	}

	LRESULT OnMouseLeave(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		T* pT = static_cast<T*>(this);
		m_pHoverElement = NULL;
		return bHandled;
	}

	LRESULT OnSetCursor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		if(m_pHoverElement) {
			switch(m_pHoverElement->type)
			{
			case ELEMENT_TYPE_HYPELINK:
				SetCursor(::LoadCursor(NULL, IDC_HAND));
				break;
			default:
				bHandled = FALSE;
				break;
			}
		}
		return bHandled;
	}
};
	
#endif//_H_UICMMCTRL2_H_